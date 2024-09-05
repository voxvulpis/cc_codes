//Libs START
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Libs END

//Define START
#define FILE_NAME "./output.bin"
#define INSERT_FILE_NAME "./insere.bin"
#define ID_LENGHT 3
#define ACRONYM_LENGHT 3
#define NAME_STR_LENGHT 50
//Define END

//Structs START
typedef struct Register
{
    char id[ID_LENGHT + 1];
    char acronym[ACRONYM_LENGHT + 1];
    char student[NAME_STR_LENGHT];
    char subject[NAME_STR_LENGHT];
    float grade;
    float attendance;
}regi;

typedef struct register_array
{
    int size;
    regi* regs;
}regi_arr;

//Structs END

//Function Declarations START
    //Top-Functions
void insert_reg(FILE* );
void remove_reg(FILE* );
void compact_file(FILE* );
void load_files(FILE* );
    //Sub-Functions
regi_arr read_input(int );
void close_input(regi_arr );
FILE* open_aux();
int read_aux();
void write_aux(int );
int find_next(FILE* , int );
regi read_next(FILE* ,int );
int find_key(FILE* , char* , char* );
void write_reg(FILE* , int , regi);
regi read(FILE* , int );
int first_fit(FILE* , int );
void close_file(FILE* );
FILE* open_file();

//Function Declarations END


//Main START
int main(){
    int f_size = 0, next_empty = -1;
    FILE* file = open_file();
    if(file == NULL) return 2;
    
    fseek(file, 0, SEEK_END);
    f_size = ftell(file);
    if(f_size == fseek(file, 0, SEEK_SET)){
        fwrite(&next_empty, sizeof(int), 1, file);
    }

    

    insert_reg(file);

    


    close_file(file);
}
//Main END

//Function Definitions START
void insert_reg(FILE* file){
    int qnt = 0;
    regi_arr input;
    int size = 0, off;

    system("clear");
    printf("\nInserir Registros:");
    printf("\n\tQuantidade de Registros a serem inseridos: ");
    scanf(" %i", &qnt);

    if( (input = read_input(qnt)).size <= 0 ){
        return;
    }

    // fseek(file, 0, SEEK_END);
    // fwrite(input.regs, sizeof(regi) * input.size, 1, file);

    for(int i = 0; i < qnt; i++){
        off = first_fit(file, sizeof(regi));
        write_reg(file, off, input.regs[i]);
    }


    system("clear");
    printf("\nRegistros Inseridos : %i\n", qnt);

    return;
}

void remove_reg(FILE* file){
    int last = -1, next = 0, off = 0;
    char id[ID_LENGHT + 1];
    char acronym[ACRONYM_LENGHT + 1];
    regi temp;
    char del = '*';

    system("clear");
    printf("Excluir Registro\n");

    printf("\n\tId:\t ");
    fgets(id, ID_LENGHT + 1, stdin);
    // gets(id);
    id[ID_LENGHT] = '\0';

    printf("\n\tSigla:\t ");
    fgets(acronym, ACRONYM_LENGHT + 1, stdin);
    // gets(acronym);
    acronym[ACRONYM_LENGHT] = '\0';

    fseek(file, 0, SEEK_SET);
    fread(&next, sizeof(int), 1, file);

    off = find_key(file, id, acronym);

    if(off != -1){
        fseek(file, off, SEEK_SET);
        fwrite(&del, sizeof(char), 1, file);
        fwrite(&next, sizeof(int), 1, file);
    }
    
}

void compact_file(FILE* file){

}

void load_files(FILE* file){

}

regi_arr read_input(int qnt){
    int read = 0;
    int debug = 0;
    int aux;
    regi_arr regs;
    regs.size = 0;
    regs.regs = (regi*)calloc(qnt, sizeof(regi));

    FILE* file;
    if ((file = fopen(INSERT_FILE_NAME,"r+b")) == NULL){
        printf("Não foi possivel abrir o arquivo");
        return regs;
    }

    aux = read_aux();

    fseek(file, sizeof(regi)*aux, SEEK_SET);
    
    if( (debug = fread(regs.regs, sizeof(regi), qnt, file)) != qnt){
        printf("ERROR: EOF size: %i read: %i", qnt, debug);
        regs.size = 0;
        free(regs.regs);
    }else{
        regs.size = qnt;
        close_input(regs);
    }

    return regs;
}

