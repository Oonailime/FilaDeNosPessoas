#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tamanho maximo da fila
#define n 11

//No
typedef struct no
{

    int nIdentificacao;
    char nome[50];
    struct no *proximo;

} No;

//Lista
typedef struct
{
    No *inicio;
    No *fim;
    int tam;
} Lista;


// Metodo construtor
void criarLista(Lista *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
}




// Metodo inserir no inicio da lista
void inserirNoInicio(Lista *lista, int nIdent, char nom[50])
{
    No *novo = malloc(sizeof(No));
    if (novo)
    {
        novo->nIdentificacao = nIdent;
        strcpy(novo->nome, nom);
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        if (lista->fim == NULL)
        {
            lista->fim = novo;
        }
        lista->fim->proximo = lista->inicio;
        lista->tam++;
    }
    else
    {
        printf("Erro ao alocar\n");
    }
}

// Metodo inserir no final
void inserirNoFinal(Lista *lista, int nIdent, char nom[50])
{
    No *aux, *novo = malloc(sizeof(No));
    if (novo)
    {
        novo->nIdentificacao = nIdent;
        strcpy(novo->nome, nom);

        // caso a lista esteja vazia, faz um construtor.
        if (lista->inicio == NULL)
        {
            lista->inicio = novo;
            lista->fim = novo;
            lista->fim->proximo = lista->inicio;
        }
        else
        {
            lista->fim->proximo = novo;
            lista->fim = novo;
            lista->fim->proximo = lista->inicio;
        }
        lista->tam++;
    }
    else
    {
        printf("Erro ao alocar!\n");
    }
}

// Metodo inserir ordenado
void inserirOrdenado(Lista *lista, int nIdent, char nom[50])
{
    No *aux, *novo = malloc(sizeof(No));
    if (novo)
    {
        novo->nIdentificacao = nIdent;
        strcpy(novo->nome, nom);
        novo->proximo = NULL;
        if (lista->inicio == NULL)
        {
            inserirNoInicio(lista, nIdent, nom);
        }
        else if (novo->nIdentificacao < lista->inicio->nIdentificacao)
        {
            inserirNoInicio(lista, nIdent, nom);
        }
        else
        {
            aux = lista->inicio;
            while (aux->proximo != lista->inicio && novo->nIdentificacao > aux->proximo->nIdentificacao)
            {
                aux = aux->proximo;
            }
            if (aux->proximo == lista->inicio)
            {
                inserirNoFinal(lista, nIdent, nom);
            }

            else
            {
                novo->proximo = aux->proximo;
                aux->proximo = novo;
                lista->tam++;
            }
        }
    }
    else
    {
        printf("Erro ao alocar!\n");
    }
}

//Metodo buscar na lista
No* Buscar(Lista *lista, int nIden){
    No *aux = lista->inicio;
    if(aux){
        do{
            if(aux->nIdentificacao==nIden){
                return aux;
            }
            aux = aux->proximo;
        }while(aux!=lista->inicio);
    }
    return NULL;
}


// Método Remover
No *remover(Lista *lista, int nIdent)
{
    No *aux, *remover = NULL;
    if (lista->inicio)
    {
        if (lista->inicio == lista->fim && lista->inicio->nIdentificacao == nIdent)
        {
            remover = lista->inicio;
            lista->inicio = NULL;
            lista->fim = NULL;
            lista->tam--;
        }
        else if (lista->inicio->nIdentificacao == nIdent)
        {
            remover = lista->inicio;
            lista->inicio = remover->proximo;
            lista->fim->proximo = lista->inicio;
            lista->tam--;
        }
        else
        {
            aux = lista->inicio;
            while (aux->proximo != lista->inicio && aux->proximo->nIdentificacao != nIdent)
            {
                aux = aux->proximo;
            }
            if (aux->proximo->nIdentificacao == nIdent)
            {
                if (lista->fim == aux->proximo)
                {
                    remover = aux->proximo;
                    aux->proximo = remover->proximo;
                    lista->fim = aux;
                }
                else
                {
                    remover = aux->proximo;
                    aux->proximo = remover->proximo;
                }
                lista->tam--;
            }
        }
    }
    return remover;
}

//Metodo imprimir
void imprimir(Lista lista)
{
    No *no = lista.inicio;
    printf("\n\tTamanho da lista: %d: \n", lista.tam);
    if (no)
    {
        do
        {
            printf("Numero de identificacao: %d\n Nome: %s", no->nIdentificacao, no->nome);
            printf("\n/\n");
            no = no->proximo;
        } while (no != lista.inicio);
        
    }
    printf("\n");
}



