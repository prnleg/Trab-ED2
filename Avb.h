#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // T
#define MIN 1

struct BTreeNode
{
    int Lydist[MAX + 1], count;
    struct BTreeNode *linker[MAX + 1];
};

struct BTreeNode *root;

// Cria o nó com todas suas caracteristicas.
struct BTreeNode *createNode(int Lydist, struct BTreeNode *child)
{
    struct BTreeNode *newNode;
    newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->Lydist[1] = Lydist;
    newNode->count = 1;
    newNode->linker[0] = root;
    newNode->linker[1] = child;
    return newNode;
}

// Adiciona um valor para um determinado nó
void addValorAoNo(int Lydist, int pos, struct BTreeNode *node,
                  struct BTreeNode *child)
{
    int j = node->count;
    while (j > pos)
    {
        node->Lydist[j + 1] = node->Lydist[j];
        node->linker[j + 1] = node->linker[j];
        j--;
    }
    node->Lydist[j + 1] = Lydist;
    node->linker[j + 1] = child;
    node->count++;
}

// divide o nó conforme nescessário
void divideNo(int Lydist, int *pval, int pos, struct BTreeNode *node,
              struct BTreeNode *child, struct BTreeNode **newNode)
{
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    j = median + 1;
    while (j <= MAX)
    {
        (*newNode)->Lydist[j - median] = node->Lydist[j];
        (*newNode)->linker[j - median] = node->linker[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN)
    {
        addValorAoNo(Lydist, pos, node, child);
    }
    else
    {
        addValorAoNo(Lydist, pos - median, *newNode, child);
    }
    *pval = node->Lydist[node->count];
    (*newNode)->linker[0] = node->linker[node->count];
    node->count--;
}

// Analiza a situação de um nó para determinar como inserir o valor ao nó.
int AnalizaCondicao(int Lydist, int *pval, struct BTreeNode *node, struct BTreeNode **child)
{
    int pos;
    if (!node)
    {
        *pval = Lydist;
        *child = NULL;
        return 1;
    }

    if (Lydist < node->Lydist[1])
    {
        pos = 0;
    }
    else
    {
        for (pos = node->count;
                (Lydist < node->Lydist[pos] && pos > 1); pos--);

        if (Lydist == node->Lydist[pos])
        {
            printf("%d",node->Lydist[pos]);
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (AnalizaCondicao(Lydist, pval, node->linker[pos], child))
    {
        if (node->count < MAX)
        {
            addValorAoNo(*pval, pos, node, *child);
        }
        else
        {
            divideNo(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Chama os métodos nescessários para se adicionar um valor a um nó
void insertion(int Lydist)
{
    int flag, i;
    struct BTreeNode *child;

    flag = AnalizaCondicao(Lydist, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

// Copia o sucessor de  um nó
void copySuccessor(struct BTreeNode *myNode, int pos)
{
    struct BTreeNode *dummy;
    dummy = myNode->linker[pos];

    for (; dummy->linker[0] != NULL;)
        dummy = dummy->linker[0];
    myNode->Lydist[pos] = dummy->Lydist[1];
}

// Remove o valor de um determinado nó
void removeValor(struct BTreeNode *myNode, int pos)
{
    int i = pos + 1;
    while (i <= myNode->count)
    {
        myNode->Lydist[i - 1] = myNode->Lydist[i];
        myNode->linker[i - 1] = myNode->linker[i];
        i++;
    }
    myNode->count--;
}

// Faz a mudança a direita.
void mudancaAdireita(struct BTreeNode *myNode, int pos)
{
    struct BTreeNode *x = myNode->linker[pos];
    int j = x->count;

    while (j > 0)
    {
        x->Lydist[j + 1] = x->Lydist[j];
        x->linker[j + 1] = x->linker[j];
    }
    x->Lydist[1] = myNode->Lydist[pos];
    x->linker[1] = x->linker[0];
    x->count++;

    x = myNode->linker[pos - 1];
    myNode->Lydist[pos] = x->Lydist[x->count];
    myNode->linker[pos] = x->linker[x->count];
    x->count--;
    return;
}

// Faz a mudança a esquerda.
void mudancaAesquerda(struct BTreeNode *myNode, int pos)
{
    int j = 1;
    struct BTreeNode *x = myNode->linker[pos - 1];

    x->count++;
    x->Lydist[x->count] = myNode->Lydist[pos];
    x->linker[x->count] = myNode->linker[pos]->linker[0];

    x = myNode->linker[pos];
    myNode->Lydist[pos] = x->Lydist[1];
    x->linker[0] = x->linker[1];
    x->count--;

    while (j <= x->count)
    {
        x->Lydist[j] = x->Lydist[j + 1];
        x->linker[j] = x->linker[j + 1];
        j++;
    }
    return;
}

// Une os nós se nescessário.
void une_nos(struct BTreeNode *myNode, int pos)
{
    int j = 1;
    struct BTreeNode *x1 = myNode->linker[pos], *x2 = myNode->linker[pos - 1];

    x2->count++;
    x2->Lydist[x2->count] = myNode->Lydist[pos];
    x2->linker[x2->count] = myNode->linker[0];

    while (j <= x1->count)
    {
        x2->count++;
        x2->Lydist[x2->count] = x1->Lydist[j];
        x2->linker[x2->count] = x1->linker[j];
        j++;
    }

    j = pos;
    while (j < myNode->count)
    {
        myNode->Lydist[j] = myNode->Lydist[j + 1];
        myNode->linker[j] = myNode->linker[j + 1];
        j++;
    }
    myNode->count--;
    free(x1);
}

// Ajusta a árvore.
void ajusta_arvore(struct BTreeNode *myNode, int pos)
{
    if (!pos)
    {
        if (myNode->linker[1]->count > MIN)
        {
            mudancaAesquerda(myNode, 1);
        }
        else
        {
            une_nos(myNode, 1);
        }
    }
    else
    {
        if (myNode->count != pos)
        {
            if (myNode->linker[pos - 1]->count > MIN)
            {
                mudancaAdireita(myNode, pos);
            }
            else
            {
                if (myNode->linker[pos + 1]->count > MIN)
                {
                    mudancaAesquerda(myNode, pos + 1);
                }
                else
                {
                    une_nos(myNode, pos);
                }
            }
        }
        else
        {
            if (myNode->linker[pos - 1]->count > MIN)
                mudancaAdireita(myNode, pos);
            else
                une_nos(myNode, pos);
        }
    }
}

// Apaga o valor contido em um nó, e reorganiza a arvore.
int apaga_valo_no(int Lydist, struct BTreeNode *myNode)
{
    int pos, flag = 0;
    if (myNode)
    {
        if (Lydist < myNode->Lydist[1])
        {
            pos = 0;
            flag = 0;
        }
        else
        {
            for (pos = myNode->count; (Lydist < myNode->Lydist[pos] && pos > 1); pos--)
                ;
            if (Lydist == myNode->Lydist[pos])
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
        if (flag)
        {
            if (myNode->linker[pos - 1])
            {
                copySuccessor(myNode, pos);
                flag = apaga_valo_no(myNode->Lydist[pos], myNode->linker[pos]);
                if (flag == 0)
                {
                    printf("Given data is not present in B-Tree\n");
                }
            }
            else
            {
                removeValor(myNode, pos);
            }
        }
        else
        {
            flag = apaga_valo_no(Lydist, myNode->linker[pos]);
        }
        if (myNode->linker[pos])
        {
            if (myNode->linker[pos]->count < MIN)
                ajusta_arvore(myNode, pos);
        }
    }
    return flag;
}

//Executa a operação de exclusão no determinado nó, reorganizando a arvore ao final.
void Delete (int Lydist, struct BTreeNode *myNode)
{
    struct BTreeNode *tmp;
    if (!apaga_valo_no(Lydist, myNode))
    {
        printf("Not present\n");
        return;
    }
    else
    {
        if (myNode->count == 0)
        {
            tmp = myNode;
            myNode = myNode->linker[0];
            free(tmp);
        }
    }
    root = myNode;
    return;
}

void print_arvore(struct BTreeNode *myNode)
{
    int i;
    if (myNode)
    {
        for (i = 0; i < myNode->count; i++)
        {
            print_arvore(myNode->linker[i]);
            printf("%d ", myNode->Lydist[i + 1]);
        }
        print_arvore(myNode->linker[i]);
    }
}

void busca_exemplo(int Lydist, int *pos, struct BTreeNode *myNode)
{

    if (!myNode)
    {
        return;
    }

    if (Lydist < myNode->Lydist[1])
    {
        *pos = 0;
    }
    else
    {
        for (*pos = myNode->count; (Lydist < myNode->Lydist[*pos] && *pos > 1); (*pos)--);

        if (Lydist == myNode->Lydist[*pos])
        {
            //printf("%d está presente", Lydist);      //descomente para exibir os dados carregados
            return;
        }
    }
    busca_exemplo(Lydist, pos, myNode->linker[*pos]);
    return;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
