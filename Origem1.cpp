/* Fig. 12.3: fig12_03.c
 * Operando e mantendo uma lista */
#include <stdio.h>
#include <stdlib.h>

 /* estrutura autorreferenciada */
struct listNode {
    char data; /* cada listNode contém um caractere */
    struct listNode* nextPtr; /* ponteiro para o próximo nó */
}; /* fim da estrutura listNode */

typedef struct listNode ListNode; /* sinônimo de struct listNode */
typedef ListNode* ListNodePtr; /* sinônimo de ListNode* */

/* protótipos */
void insert(ListNodePtr* sPtr, char value);
char delete(ListNodePtr* sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);

int main(void)
{
    ListNodePtr startPtr = NULL; /* inicialmente não existem nós */
    int choice; /* escolha do usuário */
    char item; /* char inserido pelo usuário */

    instructions(); /* exibe o menu */
    printf("? ");
    scanf("%d", &choice);

    /* loop enquanto o usuário não digita 3 */
    while (choice != 3) {

        switch (choice) {
        case 1:
            printf("Digite um caractere: ");
            scanf("\n%c", &item);
            insert(&startPtr, item); /* insere o item na lista */
            printList(startPtr);
            break;
        case 2:
            /* se a lista não estiver vazia */
            if (!isEmpty(startPtr)) {
                printf("Digite o caractere a ser excluído: ");
                scanf("\n%c", &item);

                /* se o caractere for encontrado, remove-o */
                if (delete(&startPtr, item)) { /* remove o item */
                    printf("%c excluído.\n", item);
                    printList(startPtr);
                }
                else {
                    printf("%c não encontrado.\n\n", item);
                }
            }
            else {
                printf("A lista está vazia.\n\n");
            }
            break;
        default:
            printf("Opção inválida.\n\n");
            instructions();
            break;
        } /* fim do switch */

        printf("? ");
        scanf("%d", &choice);
    } /* fim do while */

    printf("Fim da execução.\n");
    return 0; /* indica conclusão bem-sucedida */
} /* fim de main */

/* Exibe as instruções para o usuário */
void instructions(void)
{
    printf("Digite sua escolha:\n"
        "   1 para inserir um elemento na lista.\n"
        "   2 para excluir um elemento da lista.\n"
        "   3 para finalizar.\n");
} /* fim da função instructions */

/* Insere um novo valor na lista em ordem classificada */
void insert(ListNodePtr* sPtr, char value)
{
    ListNodePtr newPtr; /* ponteiro para o novo nó */
    ListNodePtr previousPtr; /* ponteiro para o nó anterior na lista */
    ListNodePtr currentPtr; /* ponteiro para o nó atual na lista */

    newPtr = malloc(sizeof(ListNode)); /* cria nó */

    if (newPtr != NULL) { /* é espaço disponível */
        newPtr->data = value; /* coloca o valor no nó */
        newPtr->nextPtr = NULL; /* nó não se vincula a outro nó */

        previousPtr = NULL;
        currentPtr = *sPtr;

        /* loop para encontrar o local correto na lista */
        while (currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr; /* vai para o próximo nó */
            currentPtr = currentPtr->nextPtr; /* ... */
        } /* fim do while */

        /* insere o novo nó no início da lista */
        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } /* fim do if */
        else { /* insere o novo nó entre previousPtr e currentPtr */
            newPtr->nextPtr = currentPtr;
            previousPtr->nextPtr = newPtr;
        } /* fim do else */
    } /* fim do if */
    else {
        printf("Memória não disponível.\n");
    } /* fim do else */
} /* fim da função insert */

/* Exclui um elemento da lista */
char delete(ListNodePtr* sPtr, char value)
{
    ListNodePtr previousPtr; /* ponteiro para o nó anterior na lista */
    ListNodePtr currentPtr; /* ponteiro para o nó atual na lista */
    ListNodePtr tempPtr; /* ponteiro temporário do nó */

    /* loop através da lista procurando o nó de valor correspondente */
    if (value == (*sPtr)->data) { /* exclui o primeiro nó */
        tempPtr = *sPtr; /* mantém o nó a ser desalocado */
        *sPtr = (*sPtr)->nextPtr; /* desvincula o nó */
        free(tempPtr); /* libera o nó */
        return value;
    } /* fim do if */
    else {
        previousPtr = *sPtr;
        currentPtr = (*sPtr)->nextPtr;

        /* loop para encontrar o local correto na lista */
        while (currentPtr != NULL && currentPtr->data != value) {
            previousPtr = currentPtr; /* vai para o próximo nó */
            currentPtr = currentPtr->nextPtr; /* ... */
        } /* fim do while */

        /* exclui o nó de currentPtr */
        if (currentPtr != NULL) {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        } /* fim do if */
    } /* fim do else */

    return '\0'; /* caractere não encontrado */
} /* fim da função delete */

/* Retorna 1 se a lista estiver vazia, 0 caso contrário */
int isEmpty(ListNodePtr sPtr)
{
    return sPtr == NULL;
} /* fim da função isEmpty */

/* Imprime a lista */
void printList(ListNodePtr currentPtr)
{
    /* se a lista estiver vazia */
    if (currentPtr == NULL) {
        printf("A lista está vazia.\n\n");
    } /* fim do if */
    else {
        printf("A lista é:\n");

        /* enquanto não estiver no final da lista */
        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        } /* fim do while */

        printf("NULL\n\n");
    } /* fim do else */
} /* fim da função printList */
