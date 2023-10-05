#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structs do programa */
typedef struct 
{
    char nomeProduto[30];
    float valorProduto;
} Produto;

typedef struct
{
    char NomeFilial[50];
    Produto **MatrizProdutosTrimestre;
} Filial;

/* Métodos do Cubo */

Produto*** AlocaCuboProdutos(int QuantidadeFiliais, int QuantidadeProdutos)
{
    Produto ***NovoCuboProdutos = (Produto ***)malloc(4 * sizeof(Produto **));
    if(NovoCuboProdutos == NULL) return NULL;

    for (int i = 0; i < 4; i++) {
        NovoCuboProdutos[i] = (Produto **)malloc(QuantidadeFiliais * sizeof(Produto *));
        if(NovoCuboProdutos[i] == NULL) return NULL;

        for (int j = 0; j < QuantidadeFiliais; j++) {
            NovoCuboProdutos[i][j] = (Produto *)malloc(QuantidadeProdutos * sizeof(Produto));
            if(NovoCuboProdutos[i][j] == NULL) return NULL;
        }
    }

    return NovoCuboProdutos;
}

Filial* AlocaListaFiliais(int QuantidadeFiliais, Produto ***CuboProdutos)
{
    Filial *novaListaFiliais;
    novaListaFiliais = (Filial *)malloc(QuantidadeFiliais*sizeof(Filial));
    if(novaListaFiliais == NULL) return NULL;

    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        novaListaFiliais[i].MatrizProdutosTrimestre = (Produto **)malloc(4 * sizeof(Produto*));
        for(int j = 0; j < 4; j++)
        {
            novaListaFiliais[i].MatrizProdutosTrimestre[j] = CuboProdutos[j][i];
        }
    }
    return novaListaFiliais;

    //ListaFiliais[Nº Filial].MatrizProdutosTrimestre[TrimestreAno][Nº Produto]
}

/* Métodos Menu */
void Headder(int qntProdutos, int qntFiliais)
{
    printf("\t*****************************************\n");
    printf("\t*\t\t\t\t\t*\n");
    printf("\t*\tSISTEMA DE GESTAO MARKET++\t*\n");
    printf("\t*\t\t\t\t\t*\n");
    printf("\t*****************************************\n");
    if(qntProdutos > 0 && qntFiliais > 0)
    {
        printf("\nProdutos:%d\n", qntProdutos);
        printf("Filiais:%d", qntFiliais);
    }
    printf("\n______________________________________________________\n");
}

void Erro(char msg[])
{
    system("cls");
    system("color 4F");
    printf("%s\n", msg);
}

/* Métodos para inputs */

void LeituraQuantidadeFiliais(int *qntFiliais)
{
    int validacao = 1;
    do {
        system("cls");
        Headder(0,0);
        if(!validacao)
        {
            printf("Numero anterior invalido!Digite novamente.\n");
        }
        validacao = 1;
        printf("Digite a quantidade de filiais: ");
        scanf(" %d", qntFiliais);
        if(*qntFiliais <= 0) validacao = 0;
    } while(!validacao);
}
void LeituraQuantidadeProdutos(int *qntProdutos)
{
    int validacao = 1;
    do {
        system("cls");
        Headder(0,0);
        if(!validacao)
        {
            printf("Numero anterior invalido!Digite novamente.\n");
        }
        validacao = 1;
        printf("Digite a quantidade de produtos no catalogo: ");
        scanf(" %d", qntProdutos);
        if(*qntProdutos <= 0) validacao = 0;
    } while(!validacao);
}

int main()
{
    int QuantidadeProdutos = 0;
    int QuantidadeFiliais = 0;
    Filial *ListaFiliais;

    LeituraQuantidadeFiliais(&QuantidadeFiliais);
    LeituraQuantidadeProdutos(&QuantidadeProdutos);

    Produto ***CuboProdutos = AlocaCuboProdutos(QuantidadeFiliais,QuantidadeProdutos);
    if(CuboProdutos == NULL)
    {
        Erro("Nao foi possivel alocar o cubo de produtos!");
        return 0;
    }

    ListaFiliais = AlocaListaFiliais(QuantidadeFiliais,CuboProdutos);
    if(ListaFiliais == NULL)
    {
        Erro("Nao foi possivel alocar a lista de produtos!");
        return 0;
    }



    // Preenchendo o cubo com valores de exemplo
    for (int t = 0; t < 4; t++) {
        for (int f = 0; f < QuantidadeFiliais; f++) {
            for (int p = 0; p < QuantidadeProdutos; p++) {
                snprintf(CuboProdutos[t][f][p].nomeProduto, 30, "Produto%d_T%d_F%d", p + 1, t + 1, f + 1);
                CuboProdutos[t][f][p].valorProduto = (p + 1) * (t + 1) * (f + 1) * 10.0; // Exemplo de valor
            }
        }
    }

    // Acesso aos dados do cubo
    printf("Exemplo de acesso: Nome do produto no 2 trimestre, 1 filial, 3 produto: %s\n", CuboProdutos[1][0][2].nomeProduto);
    printf("Exemplo de acesso: Valor do produto no 3 trimestre, 2 filial, 4 produto: %.2f\n", CuboProdutos[2][1][3].valorProduto);
    printf("Exemplo de acesso: Valor do produto no 3 trimestre, 2 filial, 4 produto: %.2f\n", ListaFiliais[1].MatrizProdutosTrimestre[2][3].valorProduto);

    return 0;
}