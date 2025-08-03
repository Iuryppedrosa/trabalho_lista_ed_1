#ifndef LIST_ESTATIC_H_INCLUDED
#define LIST_ESTATIC_H_INCLUDED

//Estrutura pra armazenar os dados de um aluno
typedef struct{
    char matricula[10];
    float nota_final;
    int faltas;
    int status; //aprovado=1 ou reprovado=0
} Aluno;

//ponteiro pra estrutura lista
typedef struct lista *Lista;

// --- PROTÓTIPOS ---

// Funções de Criação e Destruição
Lista cria_lista();
int apagar_lista(Lista *lst);

// Funções de Status da Lista
int lista_vazia(Lista lst);
int lista_cheia(Lista lst);
int tamanho_lista(Lista lst);
int esvaziar_lista(Lista lst);

// Funções de Manipulação de Elementos
int insere_elem(Lista lst, Aluno student);
int insere_elem_pos(Lista lst, Aluno student, int pos);
int remove_elem(Lista lst, char *matricula);
int get_elem_pos(Lista lst, int pos, Aluno *student);
int remove_menor(Lista lst, Aluno *aluno_removido);
int remove_faltosos(Lista lst, int max_faltas);
Lista concatena(Lista l1, Lista l2);

#endif // LIST_ESTATIC_H_INCLUDED
