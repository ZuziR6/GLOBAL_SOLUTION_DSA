#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Rover {
    int id;
    char nome[50];
    float distancia;
    float bateria;
    int desgaste;
    struct Rover *prox;
} Rover;

typedef struct Mensagem {
    char texto[100];
    struct Mensagem *prox;
} Mensagem;

typedef struct {
    Mensagem *inicio;
    Mensagem *fim;
} Fila;

/* PROTÓTIPOS */
Rover* cadastrarRover(Rover *lista);
Rover* removerRover(Rover *lista, int id);
void listarRovers(Rover *lista);
void atualizarDesgaste(Rover *lista);
void gerarRelatorio(Rover *lista);

Fila* inicializarFila();
void enqueue(Fila *f, char texto[]);
void dequeue(Fila *f);
void enviarTelemetria(Fila *f);

int contarRovers(Rover *lista);
int compararRovers(const void *a, const void *b);
void ordenarRovers(Rover *lista);

int buscarBinaria(Rover **vetor, int n, int id);
void buscarRover(Rover *lista, int id);

/* LISTA LIGADA */
Rover* cadastrarRover(Rover *lista) {
    Rover *novo = (Rover*) malloc(sizeof(Rover));

    printf("\nID do Rover: ");
    scanf("%d", &novo->id);

    printf("Nome do Rover: ");
    scanf("%s", novo->nome);

    printf("Distancia percorrida: ");
    scanf("%f", &novo->distancia);

    printf("Nivel de bateria: ");
    scanf("%f", &novo->bateria);

    novo->desgaste = rand() % 100;

    novo->prox = lista;

    printf("\nRover cadastrado com sucesso!\n");

    return novo;
}

Rover* removerRover(Rover *lista, int id) {
    Rover *atual = lista;
    Rover *anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\nRover nao encontrado.\n");
        return lista;
    }

    if (anterior == NULL) {
        lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);

    printf("\nRover removido com sucesso!\n");

    return lista;
}

void listarRovers(Rover *lista) {
    Rover *aux = lista;

    if (aux == NULL) {
        printf("\nNenhum rover cadastrado.\n");
        return;
    }

    printf("\n===== FROTA DE ROVERS =====\n");

    while (aux != NULL) {
        printf("\nID: %d", aux->id);
        printf("\nNome: %s", aux->nome);
        printf("\nDistancia: %.2f km", aux->distancia);
        printf("\nBateria: %.2f%%", aux->bateria);
        printf("\nDesgaste: %d%%\n", aux->desgaste);

        aux = aux->prox;
    }
}

/* DESGASTE */
void atualizarDesgaste(Rover *lista) {
    Rover *aux = lista;

    if (aux == NULL) {
        printf("\nNenhum rover cadastrado.\n");
        return;
    }

    while (aux != NULL) {
        aux->desgaste += rand() % 20;

        if (aux->desgaste > 100) aux->desgaste = 100;

        aux->bateria -= rand() % 15;

        if (aux->bateria < 0) aux->bateria = 0;

        aux = aux->prox;
    }

    printf("\nStatus dos rovers atualizado com sucesso!\n");
}

/* ARQUIVO */
void gerarRelatorio(Rover *lista) {
    FILE *arquivo = fopen("telemetria.txt", "w");

    if (!arquivo) {
        printf("\nErro ao criar arquivo.\n");
        return;
    }

    Rover *aux = lista;

    fprintf(arquivo, "===== RELATORIO DE TELEMETRIA =====\n");

    while (aux != NULL) {
        fprintf(arquivo, "\nID: %d\n", aux->id);
        fprintf(arquivo, "Nome: %s\n", aux->nome);
        fprintf(arquivo, "Distancia: %.2f\n", aux->distancia);
        fprintf(arquivo, "Bateria: %.2f\n", aux->bateria);
        fprintf(arquivo, "Desgaste: %d\n", aux->desgaste);

        aux = aux->prox;
    }

    fclose(arquivo);

    printf("\nRelatorio gerado com sucesso!\n");
}

