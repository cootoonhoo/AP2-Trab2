# AP2-Trab2
Segundo trabalho de Algoritmo e programação 2

## Integrantes
<ul>
    <li>Marco Antonio Batista de Souza</li>
    <li>Rafael Romancini</li>
    <li>Guilherme França Soares</li>
</ul>

## Enunciado
<h3>Controle de estoque - Market++</h3>
<p>Você é o desenvolver de um sistema computacional para uma rede de supermercados, chamada Market++. A rede de supermercados possui diferentes produtos e diferentes filiais, espalhadas pela cidade de UberLand. Identificar os produtos mais vendidos, as filiais que vendem mais, e as épocas do ano com mais vendas são questões importantes para que a Market++ aumente suas vendas.

<p>Assim, a Market++ convidou você para fazer o controle de estoque dos seus produtos, a fim de de identificar os produtos mais vendidos em determinados períodos e determinadas lojas.É importante ter um sistema que possa se adaptar à medida que novos produtos são adicionados ao catálogo de produtos da loja. Como a rede de supermercados Market++ está em plena expansão, é também importante incorporar funcionalidades que permitam inserir novas filiais no sistema.

<b>Tarefa</b>
<p>Sua missão é escrever um programa para ajudar a rede de supermercados Market++ a gerenciar as vendas dos produtos nas diferentes regiões. Você deverá escrever um programa que:

- monte um array com 3 dimensões que represente a os produtos da empresa x trimestres do ano corrente x filiais da Market++.

- apresente um menu com as seguintes opções:

<ol>
    <li>Inicialização do sistema: neste caso o usuário irá fornecer o nro de produtos do catálogo de produtos da rede Market++, bem como o nro de filiais da rede de supermercados. Você irá alocar as informações referentes a matriz de 3 dimensões que armazenará tais informações. </li>
    <li> Catálogo do Sistema: neste caso o usuário irá fornecer o nome de todos os produtos que fazem parte do catálogo do sistema. O nome dos produtos será armazenado em um vetor a parte, sendo que as posições do vetor, correspondem às posições da matriz no eixo produtos da empresa.</li>
    <li>Catálogo de filiais: neste caso o usuário irá fornecer o nome de todos as filiais da rede de supermercados. O nome das filiais será armazenado em um vetor a parte, sendo que as posições do vetor, correspondem às posições da matriz no eixo de filiais.</li>
    <li>Inserir venda de um produto/trimestre: Neste caso o usuário informa o nro correspondente ao trimestre (1, 2, 3 ou 4), o nome do produto, e a seguir é solicitado as vendas daquele produto no trimestre solicitado para cada uma das filiais.</li>
    <li>Inserir venda de um produto/filial: Neste caso o usuário informa o nome da filial, o nome do produto, e a seguir é solicitado as vendas daquele produto para aquela filial nos 4 trimestres do ano.</li>
    <li>Produto mais vendido por filial: Neste caso o usuário informa o nome da filial e o sistema retorna o produto mais vendido considerando a soma dos quatro trimestres.</li>
    <li>Filial que mais vende produtos: Neste caso o usuário informa o trimestre e o sistema retorna a filial que mais vendeu produtos, considerando todos os produtos do catálogo.</li>
    <li>Produto mais vendido: O sistema retorna o produto mais vendido, considerando todas as filiais e todos os trimestres.</li>
    <li>Filial que mais vende: O sistema retorna a filial que mais vendeu produtos, considerando todos os produtos e todos os trimestres.</li>
    <li>Melhor trimestre: O sistema retorna o trimestre que teve mais vendas, considerando todas as filiais e todos os produtos.</li>
    <li>Inserir novo produto: O sistema permite a inserção de um novo produto no catálogo de produtos. Obviamente este produto é também incorporado à matriz.</li>
    <li>Inserir nova filial: O sistema permite a inserção de um nova filial no catálogo de produtos. Obviamente esta filial é também incorporado à matriz.</li>
    <li>Remover produto: O sistema permite a remoção de um produto do catálogo de produtos. Obviamente este produto também será removido da matriz.</li>
</ol>
<p>Para a execução do projeto, use alocação dinâmica de memória!
<p><b>Requisito extra:</b>
<p>Você deverá acrescentar duas novas opções no menu do sistema proposto. É importante documentar no código qual é o objetivo daquela opção
