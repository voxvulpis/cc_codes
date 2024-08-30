//Libs START
#include<stdio.h>
#include<stdlib.h>
//Libs END

//Define START
//Define END

//Structs START
typedef struct Register
{
    int id;
    char* acronym;
    char* student;
    char* subject;
    float grade;
    float attendance;
}reg;
//Structs END

//Function Declarations START
    //Top-Functions
void insert();
void remove();
void compact();
void load_files();
    //Sub-Functions
void read_next();
void close_file(FILE* );

//Function Declarations END


//Main START
void main(){
    FILE* file = open_file();
    if(file == NULL) return 2;

    


    close_file(file);
}
//Main END

//Function Definitions START
void insert(){

}

void remove(){

}

void compact(){

}

void load_files(){

}

void read_next(){

}

FILE* open_file(){
    FILE* file;
    if ((file = fopen("arq.bin","w+b")) == NULL)
    {
        printf("Não foi possivel abrir o arquivo");
        getche();
        return 0;
    }

    return file;
}

void close_file(FILE* file){
    fclose(file);
}
//Function Definitions END