void close_input(regi_arr regs){
    regi reg;
    int aux = 0;

    // free(regs.regs);

    aux = read_aux() + regs.size;
    write_aux(aux);
}

FILE* open_aux(){
    FILE* file;

    if ((file = fopen("./aux.bin","r+b")) == NULL){
        printf("Não foi possivel abrir o arquivo");
    }

    return file;
}

int read_aux(){
    int aux = 0;
    FILE* file = open_aux();

    fseek(file, 0, SEEK_SET);

    if((fread(&aux, sizeof(int), 1, file)) == 0 ){
        aux = 0;
    }

    return aux;
}

void write_aux(int aux){
    FILE* file = open_aux();

    fseek(file, 0, SEEK_SET);

    fwrite(&aux, sizeof(int), 1, file);
}

int find_next(FILE* file, int last){
    int reg_size;

    if(last == -1) return 0;

    fseek(file, last, SEEK_SET);
    fread(&reg_size, sizeof(int), 1, file);

    if(reg_size == -1) return -1;

    return last + reg_size;
}

int first_fit(FILE* file, int size){
    int off = 0;
    int aux_size = 0;
    fseek(file, 0, SEEK_SET);

    fseek(file, off, SEEK_SET);
    fread(&off, sizeof(int), 1, file);

    while(off != -1){
        fseek(file, off, SEEK_SET);
        fread(&off, sizeof(int), 1, file);
        fseek(file, sizeof(char), SEEK_CUR);
        fread(&aux_size, sizeof(int), 1, file);

        if(aux_size >= size){
            return off;
        }
    }

    return off;
}

int find_key(FILE* file, char* id, char* acronym){
    int off = -1, reg_size = 0;
    char sep;
    regi reg;

    fseek(file, sizeof(int), SEEK_SET);
    

    while(fread(&reg_size, sizeof(char), 1, file) != 0){
        off = ftell(file);
        fread(&sep, sizeof(char), 1, file);
        if(sep == '*'){
            fseek(file, off + reg_size, SEEK_CUR);
        }else{
            fseek(file, off, SEEK_CUR);

            fread(&reg, sizeof(regi), 1, file);
            if(strcmp(reg.id, id) && strcmp(reg.acronym, acronym)){
                return off;
            }

        }

    }
    



    return -1;
}

void write_reg(FILE* file, int off, regi reg){
    int size = sizeof(regi);

    if(off != -1){
        fseek(file, off, SEEK_SET);
    }else{
        fseek(file, 0, SEEK_END);
    }

    fwrite(&size, sizeof(int), 1, file);
    fwrite(&reg, sizeof(regi), 1, file);

    return;
}

regi read_next(FILE* file, int last){//Não funcional
    // regi next;
    // next.id = NULL;
    // int off = find_next(file, last);

    // if(off != -1){
    //     next = read(file, off);
    // }

    // return next;
}

regi read(FILE* file, int off){
    regi reg;
    reg.id[0] = '\0';
    char del = 'a';

    fseek(file, off + (sizeof(int) * 2), SEEK_SET);
    fread(&del, sizeof(char), 1, file);

    if(del == '*') return reg;

    fseek(file, off + sizeof(int), SEEK_SET);
    fread(&reg, sizeof(regi), 1, file);

    return reg;
}

FILE* open_file(){
    FILE* file;
    if ((file = fopen(FILE_NAME,"r+b")) == NULL){
        if ((file = fopen(FILE_NAME,"w+b")) == NULL){
            printf("Não foi possivel abrir o arquivo");

        }
    }

    return file;
}

void close_file(FILE* file){
    fclose(file);
}
//Function Definitions END
