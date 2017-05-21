
/*
 * Compile com: gcc -o par par.c -Wall
 *
 * Execução: par
 */

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>


void even(void) {
    int i;

     for (i =0; i <=10; i=i+2 )
         printf("%3d", i);

     return;

     /* A função even ao terminar vai para a função indicada por:
      * "setcontext(&even_context->uc_link);", ou seja, a main,
      *  no retorno da chamada "getcontext(&main_context)" */
}

int main(void)
{

    ucontext_t main_context, even_context;
    char even_stack[SIGSTKSZ];  /* Pilha para o contexto even */
    int ret_code;               /* Flag para identificar o tipo de retorno de getcontext */

    /* É necessário criar uma estrutura contexto a partir de um molde.
     * O contexto da propria main serve como esse molde. */

    getcontext(&even_context);

    /* Modifica-se o molde o novo fluxo a ser criado. Cada fluxo
     * de controle recebe para qual contexto ele deve ir quando acabar
     * (uc_link), uma pilha (ss_sp) e o tamanho da mesma. */

    even_context.uc_link          = &main_context;
    even_context.uc_stack.ss_sp   = even_stack;
    even_context.uc_stack.ss_size = sizeof(even_stack);

    /* Define ainda a função a ser executada pelo fluxo de controle,
     * a quantidade (0, no caso) e os eventuais parâmetros que cada fluxo
     * recebe (nenhum). O typecast (void (*)(void)) é só para evitar warnings na
     * compilação e não afeta o comportamento da função */

    makecontext(&even_context, (void (*)(void)) even, 0);

    /* salva o contexto da main em main_context1. Quando a função "even" acabar
     * o fluxo de controle será retomado a partir deste ponto devido ao fato
     * do campo uc_link (acima) estar apontando para main_context */

    ret_code = 0;
    getcontext(&main_context);

    if (!ret_code) {
       /* Testa a variável even_finished para diferenciar se a função getcontext
          anterior retornou via uc_link (se ret_code==1) depois do término de
          even ou se ela retornou após a sua chamada simples */

        ret_code = 1;
        setcontext(&even_context); /* posiciona o contexto para even */
        printf("NUNCA será executado!\n");
        return(-1);   /* nunca será executado! */
    }

    printf("\n\n Terminando a main...\n");
    return 0;
}
