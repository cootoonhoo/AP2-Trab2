#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: Fazer a verificação no começo se os valores são nulos!
//TODO: Verificar se os inputs não são vazios

/* Structs do programa */
typedef struct 
{
    char NomeProduto[30];
    float quantidadeVendas;
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
int foiResetado;

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

    //CuboProdutos[TrimestreAno][Nº Filial][Nº Produto]
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

void LiberarMemoria() {
    //Arrumar esse código, falta muita coisa pra limpar ainda kkk
    for (int i = 0; i < 4; i++) {
        free(CuboProdutos[i]);
    }

    for (int i = 0; i < QuantidadeFiliais; i++) {
        for (int j = 0; j < 4; j++) {
            free(ListaFiliais[i].MatrizProdutosTrimestre[j]);
        }
        free(ListaFiliais[i].MatrizProdutosTrimestre);
    }
    free(ListaFiliais);

    for (int i = 0; i < QuantidadeProdutos; i++) {
        free(listaNomeProdutos[i]);
    }
    free(listaNomeProdutos);

    for (int i = 0; i < QuantidadeFiliais; i++) {
        free(listaNomeFiliais[i]);
    }
    free(listaNomeFiliais);
}

/* Features do programa */
void InserirNovaFilial() {
    char nomeFilial[50];
    setbuf(stdin, 0);
    system("cls");
    Headder(QuantidadeProdutos, QuantidadeFiliais);
    printf("\n \t\t--- Inserir nova filial ---\n\n");
    printf("Digite o nome da nova filial: ");
    fgets(nomeFilial, 50, stdin);

     for(int i = 0; i < QuantidadeFiliais; i++)
    {
        if(strcmp(nomeFilial,listaNomeFiliais[i]) == 0)
        {
            system("cls");
            Headder(QuantidadeProdutos, QuantidadeFiliais);
            printf("\n \t\t--- Inserir nova filial ---\n\n");
            printf("Esse nome ja esta sendo utilizado!\n\n");
            system("pause");
            return;
        }
    }

    QuantidadeFiliais++;

    // Alocar memória para a nova filial na lista de nomes de filiais
    listaNomeFiliais = (char **)realloc(listaNomeFiliais, QuantidadeFiliais * sizeof(char*));
    listaNomeFiliais[QuantidadeFiliais - 1 ] = malloc(50 * sizeof(char));
    strcpy(listaNomeFiliais[QuantidadeFiliais - 1], nomeFilial);

    for(int i = 0; i < 4; i++)
    {
        CuboProdutos[i] = (Produto **)realloc(CuboProdutos[i], QuantidadeFiliais * sizeof(Produto *));
        CuboProdutos[i][QuantidadeFiliais - 1] = (Produto *)malloc(QuantidadeProdutos * sizeof(Produto));
        for(int j = 0; j < QuantidadeProdutos; j++)
        {
            strcpy(CuboProdutos[i][QuantidadeFiliais - 1 ][j].NomeProduto, listaNomeProdutos[j]);
            CuboProdutos[i][QuantidadeFiliais - 1 ][j].quantidadeVendas = 0.0;
        }
    }

    ListaFiliais = (Filial *)realloc(ListaFiliais, QuantidadeFiliais * sizeof(Filial));
    strcpy(ListaFiliais[QuantidadeFiliais - 1].NomeFilial, listaNomeFiliais[QuantidadeFiliais - 1]);

    ListaFiliais[QuantidadeFiliais - 1].MatrizProdutosTrimestre = malloc(4 * sizeof(Produto*));
    for (int i = 0; i < 4; i++) 
        ListaFiliais[QuantidadeFiliais - 1].MatrizProdutosTrimestre[i] = &CuboProdutos[i][QuantidadeFiliais - 1][0];
    
    system("cls");
    Headder(QuantidadeProdutos, QuantidadeFiliais);
    printf("\n \t\t--- Inserir nova filial ---\n\n");
    printf("Nova filial inserida com sucesso!\n\n");
    system("pause");
}

void InserirNovoProduto() {
    char nomeProduto[30];
    setbuf(stdin, 0);
    system("cls");
    Headder(QuantidadeProdutos, QuantidadeFiliais);
    printf("\n \t\t--- Inserir novo produto ---\n\n");
    printf("Digite o nome do novo produto: ");
    fgets(nomeProduto, 30, stdin);

    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        if(strcmp(nomeProduto,listaNomeProdutos[i]) == 0)
        {
            system("cls");
            Headder(QuantidadeProdutos, QuantidadeFiliais);
            printf("\n \t\t--- Inserir novo produto ---\n\n");
            printf("Esse produto ja existe!\n\n");
            system("pause");
            return;
        }
    }

    QuantidadeProdutos++;

    listaNomeProdutos = (char **)realloc(listaNomeProdutos, QuantidadeProdutos * sizeof(char*));
    listaNomeProdutos[QuantidadeProdutos - 1] = malloc(30 * sizeof(char));
    strcpy(listaNomeProdutos[QuantidadeProdutos - 1], nomeProduto);
    
   
    
    system("cls");
    Headder(QuantidadeProdutos, QuantidadeFiliais);
    printf("\n \t\t--- Inserir novo produto ---\n\n");
    printf("Novo produto inserido com sucesso!\n\n");
    system("pause");
}

