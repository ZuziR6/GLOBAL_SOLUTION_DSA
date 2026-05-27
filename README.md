# Global Solution — Missão de Exploração Espacial Autônoma

## Descrição
Sistema em linguagem C para gerenciamento de Rovers autônomos utilizando estruturas de dados como lista ligada, fila FIFO, ordenação com qsort e busca binária.

## Funcionalidades
- Cadastro de Rovers
- Remoção dinâmica
- Lista ligada dinâmica
- Simulação de desgaste com rand()
- Geração de telemetria em arquivo (.txt)
- Fila FIFO para comunicação
- Ordenação com qsort
- Busca binária por ID

## Execução
Compile e execute:

```bash
gcc main.c -o rover
./rover


Projeto acadêmico — Data Structures and Algorithms


---

# 📌 PARTE 2 — main.c (organização explicada por blocos)

## 🔹 BLOCO 1 — Bibliotecas

```c id="g1"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
🔹 BLOCO 2 — Struct Rover (modelo principal)
typedef struct Rover {
    int id;
    char nome[50];
    float distancia;
    float bateria;
    int desgaste;
    struct Rover *prox;
} Rover;
🔹 BLOCO 3 — Struct Fila (telemetria FIFO)
typedef struct Mensagem {
    char texto[100];
    struct Mensagem *prox;
} Mensagem;

typedef struct {
    Mensagem *inicio;
    Mensagem *fim;
} Fila;
🔹 BLOCO 4 — Cadastro (lista ligada)
Rover* cadastrarRover(Rover *lista);

✔ Insere no início da lista
✔ Usa malloc
✔ Estrutura dinâmica

🔹 BLOCO 5 — Remoção
Rover* removerRover(Rover *lista, int id);

✔ Percorre lista
✔ Remove nó corretamente
✔ Libera memória

🔹 BLOCO 6 — Listagem
void listarRovers(Rover *lista);

✔ Percorre lista ligada
✔ Exibe todos os dados

🔹 BLOCO 7 — Simulação de desgaste
void atualizarDesgaste(Rover *lista);

✔ rand()
✔ time(NULL) no main
✔ altera dados via ponteiro

🔹 BLOCO 8 — Persistência em arquivo
void gerarRelatorio(Rover *lista);

✔ fopen
✔ fprintf
✔ fclose
✔ gera telemetria.txt

🔹 BLOCO 9 — Fila FIFO
Fila* inicializarFila();
void enqueue(Fila *f, char texto[]);
void dequeue(Fila *f);
void enviarTelemetria(Fila *f);

✔ estrutura FIFO
✔ ordem cronológica
✔ simulação de envio

🔹 BLOCO 10 — Ordenação (qsort)
int contarRovers(Rover *lista);
int compararRovers(const void *a, const void *b);
void ordenarRovers(Rover *lista);

✔ transforma lista → vetor
✔ usa qsort obrigatório

🔹 BLOCO 11 — Busca Binária
int buscarBinaria(Rover **vetor, int n, int id);
void buscarRover(Rover *lista, int id);

✔ algoritmo O(log n)
✔ exige vetor ordenado

🔹 BLOCO 12 — MAIN (menu do sistema)
int main();

✔ menu interativo
✔ integração de todas funções
✔ srand(time(NULL)) aqui
