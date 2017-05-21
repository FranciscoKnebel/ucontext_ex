/*
 * Compile com: gcc -o parimpar parimpar.c -Wall
 *
 * Execução: parimpar
 */

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

void even(ucontext_t *ctx1, ucontext_t *ctx2) {
    int i;
     for (i =0; i <=10; i=i+2 ) {
         printf("%3d", i);
         swapcontext(ctx1, ctx2);
     }

     /* A função even ao terminar vai para a função indicada por:
      * "setcontext(&even_context->uc_link);", ou seja, a main */
}

void odd(ucontext_t *ctx1, ucontext_t *ctx2) {
    int i;

     for (i =1; i <=9; i=i+2 ) {
         printf("%3d", i);
         swapcontext(ctx2, ctx1);
     }

     /* A função even ao terminar vai para a função indicada por:
      * "setcontext(&even_context->uc_link);", ou seja, a even  */
}


int main(void)
{

    ucontext_t main_context, even_context, odd_context;
    char even_stack[SIGSTKSZ];  /* Pilha para o contexto even */
    char odd_stack[SIGSTKSZ];   /* Pilha para o contexto even */

    int even_finished = 0;      /* Flag para indicar que even terminou */

    /* É necessário criar uma estrutura contexto a partir de um molde.
     * O contexto da propria main serve como esse molde. */

    getcontext(&even_context);
    getcontext(&odd_context);

    /* Modifica-se o molde para cada novo fluxo a ser criado. Cada fluxo
     * de controle recebe para qual contexto ele deve ir quando acabar
     * (uc_link), uma pilha (ss_sp) e o tamanho da mesma. */

    even_context.uc_link          = &main_context;
    even_context.uc_stack.ss_sp   = even_stack;
    even_context.uc_stack.ss_size = sizeof(even_stack);

    odd_context.uc_link          = &even_context;
    odd_context.uc_stack.ss_sp   = odd_stack;
    odd_context.uc_stack.ss_size = sizeof(odd_stack);

    /* Define ainda a função a ser executada por cada fluxo de controle,
     * a quantidade (2, no caso) e os eventuais parâmetros que cada fluxo
     * recebe. O typecast (void (*)(void)) é só para evitar warnings na
     * compilação e não afeta o comportamento da função */

    makecontext(&even_context, (void (*)(void)) even, 2, &even_context, &odd_context);
    makecontext(&odd_context, (void (*)(void)) odd, 2, &even_context, &odd_context);

    /* salva o contexto da main em main_context1. Quando a função par acabar
       o fluxo de controle será retomado a partir de onde parou */

    getcontext(&main_context);


    if (!even_finished) {
       /* Testa a variável even_finished para diferenciar se a função getcontext
          anterior retornou via uc_link (even_finish==1) depois da execução de even
          ou se ela retornou da chamada simples */

        even_finished = 1;
        setcontext(&even_context); /* posiciona o contexto para even */
        printf("NUNCA será executado!\n");
        return(-1);   /* nunca será executado! */
    }

    printf("\n\n Terminando a main...\n");
    return 0;
}
