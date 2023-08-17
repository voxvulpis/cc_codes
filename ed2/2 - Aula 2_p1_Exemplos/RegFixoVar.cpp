#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO REGISTRO COM TAMANHO FIXO CAMPO VARIAVEL
int main(void)
{

  // NOTA nao usa uma struct
  char nome[30], sobrenome[30], end[30];
  char registro[90]; // buffer 90 bytes 
  
  FILE *out;

  if ((out = fopen("arq.bin","w+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo");
		getche();
		return 0;
	 }

  // le as entradas do usuario
  printf("nome: ");
  gets(nome);
  
  while (strlen(nome) > 0)	 
   {
        printf("sobrenome: ");
        gets(sobrenome);
        printf("endereco: ");
        gets(end);      
        
        // formata os campos do registro -- somente caracteres validos
        sprintf(registro,"%s|%s|%s|",nome,sobrenome,end);
        // salva o buffer com os dados do registro
        fwrite(registro,sizeof(registro),1,out); // salva o buffer todo (incluido caracteres n validos)                
	            
        printf("nome: ");
        gets(nome);           	    
   }    

  fclose(out);

  getch();
}
