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
typedef struct remove_aux
{
    char id[ID_LENGHT + 1];
    char acronym[ACRONYM_LENGHT + 1];
}remo;

typedef struct remove_arrayr
{
    int size;
    remo* rems;
}rem_arr;



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
void remove_reg_auto(FILE* );
void compact_file(FILE** );
void load_files(FILE* );
    //Sub-Functions
rem_arr read_remove(int );
regi_arr read_input(int );
void close_input(regi_arr );
FILE* open_aux();
int read_aux();
void write_aux(int );
int find_next(FILE* , int );
regi read_next(FILE* ,int );
int find_key(FILE* , regi );
void write_reg(FILE* , int , regi);
regi read(FILE* , int );
int first_fit(FILE* , int );
void close_file(FILE* );
FILE* open_file();
int read_aux_rm();
void close_rm(rem_arr );
void write_aux_rm(int );

//Function Declarations END


//Main START
int main(){
    int f_size = 0, next_empty = -1;
    FILE* file;
    int cmd = -2;

    


    

    while(cmd != 4){
        file = open_file();
        if(file == NULL) return 2;

        fseek(file, 0, SEEK_END);
        f_size = ftell(file);
        if(f_size == fseek(file, 0, SEEK_SET)){
            fwrite(&next_empty, sizeof(int), 1, file);
        }


        system("clear");
        printf("\nEscolha Operação:");
        printf("\n\t1. Inserir:");
        printf("\n\t2. Remover:");
        printf("\n\t3. Comprimir:");
        printf("\n\t4. Sair:\n\t");

        scanf(" %i", &cmd);

        switch (cmd)
        {
        case 1:
            getchar();
            insert_reg(file);
            close_file(file);
            break;

        case 2:
            getchar();
            remove_reg_auto(file);
            close_file(file);
            break;

        case 3:
            getchar();
            compact_file(&file);
            close_file(file);
            break;

        case 4:
            getchar();
            
            break;
        
        default:
            break;
        }

    }










    // insert_reg(file);
    // remove_reg(file);
    // compact_file(&file);
    


    // close_file(file);
}
//Main END

//Function Definitions START
void insert_reg(FILE* file){
    int qnt = 0;
    regi_arr input;
    int size = 0, off, tell, off_aux = 0;

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
        tell = ftell(file);
        fseek(file, 0, SEEK_END);
        if(tell != ftell(file)){
            fseek(file, off + sizeof(char), SEEK_SET);
            fread(&off_aux, sizeof(int), 1, file);
            fseek(file, 0, SEEK_SET);
            fwrite(&off_aux, sizeof(int), 1, file);
        }
        fseek(file, 0, SEEK_END);
        write_reg(file, off, input.regs[i]);
    }


    system("clear");
    printf("\nRegistros Inseridos : %i\n", qnt);

    return;
}

void remove_reg_auto(FILE* file){
    int last = -1, next = 0, off = 0, qnt = 0;
    char id[ID_LENGHT + 1];
    char acronym[ACRONYM_LENGHT + 1];
    regi temp;
    char del = '*';
    regi reg_aux;
    rem_arr rems;

    // system("clear");
    // printf("Excluir Registro\n");

    // printf("\n\tId:\t ");
    // // fgets(id, ID_LENGHT + 1, stdin);
    // gets(reg_aux.id);
    // id[ID_LENGHT] = '\0';

    // printf("\n\tSigla:\t ");
    // // fgets(acronym, ACRONYM_LENGHT + 1, stdin);
    // gets(reg_aux.acronym);
    // acronym[ACRONYM_LENGHT] = '\0';

    system("clear");
    printf("\nRemover Registros:");
    printf("\n\tQuantidade de Registros a serem removidos: ");
    scanf(" %i", &qnt);

    if( (rems = read_remove(qnt)).size <= 0 ){
        return;
    }

    

    for(int i = 0; i < qnt; i++){
        fseek(file, 0, SEEK_SET);
        fread(&next, sizeof(int), 1, file);

        strcpy(reg_aux.id, rems.rems[i].id);
        strcpy(reg_aux.acronym, rems.rems[i].acronym);

        // reg_aux.id = rems.rems[i].id;
        // reg_aux.acronym = rems.rems[i].acronym;

        off = find_key(file, reg_aux);

        // printf("/nOFF: %i", off);

        if(off != -1){
            fseek(file, off, SEEK_SET);
            fwrite(&del, sizeof(char), 1, file);
            fwrite(&next, sizeof(int), 1, file);
            fseek(file, 0, SEEK_SET);
            fwrite(&off, sizeof(int), 1, file);
        }
        

    }

    close_rm(rems);


    
}