void RemoverProduto() {
    if(QuantidadeProdutos == 1)
    {
        system("cls");
        Headder(QuantidadeProdutos, QuantidadeFiliais);
        printf("\n \t\t--- Remover produto ---\n\n");
        printf("Impossivel deixar 0 produtos no sistema!E necessario haver pelo menos 1 produto.\n\n"); 
        system("pause");
        return;
    }

    int indiceProduto = -1;
    char nomeProduto[30];

    system("cls");
    Headder(QuantidadeProdutos, QuantidadeFiliais);
    printf("\n \t\t--- Remover produto ---\n\n");
    printf("Lista de produtos:\n");
    for (int i = 0; i < QuantidadeProdutos; i++) {
        printf(" - %s", listaNomeProdutos[i]);
    }
    setbuf(stdin, 0);
    printf("\nDigite o nome do produto: ");
    fgets(nomeProduto, 30, stdin);
    
    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        if(strcmp(nomeProduto,listaNomeProdutos[i]) == 0)
            indiceProduto = i;
    }

    if(indiceProduto == -1)
    {
        system("cls");
        Headder(QuantidadeProdutos, QuantidadeFiliais);
        printf("\n \t\t--- Remover produto ---\n\n");
        printf("Nao foi possivel encontrar o produto.\n\n"); 
        system("pause");
        return;
    }
    
    QuantidadeProdutos--;
    if(indiceProduto != QuantidadeProdutos)
    {
        for(int i = indiceProduto; i < QuantidadeProdutos; i++)
        {
            //Rearranjando ListaNomeProdutos
            strcpy(listaNomeProdutos[i], listaNomeProdutos[i+1]);
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < QuantidadeFiliais; k++)
                {
                    //Rearranjando Produtos no Cubo
                    CuboProdutos[j][k][i].quantidadeVendas = CuboProdutos[j][k][i+1].quantidadeVendas;
                    strcpy(CuboProdutos[j][k][i].NomeProduto, CuboProdutos[j][k][i+1].NomeProduto);
                }
        }
    }

    //Limpar ListaNomeProdutos
    listaNomeProdutos = (char **)realloc(listaNomeProdutos, QuantidadeProdutos);

    //Limpar CuboProdutos
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < QuantidadeFiliais; j++) {
            CuboProdutos[i][j] = (Produto *)realloc(CuboProdutos[i][j],QuantidadeProdutos * sizeof(Produto));
        }
    system("cls");
    Headder(QuantidadeProdutos, QuantidadeFiliais);
    printf("\n \t\t--- Remover produto ---\n\n");
    printf("Produto removido com sucesso!\n\n");
    system("pause");
}

