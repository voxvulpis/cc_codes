//Includes  ----------------------------------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>

//Hardcoded variables   ----------------------------------------------------------------------------------------------------------
#define DATA_PATH "./data/"
#define INSERE_BIN "insere.bin"
#define REMOVE_BIN "remove.bin"
#define DB "data_base.bin"

#define CLI_ID_LENGHT 11
#define CAR_ID_LENGHT 7
#define NAME_LENGHT 50

//Structs   ----------------------------------------------------------------------------------------------------------
typedef struct Rent{
    int size;
    char* cli_id;
    char* car_id;
    char* cli_name;
    char* car_name;
    int days_rent;
}reg_loc;

//Functions declarations    ----------------------------------------------------------------------------------------------------------

//  Menu Function
int menu();


//  Program 'Main' Functions
int insert(reg_loc* );
int remove(char [CLI_ID_LENGHT + CAR_ID_LENGHT + 1]);
int compact();
int load();

//  Search Functions
int by_key(int);
int first_fit();

//  Type handler Functions
reg_loc* reg_struct(int);
reg_loc* new_reg();
void kill_Reg(reg_loc*);
char* string_field(int);
int int_field(int);

//  File Handling
int reg_open(FILE*);
void reg_close(FILE*);



//Main  ----------------------------------------------------------------------------------------------------------
int main(){
    menu();

    return 0;
}


//Functions ----------------------------------------------------------------------------------------------------------
int menu(){
    
}

int insert(reg_loc* reg){

}

int remove(char key[CLI_ID_LENGHT + CAR_ID_LENGHT + 1])
{
    return 0;
}

int compact()
{
    return 0;
}

int load()
{
    return 0;
}

int by_key(int key)
{
    return 0;
}

int first_fit()
{
    return 0;
}

reg_loc* reg_struct(int offset)
{
    reg_loc* reg;
    return reg;
}

reg_loc *new_reg()
{
    reg_loc* reg = (reg_loc*) malloc(sizeof(reg_loc));

    reg->size = 0;
    reg->cli_id = (char*) malloc(0);
    reg->car_id = (char*) malloc(0);
    reg->cli_name = (char*) malloc(0);
    reg->car_name = (char*) malloc(0);
    reg->days_rent = 0;

    return reg;
}

void kill_reg(reg_loc* reg){
    free(reg->cli_id);
    free(reg->car_id);
    free(reg->cli_name);
    free(reg->car_name);
    free(reg);
}

char* string_field(int offset)
{
    char* str;
    return str;
}

int int_field(int offset)
{
    return 0;
}
