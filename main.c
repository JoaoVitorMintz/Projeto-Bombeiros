#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_ARESTAS 200

// Função que ordena esquinas do menor tempo para o maior tempo.
void reordenar_sequencia(int origem[], int destino[], int tempo[], int qtdArestas) {
    for (int i = 0; i < qtdArestas - 1; i++) {
        for (int j = i+1; j < qtdArestas; j++) {
            if (tempo[i] > tempo[j]) {
                // Reordenar para começar com o menor valor de tempo no vetor
                int temp = tempo[i];
                tempo[i] = tempo[j];
                tempo[j] = temp;

                // Reordenar origem para manter a sequência com base no tempo
                temp = origem[i];
                origem[i] = origem[j];
                origem[j] = temp;

                // Reordenar destino para manter a sequência com base no tempo
                temp = destino[i];
                destino[i] = destino[j];
                destino[j] = temp;
            }
        }
    }
}

// Função que cria um vetor com o menor tempo percorrido.
void rota_mais_rapida_dijkstra(int origem[], int destino[], int tempo[], int n, int m, int qtdArestas) {
    reordenar_sequencia(origem, destino, tempo, qtdArestas);
    
    int grafo[m + 1][m + 1];
    int dist[m + 1];
    int anterior[m + 1];
    bool visitado[m + 1];

    // Inicializa a matriz (Dijkstra é usado com grafo então é uma adaptação para matriz) e vetores auxiliares
    for (int i = 1; i <= m; i++) {
        dist[i] = INT_MAX;
        anterior[i] = -1;
        visitado[i] = false;
        for (int j = 1; j <= m; j++) {
            grafo[i][j] = INT_MAX;
        }
    }

    // Preenche a matriz com as arestas
    for (int i = 0; i < qtdArestas; i++) {
        grafo[origem[i]][destino[i]] = tempo[i];
    }

    int inicio = 1; // esquina inicial é sempre 1 (bombeiros)
    dist[inicio] = 0;

    // Dijkstra
    for (int i = 1; i <= m; i++) {
        int u = -1;

        for (int j = 1; j <= m; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INT_MAX) break;

        visitado[u] = true;

        for (int v = 1; v <= m; v++) {
            if (grafo[u][v] != INT_MAX && dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
                anterior[v] = u;
            }
        }
    }

    // Exibe o resultado apenas com a rota e tempo total
    if (dist[n] == INT_MAX) {
        printf("\nNao ha rota ate a esquina %d.\n", n);
        return;
    }

    int caminho[MAX_ARESTAS];
    int tam = 0;
    for (int v = n; v != -1; v = anterior[v]) {
        caminho[tam++] = v;
    }

    printf("\nRota mais rapida ate a esquina %d:\n", n);
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d", caminho[i]);
        if (i > 0) printf(" -> ");
    }

    printf("\nTempo total da rota = %d min.\n", dist[n]);
}

int main(void) {
    int n; // número da esquina onde ocorre o incêndio.
    int m; // número de esquinas que constam no mapa.
    FILE *entrada; // Variável para leitura do bombeiro.txt.
    char linha[100];
    int origem[MAX_ARESTAS]; // Vetor que armazena o ponto de origem
    int destinos[MAX_ARESTAS]; // Vetor que armazena o ponto de chegada
    int tempo[MAX_ARESTAS]; // Vetor que armazena o tempo entre os dois pontos
    int a, b, t;
    int qtdArestas = 0;

    entrada = fopen("bombeiro.txt", "r");

    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fscanf(entrada, "%d", &n);
    fscanf(entrada, "%d", &m);

    printf("Esquina onde está ocorrendo o incêndio: %d\n", n);
    printf("Total de esquinas no mapa: %d\n", m);    
    printf("informações do bombeiro.txt:");
    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        printf("%s", linha);
    }

    // Volta para o início do arquivo para reler as arestas
    rewind(entrada);

    fscanf(entrada, "%d", &n);
    fscanf(entrada, "%d", &m);

    while(1) {
        fscanf(entrada, "%d", &a);
        if (a == 0) break; // Fim do arquivo
        fscanf(entrada, "%d %d", &b, &t);

        origem[qtdArestas] = a;
        destinos[qtdArestas] = b;
        tempo[qtdArestas] = t;
        qtdArestas++;
    }

    fclose(entrada);

    rota_mais_rapida_dijkstra(origem, destinos, tempo, n, m, qtdArestas);

    return 0;
}