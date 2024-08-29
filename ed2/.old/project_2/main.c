//Includes  ----------------------------------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

//Hardcoded variables   ----------------------------------------------------------------------------------------------------------

#define INSERE_BIN "./data/insere.bin"
#define REMOVE_BIN "./data/remove_reg.bin"
#define DB_PATH "./data/data_base.bin"

#define INSERE_BIN_WIN "\\data\\insere.bin"
#define REMOVE_BIN_WIN "\\data\\remove_reg.bin"
#define DB_PATH_WIN "\\data\\data_base.bin"

#define CLI_ID_LENGHT 11
#define CAR_ID_LENGHT 7
#define NAME_LENGHT 50

//Structs   ----------------------------------------------------------------------------------------------------------
typedef struct rent{
    int size;
    char* cli_id;
    char* car_id;
    char* cli_name;
    char* car_name;
    int days_rent;
}reg_loc;

typedef struct primary_key_index{
    char* cli_id;
    char* car_id;
}pri_key;

//Functions declarations    ----------------------------------------------------------------------------------------------------------

//  Menu Function
int menu_wrp();
int menu();


//  Program 'Main' Functions
int insert_reg(reg_loc* , int);
int remove_reg(int );
int compact_file();
int load_test();
reg_loc load_reg();
pri_key* load_index();

//      Wrappers
int insert_reg_wrp();
int remove_reg_wrp();
int compact_file_wrp();
int load_test_wrp();

//  Search Functions
int by_key(pri_key* );
int first_fit(int );
int is_empty(FILE* );

//  Type handler Functions
reg_loc* reg_struct(int);
reg_loc* new_reg();
void kill_reg(reg_loc*);
char* string_field(int);
int int_field(int);

//  File Handling
int file_open(FILE**);
void file_close(FILE**);
int create_file();
int compare(const void* , const void*);

//OS Handling
void console_clear();
void wait_for(unsigned int);
// void input_clear();
unsigned short int op_sys();



//Main  ----------------------------------------------------------------------------------------------------------
int main(){
    return menu_wrp();
    // FILE* fp ;
    // file_open(&fp);


    // file_close(&fp);

    return 0;

}


//Functions ----------------------------------------------------------------------------------------------------------

int menu_wrp(){

}


int menu(){

}




//  Program 'Main' Functions
int insert_reg(reg_loc* reg, int offset){

}


int remove_reg(int offset){

}


int compact_file(){

}


int load_test(){

}


reg_loc load_reg(){

}

pri_key* load_index(){
    pri_key* index = (pri_key*)malloc(sizeof(pri_key));
}



//      Wrappers
int insert_reg_wrp(){

}


int remove_reg_wrp(){

}


int compact_file_wrp(){

}


int load_test_wrp(){

}



//  Search Functions
int by_key(pri_key* key){

}


int first_fit(int size){

}


int is_empty(FILE* fp){

}



//  Type handler Functions
reg_loc* reg_struct(int offset){

}


reg_loc* new_reg(){
    reg_loc* reg = (reg_loc*) malloc(sizeof(reg_loc));

    reg->size = 0;
    reg->cli_id = (char*) malloc(CLI_ID_LENGHT + 1);
    reg->car_id = (char*) malloc(CAR_ID_LENGHT + 1);
    reg->cli_name = (char*) malloc(NAME_LENGHT);
    reg->car_name = (char*) malloc(NAME_LENGHT);
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


char* string_field(int offset){

}



//  File Handling
int file_open(FILE** fp){

    if(op_sys() == 10){
        if( (*fp = fopen(DB_PATH, "r+b")) != NULL ){
            printf("OPEN FILE\n");
            return 0;
        }
        else{
            printf("ERROR: OPEN FILE\n");
            return 1;
        }
    }else{
        if( (*fp = fopen(DB_PATH_WIN, "r+b")) != NULL ){
            return 0;
        }
        else{
            printf("ERROR: OPEN FILE\n");
            return 1;
        }
    }
}

int create_file(){
    FILE* fp;
    int insert[] = {-1, -1};

    if(op_sys() == 10){
        // fp = fopen(DB_PATH, "wb");
        if( (fp = fopen(DB_PATH, "wb")) != NULL ){
            printf("CREATE FILE\n");
            fwrite(insert, sizeof(int), sizeof(insert), fp);
            fseek(fp, 8, SEEK_SET);
            


            file_close(&fp);
            return 0;
        }
        else{
            printf("ERROR: CREATE FILE\n");
            return 1;
        }
    }else{
        if( (fp = fopen(DB_PATH_WIN, "wb")) != NULL ){
            file_close(&fp);
            return 0;
        }
        else{
            printf("ERROR: CREATE FILE\n");
            return 1;
        }
    }
}

void file_close(FILE** fp){
    fclose(*fp);
}

void console_clear(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #elif _WIN64
        system("cls");
    #endif
}

void wait_for(unsigned int wait){
    unsigned int end_time = time(0) + wait;
    while(time(0) < end_time);

    return;
}

void input_clear(){
    // scanf("%*[^\n]%1*[\n]");
}

unsigned short int op_sys(){
    unsigned short int sys_os = 0;
    #ifdef _WIN32
        sys_os = 1;
    #elif _WIN64
        sys_os = 2;
    #elif __linux__
        sys_os = 10;
    #endif

    printf("%i\n", sys_os);

    return sys_os;
}