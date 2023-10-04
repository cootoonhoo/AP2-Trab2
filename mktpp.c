#include <stdio.h>
#include <stdlib.h>

/* Structs do programa */
typedef struct 
{
    char nomeProduto[30];
    float valorProduto;
} Produto;

typedef struct
{
    char NomeFilia[50];
    Produto *listaProdutos;
} Filial;

/* Variáveis globais no escopo da aplicação*/
int QuantidadeProdutosCatalogo = 0;
int QuantidadeFiliais = 0;

/* Métodos de menu */
void HeadderBoasVindas()
{
    printf("\t*****************************************\n");
    printf("\t*\t\t\t\t\t*\n");
    printf("\t*\tSISTEMA DE GESTAO MARKET++\t*\n");
    printf("\t*\t\t\t\t\t*\n");
    printf("\t*****************************************\n");
    printf("\n______________________________________________________\n");
}

void HeadderSistema(char text[])
{
    printf("\t*****************************************\n");
    printf("\t*\t\t\t\t\t*\n");
    printf("\t*\t\t %s \t\t\t*\n", text);
    printf("\t*\t\t\t\t\t*\n");
    printf("\t*****************************************\n");
    printf("\nProdutos:%d\n", QuantidadeProdutosCatalogo);
    printf("Filiais:%d", QuantidadeFiliais);
    printf("\n______________________________________________________\n");
}

int LeituraQuantidadeFiliais()
{
    printf("Digite a quantidade de filiais: ");
    scanf(" %d", &QuantidadeFiliais);
    if(QuantidadeFiliais > 0) return 1;
    else return 0;
}

int LeituraQuantidadeProdutos()
{
    printf("Digite a quantidade de produtos catalogados: ");
    scanf(" %d", &QuantidadeProdutosCatalogo);
    if(QuantidadeProdutosCatalogo > 0) return 1;
    else return 0;
}

void InicializaSistema()
{
    int ValidacaoInput = 1;
    do
    {
        system("cls");
        HeadderBoasVindas();
        if(!ValidacaoInput)
        {
            printf("Valor anterior invalido!\n\n");
        }
        ValidacaoInput = LeituraQuantidadeProdutos();
    }while(!ValidacaoInput);

    do
    {
        system("cls");
        HeadderBoasVindas();
        if(!ValidacaoInput)
        {
            printf("Valor anterior invalido!\n\n");
        }
        ValidacaoInput = LeituraQuantidadeFiliais();
    }while(!ValidacaoInput);
}


int main()
{
    InicializaSistema();
        system("cls");
    HeadderSistema("Menu");
    return 0;
}