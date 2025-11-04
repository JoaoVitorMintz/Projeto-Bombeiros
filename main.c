#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

}

int main(void) {
    int n; // número da esquina onde ocorre o incêndio.
    int m; // número de esquinas que constam no mapa.
    FILE *entrada; // Variável para leitura do bombeiro.txt.
    int linha[100];
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
    printf("\nCom base nisso, esta é a sequência mais curta: ");

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