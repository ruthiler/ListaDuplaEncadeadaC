#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "aps.h"

int main(void) {

    setlocale(LC_ALL, "Portuguese");

    noh * lista = NULL;
    long long busca_cpf;
    char cpf[11];
    char continuar;


	  printf("Carregando...\n");
    carregar_do_arquivo(&lista, "aps.txt");

    printf("Ordenando...\n");
    ordenar();
    printf("Ordenado!\n");

    printf("\nA Lista tem %d elementos.\n", tamanho_lista(lista));
    printf("\n");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
    printf("\n\n");


    do {

       do{
            printf("DIGITE O NÚMERO DO CPF PARA PESQUISAR E EXCLUIR DA LISTA.\n\n");
            printf("Digite o CPF: ");
            scanf("%s", cpf);
            busca_cpf=atoll(cpf);

            if (busca_cpf!=0) {
                printf("\n");
                removelist(&lista,busca_cpf);
            }else{
                printf("\nDigite um número válido.\n");
            }

       }while (busca_cpf==0);

       printf("\nPressione 0 para sair ou qualquer tecla para continuar:  ");
       scanf("%s", &continuar);

       system("clear");

  }while (continuar!='0');    // Busca o CPF digitado pelo usuario
                             // e repete ate que o mesmo digite 0 (zero)

	printf("\n");
	printf("Retirado(s) %d elemento(s) da lista.\n", cpf_retirado());    //Conta quantos elementos foram retirados da lista
	printf("A Lista tem %d elementos.\n", tamanho_lista(lista));         //Conta quantos elementos ainda restam na lista

	// Antes de sair do programa, limpa e libera de volta a memoria utilizada

	printf("\n");
	clean(lista);

	printf("\nPressione ENTER...\n");
	getchar();
  getchar();

	exit(EXIT_SUCCESS);
}
