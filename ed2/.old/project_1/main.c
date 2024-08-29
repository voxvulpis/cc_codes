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
int menu_wrp();
int menu();


//  Program 'Main' Functions
int insert_reg(reg_loc* , int);
int remove_reg(int );
int compact_file();
int load_test();
//      Wrappers
int insert_reg_wrp();
int remove_reg_wrp();
int compact_file_wrp();
int load_test_wrp();

//  Search Functions
int by_key(char* , char *);
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
    unsigned short int sys_os = op_sys();
    FILE* fp;
    char cmd = 'n';

    if(sys_os == 1 || sys_os == 2)
        printf("OS: WINDOWS\n");
    else if(sys_os == 10){
        printf("OS: LINUX\n");
    }
    else
        printf("OS: UNDEFINED\n");

    printf("PROJECT_1: START");


    //Check file
    if(file_open(&fp)){
        printf("Program could not open file, Create a new one? (y/n)");
        scanf(" %c", &cmd);
        
        if(cmd == 'y' || cmd == 'Y'){
            create_file();
            // return 0;
        }else{
            return 1;
        }

    }

    wait_for(1);
    console_clear();
    while (menu() > 1);
    
}

int menu(){
    char cmd = '5';

    printf("Project 1\n\t1.Insert\n\t2.Remove\n\t3.Compact\n\t4.Load Test File\n\t5.Exit\n");

    // input_clear();
    scanf("%c", &cmd);
    
    switch (cmd)
    {
    case '1':
        insert_reg_wrp();
        break;

    case '2':
        remove_reg_wrp();
        break;

    case '3':
        compact_file_wrp();
        break;

    case '4':
        load_test_wrp();
        break;

    case '5':
        return 2;
    
    default:
        return 0;
        break;
    }
}

int insert_reg(reg_loc* reg, int offset){
    FILE* fp;

    int size = 6 + CLI_ID_LENGHT + CAR_ID_LENGHT + strlen(reg->cli_name) + strlen(reg->car_name) + 1;
    // offset = first_fit(size);
    int rest = 0;
    char div = '|';
    char flg = '*';

    file_open(&fp);
    if(offset != -1)
        fseek(fp, offset, SEEK_SET);
    else
        fseek(fp, 0, SEEK_END);
    fread(&rest, sizeof(int), 1, fp);
    rest -= size;

    fseek(fp, offset, SEEK_SET);

    fwrite(&size, sizeof(int), 1, fp);

    fwrite(reg->cli_id, sizeof(char), CLI_ID_LENGHT, fp);
    fwrite(&div, sizeof(char), 1, fp);

    fwrite(reg->car_id, sizeof(char), CAR_ID_LENGHT, fp);
    fwrite(&div, sizeof(char), 1, fp);

    fwrite(reg->cli_name, sizeof(char), strlen(reg->cli_name), fp);
    fwrite(&div, sizeof(char), 1, fp);

    fwrite(reg->car_name, sizeof(char), strlen(reg->car_name), fp);
    fwrite(&div, sizeof(char), 1, fp);

    fwrite(&reg->days_rent, sizeof(int), 1, fp);
    fwrite(&div, sizeof(char), 1, fp);

    if(rest >= 3){
        fwrite(&rest, sizeof(int), 1, fp);

    }
    

    file_close(&fp);
    return 0;
}

int remove_reg(int offset){
    int next = 0;
    char flg = '*';
    FILE* fp;
    file_open(&fp);

    fseek(fp, 0, SEEK_SET);
    fread(&next, sizeof(int), 1, fp);

    while(next != -1){
        fseek(fp, next + 2, SEEK_SET);
        fread(&next, sizeof(int), 1, fp);

    }

    fseek(fp, 0, SEEK_CUR - 1);
    fwrite(&offset, sizeof(int), 1, fp);

    fseek(fp, offset + 1, SEEK_SET);
    fwrite(&flg, sizeof(char), 1, fp);
    offset = -1;
    fwrite(&offset, sizeof(int), 1, fp);


    file_close(&fp);
    return 0;
}

int compact_file(){
    FILE* fp;
    file_open(&fp);

    reg_loc* reg;

    int aux = 0;

    int old = 1;
    int new = 1;

    fseek(fp, 1, SEEK_SET);

    while(fgetc(fp) != EOF){
        if(fgetc(fp) == '*'){
            fread(&aux, sizeof(int), 1, fp);

            old += aux;
        }else{
            reg = reg_struct(old);
            insert_reg(reg, new);

        }
        // fseek(fp, -1, SEEK_CUR);

        fseek(fp, old, SEEK_SET);
    }


    fseek(fp, -1, SEEK_END);
    fputc(EOF, fp);
    file_close(&fp);
    return 0;
}

int load_test(){
    return 0;
}