void RemoverFilial() {
    if(QuantidadeFiliais == 1)
    {
        system("cls");
        Headder(QuantidadeProdutos, QuantidadeFiliais);
        printf("\n \t\t--- Remover filial ---\n\n");
        printf("Impossivel deixar 0 filiais no sistema!E necessario haver pelo menos 1 filial.\n\n"); 
        system("pause");
        return;
    }

    char nomeFilial[50];
    int indiceFilial = -1;
    system("cls");
    Headder(QuantidadeProdutos, QuantidadeFiliais);
    printf("\n \t\t--- Remover filial ---\n\n");
    printf("Lista de filiais: \n");
    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        printf(" - %s", listaNomeFiliais[i]);
    }
    printf("Digite o nome da filial:");
    setbuf(stdin, 0);
    fgets(nomeFilial, 50, stdin);

    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        if(strcmp(nomeFilial,listaNomeFiliais[i]) == 0)
        {
            indiceFilial = i;
            break;
        }
    }

    if(indiceFilial == -1)
    {
        system("cls");
        Headder(QuantidadeProdutos, QuantidadeFiliais);
        printf("\n \t\t--- Remover filial ---\n\n");
        printf("Nao foi possivel encontrar a filial.\n\n"); 
        system("pause");
        return;
    }

    QuantidadeFiliais--;
    if(indiceFilial != QuantidadeFiliais)
    {
        for(int i = indiceFilial; i < QuantidadeFiliais; i++)
        {
            strcpy(listaNomeFiliais[i],listaNomeFiliais[i+1]);
            for(int j = 0; j < 4; j++)
            {
                CuboProdutos[i][j] = CuboProdutos[i][j+1];
            }
        }
    }

    //Limpar listaNomeFiliais
    listaNomeFiliais = (char **)realloc(listaNomeFiliais, QuantidadeFiliais);

    //Limpar CuboProdutos
    for (int i = 0; i < 4; i++)
        CuboProdutos[i] = (Produto **)realloc(CuboProdutos[i],QuantidadeFiliais * sizeof(Produto *));
    system("cls");
    Headder(QuantidadeProdutos, QuantidadeFiliais);
    printf("\n \t\t--- Remover filial ---\n\n");
    printf("Filial removida com sucesso!\n\n");
    system("pause");
}

void ReiniciarSistema(){
    //Função adicional
    printf("Coneçlar Sistema Reniciado com sucesso\n");
    LiberarMemoria();
    QuantidadeProdutos = 0;
    QuantidadeFiliais = 0;
    printf("Sistema Reniciado com sucesso\n");
}

void VendaProdutoTrimestre()
{
    int NumTrimestre = 0, indiceProduto = 0, validaProduto = 0;
    float vendas;
    char NomeProd[30];
    do
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t--- Venda de produto no trimeste ---\n\n");
        if(NumTrimestre < 0 || NumTrimestre > 3)
            printf("Numero anterior invalido! Digite novamente.\n");
        printf("Digite o numero do trimestre(1,2,3 ou 4): ");
        scanf(" %d", &NumTrimestre);
        NumTrimestre--;
    } while (NumTrimestre < 0 || NumTrimestre > 3);

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Venda de produto no trimeste ---\n\n");
    printf("Lista de produtos: \n");
    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        printf(" - %s", listaNomeProdutos[i]);
    }
    setbuf(stdin, 0);
    printf("Digite o nome do produto: ");
    fgets(NomeProd,30,stdin);

    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        if(strcmp(NomeProd,listaNomeProdutos[i]) == 0)
        {
            validaProduto = 1;
            indiceProduto = i;
            break;
        }
    }

    if(!validaProduto)
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t--- Venda de produto no trimeste ---\n\n");
        printf("Produto nao encontrado!\n\n");
        system("pause");
        return;
    }

    //Registrando vendas em cada filial
    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t--- Venda de produto no trimeste ---\n\n");
        printf("Digite o valor(R$) de vendas feitas na filial %s", ListaFiliais[i].NomeFilial);
        scanf(" %f", &vendas);
        CuboProdutos[NumTrimestre][i][indiceProduto].quantidadeVendas += vendas;
    }

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Venda de produto no trimeste ---\n\n");
    printf("Vendas registradas com suecsso!\n\n");
    system("pause");
}

