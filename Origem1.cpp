/* Fig. 12.3: fig12_03.c
 * Operando e mantendo uma lista */
#include <stdio.h>
#include <stdlib.h>

 /* estrutura autorreferenciada */
struct listNode {
    char data; /* cada listNode cont�m um caractere */
    struct listNode* nextPtr; /* ponteiro para o pr�ximo n� */
}; /* fim da estrutura listNode */

typedef struct listNode ListNode; /* sin�nimo de struct listNode */
typedef ListNode* ListNodePtr; /* sin�nimo de ListNode* */

/* prot�tipos */
void insert(ListNodePtr* sPtr, char value);
char delete(ListNodePtr* sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);

int main(void)
{
    ListNodePtr startPtr = NULL; /* inicialmente n�o existem n�s */
    int choice; /* escolha do usu�rio */
    char item; /* char inserido pelo usu�rio */

    instructions(); /* exibe o menu */
    printf("? ");
    scanf("%d", &choice);

    /* loop enquanto o usu�rio n�o digita 3 */
    while (choice != 3) {

        switch (choice) {
        case 1:
            printf("Digite um caractere: ");
            scanf("\n%c", &item);
            insert(&startPtr, item); /* insere o item na lista */
            printList(startPtr);
            break;
        case 2:
            /* se a lista n�o estiver vazia */
            if (!isEmpty(startPtr)) {
                printf("Digite o caractere a ser exclu�do: ");
                scanf("\n%c", &item);

                /* se o caractere for encontrado, remove-o */
                if (delete(&startPtr, item)) { /* remove o item */
                    printf("%c exclu�do.\n", item);
                    printList(startPtr);
                }
                else {
                    printf("%c n�o encontrado.\n\n", item);
                }
            }
            else {
                printf("A lista est� vazia.\n\n");
            }
            break;
        default:
            printf("Op��o inv�lida.\n\n");
            instructions();
            break;
        } /* fim do switch */

        printf("? ");
        scanf("%d", &choice);
    } /* fim do while */

    printf("Fim da execu��o.\n");
    return 0; /* indica conclus�o bem-sucedida */
} /* fim de main */

/* Exibe as instru��es para o usu�rio */
void instructions(void)
{
    printf("Digite sua escolha:\n"
        "   1 para inserir um elemento na lista.\n"
        "   2 para excluir um elemento da lista.\n"
        "   3 para finalizar.\n");
} /* fim da fun��o instructions */

/* Insere um novo valor na lista em ordem classificada */
void insert(ListNodePtr* sPtr, char value)
{
    ListNodePtr newPtr; /* ponteiro para o novo n� */
    ListNodePtr previousPtr; /* ponteiro para o n� anterior na lista */
    ListNodePtr currentPtr; /* ponteiro para o n� atual na lista */

    newPtr = malloc(sizeof(ListNode)); /* cria n� */

    if (newPtr != NULL) { /* � espa�o dispon�vel */
        newPtr->data = value; /* coloca o valor no n� */
        newPtr->nextPtr = NULL; /* n� n�o se vincula a outro n� */

        previousPtr = NULL;
        currentPtr = *sPtr;

        /* loop para encontrar o local correto na lista */
        while (currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr; /* vai para o pr�ximo n� */
            currentPtr = currentPtr->nextPtr; /* ... */
        } /* fim do while */

        /* insere o novo n� no in�cio da lista */
        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } /* fim do if */
        else { /* insere o novo n� entre previousPtr e currentPtr */
            newPtr->nextPtr = currentPtr;
            previousPtr->nextPtr = newPtr;
        } /* fim do else */
    } /* fim do if */
    else {
        printf("Mem�ria n�o dispon�vel.\n");
    } /* fim do else */
} /* fim da fun��o insert */

/* Exclui um elemento da lista */
char delete(ListNodePtr* sPtr, char value)
{
    ListNodePtr previousPtr; /* ponteiro para o n� anterior na lista */
    ListNodePtr currentPtr; /* ponteiro para o n� atual na lista */
    ListNodePtr tempPtr; /* ponteiro tempor�rio do n� */

    /* loop atrav�s da lista procurando o n� de valor correspondente */
    if (value == (*sPtr)->data) { /* exclui o primeiro n� */
        tempPtr = *sPtr; /* mant�m o n� a ser desalocado */
        *sPtr = (*sPtr)->nextPtr; /* desvincula o n� */
        free(tempPtr); /* libera o n� */
        return value;
    } /* fim do if */
    else {
        previousPtr = *sPtr;
        currentPtr = (*sPtr)->nextPtr;

        /* loop para encontrar o local correto na lista */
        while (currentPtr != NULL && currentPtr->data != value) {
            previousPtr = currentPtr; /* vai para o pr�ximo n� */
            currentPtr = currentPtr->nextPtr; /* ... */
        } /* fim do while */

        /* exclui o n� de currentPtr */
        if (currentPtr != NULL) {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        } /* fim do if */
    } /* fim do else */

    return '\0'; /* caractere n�o encontrado */
} /* fim da fun��o delete */

/* Retorna 1 se a lista estiver vazia, 0 caso contr�rio */
int isEmpty(ListNodePtr sPtr)
{
    return sPtr == NULL;
} /* fim da fun��o isEmpty */

/* Imprime a lista */
void printList(ListNodePtr currentPtr)
{
    /* se a lista estiver vazia */
    if (currentPtr == NULL) {
        printf("A lista est� vazia.\n\n");
    } /* fim do if */
    else {
        printf("A lista �:\n");

        /* enquanto n�o estiver no final da lista */
        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        } /* fim do while */

        printf("NULL\n\n");
    } /* fim do else */
} /* fim da fun��o printList */
