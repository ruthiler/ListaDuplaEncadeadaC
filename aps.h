#include <string.h>
#define MIL 1000
#define MILHAO MIL * MIL

typedef struct str_noh {
    long long cpf;
    struct str_noh *anterior;
    struct str_noh *proximo;
} noh;

noh * vetor[1 * MILHAO];
int retirado=0;

noh * novo_noh(long long cpf) {
    noh * novo;
    novo = (noh *)malloc(sizeof(noh));
    novo->cpf = cpf;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
}

void clean(noh * lista) {
    noh * atual = lista;
    noh * clear;

    if (lista == NULL)
        return;

    printf("Iniciando limpeza...\n");
    while (atual->proximo != NULL) {
        clear = atual;
        atual = atual->proximo;
        free(clear);
    }
    printf("Concluindo limpeza...\n");
    if(atual)
        free(atual);

    printf("Limpeza concluida.\n");
}

noh * inserir_no_inicio(noh ** lista, long long cpf) {

    noh * cabeca = *lista;
    noh * n = novo_noh(cpf);

    if (cabeca == NULL)
    {
        *lista = n;
        return n;
    }

    (*lista)->anterior = n;
    n->proximo = *lista;
    *lista = n;

    return n;
}

noh * carregar_do_arquivo(noh ** lista, char * nome_arquivo) {
	FILE * fp;
	char * line;
	char * ptr;
	long cpf;
	size_t len = 0;
	size_t read;

	fp = fopen(nome_arquivo, "r");
	if (fp == NULL) {
		printf("Falha ao abrir o arquivo. MOTIVO: %d", EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}

	int i=0;
	while ((read = getline(&line, &len, fp)) != -1) {
		vetor[i++] = inserir_no_inicio(lista, strtol(line, &ptr, 10));
	}

	fclose(fp);
	if (line)
		free(line);

	return *lista;
}

int cpf_retirado () {

    return retirado;
}

int tamanho_lista(noh * lista) {

    noh*atual=lista;
    int tam=0;

    while (atual != NULL) {
        atual=atual->proximo;
        tam++;
    }
    return tam;
}


int buscar(long long cpf) {       //FAZ A BUSCA BINARIA NO VETOR

    int inicio=0;
    int fim=MILHAO-1;
    int meio=0;

    while(inicio<=fim) {
        meio=(inicio+fim)/2;

        if(cpf<vetor[meio]->cpf) {
            fim=meio-1;
        }else{
            if(cpf>vetor[meio]->cpf){
                inicio=meio+1;
            }else{
               return meio;
               break;
            }
        }
    }
    return -1; // RETORNA -1 SE NAO ENCONTRAR O CPF
}

void removelist (noh ** lista, long long cpf) {    //Remove o CPF da lista

    int pos;

    if(*lista==NULL) {                   // Verifica se a lista nao esta vazia. Se estiver para a função e retorna.
        printf("A lista já esta VAZIA. Pressione '0' (zero) para sair.\n\n");
        return;
    }

    pos=buscar(cpf);      // Chama a funcao buscar e se encontrar retorna o valor para retirar da lista

    if(pos==-1) {                   // Verifica se a função buscar encontrou, se nao encontrou para a função e retorna.
        printf("> CPF nao encontrado ou ja retirado da lista.\n\n");
        return;
    }

    long long cpf_localizado=vetor[pos]->cpf;

    if(vetor[pos]->anterior && vetor[pos]->proximo == NULL) {
        free(vetor[pos]);
        *lista=NULL;
        printf("> CPF %011lld encontrado e retirado da lista.\n", cpf_localizado);
        printf("> A Lista está Vazia");  //Avisa se o elemento foi encontrado e retirado da lista
        retirado++;
        return;
    }

    if(vetor[pos]->proximo != NULL) {                            // Exclue o elemento da lista e libera a memoria
        vetor[pos]->proximo->anterior= vetor[pos]-> anterior;
    }
    if(vetor[pos]-> anterior != NULL) {
        vetor[pos]->anterior->proximo = vetor[pos]-> proximo;
        free(vetor[pos]);
    }else{
        (*lista) = vetor[pos]-> proximo;
        free(vetor[pos]);
    }
    printf("> CPF %011lld encontrado e retirado da lista.\n\n", cpf_localizado);  //Avisa se o elemento foi encontrado e retirado da lista
    retirado++;    //Conta quantos elementos foram retirados
}



void intercala(int inicio, int meio, int fim) {  //Junta e ordena os elementos separados no mergesort

    int i,j,k;

    noh ** aux;
    aux = (noh**)calloc(fim-inicio+1,sizeof(noh));

    i = inicio;
    j = meio+1;
    k = 0;

    while( i<=meio && j<=fim ) {

        if ( vetor[i]->cpf <= vetor[j]->cpf ) {
            aux[k] = vetor[i];
            i++;
        }else{
            aux[k] = vetor[j];
            j++;
        }
        k++;
    }

    while( i <= meio ) {
        aux[k] = vetor[i];
        i++;
        k++;
    }

    while( j <= fim ) {
        aux[k] = vetor[j];
        j++;
        k++;
    }

    for( i = 0; i< (fim - inicio)+1; i++) {
        vetor[inicio + i] = aux[i];
    }

    free(aux);
    return;
}

void mergesort(int inicio,int fim) {

    int meio;

    if (inicio < fim){
        meio = (inicio+fim)/2;
        mergesort(inicio, meio);
        mergesort(meio+1, fim);
        intercala(inicio, meio, fim);
    }

    return;
}


void ordenar() {
    mergesort(0, MILHAO-1);
}


