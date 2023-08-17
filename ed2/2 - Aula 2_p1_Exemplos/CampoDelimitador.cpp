#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO CAMPO COM DELIMITADORES
int pega_campo(FILE *p_out, char *p_campo);

int main(void)
{
  char nome[30], sobrenome[30], end[30];
  char campo[30], buffer[100];
  FILE *out;
  int tam_campo;

  if ((out = fopen("arq.bin","w+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo");
		getch();
		return 0;
	 }
	 
  printf("nome: ");
  fgets(nome, 30, stdin);
  
  while (strlen(nome) > 0)	 
   {
        printf("sobrenome: ");
        fgets(sobrenome, 30, stdin);
        printf("endereco: ");
        fgets(end, 30, stdin);      
        
        // formata os campos separando por delimitadores (e.g., '|')
        // e.g., ana|silva|rua 20|
        sprintf(buffer,"%s|%s|%s|",nome,sobrenome,end);
        // grava os campos formatados no arquivo
        fwrite(buffer,sizeof(char),strlen(buffer),out);
        
        printf("nome: ");
        fgets(nome, 30, stdin);           	    
   }    

  // volta ao inicio do arquivo
  fseek(out,0,0);
  
  // processamento para recuperar cada campo
  tam_campo = pega_campo(out,campo);	 
  
  // imprime os campos
  while (tam_campo > 0)
   {        
        printf("tamanho: %d\n",tam_campo);
        printf("campo: %s\n\n",campo);  
        
        // proc. para recuperar prox. campo
        tam_campo = pega_campo(out,campo); 
		       
        getch();      
   } 
  
  fclose(out);

  getch();  
}

/* recupera cada campo e armazena (retorna) no buffer 'p_campo'*/
int pega_campo(FILE *p_out, char *p_campo)
{
     char ch;
     int i=0;

     p_campo[i] = '\0'; // inicializa o buffer
     
     // forma alternativa - usando a funcao 'fgetc' e 'EOF'
     /*ch = fgetc(p_out);     
     while ((ch != '|') && (ch != EOF))
      {                      
           p_campo[i] = ch;
           i++;
           ch = fgetc(p_out);           
      }     */
      
     while (fread(&ch,sizeof(char),1,p_out)) // le caractere a caractere
       {
           if (ch == '|') // para qnd for igual ao delimitador
             break;
           else p_campo[i] = ch; // senao salva o caracter no buffer
           
           i++;	// incrementa o indice do buffer
       }
     
     p_campo[i] = '\0'; // inclue o delimitador de string
     
     return strlen(p_campo); // retorna o tam do campo salvo no buffer
}     
