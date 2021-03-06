#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNT 5

// estrutura autoreferenciada
struct nodo_arvore {
    struct nodo_arvore *ponteiro_esquerda; // ponteiro para  a subarvore a esquerda
    int dado; // valor contido no nodo
    struct nodo_arvore *ponteiro_direita; // ponteiro para a subarvore a direita
}; // fim da estrutura nodo da arvore

typedef struct nodo_arvore nodo_arvore; // sinonimo para a estrutura de nodo da arvore
typedef nodo_arvore *nodo_arvore_ponteiro; // sinonimo para o ponteiro de estrutura de nodo da arvore

// prototipos de função
void inserir_na_arvore(nodo_arvore_ponteiro *ponteiro_arvore, int valor);
void percurso_em_ordem(nodo_arvore_ponteiro ponteiro_arvore);
void impressao_formato_arvore(nodo_arvore_ponteiro ponteiro_arvore, int espaco);
nodo_arvore_ponteiro busca_nodo(nodo_arvore_ponteiro ponteiro_arvore, int valor);
nodo_arvore_ponteiro remove_nodo(nodo_arvore_ponteiro ponteiro_arvore, int valor);

// função main inicia execução do programa
int main( int argc, char **argv )
{
    unsigned int i; // contador de loop de 1-10
    int item; // variável para armazenar os valores randômicos criados
    nodo_arvore_ponteiro ponteiro_raiz = NULL; // inicializando a árvore como nula

    srand(time(NULL));
    puts("Os numeros a serem inseridos na arvore sao:");

    // inserindo valores randômicos entre 0 e 14 na árvore
    for (i = 1; i <= 20; ++i)
    {
        item = rand() % 100;
        printf("%3d", item);
        inserir_na_arvore(&ponteiro_raiz, item); //insere valores aleatorios no nodo
    } // fim do laço for
    
    // percorrendo percurso em ordem
    puts("\n\nO percuro em-ordem:");
    percurso_em_ordem(ponteiro_raiz);

    printf("\n");

    impressao_formato_arvore(ponteiro_raiz,0);

    int valor_busca;

    printf("\nDigite um valor para busca na arvore: ");
    scanf("%d",&valor_busca);
    
    if(busca_nodo(ponteiro_raiz, valor_busca) == NULL)
    {
        printf("\nO valor nao existe na arvore!\n");
    }
    else
    {
        printf("\nO valor existe na arvore!\n");
    }

    exit(0);
} // fim da função principal

// inserindo nodo na árvore
void inserir_na_arvore(nodo_arvore_ponteiro *ponteiro_arvore, int valor)
{
    // se a árvore estiver vazia
    if (*ponteiro_arvore == NULL)
    {
        *ponteiro_arvore = malloc(sizeof(nodo_arvore));

        // se um espaço de memória foi alocado, então o nodo recebe o dado
        if (*ponteiro_arvore != NULL)
        {
            (*ponteiro_arvore)->dado = valor;
            (*ponteiro_arvore)->ponteiro_esquerda = NULL;
            (*ponteiro_arvore)->ponteiro_direita = NULL;
        } // fim do condicional if
        else
        {
            printf( "%d nao inserido. Sem memoria disponivel.\n", valor );
        } // fim do condicional else
    } // fim do condional if
    else // a árvore não está vazia
    {
        // valor a ser inserido na árvore é menor que o valor presente no nodo atual
        if (valor < (*ponteiro_arvore)->dado)
        {
            inserir_na_arvore(&((*ponteiro_arvore)->ponteiro_esquerda), valor );
        } // fim do condicional if
        
        // valor a ser inserido na árvore é maior que o valor presente no nodo atual
        else if (valor > (*ponteiro_arvore)->dado)
        {
            inserir_na_arvore(&((*ponteiro_arvore)->ponteiro_direita), valor);
        } // fim do condicional else if
        else// ignorar valor dentro nó duplicado
        { 
            //printf("%s", " (valor duplicado)");
        } // fim do condicional else
    } // fim do condicional else
} // fim da função inserir_na_arvore

// inicia percurso em ordem da árvore
void percurso_em_ordem(nodo_arvore_ponteiro ponteiro_arvore)
{
    // se a árvore não está vazia, então percorre a mesma
    if (ponteiro_arvore != NULL)
    {
        percurso_em_ordem(ponteiro_arvore->ponteiro_esquerda);
        printf("%3d", ponteiro_arvore->dado);
        percurso_em_ordem(ponteiro_arvore->ponteiro_direita);
    } // fim do condicional if
}// fim da função percurso_em_ordem

