/*--------------------------------------------Libs--------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

/*--------------------------------------------Defines--------------------------------------------*/

#define ORDER 4
#define K_MAX (ORDER-1)
#define ID_LENGHT 4 //Lenght + End of String
#define ACR_LENGHT 4 //Lenght + End of String
#define K_LENGHT (ID_LENGHT + ACR_LENGHT - 1)
#define NAME_LENGHT 50 //Lenght + End of String
#define SUBJ_LENGHT 50 //Lenght + End of String
#define ARCHIVE "./archive.bin"
#define INDEX "./index.bin"
#define AUX "./aux.bin"

/*--------------------------------------------Structs--------------------------------------------*/

typedef struct page
{
    short kcount;
    char key[K_MAX][K_LENGHT];
    short ptr[ORDER];
}Page;

typedef struct reg
{
    char* id;
    char* acr;
    char* name;
    char* subj;
    float mean;
    float atte;
}Reg;

typedef struct hist {
    char id_aluno[4];
    char sigla_disc[4];
    char nome_aluno[50];
    char nome_disc[50];
    float media;
    float freq;
}Hist;

typedef struct busca {
    char id_aluno[4];
    char sigla_disc[4];
}Busca;

typedef struct aux
{
    int last_arch;
    int last_search;
}Aux;


/*--------------------------------------------Function Definitions--------------------------------------------*/

void menu();
void init();
bool file_exists(const char*);
void create_file(const char*);
void list_all();
void list_one();

/*--------------------------------------------Main--------------------------------------------*/

int main(){

    init();
    menu();

    return 0;
}

/*--------------------------------------------Functions Bodies--------------------------------------------*/

void menu(){

    int option;
    do {
        printf("Escolha uma opcao:\n");
        printf("1. Insercao\n");
        printf("2. Listar todes\n");
        printf("3. Pesquisa por chave\n");
        printf("0. Sair\n");

        scanf("%d", &option);
        getchar(); // Limpa o buffer

        switch (option) {
            case 1:
                insert();
                break;
            case 2:
                list_all();
                break;
            case 3:
                list_one();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (option != 0);

}

void insert(){

}

int insert_entry(Reg* reg){
    char separator = '#';
    int size = 0;
    FILE *fp = fopen(ARCHIVE, "r+b");
    fseek(fp, 0, SEEK_END);
    
    size += sizeof(char) * strlen(reg->id);
    size += sizeof(char) * strlen(reg->acr);
    size += sizeof(char) * strlen(reg->name);
    size += sizeof(char) * strlen(reg->subj);
    size += sizeof(float);
    size += sizeof(float);

    fwrite(&size, sizeof(size), 1, fp);
    fwrite(&separator, sizeof(separator), 1, fp);
    fwrite(reg->id, sizeof(sizeof(char) * strlen(reg->id)), 1, fp);
    fwrite(&separator, sizeof(separator), 1, fp);
    fwrite(reg->acr, sizeof(sizeof(char) * strlen(reg->acr)), 1, fp);
    fwrite(&separator, sizeof(separator), 1, fp);
    fwrite(reg->name, sizeof(sizeof(char) * strlen(reg->name)), 1, fp);
    fwrite(&separator, sizeof(separator), 1, fp);
    fwrite(reg->subj, sizeof(sizeof(char) * strlen(reg->subj)), 1, fp);
    fwrite(&separator, sizeof(separator), 1, fp);
    fwrite(&reg->mean, sizeof(sizeof(long)), 1, fp);
    fwrite(&separator, sizeof(separator), 1, fp);
    fwrite(&reg->atte, sizeof(sizeof(long)), 1, fp);
    fwrite(&separator, sizeof(separator), 1, fp);

}

void list_all(){

}

void list_one(){
    int numKeys;
    Aux aux;

    // Pergunta ao usuário quantas chaves serão buscadas
    printf("Informe a quantidade de chaves a serem buscadas: ");
    scanf("%d", &numKeys);
    getchar(); // Limpa o buffer

    FILE* fp = fopen(AUX, "r+b");
    fread(&aux, sizeof(aux), 1, fp);

}

void init(){
    char file_name[50];

    strcpy(file_name, ARCHIVE);
    if(!file_exists(file_name)){
        create_file(file_name);
    }

    strcpy(file_name, INDEX);
    if(!file_exists(file_name)){
        create_file(file_name);
    }

    strcpy(file_name, AUX);
    if(!file_exists(file_name)){
        create_file(file_name);
        FILE *fp = fopen(file_name, "r+b");
        Aux aux;
        aux.last_arch = 0;
        aux.last_search = 0;
        fwrite(&aux, sizeof(Aux), 1, fp);
        fclose(fp);
    }
}


bool file_exists(const char *filename){
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}

void create_file(const char *filename){
    FILE *fp = fopen(filename, "wb");
    fclose(fp);
}