int insert_reg_wrp(){
    char buff[50];
    reg_loc* reg = new_reg();
    
    console_clear();
    getc(stdin);
    printf("Input Client Code: ");
    // input_clear();
    fflush(stdin);
    fgets(buff, 12, stdin);
    strcpy(reg->cli_id, buff);


    getc(stdin);
    printf("Input Car Code: ");
    // input_clear();
    fflush(stdin);
    fgets(buff, 8, stdin);
    strcpy(reg->car_id, buff);

    //Searches for existent primary key
    if(by_key(reg->cli_id, reg->car_id) > 0){
        kill_reg(reg);
        printf("Duplicated Primary Key");
        return 1;
    }

    getc(stdin);
    printf("Input Client Name: ");
    // input_clear();
    fflush(stdin);
    fgets(buff, 50, stdin);
    strcpy(reg->cli_name, buff);

    getc(stdin);
    printf("Input Car Name: ");
    // input_clear();
    fflush(stdin);
    fgets(buff, 50, stdin);
    strcpy(reg->car_name, buff);

    getc(stdin);
    printf("Input the Number of Days: ");
    // input_clear();
    scanf(" %i", &reg->days_rent);

    insert_reg(reg, first_fit(6 + CLI_ID_LENGHT + CAR_ID_LENGHT + strlen(reg->cli_name) + strlen(reg->car_name) + 1));


    kill_reg(reg);
    return 0;
}

int remove_reg_wrp(){
    int offset = 0;
    reg_loc* reg = new_reg();
    
    console_clear();
    printf("Input Client Code: ");
    // input_clear();
    fgets(reg->cli_id, CLI_ID_LENGHT, stdin);
    printf("Input Car Code: ");
    fgets(reg->car_id, CAR_ID_LENGHT, stdin);



    //Searches for existent primary key
    offset = by_key(reg->cli_id, reg->car_id);
    if(offset == -1){
        kill_reg(reg);
        printf("Non-existent Primary Key");
        return 1;
    }

    remove_reg(offset);



    kill_reg(reg);
    return 0;
}

int compact_file_wrp(){

    return compact_file();
}

int load_test_wrp(){

    return load_test();
}

int by_key(char* cli_id, char* car_id){
    FILE* fp;
    int offset = 0;
    int total_offset = sizeof(int);
    char buff[50];
    char empty = '.';
    reg_loc* reg = new_reg();

    file_open(&fp);

    if(is_empty(fp))
        return 0;

    fseek(fp, 1, SEEK_SET);


    while(fgetc(fp) != EOF){

        fseek(fp, total_offset, SEEK_SET);
        fread(&empty, sizeof(char), 1, fp);

        if(empty == '*'){
            empty = '.';
            fseek(fp, total_offset, SEEK_SET);
            fread(&offset, sizeof(int), 1, fp);
            total_offset += offset;

        }else{
            fseek(fp, total_offset, SEEK_SET);
            
            fread(&offset, sizeof(int), 1, fp);

            fread(buff, CLI_ID_LENGHT, 1, fp);
            buff[CLI_ID_LENGHT] = 0;
            strcpy(reg->cli_id, buff);
            // fgets(reg->cli_id, 12, fp);
            fgetc(fp);
            fread(buff, CAR_ID_LENGHT, 1, fp);
            buff[CAR_ID_LENGHT] = 0;
            strcpy(reg->car_id, buff);
            fgetc(fp);

            
            
            cli_id[CLI_ID_LENGHT] = 0;
            car_id[CAR_ID_LENGHT] = 0;

            if(strcmp(cli_id, reg->cli_id) == 0 && strcmp(car_id, reg->car_id) == 0){
                kill_reg(reg);
                file_close(&fp);
                return total_offset;
            }

            total_offset += offset;
        }


        

    }

    kill_reg(reg);
    file_close(&fp);
    return 0;
}

int first_fit(int size){
    int offset = 0;
    int reg_size = 0;
    FILE* fp;
    file_open(&fp);

    fseek(fp, offset, SEEK_SET);
    fread(&offset, sizeof(int), 1, fp);

    while (offset != -1)
    {
        fseek(fp, offset, SEEK_SET);
        fread(&offset, sizeof(int), 1, fp);

        if(offset >= size){
            file_close(&fp);
            return offset;
        }

        fseek(fp, 1, SEEK_CUR);
        fread(&offset, sizeof(int), 1, fp);
        
    }

    
    



    file_close(&fp);
    return -1;
}

int is_empty(FILE* fp){
    int offset = 0;

    fseek(fp, sizeof(int), SEEK_SET);
    fread(&offset, sizeof(int), 1, fp);

    if(offset > 0){
        return 0;
    }
    
    return 1;

}

reg_loc* reg_struct(int offset){
    reg_loc* reg = new_reg();
    FILE* fp;
    file_open(&fp);

    char aux = 'a';
    
    reg->cli_name[0] = 0;
    reg->car_name[0] = 0;


    fseek(fp, offset, SEEK_SET);

    fread(&reg->size, sizeof(int), 1, fp);

    fread(reg->cli_id, sizeof(char), CLI_ID_LENGHT, fp);
    fgetc(fp);

    fread(reg->car_id, sizeof(char), CAR_ID_LENGHT, fp);
    fgetc(fp);

    while((aux = fgetc(fp)) != '|'){
        reg->cli_name[strlen(reg->cli_name)] = 0;
    }

    while((aux = fgetc(fp)) != '|'){
        reg->car_name[strlen(reg->car_name)] = 0;
    }

    fread(&reg->days_rent, sizeof(int), 1, fp);

    printf("Struct: \nSize\t%i\nCli_id\t%s\nCar_id\t%s\nCli_name\t%s\nCar_name\t%s\nDasy\t%i", reg->size, reg->cli_id, reg->car_id, reg->cli_name, reg->car_name,reg->days_rent);



    file_close(&fp);
    return reg;
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
    char* str;
    return str;
}

int int_field(int offset){
    return 0;
}

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