// Função para imprimir árvore binária de busca
void impressao_formato_arvore(nodo_arvore_ponteiro ponteiro_arvore, int espaco)
{
    // Caso base
    if (ponteiro_arvore == NULL)
        return;
 
    // Incrementa a distância entre níveis
    espaco += COUNT;
 
    // Processa nó a direita primeiro
    impressao_formato_arvore(ponteiro_arvore->ponteiro_direita, espaco);
 
    // Imprime nó atual depois de dar o número de espaços
    // contador
    printf("\n");
    int i;
    for (i = COUNT; i < espaco; i++)
    {
        printf(" ");
    }
    
    printf("%d\n", ponteiro_arvore->dado);
 
    // Processa nós a esquerda
    impressao_formato_arvore(ponteiro_arvore->ponteiro_esquerda, espaco);
}

//A função abaixo busca o nó da árvore que possui um valor específico
//A função retorna o nó onde está o valor buscado ou NULL caso o valor não seja encontrado na árvore
nodo_arvore_ponteiro busca_nodo(nodo_arvore_ponteiro ponteiro_arvore, int valor)
{
    if(ponteiro_arvore == NULL) //se a árvore estiver vazia ou o valor não for encontrado
    {
        return NULL;
    }
    else if(ponteiro_arvore->dado > valor) //quando o valor buscado é menor que o valor presente no nó atual
    {
        return busca_nodo(ponteiro_arvore->ponteiro_esquerda, valor);//busca na árvore continua pelo nó filho a esquerda do nó atual
    }
    else if(ponteiro_arvore->dado < valor) //quando o valor buscado é maior que o valor presente no nó atual
    {
        return busca_nodo(ponteiro_arvore->ponteiro_direita , valor);//busca na árvore continua pelo nó filho a direita do nó atual
    }
    else
    {
        return ponteiro_arvore; //quando o nó com o valor buscado é encontrado
    }
}

//A função abaixo remove um nó obtido na função de busca de um elemento presente na árvore
nodo_arvore_ponteiro remove_nodo(nodo_arvore_ponteiro ponteiro_arvore, int valor)
{
    //A condição abaixo é utilizada quando o nó a ser deletado não possui filhos
    if(ponteiro_arvore->ponteiro_esquerda == NULL && ponteiro_arvore->ponteiro_direita==NULL)
    {
        free(ponteiro_arvore); //Deletando(limpando da memória) o nó para remoção
    }

    //A condição abaixo é utilizada quando o nó possui apenas filho à direita
    else if(ponteiro_arvore->ponteiro_esquerda == NULL)
    {
        nodo_arvore_ponteiro auxiliar; //Nó auxiliar é criado
        auxiliar = ponteiro_arvore; //Nó auxiliar recebe o nó atual
        ponteiro_arvore = ponteiro_arvore->ponteiro_direita; //O nó atual é "descolado" e ocupa o "lugar" do seu filho à direita
        free(auxiliar); //Deletando(limpando da memória) o nó auxiliar que possui o nó atual a ser removido
    }

    //A condição abaixo é utilizada quando o nó possui apenas filho à esquerda
    else if(ponteiro_arvore->ponteiro_direita == NULL)
    {
        nodo_arvore_ponteiro auxiliar; //Nó auxiliar é criado
        auxiliar = ponteiro_arvore; //Nó auxiliar recebe o nó atual
        ponteiro_arvore = ponteiro_arvore->ponteiro_esquerda; //O nó atual é "descolado" e ocupa o "lugar" do seu filho à esquerda
        free(auxiliar); //Deletando(limpando da memória) o nó auxiliar que possui o nó atual a ser removido
    }

    //A condição abaixo é utilizada quando o nós possui filhos tanto à esquerda quanto à direita
    //Onde será procurado o melhor valor para ocupar o lugar do nó deletado para não perder alguma propriedade da árvore
    else
    {
        nodo_arvore_ponteiro auxiliar; //Nó auxiliar é criado
        auxiliar = ponteiro_arvore->ponteiro_esquerda; //Nó auxiliar recebe o filho nó atual à esquerda

        //O loop abaixo vai buscar o maior valor à direta do nó atual do nó atual para colocá-lo no lugar do nó atual 
        while(auxiliar->ponteiro_direita != NULL) 
        {
            auxiliar = auxiliar->ponteiro_direita;
        }

        ponteiro_arvore->dado = auxiliar->dado; //O nó atual recebe o maior valor à direita dele, obtido no loop acima
        auxiliar->dado = valor; //O nó auxiliar recebe o valor buscado

        //O nó filho do nó atual recebe o "restante" da árvore após a remoção
        ponteiro_arvore->ponteiro_esquerda = remove_nodo(ponteiro_arvore->ponteiro_esquerda,valor);
    }

    return ponteiro_arvore; //Retorna a árvore completa após a remoção do nó selecionado
}