void VendaProdutoFilial()
{
    int validaFilial = 0, indiceFilial = 0, indiceProduto = 0, validaProduto = 0;
    float vendas;
    char NomeProd[30], NomeFilial[50];

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Venda de produto na filial ---\n\n");
    printf("Lista de filiais: \n");
    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        printf(" - %s", listaNomeFiliais[i]);
    }
    setbuf(stdin, 0);
    printf("Digite o nome da filial: ");
    fgets(NomeFilial,50,stdin);

    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        if(strcmp(NomeFilial,listaNomeFiliais[i]) == 0)
        {
            validaFilial = 1;
            indiceFilial = i;
            break;
        }
    }

    if(!validaFilial)
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t--- Venda de produto na filial ---\n\n");
        printf("Filial nao encontrada!\n\n");
        system("pause");
        return;
    }

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Venda de produto na filial ---\n\n");
    printf("Lista de produtos: \n");
    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        printf(" - %s", listaNomeProdutos[i]);
    }
    setbuf(stdin, 0);
    printf("Digite o nome do produto: ");
    fgets(NomeProd,30,stdin);

    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        if(strcmp(NomeProd,listaNomeProdutos[i]) == 0)
        {
            validaProduto = 1;
            indiceProduto = i;
            break;
        }
    }

    if(!validaProduto)
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t--- Venda de produto no trimeste ---\n\n");
        printf("Produto nao encontrado!\n\n");
        system("pause");
        return;
    }

    //Registrando vendas em cada trimestre
    for(int i = 0; i < 4; i++)
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t--- Venda de produto no trimeste ---\n\n");
        printf("Digite o valor(R$) de vendas feitas no trimestre %d:\n", i+1);
        scanf(" %f", &vendas);
        CuboProdutos[i][indiceFilial][indiceProduto].quantidadeVendas += vendas;
    }

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Venda de produto no trimeste ---\n\n");
    printf("Vendas registradas com suecsso!\n\n");
    system("pause");
}

void ProdutoMaisVendido()
{
    float *totalSomaProdutos, maiorValor;
    char produtoMaisVendido[30];
    totalSomaProdutos = (float *)malloc(QuantidadeProdutos * sizeof(float));

    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        for(int j = 0; j < QuantidadeProdutos; j++)
        {
            totalSomaProdutos[j] = 0;
            totalSomaProdutos[j] += CuboProdutos[0][i][j].quantidadeVendas;
            totalSomaProdutos[j] += CuboProdutos[1][i][j].quantidadeVendas;
            totalSomaProdutos[j] += CuboProdutos[2][i][j].quantidadeVendas;
            totalSomaProdutos[j] += CuboProdutos[3][i][j].quantidadeVendas;
        }
    }

    maiorValor = totalSomaProdutos[0];
    strcpy(produtoMaisVendido, listaNomeProdutos[0]);

    for(int i = 1; i < QuantidadeProdutos; i++)
    {
        if(totalSomaProdutos[i] > maiorValor)
        {
            maiorValor = totalSomaProdutos[i];
            strcpy(produtoMaisVendido, listaNomeProdutos[i]);
        }
    }

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Relatorio produto mais vendido ---\n\n");
    printf("O produto mais vendido: %s", produtoMaisVendido);
    printf("Valor das vendas: R$%.2f\n\n", maiorValor);
    system("pause");
    free(totalSomaProdutos);
}

void ProdutoMaisVendidoPorFilial()
{
    int validaFilial = 0, indiceFilial = 0, indiceProduto = 0;
    float *totalSomaProdutos, maiorVenda;
    char NomeFilial[50], nomeProduto[30];
    totalSomaProdutos = (float *)malloc(QuantidadeProdutos * sizeof(float));

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Produto mais vendido pela filial ---\n\n");
    printf("Lista de filiais: \n");
    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        printf(" - %s", listaNomeFiliais[i]);
    }
    setbuf(stdin, 0);
    printf("Digite o nome da filial: ");
    fgets(NomeFilial,50,stdin);

    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        if(strcmp(NomeFilial,listaNomeFiliais[i]) == 0)
        {
            validaFilial = 1;
            indiceFilial = i;
            break;
        }
    }

    if(!validaFilial)
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t--- Produto mais vendido pela filial ---\n\n");
        printf("Filial nao encontrada!\n\n");
        system("pause");
        return;
    }

    for(int i = 0; i < QuantidadeProdutos; i++)
    {
        totalSomaProdutos[i] = 0;
        for(int j = 0; j < 4; j++)
        {
            totalSomaProdutos[i] += ListaFiliais[indiceFilial].MatrizProdutosTrimestre[j][i].quantidadeVendas;
        }
    }

    indiceProduto = 0;
    maiorVenda = totalSomaProdutos[0];
    for(int i = 1; i < 4; i++)
    {
        if(maiorVenda < totalSomaProdutos[i])
        {
            indiceProduto = i;
            maiorVenda = totalSomaProdutos[i];
        }
    }
    strcpy(nomeProduto, listaNomeProdutos[indiceProduto]);
    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Produto mais vendido pela filial ---\n\n");
    printf("O produto mais vendido pela filial : %s", nomeProduto);
    printf("Quantidade de vendas R$: %.2f\n\n", maiorVenda);
    system("pause");
}

