#include <stdio.h>                                            //  ./Run para compilar o código
#include <stdlib.h>                           
#include <string.h>                                          //  make TesteTodos   para criar os executáveis.
#include <time.h>
#include "Avb.h"
#include "Hash.h"



int main()
{
    int Lydist, ch,i, aux=0, valList[2000], input;                     //Lydist atua em dois aspectos, como dados, guardando a distancia em anos luz de uma estrela e como indice  da arvore B;
    int M = 20000;
    Hash *H = create_hash (M);                                     //Cria a hash que vai armazenar a parte 'char' dos dados de uma determinada estrela.
    double Tempo;
    clock_t Ticks[2];

    char TEMPnome[256];
    char TEMPdist_ang[128];                                       // O uso de temporários para os dados se faz necessário evido a estrutura em que estão dispostos od dados no .txt
    char TEMPdeclinacao[128];                                     // A distancia "Lydist" só é lida no meio da linha, ou seja, os dados antes dela não tem endereço a serem colocados,
    char TEMPmagnitude[64];                                       // então todos os dados são  lidos e  guardados nos temporários, e depois inseridos na Hash e na AVB de uma vez.
    char TEMPmagnitudeGeral[64];
    char TEMPclasse[128];
    char TEMPtrivia[512];

    FILE *fp;                                                       // Este trecho do código  executa o load e a abertura do .txt contendo os dados.
    fp = fopen("DataStar.txt", "r");
    char buff[1024 * 4];
    if(fp != NULL)
        printf("\nStar Data carregado com sucesso!\n");

    while (fgets(buff, 1024 * 4, (FILE *)fp))
    {
        char delim[] = "$";
        char *ptr = strtok(buff, delim);

        int index = 0;
        Lydist=0;
        aux++; //auxilia na correta incerção dos valores "Lydist" no vertor auxiliar "valList".
        while (ptr != NULL)
        {
            if (index == 0)  // Nome da estrela
            {
                strcpy(TEMPnome,ptr);
            }

            else if (index == 1)  // Distancia angular
            {
                strcpy(TEMPdist_ang, ptr);
            }

            else if (index == 2)  // Declinação
            {
                strcpy(TEMPdeclinacao, ptr);
            }

            else if (index == 3)  // Magnitude
            {
                strcpy(TEMPmagnitude, ptr);
            }

            else if (index == 4)  // Magnitude geral
            {
                strcpy(TEMPmagnitudeGeral,ptr);
            }

            else if (index == 5)  // distancia
            {
                Lydist= atoi(ptr);
                insertion(Lydist);
            }

            else if (index == 6)  // Classe
            {
                strcpy(TEMPclasse,ptr);
            }
            else if (index == 7)  // Trivia
            {
				strcpy(TEMPtrivia,ptr);
						insert_chained(H, Lydist, TEMPnome,TEMPdist_ang,TEMPdeclinacao, //Faz a atribuição na Hash após todos os dados da linha do txt terem sido lidos.
								TEMPmagnitude,TEMPmagnitudeGeral,TEMPclasse,TEMPtrivia) ;
				    valList[aux]=Lydist;
            }

            ptr = strtok(NULL, delim);
            index++;

        }

    }
    fclose(fp);

    while (1)
    {
        printf("1. Mostar exemplo de 10 acessos\n2. Mostar exemplo de 100 acessos \n");
        printf("3. Mostar exemplo de 500 acessos\n4. Mostar exemplo de 1000 acessos\n5. Mostar exemplo de 1500 acessos\n");
        printf("6. Mostar exemplo de N acessos\n7. Demonstração de N dados armazenados.\n");
        printf("8. Demonstração de um dado especifico\n9.SAIR\n Digite sua opção:");
        scanf("%d", &ch);

        switch (ch){  	
			case 1:
				Ticks[0] = clock();
				for(i=0; i<10; i++)
				{
					busca_exemplo(valList[i],root->Lydist,root);
				}
				Ticks[1] = clock();
				Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
				printf("Tempo gasto: %g ms. \n", Tempo);
				break;

			case 2:
				Ticks[0] = clock();
				for(i=0; i<100; i++)
				{
					busca_exemplo(valList[i],root->Lydist,root);
				}
				Ticks[1] = clock();
				Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
				printf("Tempo gasto: %g ms. \n", Tempo);
				break;

			case 3:
				Ticks[0] = clock();
				for(i=0; i<500; i++)
				{
					busca_exemplo(valList[i],root->Lydist,root);
				}
				Ticks[1] = clock();
				Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
				printf("Tempo gasto: %g ms. \n", Tempo);
				break;

			case 4:
				Ticks[0] = clock();
				for(i=0; i<1000; i++)
				{
					busca_exemplo(valList[i],root->Lydist,root);
				}
				Ticks[1] = clock();
				Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
				printf("Tempo gasto: %g ms. \n", Tempo);

				break;

			case 5:
				Ticks[0] = clock();
				for(i=0; i<1530; i++)
				{
					busca_exemplo(valList[i],root->Lydist,root);
				}
				Ticks[1] = clock();
				Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
				printf("Tempo gasto: %g ms. \n", Tempo);

				break;
				
			case 6:
				Ticks[0] = clock();
				printf("Digite o valor de acessos a serem efetuados(1~1500)");
				scanf("%d", &input);
				for(i=0; i<input; i++)
				{
					busca_exemplo(valList[i],root->Lydist,root);
				}
				Ticks[1] = clock();
				Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
				printf("Tempo gasto: %g ms. \n", Tempo);
				break;
				
			case 7:
				printf("Digite o numero de dados a serem exemplificados (1~1500)");
				scanf("%d", &input);
				Ticks[0] = clock();
				for(i=1; i<input; i++)
				{
					print_hash(H,valList[i]);
				}
				Ticks[1] = clock();
				Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
				printf("Tempo gasto: %g ms. \n", Tempo);
				break;

			case 8:
			    print_complex(H, 97);
				break;

			case 9:
			    exit(0);
			    break;

			default:
			    printf("Digite uma opçao válida.!!\n");
				break;
			}
	break;
     
    }
}
