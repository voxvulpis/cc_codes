#include<stdlib.h>
#include<stdio.h>

#define FILE_ADRESS "./fixo.dad"
#define REGS_LENGHT 10

typedef struct resgister
{
    char name[15];
    char surname[15];
    char adress[26];
    int houseNumber;
}Reg;


FILE* openFile();
void readReg(Reg* , FILE*);
void printReg(Reg);


int main(){
    Reg regs[10];
    FILE* in;

    if((in = openFile()) == NULL){
        return 2;
    }

    fseek(in, 0, SEEK_SET);

    readReg(regs, in);

    // fread(regs[0].name, sizeof(char), 15, in);

    // printf("%s", regs[0].name);

    for(int i = 0; i < REGS_LENGHT; i++){
        printReg(regs[i]);

    }


    fclose(in);
    return 0;
}


FILE* openFile(){
    FILE* file;

    if((file = fopen(FILE_ADRESS, "rb")) == NULL){
        printf("Error: Could not open file.");
        return NULL;
    }else{
        return file;
    }
}

void readReg(Reg* regs, FILE* file){
    for(int i = 0; i < REGS_LENGHT; i++){
        fread(&regs[i].name, sizeof(char), 15, file);
        fread(&regs[i].surname, sizeof(char), 15, file);
        fread(&regs[i].adress, sizeof(char), 26, file);
        fread(&regs[i].houseNumber, sizeof(int), 1, file);
    }
}

void printReg(Reg reg){
    printf("Name: \t%s\n", reg.name);
    printf("Surname: \t%s\n", reg.surname);
    printf("Adress: \t%s\n", reg.adress);
    printf("House Number: \t%i\n", reg.houseNumber);
}