void FilialMaisVende()
{
    float *VendasTotaisFiliais, maiorVendas;
    char NomeFilial[50];

    VendasTotaisFiliais = (float *)malloc(QuantidadeFiliais * sizeof(float));

    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        VendasTotaisFiliais[i] = 0;
        for(int j = 0; j < QuantidadeProdutos; j++)
        {
            VendasTotaisFiliais[i] += ListaFiliais[i].MatrizProdutosTrimestre[0][j].quantidadeVendas;
            VendasTotaisFiliais[i] += ListaFiliais[i].MatrizProdutosTrimestre[1][j].quantidadeVendas;
            VendasTotaisFiliais[i] += ListaFiliais[i].MatrizProdutosTrimestre[2][j].quantidadeVendas;
            VendasTotaisFiliais[i] += ListaFiliais[i].MatrizProdutosTrimestre[3][j].quantidadeVendas;
        }
    }

    maiorVendas = VendasTotaisFiliais[0];
    strcpy(NomeFilial, listaNomeFiliais[0]);

    for(int i = 0; i < QuantidadeFiliais; i++)
        if(VendasTotaisFiliais[i] > maiorVendas)
        {
            strcpy(NomeFilial, listaNomeFiliais[i]);
            maiorVendas = VendasTotaisFiliais[i];
        }
    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Relatorio filial com mais vendidas ---\n\n");
    printf("A filial com mais vendas: %s", NomeFilial);
    printf("Valor das vendas: R$%.2f\n\n", maiorVendas);
    system("pause");
    free(VendasTotaisFiliais);
}

void FilialMaisProdutosPorTrimeste()
{
    float *VendasTotaisFiliais, maiorVendas;
    int Trimestre = 0;
    char NomeFilial[50];
    do
    {
    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Relatorio filial com mais vendidas ---\n\n");
    printf("Digite qual trismestre deseja consultar(1,2,3 ou 4): ");
    scanf(" %d", &Trimestre);
    Trimestre--;
    }while(Trimestre < 0 || Trimestre > 3);
    VendasTotaisFiliais = (float *)malloc(QuantidadeFiliais * sizeof(float));

    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        VendasTotaisFiliais[i] = 0;
        for(int j = 0; j < QuantidadeProdutos; j++)
            VendasTotaisFiliais[i] += ListaFiliais[i].MatrizProdutosTrimestre[Trimestre][j].quantidadeVendas;
    }

    maiorVendas = VendasTotaisFiliais[0];
    strcpy(NomeFilial, listaNomeFiliais[0]);

    for(int i = 0; i < QuantidadeFiliais; i++)
        if(VendasTotaisFiliais[i] > maiorVendas)
        {
            strcpy(NomeFilial, listaNomeFiliais[i]);
            maiorVendas = VendasTotaisFiliais[i];
        }
    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Relatorio filial com mais vendidas ---\n\n");
    printf("A filial com mais vendas no trimestre %d: %s",Trimestre + 1, NomeFilial);
    printf("Valor das vendas: R$%.2f\n\n", maiorVendas);
    system("pause");
    free(VendasTotaisFiliais);
}

