#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list_estatic.h"

#define MAX_ALUNOS 15

struct lista{
    Aluno student[MAX_ALUNOS];
    int fim;
};


/*
CRIA_LISTA()
entrada: Nenhuma.
pre-condicao: Nenhuma.
processo: Aloca memoria para uma nova lista estatica.
saida: Ponteiro para a nova lista.
pos-condicao: Cria lista e inicializa-a como vazia.
*/
Lista cria_lista(){
    Lista lst = (Lista) malloc(sizeof(struct lista)); //alocando memoria

    if(lst != NULL){ //verificando se o ponteiro do primeiro elemento nao eh null
        lst->fim = 0; //apontando pro primeiro elemento
    }
    return lst; //retorna o endereco da primeira posicao
};


/*
LISTA_VAZIA()
entrada: ponteiro struct lista.
pre-condicao: a lista existir.
processo: Verifica se a lista e igual NULL ou o fim = 0.
saida: Retorna 1 se alguma das condicionais for true, 0 sen�o.
pos-condicao: Nenhuma.
*/
int lista_vazia(Lista lst){
    if(lst == NULL || lst->fim == 0){ //se fim da lista == 0 quer dizer que esta vazia
        return 1;
    }else{
        return 0;
    }
}


/*
LISTA_CHEIA()
entrada: ponteiro struct lista.
pre-condicao: a lista existir.
processo: Verifica se a lista e igual NULL ou o fim = 0.
saida: Retorna 1 se alguma das condicionais for true, 0 sen�o.
pos-condicao: Nenhuma.
*/
int lista_cheia(Lista lst){
    if(lst == NULL || lst->fim == MAX_ALUNOS){ //ate a posicao MAX-1 tera elementos, isto e, lista cheia.
        return 1;
    }else{
        return 0;
    }
}


/*
TAMANHO_LISTA()
entrada: ponteiro struct lista e elemento do tipo aluno.
pre-condicao: lista existir.
processo: retornar a quantidade de elementos na lista.
saida: Retorna 0 se a  lista nao existir, e o tamanho da lista caso exista.
pos-condicao: nenhuma.
*/
int tamanho_lista(Lista lst){
    if(lst == NULL){
        return 0;
    }
    return lst->fim;
}


/*
ESVAZIAR_LISTA()
entrada: ponteiro struct lista.
pre-condicao: a lista existir e nao estar vazia.
processo: Verifica se a lista e igual NULL ou esta vazia.
saida: Retorna 1 se alguma das condicionais for false, 0 se true.
pos-condicao: Lista sera esvaziada, mas ainda ocupara espaco na memoria.
*/
int esvaziar_lista(Lista lst){
    if(lst == NULL || lista_vazia(lst)){
        return 0;
    }

    lst->fim = 0;
    return 1;
}


/*
APAGAR_LISTA()
entrada: endereco do ponteiro struct lista.
pre-condicao: ponteiro e o ponteiro que ele aponta devem ser validos.
processo: liberar a memoria alocada pra lista e atribuir null ao ponteiro.
saida: Retorna 1 se alguma das condicionais for false, 0 se true.
pos-condicao: a memoria alocada pra lista e liberada e o ponteiro aponta pra NULL.
*/
int apagar_lista(Lista *lst){//passagem do endereco do ponteiro da lista
    if(lst == NULL || *lst == NULL){
        return 0;
    }

    free(*lst);  //liberando a memoria
    *lst = NULL; //atribui null ao endereco do ponteiro da lista
    return 1;
}


/*
INSERE_ELEM()
entrada: ponteiro struct lista e elemento do tipo aluno.
pre-condicao: lista existir e nao estar cheia.
processo: inserir elemento no final da lista e incrementar +1 o fim da lista.
saida: Retorna 1 se conseguir inserir no fim da lista.
pos-condicao: elemento e inserido no fim da lista e fim da lista e incrementado em +1.
*/
int insere_elem(Lista lst, Aluno student){
    if(lst == NULL || lista_cheia(lst)){
        return 0;
    }

    lst->student[lst->fim] = student;
    lst->fim++;
    return 1;
}


