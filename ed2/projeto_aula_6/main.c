#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_ACRONYM 4
#define MAX_NAME 50
#define MAX_INDEX 100
#define MAX_RECORD_SIZE 256
#define LAST_ACCESS_FILE "last_access.bin"
#define PRIMARY_INDEX_FILE "indice.bin"
#define SECONDARY_INDEX_FILE "sec_indice.bin"
#define DATA_FILE "arq.bin"
#define INSERT_FILE "insere.bin"
#define SEARCH_PRIMARY_FILE "busca_p.bin"
#define SEARCH_SECONDARY_FILE "busca_s.bin"

typedef struct {
    char id_aluno[4]; // ID do aluno (3 caracteres + terminador)
    char sigla_disc[4]; // Sigla da disciplina (3 caracteres + terminador)
    char nome_aluno[50]; // Nome do aluno
    char nome_disc[50]; // Nome da disciplina
    float media; // Média
    float freq; // Frequência
} hist;

typedef struct {
    char key[8]; // ID + Sigla (sem espaço)
    long offset; // Deslocamento no arquivo
} indexEntry;

typedef struct {
    char nome_aluno[MAX_NAME]; // Nome do aluno
    long offset;
    long firstOffset; // Primeiro offset na lista ligada
} secondaryIndexEntry;

typedef struct {
    char key[8]; // Chave
    long offset;
    long nextOffset; // Próximo deslocamento na lista ligada
} secondaryLinkedListEntry;

hist *insertRecords = NULL;
indexEntry primaryIndex[MAX_INDEX];
secondaryIndexEntry secondaryIndex[MAX_INDEX];
int numPrimaryIndexEntries = 0;
int numSecondaryIndexEntries = 0;

void insert();
void searchByKey();
void searchByStudentName();
void loadFiles();
void createPrimaryIndex();
void createSecondaryIndex();
void loadPrimaryIndex();
void loadSecondaryIndex();
void savePrimaryIndex();
void saveSecondaryIndex();
void handleError(const char *message);
int readLastAccess();
void writeLastAccess(int index);
void freeResources();
void printRecord(hist *record);
int fileExists(const char *filename);