void remove_reg(FILE* file){
    int last = -1, next = 0, off = 0;
    char id[ID_LENGHT + 1];
    char acronym[ACRONYM_LENGHT + 1];
    regi temp;
    char del = '*';
    regi reg_aux;

    system("clear");
    printf("Excluir Registro\n");

    printf("\n\tId:\t ");
    // fgets(id, ID_LENGHT + 1, stdin);
    gets(reg_aux.id);
    id[ID_LENGHT] = '\0';

    printf("\n\tSigla:\t ");
    // fgets(acronym, ACRONYM_LENGHT + 1, stdin);
    gets(reg_aux.acronym);
    acronym[ACRONYM_LENGHT] = '\0';

    fseek(file, 0, SEEK_SET);
    fread(&next, sizeof(int), 1, file);

    off = find_key(file, reg_aux);

    // printf("/nOFF: %i", off);

    if(off != -1){
        fseek(file, off, SEEK_SET);
        fwrite(&del, sizeof(char), 1, file);
        fwrite(&next, sizeof(int), 1, file);
        fseek(file, 0, SEEK_SET);
        fwrite(&off, sizeof(int), 1, file);
    }
    
}

void compact_file(FILE** file){
    regi reg;
    int size, off, menos_um = -1;
    char del = 'a';

    FILE* file_aux = fopen("file_aux.bin", "w+b");



    fwrite(&menos_um, sizeof(int), 1, file_aux);
    fseek(*file, sizeof(int), SEEK_SET);

    while(fread(&size, sizeof(int), 1, *file) > 0){
        off = ftell(*file);
        fread(&del, sizeof(char), 1, *file);
        if(del != '*'){
            fseek(*file, off, SEEK_SET);
            fread(&reg, sizeof(regi), 1, *file);
            fwrite(&size, sizeof(int), 1, file_aux);
            fwrite(&reg, sizeof(regi), 1, file_aux);

        }else{
            fseek(*file, off + size, SEEK_SET);
        }
    }

    fclose(*file);
    fclose(file_aux);

    remove(FILE_NAME);
    rename("file_aux.bin", FILE_NAME);

    *file = open_file();
    if(file == NULL){
        printf("\nERROR: 2");
    }

}

void load_files(FILE* file){

}

rem_arr read_remove(int qnt){
    int read = 0;
    int debug = 0;
    int aux;
    rem_arr rems;
    rems.size = 0;
    rems.rems = (remo*)calloc(qnt, sizeof(remo));

    FILE* file;
    if ((file = fopen("./remove.bin","r+b")) == NULL){
        printf("Não foi possivel abrir o arquivo");
        return rems;
    }

    aux = read_aux_rm();

    fseek(file, sizeof(remo)*aux, SEEK_SET);
    
    if( (debug = fread(rems.rems, sizeof(remo), qnt, file)) != qnt){
        printf("ERROR: EOF size: %i read: %i", qnt, debug);
        rems.size = 0;
        free(rems.rems);
    }else{
        rems.size = qnt;
        close_rm(rems);
    }

    return rems;

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

void close_rm(rem_arr rems){
    regi reg;
    int aux = 0;

    // free(regs.regs);

    aux = read_aux_rm() + rems.size;
    write_aux_rm(aux);
}

FILE* open_aux(){
    FILE* file;

    if ((file = fopen("./aux.bin","r+b")) == NULL){
        printf("Não foi possivel abrir o arquivo");
    }

    return file;
}

FILE* open_aux_rm(){
    FILE* file;

    if ((file = fopen("./aux_rm.bin","r+b")) == NULL){
        if ((file = fopen("./aux_rm.bin","w+b")) == NULL){
                printf("Não foi possivel abrir o arquivo");
        }
        

        
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

int read_aux_rm(){
    int aux = 0;
    FILE* file = open_aux_rm();

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

void write_aux_rm(int aux){
    FILE* file = open_aux_rm();

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
    fread(&off, sizeof(int), 1, file);

    while(off != -1){
        fseek(file, off - sizeof(int), SEEK_SET);
        fread(&aux_size, sizeof(int), 1, file);

        if(aux_size >= size){
            return off;
        }

        fseek(file, sizeof(char), SEEK_CUR);
        fread(&off, sizeof(int), 1, file);
    }

    return off;
}

int find_key(FILE* file, regi reg_aux){
    int off = -1, reg_size = 0;
    char sep;
    regi reg;

    fseek(file, sizeof(int), SEEK_SET);

    

    while(fread(&reg_size, sizeof(int), 1, file) != 0){
        off = ftell(file);
        // fread(&sep, sizeof(char), 1, file);

        fread(&reg, sizeof(regi), 1, file);
        if(strcmp(reg.id, reg_aux.id) == 0 && strcmp(reg.acronym, reg_aux.acronym) == 0){
            return off;
        }




        // if(sep == '*'){
        //     fseek(file, off + reg_size, SEEK_CUR);
        // }else{
        //     fseek(file, off, SEEK_CUR);

        //     fread(&reg, sizeof(regi), 1, file);
        //     if(strcmp(reg.id, id) && strcmp(reg.acronym, acronym)){
        //         return off;
        //     }

        // }

    }
    



    return -1;
}

void write_reg(FILE* file, int off, regi reg){
    int size = sizeof(regi);

    if(off != -1){
        fseek(file, off - sizeof(int), SEEK_SET);
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