/*
INSERE_ELEMETO_POS()
entrada: ponteiro struct lista, struct aluno, posicao a ser incluido.
pre-condicao: lista existir, n�o estar cheia e a posicao ser valida (menor que o fim da lista e maior que 1).
processo: percorrer lista, deslocar os elemento para a direita e inserir o sluno na posicao desejada.
saida: Retorna 0 se falhar nas condicionais ou 1 se o elemento for inserido na posicao desejada.
pos-condicao: o fim da lista e incrementado em 1.
*/
int insere_elem_pos(Lista lst, Aluno student, int pos){

    if(lst == NULL || lista_cheia(lst) || pos > lst->fim+1 || pos < 1){
        return 0;
    }

    for(int i=lst->fim-1; i >= pos-1; i--){
        lst->student[i+1] = lst->student[i];
    }
    lst->student[pos-1] = student;
    lst->fim++;
    return 1;
}


/*
REMOVE_ELEMETO()
entrada: ponteiro struct lista e matricula do elemento.
pre-condicao: lista existir, n�o estar vazia e a matricula existir.
processo: percorrer lista e deslocar os elementos posterior aquele que sera removido para a esquerda.
saida: Retorna 0 se falhar nas condicionais ou 1 se o elemento for removido.
pos-condicao: o fim da lista e decrementado em 1.
*/
int remove_elem(Lista lst, char *matricula){
    if(lst == NULL || lista_vazia(lst)){
        return 0;
    }

    int aux = -1;
    int i = 0;
    for(i; i < lst->fim; i++){
        if(strcmp(lst->student[i].matricula, matricula) == 0){
            aux = i; //guarda a posicao onde o aluno foi encontrado
            break;
        }
    }

    if(aux == -1){
        return 0; //falha, elemento nao encontrado
    }

    //desloca os elementos pra esquerda
    for(i = aux; i < lst->fim-1; i++){
        lst->student[i] = lst->student[i+1];
    }

    lst->fim--;
    return 1;

}


/*
GET_ELEM_POS()
entrada: Lista lst, posi��o 'pos' do aluno e ponteiro '*student' para retorno.
pre-condicao: Lista existir e 'pos' ser uma posi��o v�lida (1 <= pos <= fim).
processo: Valida as condi��es e copia o aluno da lista[pos-1] para '*student'.
saida: 1 em caso de sucesso, 0 em caso de falha. Dados retornados via ponteiro.
pos-condicao: A lista n�o � alterada. '*student' recebe a c�pia do aluno.
*/
int get_elem_pos(Lista lst, int pos, Aluno *student){

    if(lst == NULL || lista_vazia(lst) || pos > lst->fim+1 || pos < 1){
        return 0;
    }
    *student = lst->student[pos-1];
    return 1;
}


/*
REMOVE_MENOR()
entrada: Ponteiro para a lista e ponteiro para um Aluno que receber� os dados do removido.
pre-condicao: A lista deve existir e n�o estar vazia.
processo: Procura pelo aluno com a menor matr�cula (usando strcmp). Ap�s encontrar, copia seus dados para a vari�vel de retorno e o remove da lista,
          deslocando os elementos posteriores para a esquerda.
saida: Retorna 1 se a remo��o for bem-sucedida, 0 caso contr�rio.
pos-condicao: A lista fica com um elemento a menos. Os dados do aluno removido s�o retornados atrav�s do ponteiro 'aluno_removido'.
*/
int remove_menor(Lista lst, Aluno *aluno_removido) {
    if (lista_vazia(lst)) {
        return 0;
    }

    int i;
    int pos_menor = 0; // Assume que o primeiro � o menor inicialmente

    // 1. Encontra a posi��o do aluno com a menor matr�cula
    for (i = 1; i < lst->fim; i++) {
        // strcmp retorna < 0 se a string1 for menor que a string2
        if (strcmp(lst->student[i].matricula, lst->student[pos_menor].matricula) < 0) {
            pos_menor = i;
        }
    }

    // 2. Copia os dados do aluno a ser removido para o ponteiro de retorno
    *aluno_removido = lst->student[pos_menor];

    // 3. Remove o aluno da lista, deslocando os elementos
    for (i = pos_menor; i < lst->fim - 1; i++) {
        lst->student[i] = lst->student[i+1];
    }

    lst->fim--;
    return 1;
}