/* FILA */
Fila* inicializarFila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void enqueue(Fila *f, char texto[]) {
    Mensagem *novo = (Mensagem*) malloc(sizeof(Mensagem));
    strcpy(novo->texto, texto);
    novo->prox = NULL;

    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void dequeue(Fila *f) {
    if (f->inicio == NULL) return;

    Mensagem *temp = f->inicio;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL)
        f->fim = NULL;

    free(temp);
}

void enviarTelemetria(Fila *f) {
    printf("\n===== TELEMETRIA FIFO =====\n");

    while (f->inicio != NULL) {
        printf("Enviando: %s\n", f->inicio->texto);
        dequeue(f);
    }

    printf("\nEnvio concluido.\n");
}

/* ORDENACAO */
int contarRovers(Rover *lista) {
    int c = 0;
    while (lista) {
        c++;
        lista = lista->prox;
    }
    return c;
}

int compararRovers(const void *a, const void *b) {
    Rover *r1 = *(Rover**)a;
    Rover *r2 = *(Rover**)b;
    return r1->id - r2->id;
}

void ordenarRovers(Rover *lista) {
    int n = contarRovers(lista);
    if (n == 0) return;

    Rover **vetor = malloc(n * sizeof(Rover*));

    Rover *aux = lista;
    for (int i = 0; i < n; i++) {
        vetor[i] = aux;
        aux = aux->prox;
    }

    qsort(vetor, n, sizeof(Rover*), compararRovers);

    printf("\n===== ROVERS ORDENADOS =====\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nome: %s\n", vetor[i]->id, vetor[i]->nome);
    }

    free(vetor);
}

/* BUSCA BINARIA */
int buscarBinaria(Rover **vetor, int n, int id) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        if (vetor[meio]->id == id)
            return meio;

        if (vetor[meio]->id < id)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

void buscarRover(Rover *lista, int id) {
    int n = contarRovers(lista);
    if (n == 0) return;

    Rover **vetor = malloc(n * sizeof(Rover*));

    Rover *aux = lista;
    for (int i = 0; i < n; i++) {
        vetor[i] = aux;
        aux = aux->prox;
    }

    qsort(vetor, n, sizeof(Rover*), compararRovers);

    int pos = buscarBinaria(vetor, n, id);

    if (pos == -1) {
        printf("\nRover nao encontrado.\n");
    } else {
        printf("\nROVER ENCONTRADO:\n");
        printf("ID: %d\n", vetor[pos]->id);
        printf("Nome: %s\n", vetor[pos]->nome);
        printf("Distancia: %.2f\n", vetor[pos]->distancia);
        printf("Bateria: %.2f\n", vetor[pos]->bateria);
        printf("Desgaste: %d\n", vetor[pos]->desgaste);
    }

    free(vetor);
}

/* MAIN */
int main() {
    Rover *lista = NULL;
    Fila *fila = inicializarFila();

    int opcao, id;

    srand(time(NULL));

    do {
        printf("\n===== MENU =====\n");
        printf("1 Cadastrar\n2 Remover\n3 Listar\n4 Desgaste\n5 Relatorio\n6 Fila\n7 Ordenar\n8 Buscar\n0 Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                lista = cadastrarRover(lista);
                break;
            case 2:
                scanf("%d", &id);
                lista = removerRover(lista, id);
                break;
            case 3:
                listarRovers(lista);
                break;
            case 4:
                atualizarDesgaste(lista);
                break;
            case 5:
                gerarRelatorio(lista);
                break;
            case 6:
                enqueue(fila, "Telemetria enviada");
                enqueue(fila, "Status atualizado");
                enviarTelemetria(fila);
                break;
            case 7:
                ordenarRovers(lista);
                break;
            case 8:
                scanf("%d", &id);
                buscarRover(lista, id);
                break;
        }

    } while (opcao != 0);

    return 0;
}