int main() {
    setlocale(LC_ALL, "");

    loadPrimaryIndex(); // Carregar índice primário
    if (numPrimaryIndexEntries == 0) {
        createPrimaryIndex(); // Criar índice se não houver entradas
    }

    loadSecondaryIndex(); // Carregar índice secundário
    if (numSecondaryIndexEntries == 0) {
        createSecondaryIndex(); // Criar índice se não houver entradas
    }

    int option;
    do {
        printf("Escolha uma opcao:\n");
        printf("1. Insercao\n");
        printf("2. Pesquisa por chave primaria\n");
        printf("3. Pesquisa por nome do aluno\n");
        printf("4. Carregar Arquivos\n");
        printf("0. Sair\n");

        scanf("%d", &option);
        getchar(); // Limpa o buffer

        switch (option) {
            case 1:
                insert();
                break;
            case 2:
                searchByKey();
                break;
            case 3:
                searchByStudentName();
                break;
            case 4:
                loadFiles();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (option != 0);

    freeResources();
    return 0;
}

void insert() {
    FILE *file = fopen(DATA_FILE, "a+b");
    if (!file) {
        handleError("Erro ao abrir o arquivo de dados.");
        return;
    }

    FILE *insertFile = fopen(INSERT_FILE, "rb");
    if (!insertFile) {
        handleError("Erro ao abrir o arquivo de inserÃ§Ã£o.");
        fclose(file);
        return;
    }

    int lastAccess = readLastAccess();
    fseek(insertFile, lastAccess * sizeof(hist), SEEK_SET);

    int numRecords;
    printf("Quantos registros vocÃª deseja inserir? ");
    scanf("%d", &numRecords);
    getchar();

    for (int i = 0; i < numRecords; ++i) {
        hist newRecord;
        memset(&newRecord, 0, sizeof(hist));

        if (fread(&newRecord, sizeof(hist), 1, insertFile) != 1) {
            printf("NÃ£o hÃ¡ mais registros para ler no arquivo de inserÃ§Ã£o.\n");
            break;
        }

        // Formatar registro
        char record[MAX_RECORD_SIZE];
        int recordLength = snprintf(record, sizeof(record), "%s#%s#%s#%s#%.2f#%.2f",
                                    newRecord.id_aluno, newRecord.sigla_disc,
                                    newRecord.nome_aluno, newRecord.nome_disc,
                                    newRecord.media, newRecord.freq);

        // Escrever tamanho e registro no arquivo
        
        fwrite(&recordLength, sizeof(int), 1, file);
        long offset = ftell(file);
        fwrite(record, sizeof(char), recordLength, file);

        // Adicionar entrada ao Ã­ndice primÃ¡rio
        if (numPrimaryIndexEntries < MAX_INDEX) {
            snprintf(primaryIndex[numPrimaryIndexEntries].key, sizeof(primaryIndex[numPrimaryIndexEntries].key),
                     "%s%s", newRecord.id_aluno, newRecord.sigla_disc);
            primaryIndex[numPrimaryIndexEntries].offset = offset;
            numPrimaryIndexEntries++;
        }

        // Adicionar entrada ao Ã­ndice secundÃ¡rio
        if (numSecondaryIndexEntries < MAX_INDEX) {
            int found = 0;
            for (int j = 0; j < numSecondaryIndexEntries; j++) {
                if (strcmp(secondaryIndex[j].nome_aluno, newRecord.nome_aluno) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                snprintf(secondaryIndex[numSecondaryIndexEntries].nome_aluno, sizeof(secondaryIndex[numSecondaryIndexEntries].nome_aluno), "%s", newRecord.nome_aluno);
                secondaryIndex[numSecondaryIndexEntries].offset = offset; 
                numSecondaryIndexEntries++;
            }
        }
    }

    lastAccess += numRecords;
    writeLastAccess(lastAccess);

    // Salvar Ã­ndices apÃ³s inserÃ§Ã£o
    savePrimaryIndex();
    saveSecondaryIndex();

    fclose(file);
    fclose(insertFile);
}

void searchByKey() {
    int numKeys;

    // Pergunta ao usuário quantas chaves serão buscadas
    printf("Informe a quantidade de chaves a serem buscadas: ");
    scanf("%d", &numKeys);
    getchar(); // Limpa o buffer

    // Abre o arquivo de busca
    FILE *searchFile = fopen(SEARCH_PRIMARY_FILE, "rb");
    if (!searchFile) {
        handleError("Erro ao abrir o arquivo de busca primária.");
        return;
    }

    // Chave para armazenar a combinação ID + Sigla
    char key[8];  // Para armazenar a chave (ID + Sigla)

    // Lê as chaves do arquivo de busca_p.bin
    for (int i = 0; i < numKeys; i++) {
        // Aqui, você deve ler tanto o ID quanto a Sigla do arquivo
        char id[4];  // ID de 3 caracteres + terminador
        char sigla[4]; // Sigla de 3 caracteres + terminador
        
        fread(id, sizeof(char), sizeof(id), searchFile); // Lê o ID
        id[3] = '\0'; // Garantir que o ID é uma string válida

        fread(sigla, sizeof(char), sizeof(sigla), searchFile); // Lê a sigla
        sigla[3] = '\0'; // Garantir que a sigla é uma string válida

        // Concatena o ID e a sigla
        snprintf(key, sizeof(key), "%s%s", id, sigla);

        // Verifica se a chave existe no índice primário
        int found = 0;
        for (int j = 0; j < numPrimaryIndexEntries; j++) {
            if (strcmp(primaryIndex[j].key, key) == 0) {
                found = 1;

                // Abre o arquivo de dados para buscar o registro
                FILE *file = fopen(DATA_FILE, "rb");
                if (!file) {
                    handleError("Erro ao abrir o arquivo de dados.");
                    return;
                }

                // Move para o deslocamento do registro
                fseek(file, primaryIndex[j].offset, SEEK_SET);
                int recordLength;
                fread(&recordLength, sizeof(int), 1, file);
                char record[MAX_RECORD_SIZE];
                fread(record, sizeof(char), recordLength, file);

                // Prepara a estrutura do registro encontrado
                hist foundRecord;
                sscanf(record, "%[^#]#%[^#]#%[^#]#%[^#]#%f#%f",
       foundRecord.id_aluno,       // Primeiro campo (ID Aluno)
       foundRecord.sigla_disc,     // Segundo campo (Sigla Disciplina)
       foundRecord.nome_aluno,     // Terceiro campo (Nome Aluno)
       foundRecord.nome_disc,      // Quarto campo (Nome Disciplina)
       &foundRecord.media,         // Quinto campo (Média)
       &foundRecord.freq);         // Sexto campo (Frequência)

// Imprimir os valores capturados
printf("ID Aluno: %s\n", foundRecord.id_aluno);
printf("Sigla Disciplina: %s\n", foundRecord.sigla_disc);
printf("Nome Aluno: %s\n", foundRecord.nome_aluno);
printf("Nome Disciplina: %s\n", foundRecord.nome_disc);
printf("Média: %.2f\n", foundRecord.media);
printf("Frequência: %.2f\n", foundRecord.freq);

fclose(file);
break;
            }
        }

        if (!found) {
            printf("Chave '%s' não encontrada no índice primário.\n", key);
        }
    }

    fclose(searchFile);
}



void searchByStudentName() {
    int numNames;
    printf("Quantos nomes você deseja pesquisar? ");
    scanf("%d", &numNames);
    getchar(); // Limpa o buffer do stdin

    FILE *searchFile = fopen(SEARCH_SECONDARY_FILE, "rb");
    if (!searchFile) {
        handleError("Erro ao abrir o arquivo de busca secundária.");
        return;
    }

    // Lê os nomes do arquivo de busca_s.bin
    for (int i = 0; i < numNames; i++) {
        char name[MAX_NAME];
        // Lê o nome do arquivo
        if (fgets(name, sizeof(name), searchFile) == NULL) {
            printf("Erro ao ler o nome do arquivo de busca secundária.\n");
            break;
        }
        name[strcspn(name, "\n")] = 0; // Remove o newline

        // Verifica se o nome existe no índice secundário
        for (int j = 0; j < numSecondaryIndexEntries; j++) {
            if (strcmp(secondaryIndex[j].nome_aluno, name) == 0) {
                // Abre o arquivo de dados para buscar os registros
                FILE *file = fopen(DATA_FILE, "rb");
                if (!file) {
                    handleError("Erro ao abrir o arquivo de dados.");
                    return;
                }

                long currentOffset = secondaryIndex[j].firstOffset;
                while (currentOffset != -1) {
                    fseek(file, currentOffset, SEEK_SET);
                    secondaryLinkedListEntry linkedEntry;
                    fread(&linkedEntry, sizeof(secondaryLinkedListEntry), 1, file);

                    // A chave primária é lida do campo key da estrutura
                    char primaryKey[8];
                    snprintf(primaryKey, sizeof(primaryKey), "%s", linkedEntry.key); // Aqui assumimos que linkedEntry.key é um array de char

                    // Move para o deslocamento do registro correspondente
                    fseek(file, linkedEntry.offset, SEEK_SET); // Assumindo que offset faz parte do linkedEntry
                    int recordLength;
                    fread(&recordLength, sizeof(int), 1, file);
                    char record[MAX_RECORD_SIZE];
                    fread(record, sizeof(char), recordLength, file);

                    // Prepara a estrutura do registro encontrado
                    hist foundRecord;
                    sscanf(record, "%[^#]#%[^#]#%[^#]#%[^#]#%f#%f",
                           foundRecord.id_aluno, foundRecord.sigla_disc,
                           foundRecord.nome_aluno, foundRecord.nome_disc,
                           &foundRecord.media, &foundRecord.freq);

                    printRecord(&foundRecord);

                    // Lê o próximo offset da lista ligada
                    currentOffset = linkedEntry.nextOffset;
                }

                fclose(file);
                break;
            }
        }
    }

    fclose(searchFile);
}
void loadFiles() {

    /*loadPrimaryIndex();
    loadSecondaryIndex();*/
   
   
    printf("Tentando abrir o arquivo de dados: %s\n", DATA_FILE);
    FILE *file = fopen(DATA_FILE, "rb");
    if (!file) {
        printf("Arquivo não encontrado. Criando um novo...\n");
        file = fopen(DATA_FILE, "wb");
        if (!file) {
            handleError("Erro ao criar o arquivo de dados.");
            return;
        }
        printf("Arquivo criado com sucesso: %s\n", DATA_FILE);
        fclose(file); // Fecha o arquivo após criá-lo
        return; // Retorna, pois não há dados a carregar
    }

    // Continuar carregando dados se o arquivo foi encontrado
    while (1) {
        int recordLength;
        if (fread(&recordLength, sizeof(int), 1, file) != 1) {
            break; // Fim do arquivo
        }

        char record[MAX_RECORD_SIZE];
        fread(record, sizeof(char), recordLength, file);
        hist newRecord;
        sscanf(record, "%[^#]#%[^#]#%[^#]#%[^#]#%f#%f",
               newRecord.id_aluno, newRecord.sigla_disc,
               newRecord.nome_aluno, newRecord.nome_disc,
               &newRecord.media, &newRecord.freq);
        printRecord(&newRecord);
    }
    fclose(file);
}


void createPrimaryIndex() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (!file) {
        printf("Arquivo de dados não encontrado. Criando um novo...\n");
        file = fopen(DATA_FILE, "wb");
        if (!file) {
            handleError("Erro ao criar o arquivo de dados.");
            return;
        }
        fclose(file); // Fecha o arquivo após criá-lo
        return; // Retorna, pois não há dados para criar o índice
    }

    // Limpa o índice primário antes de preenchê-lo
    numPrimaryIndexEntries = 0;

    while (1) {
        int recordLength;
        if (fread(&recordLength, sizeof(int), 1, file) != 1) {
            break; // Fim do arquivo
        }

        char record[MAX_RECORD_SIZE];
        fread(record, sizeof(char), recordLength, file);
        hist newRecord;
        sscanf(record, "%[^#]#%[^#]#%[^#]#%[^#]#%f#%f",
               newRecord.id_aluno, newRecord.sigla_disc,
               newRecord.nome_aluno, newRecord.nome_disc,
               &newRecord.media, &newRecord.freq);

        // Adicionar entrada ao índice primário
        if (numPrimaryIndexEntries < MAX_INDEX) {
            snprintf(primaryIndex[numPrimaryIndexEntries].key, sizeof(primaryIndex[numPrimaryIndexEntries].key),
                     "%s%s", newRecord.id_aluno, newRecord.sigla_disc);
            primaryIndex[numPrimaryIndexEntries].offset = ftell(file) - (sizeof(int) + recordLength); // Offset correto
            numPrimaryIndexEntries++;
        }
    }

    fclose(file);
    savePrimaryIndex();
}


void createSecondaryIndex() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (!file) {
        printf("Arquivo de dados não encontrado. Criando um novo...\n");
        file = fopen(DATA_FILE, "wb");
        if (!file) {
            handleError("Erro ao criar o arquivo de dados.");
            return;
        }
        fclose(file); // Fecha o arquivo após criá-lo
        return; // Retorna, pois não há dados para criar o índice
    }

    // Limpa o índice secundário antes de preenchê-lo
    numSecondaryIndexEntries = 0;
    FILE *linkedListFile = fopen(SECONDARY_INDEX_FILE, "wb");
    if (!linkedListFile) {
        handleError("Erro ao abrir o arquivo da lista ligada do índice secundário.");
        fclose(file);
        return;
    }

    while (1) {
        int recordLength;
        if (fread(&recordLength, sizeof(int), 1, file) != 1) {
            break; // Fim do arquivo
        }

        char record[MAX_RECORD_SIZE];
        fread(record, sizeof(char), recordLength, file);
        hist newRecord;
        sscanf(record, "%[^#]#%[^#]#%[^#]#%[^#]#%f#%f",
               newRecord.id_aluno, newRecord.sigla_disc,
               newRecord.nome_aluno, newRecord.nome_disc,
               &newRecord.media, &newRecord.freq);

        // Adicionar entrada ao índice secundário
        int found = -1;
        for (int i = 0; i < numSecondaryIndexEntries; i++) {
            if (strcmp(secondaryIndex[i].nome_aluno, newRecord.nome_aluno) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            // Novo nome de aluno
            snprintf(secondaryIndex[numSecondaryIndexEntries].nome_aluno, sizeof(secondaryIndex[numSecondaryIndexEntries].nome_aluno), "%s", newRecord.nome_aluno);
            secondaryIndex[numSecondaryIndexEntries].firstOffset = ftell(linkedListFile); // Define o offset inicial da lista
            numSecondaryIndexEntries++;

            // Escrever entrada inicial na lista ligada
            secondaryLinkedListEntry newEntry;
            snprintf(newEntry.key, sizeof(newEntry.key), "%s%s", newRecord.id_aluno, newRecord.sigla_disc);
            newEntry.offset = ftell(file) - (sizeof(int) + recordLength); // Ajuste o offset para o registro
            newEntry.nextOffset = -1; // Termina a lista

            fwrite(&newEntry, sizeof(secondaryLinkedListEntry), 1, linkedListFile);
        } else {
            // Adicionar à lista ligada existente
            long currentOffset = secondaryIndex[found].firstOffset;
            secondaryLinkedListEntry newEntry;
            snprintf(newEntry.key, sizeof(newEntry.key), "%s%s", newRecord.id_aluno, newRecord.sigla_disc);
            newEntry.offset = ftell(file) - (sizeof(int) + recordLength); // Ajuste o offset para o registro
            newEntry.nextOffset = -1; // Termina a lista

            // Encontrar o final da lista ligada
            while (currentOffset != -1) {
                fseek(linkedListFile, currentOffset, SEEK_SET);
                secondaryLinkedListEntry existingEntry;
                fread(&existingEntry, sizeof(secondaryLinkedListEntry), 1, linkedListFile);

                if (existingEntry.nextOffset == -1) {
                    existingEntry.nextOffset = ftell(linkedListFile); // Atualiza o deslocamento para o novo registro
                    fseek(linkedListFile, currentOffset, SEEK_SET); // Volta para o início da entrada existente
                    fwrite(&existingEntry, sizeof(secondaryLinkedListEntry), 1, linkedListFile); // Atualiza a entrada existente
                    break;
                }
                currentOffset = existingEntry.nextOffset; // Avança na lista
            }

            // Escrever o novo registro na lista ligada
            fwrite(&newEntry, sizeof(secondaryLinkedListEntry), 1, linkedListFile);
        }
    }

    fclose(file);
    fclose(linkedListFile);
    saveSecondaryIndex();
}


void loadPrimaryIndex() {
    FILE *file = fopen(PRIMARY_INDEX_FILE, "rb");
    if (file) {
        fread(&numPrimaryIndexEntries, sizeof(int), 1, file);
        fread(primaryIndex, sizeof(indexEntry), numPrimaryIndexEntries, file);
        fclose(file);
    }
}

void loadSecondaryIndex() {
    FILE *file = fopen(SECONDARY_INDEX_FILE, "rb");
    if (file) {
        fread(&numSecondaryIndexEntries, sizeof(int), 1, file);
        fread(secondaryIndex, sizeof(secondaryIndexEntry), numSecondaryIndexEntries, file);
        fclose(file);
    }
}

void savePrimaryIndex() {
    FILE *file = fopen(PRIMARY_INDEX_FILE, "wb");
    if (file) {
        fwrite(&numPrimaryIndexEntries, sizeof(int), 1, file);
        fwrite(primaryIndex, sizeof(indexEntry), numPrimaryIndexEntries, file);
        fclose(file);
    }
}

void saveSecondaryIndex() {
    FILE *file = fopen(SECONDARY_INDEX_FILE, "wb");
    if (file) {
        fwrite(&numSecondaryIndexEntries, sizeof(int), 1, file);
        fwrite(secondaryIndex, sizeof(secondaryIndexEntry), numSecondaryIndexEntries, file);
        fclose(file);
    }
}

void handleError(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int readLastAccess() {
    FILE *file = fopen(LAST_ACCESS_FILE, "rb");
    if (!file) {
        return 0; // Se o arquivo não existe, começa do zero
    }

    int lastAccess;
    fread(&lastAccess, sizeof(int), 1, file);
    fclose(file);
    return lastAccess;
}

void writeLastAccess(int index) {
    FILE *file = fopen(LAST_ACCESS_FILE, "wb");
    if (file) {
        fwrite(&index, sizeof(int), 1, file);
        fclose(file);
    }
}

void freeResources() {
    free(insertRecords);
}

void printRecord(hist *record) {
    printf("\n");
    printf("ID Aluno: %s\n", record->id_aluno);
    printf("Sigla Disciplina: %s\n", record->sigla_disc);
    printf("Nome Aluno: %s\n", record->nome_aluno);
    printf("Nome Disciplina: %s\n", record->nome_disc);
    printf("Média: %.2f\n", record->media);
    printf("Frequência: %.2f\n", record->freq);
    printf("\n");
}

int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1; // O arquivo existe
    }
    return 0; // O arquivo não existe
}