void FilialQueMaisVende()
{
    char NomeFilial[30];
    int indiceFilial;
    float maiorVendas, *vendasTotais;
    vendasTotais = (float *)malloc(QuantidadeFiliais * sizeof(float));

    for(int j = 0; j < QuantidadeFiliais; j++)
    {
        vendasTotais[j] = 0;
        for(int i = 0; i < 4; i++)
            for(int k = 0; k < QuantidadeProdutos; k++)
                vendasTotais[j] += CuboProdutos[i][j][k].quantidadeVendas; 
    }

    maiorVendas = vendasTotais[0];
    indiceFilial = 0;
    for(int i = 1; i < QuantidadeFiliais; i++)
    {
        if(maiorVendas < vendasTotais[i])
        {
            indiceFilial = i;
            maiorVendas= vendasTotais[i];
        }
    }
    strcpy(NomeFilial,listaNomeFiliais[indiceFilial]);

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Relatorio filial que mais vende ---\n\n");
    printf("A filial que mais vendeu no ano: %s",NomeFilial);
    printf("Valor das vendas: R$%.2f\n\n", maiorVendas);
    system("pause");
    free(vendasTotais);
}

void MelhorTrimestre()
{
    float maiorVendas, *vendasTotais;
    int trimestre;
    vendasTotais = (float *)malloc(4 * sizeof(float));

    for(int i = 0; i < 4; i++)
    {
        vendasTotais[i] = 0;
        for(int j = 0; j < QuantidadeFiliais; j++)
            for(int k = 0; k < QuantidadeProdutos; k++)
                vendasTotais[i] += CuboProdutos[i][j][k].quantidadeVendas;
    }

    maiorVendas = vendasTotais[0];
    trimestre = 0;

    for(int i = 1; i < 4; i++)
    {
        if(maiorVendas < vendasTotais[i])
        {
            trimestre = i;
            maiorVendas = vendasTotais[i];
        }
    }

    system("cls");
    Headder(QuantidadeProdutos,QuantidadeFiliais);
    printf("\n \t\t--- Relatorio filial que mais vende ---\n\n");
    printf("A trimeste que mais vendeu no ano: %d trimestre\n",trimestre +1);
    printf("Valor das vendas: R$%.2f\n\n", maiorVendas);
    system("pause");
    free(vendasTotais);
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

int MenuInserir()
{
    int OpcaoMenu = 1;
    do
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t=== Menu Insercao ===\n\n");
        printf("1 - Inserir venda de um produto/trimestre\n");
        printf("2 - Inserir venda de um produto/filial\n");
        printf("3 - Inserir novo produto\n");
        printf("4 - Inserir nova filial\n");
        printf("5 - Sair\n");
        if(OpcaoMenu < 1 || OpcaoMenu > 5)
            printf("\nOpcao anterior invalida!\n");
        printf("\nSelecione uma opcao do menu: ");
        scanf(" %d", &OpcaoMenu);
    } while (OpcaoMenu < 1 || OpcaoMenu > 5);
    switch (OpcaoMenu)
    {
    case 1:
        VendaProdutoTrimestre();
        break;
    case 2:
        VendaProdutoFilial();
        break;
    case 3:
        InserirNovoProduto();
        break;    
    case 4:
        InserirNovaFilial();
        break;  
    default:
        return;
    }
}

int MenuRemover()
{
    int OpcaoMenu = 1;
    char resp = ' ';
    do
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t=== Menu Remocao ===\n\n");
        printf("1 - Remover Produto\n");
        printf("2 - Remover filial\n"); //Adicao
        printf("3 - Reiniciar todo o sistema (!)\n");
        printf("4 - Sair\n");
        if(OpcaoMenu < 1 || OpcaoMenu > 4)
            printf("\nOpcao anterior invalida!\n");
        printf("\nSelecione uma opcao do menu: ");
        scanf(" %d", &OpcaoMenu);
    } while (OpcaoMenu < 1 || OpcaoMenu > 4);
    switch (OpcaoMenu)
    {
    case 1:
        RemoverProduto();
        break;
    case 2:
        RemoverFilial();
        break;
    case 3:
        system("cls");
        Headder(QuantidadeProdutos, QuantidadeFiliais);
        system("color 4f");
        printf("\n === ATENCAO === \n\n");
        printf("Deseja mesmo reiniciar todo o sistema? (s/n)\n");
        scanf(" %c", &resp);
        system("color 0f");
            if(resp == 's')
            {
                ReiniciarSistema();
                foiResetado = 1;
                main();
            }
        break; 
    default:
        return;
    }
}

