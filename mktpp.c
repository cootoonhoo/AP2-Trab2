#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structs do programa */
typedef struct 
{
    char NomeProduto[30];
    float ValorProduto;
    int quantidadeVendas
} Produto;

typedef struct
{
    char NomeFilial[50];
    Produto **MatrizProdutosTrimestre;
} Filial;

/* Variáveis Globais */
int QuantidadeProdutos = 0;
int QuantidadeFiliais = 0;
Produto ***CuboProdutos;
Filial *ListaFiliais;
char **listaNomeProdutos;
char **listaNomeFiliais;

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

char** AlocaListaNomeProdutos(int QuantidadeProdutos)
{
    char **novaListaNomes = (char**)malloc(QuantidadeProdutos * sizeof(char*));
    if(novaListaNomes == NULL) return NULL;

    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        novaListaNomes[i] = (char *)malloc(30 * sizeof(char));
        if(novaListaNomes[i] == NULL) return NULL;
    }
    return novaListaNomes;
}

char** AlocaListaNomeFiliais(int QuantidadeFiliais)
{
    char **novaListaNomes = (char**)malloc(QuantidadeFiliais * sizeof(char*));
    if(novaListaNomes == NULL) return NULL;

    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        novaListaNomes[i] = (char *)malloc(50 * sizeof(char));
        if(novaListaNomes[i] == NULL) return NULL;
    }
    return novaListaNomes;
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

void LeituraQuantidadeFiliais()
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
        scanf(" %d", &QuantidadeFiliais);
        if(QuantidadeFiliais <= 0) validacao = 0;
    } while(!validacao);
}

void LeituraQuantidadeProdutos()
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
        scanf(" %d", &QuantidadeProdutos);
        if(QuantidadeProdutos <= 0) validacao = 0;
    } while(!validacao);
}

void LeituraListaProdutos()
{
    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        setbuf(stdin, 0);
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("Digite o nome do produto %d: ", i+1);
        fgets(listaNomeProdutos[i],30,stdin);
    }
}

void LeituraNomeFiliais()
{
    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        setbuf(stdin, 0);
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("Digite o nome da Filial numero %d: ", i+1);
        fgets(listaNomeFiliais[i],50,stdin);
    }
}

void PreencherDadosCubo()
{
    system("COLOR 1F");
    printf("IMPLEMENTAR DADOS CUBOS")
    system("pause");
}

/* Metodos do programa - Organização */
int IniciarSistema()
{
    LeituraQuantidadeFiliais();
    LeituraQuantidadeProdutos();

    CuboProdutos = AlocaCuboProdutos(QuantidadeFiliais,QuantidadeProdutos);
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

    listaNomeProdutos = AlocaListaNomeProdutos(QuantidadeProdutos);
    if(listaNomeProdutos == NULL)
    {
        Erro("Nao foi possivel alocar a lista de nome dos produtos!");
        return 0;
    }

    listaNomeFiliais = AlocaListaNomeFiliais(QuantidadeFiliais);
    if(listaNomeFiliais == NULL)
    {
        Erro("Nao foi possivel alocar a lista de nome dos produtos!");
        return 0;
    }

    LeituraListaProdutos();
    LeituraNomeFiliais();
    PreencherDadosCubo();
    return 1;
}

int main()
{
    int ControleDeFluxo = 0;
    ControleDeFluxo = IniciarSistema();
    if(!ControleDeFluxo) return 0;

    // Preenchendo o cubo com valores de exemplo
    for (int t = 0; t < 4; t++) {
        for (int f = 0; f < QuantidadeFiliais; f++) {
            for (int p = 0; p < QuantidadeProdutos; p++) {
                snprintf(CuboProdutos[t][f][p].NomeProduto, 30, "Produto%d_T%d_F%d", p + 1, t + 1, f + 1);
                CuboProdutos[t][f][p].ValorProduto = (p + 1) * (t + 1) * (f + 1) * 10.0; // Exemplo de valor
            }
        }
    }

    // Acesso aos dados do cubo
    printf("Exemplo de acesso: Nome do produto no 2 trimestre, 1 filial, 3 produto: %s\n", CuboProdutos[0][0][0].NomeProduto);
    printf("Exemplo de acesso: Valor do produto no 3 trimestre, 2 filial, 4 produto: %.2f\n", CuboProdutos[0][0][0].ValorProduto);
    printf("Valor Produto pela ListaFiliais: %.2f\n", ListaFiliais[0].MatrizProdutosTrimestre[0][0].ValorProduto);

    return 0;
}