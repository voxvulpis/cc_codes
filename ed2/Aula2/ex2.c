#include<stdlib.h>
#include<string.h>
#include<stdio.h>
// #include<curses.h>

typedef struct reg
{
    char nome[15];
    char sobrenome[15];
    char rua[26];
    int num;
}Reg;




int main(){
    char nome[15], sobrenome[15], rua[26];
    int num;
    FILE* fin;
    Reg regs[10];
    char str[60];


    if((fin = fopen("fixo.dat", "a+b")) == NULL){
        printf("ERROR \tCouldn't open file.\n");
        // getch();
        return 1;
    }

    fseek(fin, 0, 0);

    for (int i = 0; i < 10; i++)
    {
        str[0] = '\0';
        fgets(str, 60, fin);
        // fread(regs[i].nome, sizeof(regs[i].nome), 1, fin);
        // fread(regs[i].sobrenome, sizeof(regs[i].sobrenome), 1, fin);
        // fread(regs[i].rua, sizeof(regs[i].rua), 1, fin);
        // fread(&regs[i].num, sizeof(int), 1, fin);
        printf("%s\n", str);


    }

    // for(int i = 0; i < 10; i++){
    //     printf("%15s \t%15s \t%26s \t%8i \n", regs[i].nome, regs[i].sobrenome, regs[i].rua, regs[i].num);
    // }
    
    fclose(fin);
    return 0;
}
