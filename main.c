#include <stdio.h>
#include <stdlib.h>

// Função que ordena esquinas do menor tempo para o maior tempo.
int reordenar_sequencia(int m, int *M) {

}

// Função que cria um vetor com o menor tempo percorrido.
void rota_mais_rapida_dijkstra(int *M, int n, int m) {
    int E[m]; // Conjunto E que armazena as esquinas do mapa M
    int T[50]; // Vetor para armazenar tempos
    int R[50]; // Vetor para armazenar rotas mais rápidas
    for (int i = 0; i < E[i]; i++) {
        T[i] = 0;
    }
    T[1] = 0;
    while (E[m] != NULL) {
        int v = E[m--];
    }

}

int main(void) {
    int n; // número da esquina onde ocorre o incêndio.
    int m; // número de esquinas que constam no mapa.
    FILE *entrada; // Variável para leitura do bombeiro.txt.
    int linha[100];

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
    

    fclose(entrada);

    return 0;
}