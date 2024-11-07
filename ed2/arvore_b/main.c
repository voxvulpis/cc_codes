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

}

void insert(){

}

void list_all(){

}

void list_one(){

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