#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO REGISTRO TAMANHO VARIAVEL COM INDICADOR DE TAMANHO

int pega_campo(char *p_registro, int *p_pos, char *p_campo);
int pega_registro(FILE *p_out, char *p_reg);

int main(void)
{
  // campos do registro
  int ra;
  char nome[30], end[30];
  
  char campo[30], registro[90]; // buffers
  
  FILE *out;
  int tam_campo, tam_reg, pos;

  if ((out = fopen("arq.bin","w+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo");
		getch();
		return 0;
	 }

  // le os campos informados pelo usuario
  printf("ra: ");
  scanf("%d",&ra);
  fflush(stdin);          
  
  while (ra != 0)	 
   {
        printf("nome: ");
        gets(nome);
        printf("endereco: ");
        gets(end);      
        
        // formata os campos e salva no buffer
        sprintf(registro,"%d|%s|%s|",ra,nome,end); // NOTA - nro passa a ser texto!!
        tam_reg = strlen(registro); // calcula o tam. dos caracteres validos (NOTA sem '\0')
        
        fwrite(&tam_reg, sizeof(int), 1, out); // escreve o tamanho do registro
        fwrite(registro, sizeof(char), tam_reg, out); // escreve os dados do registro
        
        // ALTERNATIVA - escrever nro como int
//        sprintf(registro,"|%s|%s|",nome,end); // formata campos do tipo string no buffer
//        tam_reg = strlen(registro) + sizeof(int); // tam dos campos string + tam do RA (int)
//        fwrite(&tam_reg, sizeof(int), 1, out); // escreve indicador de tam. do registro
//        fwrite(&ra, sizeof(int), 1, out); // escreve RA
//        fwrite(registro, sizeof(char), strlen(registro), out); // escreve o restante dos campos
		// TODO - alterar funcao read!
        
        printf("\nra: ");
        scanf("%d",&ra);        
        fflush(stdin);             	    
   }    

  fseek(out,0,0); // volta ao inicio do arquivo
  
  tam_reg = pega_registro(out,registro); // le o tam do registro e armazena todo o registro no buffer 'registro'
  
  while (tam_reg > 0) // enquanto haver registro 
   {
        pos = 0; // posicao de cada campo no registro       
        tam_campo = pega_campo(registro,&pos,campo); // le o campo em dada posicao
		       
        while (pos <= tam_reg)
          {            
            printf("tamanho: %d\n",tam_campo);
            printf("campo: %s\n\n",campo);            
            tam_campo = pega_campo(registro,&pos,campo); // proximo campo                             
          }  
        tam_reg = pega_registro(out,registro); // proximo registro
        getch();      
   } 

  fclose(out);

  getch();  
}

int pega_registro(FILE *p_out, char *p_reg)
{
     int bytes;
     
     if (!fread(&bytes, sizeof(int), 1, p_out)) // le o indicador de tam. e guarda em 'bytes'
       return 0; // se fim de arquivo retorna 0
     else { // senao
            fread(p_reg, bytes, 1, p_out); // le a qtd de bytes (indicador de tam) para o buffer 'p_reg'
            return bytes;
          }  
}     

int pega_campo(char *p_registro, int *p_pos, char *p_campo)
{
     char ch;
     int i=0;

     p_campo[i] = '\0'; // inicializa buffer do campo
     
     ch = p_registro[*p_pos]; // carrega em ch o caracter na posicao 'p_pos' do registro
     
     while ((ch != '|') && (ch!='\0')) // enquanto n encontrar o delimitador
      {                      
           p_campo[i] = ch; // carrega caracter a caracter no buffer
           i++;
           ch = p_registro[++(*p_pos)]; // carrega caracter da prox. posicao (e incrementa posicao)
      }     
     
	 ++(*p_pos); // qnd sair incrementa para voltar depois do delimitador
     p_campo[i] = '\0';
     
     return strlen(p_campo);
}     
