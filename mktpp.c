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

/* Variáveis globais no escopo da aplicação*/
int QuantidadeProdutosCatalogo = 0;
int QuantidadeFiliais = 0;
Produto ***CuboProdutos;
Filial *ListaFiliais;

/* Metodos para o Cubo */

int AlocarCuboProdutos()
{
    //Primeira dimensão = Camada de Trimestres do ano
    CuboProdutos = (Produto ***)malloc(4 * sizeof(Produto**));
    if(CuboProdutos == NULL) return 0;

    for(int i = 0; i < 4; i++)
    {
        // Segunda dimensão = Camada de Filiais
        *(CuboProdutos+i) = (Produto **)malloc(QuantidadeFiliais * sizeof(Produto*));
        if(*(CuboProdutos+i) == NULL) return 0;

        for(int j = 0; j < QuantidadeFiliais; j++)
        {
            // Terceira dimensõa = Camda de produtos
            *(*(CuboProdutos+i)+j) = (Produto *)malloc(QuantidadeProdutosCatalogo * sizeof(Produto));
            if(*(*(CuboProdutos+i)+j) == NULL) return 0;
        }
    }
    return 1;
}

int AlocarListaFiliais()
{
    ListaFiliais = (Filial *)malloc(QuantidadeFiliais * sizeof(Filial));
    if(ListaFiliais == NULL) return 0;
    for(int i = 0; i < QuantidadeFiliais; i++)
        for(int j = 0; j < 4; j++)
            ListaFiliais[i].MatrizProdutosTrimestre[j] = (((CuboProdutos)+i)+j);
    return 1;
}


/* Metodos auxiliares */
int getStringLength(char text[255])
{
    int i;
    for(i = 0; text[i]!='\0'; i++);
    return i;
}

/* Métodos de menu */
void Headder()
{
    printf("\t*****************************************\n");
    printf("\t*\t\t\t\t\t*\n");
    printf("\t*\tSISTEMA DE GESTAO MARKET++\t*\n");
    printf("\t*\t\t\t\t\t*\n");
    printf("\t*****************************************\n");
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


int InicializaSistema()
{
    int ValidacaoInput = 1;
    int ValidacaoCubo = 0;
    int ValidaListaFiliais = 0;
    do
    {
        system("cls");
        Headder();
        if(!ValidacaoInput)
        {
            printf("Valor anterior invalido!\n\n");
        }
        ValidacaoInput = LeituraQuantidadeProdutos();
    }while(!ValidacaoInput);

    do
    {
        system("cls");
        Headder();
        if(!ValidacaoInput)
        {
            printf("Valor anterior invalido!\n\n");
        }
        ValidacaoInput = LeituraQuantidadeFiliais();
    }while(!ValidacaoInput);

    ValidacaoCubo = AlocarCuboProdutos();
    if(!ValidacaoCubo)
    {
        system("cls");
        system("color 4F");
        printf("Erro na Alocacao do Cubo de produtos!");
        return 0;
    }

    ValidaListaFiliais = AlocarListaFiliais();
    if(!ValidacaoCubo)
    {
        system("cls");
        system("color 4F");
        printf("Erro na Alocacao da lista de Filiaias!");
        return 0;
    }    
    return 1;
}


int main()
{
    int ValidadorDeRotinas = 0;
    ValidadorDeRotinas = InicializaSistema();
    if(!ValidadorDeRotinas) return 0;
    return 0;
}