int MenuRelatorios()
{
    int OpcaoMenu = 1;
    do
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t=== Menu Relatorios ===\n\n");
        printf("1 - Produto mais vendido por filial\n");
        printf("2 - Filial que mais vende produtos num trimestre\n");
        printf("3 - Produto mais vendido\n");
        printf("4 - Filial que mais vende\n");
        printf("5 - Melhor trimestre\n");
        printf("6 - Sair\n");
        if(OpcaoMenu < 1 || OpcaoMenu > 6)
            printf("\nOpcao anterior invalida!\n");
        printf("\nSelecione uma opcao do menu: ");
        scanf(" %d", &OpcaoMenu);
    } while (OpcaoMenu < 1 || OpcaoMenu > 6);
    switch (OpcaoMenu)
    {
    case 1:
        ProdutoMaisVendidoPorFilial();
        break;
    case 2:
        FilialMaisProdutosPorTrimeste();
        break;    
    case 3:
        ProdutoMaisVendido();
        break;    
    case 4:
        FilialQueMaisVende();
        break;    
    case 5:
        MelhorTrimestre();
        break; 
    default:
        return;
    }
}

int MenuPrincipal()
{
    int OpcaoMenu = 1;
    do
    {
        system("cls");
        Headder(QuantidadeProdutos,QuantidadeFiliais);
        printf("\n \t\t=== Menu Principal ===\n\n");
        printf("1 - Inserir dados\n");
        printf("2 - Remover dados\n");
        printf("3 - Relatorios\n");
        printf("4 - Sair\n");
        if(OpcaoMenu < 1 || OpcaoMenu > 4)
            printf("\nOpcao anterior invalida!\n");
        printf("\nSelecione uma opcao do menu: ");
        scanf(" %d", &OpcaoMenu);
    } while (OpcaoMenu < 1 || OpcaoMenu > 4);   
    switch (OpcaoMenu)
    {
    case 1:
        MenuInserir();
        MenuPrincipal();
        break;
    case 2:
        MenuRemover();
        if(!foiResetado)
            MenuPrincipal();
        break;
    case 3:
        MenuRelatorios();
        MenuPrincipal();
        break;    
    default:
        return;
    }
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
    //Preenchendo dados das filiais
    for(int i = 0; i < QuantidadeFiliais; i++)
    {
        strcpy(ListaFiliais[i].NomeFilial, listaNomeFiliais[i]);
        for(int j = 0; j < QuantidadeProdutos; j++)
        {
            strcpy(CuboProdutos[0][i][j].NomeProduto, listaNomeProdutos[j]);
            strcpy(CuboProdutos[1][i][j].NomeProduto, listaNomeProdutos[j]);
            strcpy(CuboProdutos[2][i][j].NomeProduto, listaNomeProdutos[j]);
            strcpy(CuboProdutos[3][i][j].NomeProduto, listaNomeProdutos[j]);
            CuboProdutos[0][i][j].quantidadeVendas = 0.0;
            CuboProdutos[1][i][j].quantidadeVendas = 0.0;
            CuboProdutos[2][i][j].quantidadeVendas = 0.0;
            CuboProdutos[3][i][j].quantidadeVendas = 0.0;
        }
    }
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
    PreencherDadosCubo(CuboProdutos);
    return 1;
}

/* 

        ORDEM DE MANIPULAÇÃO DOS DADOS 
    CuboProdutos[TrimestreAno][Nº Filial][Nº Produto]
        - NomeProduto
        - quantidadeVendas
    
    ListaFiliais[Nº Filial]
        - NomeFiliai
        - MatrizProdutosTrimestre[TrimestreAno][Nº Produto]
            - NomeProduto
            - quantidadeVendas  
*/

int main()
{

    int ControleDeFluxo = 0;
    ControleDeFluxo = IniciarSistema();
    if(!ControleDeFluxo) return 0;
    MenuPrincipal();
    return 0;
}