//Fila
typedef struct{
    No pessoa[n];
    int inicio;
    int fim;

}fila;

//construtor da fila
void criarFila(fila *f){
    f->inicio = 0;
    f->fim = 0;
}

//retorna se fila está cheia
int filaEstaCheia(fila *f){
    return (f->inicio == ((f->fim+1)%n));
}
//retorna se fila está vazia
int filaEstaVazia(fila *f){
    return (f->inicio == f->fim);
}

//Rnfileira
int enfileira(fila *f, No *P){

    if(filaEstaCheia(f)){
        printf("\nErro! A fila esta cheia!");
        return 0;
    }
    
    f->fim = (f->fim+1)%n;
    f->pessoa[f->fim].nIdentificacao = P->nIdentificacao;
    strcpy(f->pessoa[f->fim].nome, P->nome);

    return 1;

}

//Remove da fila
int revomeFila(fila *f,No *P){
    if(filaEstaVazia(f)){
        printf("Erro! Fila ja esta vazia!");
        return 0;
    }
    f->inicio = (f->inicio+1)%n;
    (*P).nIdentificacao = f->pessoa[f->inicio].nIdentificacao;
    strcpy((*P).nome,f->pessoa[f->inicio].nome);
    return 1;
}

//Retorna primeiro elemento da fila
No * inicioFila(fila *f){
    if(filaEstaVazia(f)){
        return NULL;
    }
    No *p = (No *)malloc(sizeof(No));
    int i = (f->inicio+1)%n;
    p->nIdentificacao = f->pessoa[i].nIdentificacao;
    strcpy(p->nome,f->pessoa[i].nome);
    return p;
}








int main()
{

    int escolha, nIdent;
    char nome[50];
    Lista lista;
    No *remov;
    
    No *p = (No *)malloc(sizeof(No));
    fila *Fila = (fila *) malloc(sizeof(fila));

    
    criarFila(Fila);
    criarLista(&lista);

    do
    {
        printf("\n+-------------------------------------------+");
        printf("\n|              Selecione o metodo           |");
        printf("\n+-------------------------------------------+");
        printf("\n| 0 - Encerrar programa                     |");
        printf("\n| 1 - Inserir Pessoa                        |");
        printf("\n| 2 - Excluir Pessoa                        |");
        printf("\n| 3 - Inserir na fila                       |");
        printf("\n| 4 - Atender a fila                        |");
        printf("\n| 5 - Imprimir fila                         |");
        printf("\n| 6 - Imprimir Pessoas de forma ordenada    |");
        printf("\n|                                           |");
        printf("\n+-------------------------------------------+\n");

        scanf("%d", &escolha);

        switch (escolha)
        {

        case 0:
            break;
        case 1:

            printf("\nDigite o numero de identificacao: ");
            scanf("%d", &nIdent);

            printf("\nDigite o nome: ");
            scanf("%s", &nome);

            inserirOrdenado(&lista, nIdent, nome);

            break;
        case 2:
            printf("\nDigite o numero de identificacao que deseja remover: ");
            scanf("%d", &nIdent);
            remov = remover(&lista, nIdent);
            if (remov)
            {
                printf("A pessoa: %d foi removida.\n", remov->nIdentificacao);
                free(remov);
            }
            else
            {
                printf("Essa pessoa não esta na lista!\n");
            }
            break;

        case 3:
            printf("\nDigite o numero de identificacao que ira para a fila: ");
            scanf("%d", &nIdent);

            
            strcpy(p->nome, Buscar(&lista,nIdent)->nome);
            enfileira(Fila, p);
            break;
        case 4:
            if(revomeFila(Fila,p)){
                printf("\nAtender pessoa: %s \n", p->nome);
            }
            else{
                printf("A fila esta vazia.");
            }
            
            break;
        //Erro no Fila->inicio por isso que não imprime quando a função Atender é ativada
        //Como A parte de imprimir fila não é pedida no problema, deixarei essa implementação para o futuro
        case 5:
            for(int i=Fila->inicio+1; i <= Fila->fim;i++){
        		printf("\nPessoa em espera %d: \nnome: %s \n",i, Fila->pessoa[i].nome);
			}	
            break;
        case 6:
            imprimir(lista);
            break;
        
        default:
            if (escolha != 0)
            {
                printf("ERRO! Digite uma opção valida: ");
            }
        }

    } while (escolha != 0);
}
