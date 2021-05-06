#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura da Hash
typedef struct node
{
    char nome[64];
    char distancia_ang[128];
    char declinacao[128];
    char magnitude[32];
    char magnitudeGeral[32];
    char classe[256];
    char trivia[1024];
    struct node *next;
} Node;

typedef struct hash
{
    int M; //Número de entradas no hash.
    int N; //Número de chaves armazenadas.
    Node **list; //Vetor de listas.
} Hash;

void print_hash (Hash *H,int h)
{

    Node *aux;
    aux=H->list[h];
    printf ("\n");
    printf ("| %s |", aux->nome);
    printf ("| %s |", aux->distancia_ang);
    printf ("| %s |", aux->declinacao);
    printf ("| %s |", aux->magnitude);
    printf ("| %s |", aux->magnitudeGeral);
    printf ("|%d|",h);
    printf ("| %s |", aux->classe);
    printf ("| %s |", aux->trivia);

}

void free_hash (Hash *H)
{
    int h;
    for (h = 0; h < H->M; h++)
    {
        free (H->list[h]);
    }
    free (H);
}
//cria a hash
Hash* create_hash (int M)
{
    Hash *H = (Hash *)malloc(sizeof(Hash));
    H->M = M;
    H->N = 0;
    H->list = (Node **)malloc(sizeof(Node*)*M);
    int h;
    for (h = 0; h < H->M; h++)
    {
        H->list[h] = NULL;
    }
    return H;
}
//insere na hash
void insert_chained (Hash *H,int h,char *nome,char *distancia_ang,char *declinacao,
                     char *magnitude,char *magnitudeGeral,char *classe,char *trivia)
{

    Node *n = (Node *)malloc(sizeof(Node));

    strcpy(n->nome,nome);
    strcpy(n->distancia_ang,distancia_ang);
    strcpy(n->declinacao,declinacao);
    strcpy(n->magnitude,magnitude);
    strcpy(n->magnitudeGeral,magnitudeGeral);
    strcpy(n->classe,classe);
    strcpy(n->trivia,trivia);
    n->next = H->list[h];
    H->list[h] = n; /*n é a nova cabeça!*/
    H->N++; /*incremento do num. de chaves!*/
}

// print de forma organizada os dados.
void print_complex (Hash *H,int h)
{
    Node *aux;
    aux=H->list[h];
    printf ("\n");


    printf ("Nome da estrela:    \t\t\t\t\t\t\t\t\t\t\t    %s\n", aux->nome);
    printf ("Distancia angular da estrela: \t\t\t\t\t\t\t\t %s\n", aux->distancia_ang);
    printf ("Declinação da estrela:        \t\t\t\t\t\t\t\t %s\n", aux->declinacao);
    printf ("Magnitude(Brilho visível da terra: \t\t\t\t\t\t\t\t %s\n", aux->magnitude);
    printf ("Magnitude geral(Brilho visível a uma distancia de 10 Parsecs:\t %s\n", aux->magnitudeGeral);
    printf ("Distancia em anos luz da terra:\t\t\t\t\t\t\t\t\t\t %d\n",h);
    printf ("Classe da estrela em sua galáxia:  \t\t\t\t\t\t\t\t  %s\n", aux->classe);
    printf ("Peculiaridade sobre a estrela: \t\t \t\t\t\t\t\t %s\n\n\n ", aux->trivia);

    printf("   %s\n",aux->nome);
    printf("    @@@@@@\n   @@@@@@@@\n @@@@@@@@@@@\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tTerra\n@@@@@@@@@@@@@ \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t @@@ \n");
    printf("@@@@@@@@@@@@@\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t@@@@@\n @@@@@@@@@@@\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t@@@@@\n   @@@@@@@@\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t @@@ \n    @@@@@@------------ ");
    printf("A viagem da terra até %s demoraria %d anos com a tecnologia atual --------------\n",aux->nome,(h*300000)/70000);
    printf("\n");

}

