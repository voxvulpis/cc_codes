#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO CAMPO COM INDICADOR DE COMPRIMENTO (qnts bytes tem cada campo)
// e.g., 3ana5silva6rua 20...

int main(void)
{
  char nome[30], sobrenome[30], end[30];
  FILE *out;
  int tam;

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
        
        // processamento necessario para definir o tam do campo (a ser usado no indicador)
  	    tam = strlen(nome); // qtd caracteres validos
  	    tam++; // +1 - '\0'
  	    
  	    fwrite(&tam,sizeof(int),1,out); // grava tam                
        fwrite(nome,sizeof(char),tam,out); // grava campo
        
	    tam = strlen(sobrenome);
	    tam++;
  	    fwrite(&tam,sizeof(int),1,out);                 
        fwrite(sobrenome,sizeof(char),tam,out);
        
        tam = strlen(end);
        tam++;
  	    fwrite(&tam,sizeof(int),1,out);                         
	    fwrite(end,sizeof(char),tam,out);    
        
        // proximo campo - proxima entidade
        printf("nome: ");
        gets(nome);           	    
   }   
    
  rewind(out); // volta ao inicio do arquivo
  
  char buffer[255];
  
  // primeiro le o tam. do campo (armazenado como int - 4bytes)
  while (fread(&tam,sizeof(int),1,out)) 
   {      
        // le o campo (Nota nao eh preciso ler caracter a caracter)
		fread(buffer,sizeof(char),tam,out); 
        //buffer[tam]='\0';
        
        printf("\ncampo: %s",buffer);
        getch();
   }

  fclose(out);

  getch();
}
