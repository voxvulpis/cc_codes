#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO SEQUENCIA DE BYTES
int main(void)
{
  char nome[30], sobrenome[30], end[30];
  FILE *out;

  if ((out = fopen("arq.bin","w+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo");
		getche();
		return 0;
	 }
	 
  printf("nome: ");
  gets(nome);
  
  while (strlen(nome) > 0)	 
   {
        printf("sobrenome: ");
        gets(sobrenome);
        printf("endereco: ");
        gets(end);      
        
        // escreve apenas caracteres validos de cada campo
        fwrite(nome,sizeof(char),strlen(nome),out);
  	    fwrite(sobrenome,sizeof(char),strlen(sobrenome),out);
  	    fwrite(end,sizeof(char),strlen(end),out);
        
        printf("nome: ");
        gets(nome);           	    
   }    

  fclose(out);

  getch();
}
