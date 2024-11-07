#include<stdio.h>
#include<conio.h>

int main() {
    FILE *fd;
    
    //////////////////////////////
    struct hist {
        char id_aluno[4];
        char sigla_disc[4];
        char nome_aluno[50];
        char nome_disc[50];
        float media;
        float freq;
    } vet[6] = {{"001", "333", "Nome-1", "Disc-333", 5.4, 79.7},
                {"001", "222", "Nome-1", "Disc-222", 8.2, 80.4},
                {"002", "444", "Nome-2", "Disc-444", 6.8, 91.3},   
				             
                {"003", "666", "Nome-3", "Disc-666", 8.3, 77.7},                
	            {"001", "111", "Nome-1", "Disc-111", 7.5, 72.3},            
                {"002", "555", "Nome-2", "Disc-555", 6.3, 72.7}};
       
    fd = fopen("insere.bin", "w+b");
    fwrite(vet, sizeof(vet), 1, fd);
    fclose(fd);
    
    //////////////////////////////
    struct busca_p {
        char id_aluno[4];
        char sigla_disc[4];
    } vet_bp[6] = {{"001","222"},
                   {"001","777"},
                   {"001","222"},
                   
                   {"003","666"},
                   
                   {"001","222"},
                   {"003","666"}};
    
    fd = fopen("busca_p.bin", "w+b");
    fwrite(vet_bp, sizeof(vet_bp), 1, fd);
    fclose(fd);
    
    //////////////////////////////
	const int quantidade = 8;
    char nomes[quantidade][50] = {"Nome-1", "Nome-X", "Nome-2", "Nome-1", "Nome-1", "Nome-2", "Nome-X", "Nome-3"};
       
    fd = fopen("busca_s.bin", "w+b");
    for (int i=0; i<quantidade; i++)
       fwrite(nomes[i], sizeof(char), 50, fd);
    fclose(fd);
    
    /*char buffer[50];
    fd = fopen("busca_s.bin", "r+b");
    for (int i=0; i<quantidade; i++)
       {
         fread(buffer, sizeof(buffer), 1, fd);
         printf("\n%s",buffer);
       }
    fclose(fd);
    getch();*/
}