/*
REMOVE_FALTOSOS()
entrada: Ponteiro para a lista e o n�mero m�ximo de faltas permitidas.
pre-condicao: A lista deve existir.
processo: Percorre a lista usando uma t�cnica de "filtro no lugar".
          Mant�m um �ndice 'j' para a pr�xima posi��o v�lida. Se um aluno n�o for "faltoso" (faltas <= max_faltas), ele � copiado para a posi��o 'j'.
          Alunos "faltosos" s�o simplesmente ignorados (sobrescritos).
saida: Retorna a quantidade de alunos que foram removidos.
pos-condicao: A lista cont�m apenas os alunos com n�mero de faltas dentro
              do limite. O 'fim' da lista � atualizado.
*/
int remove_faltosos(Lista lst, int max_faltas) {
    if (lista_vazia(lst)) {
        return 0; // Nenhum aluno removido
    }

    int i;
    int j = 0; // �ndice para a posi��o do pr�ximo aluno "n�o-faltoso"
    int removidos_cont = 0;
    int fim_original = lst->fim;

    for (i = 0; i < fim_original; i++) {
        // Se o aluno atual N�O deve ser removido
        if (lst->student[i].faltas <= max_faltas) {
            // Se i e j forem diferentes, significa que houve remo��es
            // e precisamos mover o aluno para a posi��o correta
            if (i != j) {
                lst->student[j] = lst->student[i];
            }
            j++; // Avan�a o �ndice dos "n�o-faltosos"
        }
        // Se o aluno DEVE ser removido (faltas > max_faltas),
        // ele � simplesmente "ignorado". O 'j' n�o avan�a,
        // e ele ser� sobrescrito por um futuro aluno "n�o-faltoso".
    }

    removidos_cont = fim_original - j;
    lst->fim = j; // Atualiza o novo fim da lista

    return removidos_cont;
}


/*
CONCATENA()
entrada: Duas listas (l1 e l2).
pre-condicao: As listas l1 e l2 devem existir. A soma dos seus tamanhos n�o
              pode exceder a capacidade m�xima da lista (MAX_ALUNOS).
processo: Cria uma terceira lista (l3). Copia todos os elementos de l1 para l3,
          e em seguida, todos os elementos de l2 para l3.
saida: Retorna um ponteiro para a nova lista l3. Retorna NULL se a opera��o
       falhar (mem�ria insuficiente ou tamanho combinado excede o limite).
pos-condicao: As listas originais (l1 e l2) n�o s�o alteradas. Uma nova lista
              � alocada na mem�ria.
*/
Lista concatena(Lista l1, Lista l2) {
    if (l1 == NULL || l2 == NULL) {
        return NULL; // Listas de entrada inv�lidas
    }

    // Verifica se a lista resultante caber� no espa�o m�ximo
    if ((l1->fim + l2->fim) > MAX_ALUNOS) {
        return NULL; // Falha: a lista concatenada seria maior que o permitido
    }

    // Cria a nova lista
    Lista l3 = cria_lista();
    if (l3 == NULL) {
        return NULL; // Falha ao alocar mem�ria para a nova lista
    }

    int i;
    // Copia elementos de l1 para l3
    for (i = 0; i < l1->fim; i++) {
        // Usando atribui��o direta, pois n�o h� necessidade de deslocamento
        l3->student[i] = l1->student[i];
    }
    l3->fim = l1->fim; // Atualiza o fim de l3

    // Copia elementos de l2 para l3
    for (i = 0; i < l2->fim; i++) {
        l3->student[l3->fim] = l2->student[i];
        l3->fim++;
    }

    return l3;
}

