#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define FILENAME "../matrix_of_incendence1.txt"
#define MAX_SIZE 50


typedef struct Edge {
    int originNode, destNode;
} Edge_t;

int main() {
    FILE *f;
    f = fopen(FILENAME, "r+");
    char fData[1000];
    fread(fData, sizeof(char), sizeof(fData), f);
    fData[ftell(f)-1] = '\0';

    char c = '.'; int i = 0;
    int edges = 0, vertexes = 0;
    int matrix[MAX_SIZE][MAX_SIZE];

    while (true) {
        c = fData[i]; i++;
        if (c == ' ') continue;
        if (c == '1') {matrix[edges][vertexes] = 1; edges++;}
        if (c == '0') {matrix[edges][vertexes] = 0; edges++;}
        if (c == '\n') {vertexes++; edges = 0;}
        if (c == '\0') {vertexes++; break;}
    }
    fclose(f);

    printf("Read data: \n");
    for (int p = 0; p < vertexes; p++) {
        for (int q = 0; q < edges; q++) {
            printf("%2d ", matrix[q][p]);
        }
        printf("\n");
    }


    FILE* dotFile = fopen("../graph.dot", "w");
    fprintf(dotFile, "graph G {\n");

    Edge_t edge;
    bool NotLoop = false;

    for (int p = 0; p < edges; p++) {
        for (int q = 0; q < vertexes; q++) {
            if (matrix[p][q] == 1) {
                if (NotLoop) {
                    edge.destNode = q+1;
                }
                else {
                    edge.originNode = q+1;
                    edge.destNode = q+1;
                }
                NotLoop = true;
            }

            else continue;
        }
        NotLoop = false;
        fprintf(dotFile, "\t%d -- %d; \n", edge.originNode, edge.destNode);
    }

    fprintf(dotFile, "}");
    fclose(dotFile);

    system("dot -Tpng ../graph.dot -o ../graph.png");
    system("start ../graph.png");

    if (edges > ((vertexes -1 ) * (vertexes - 2)) / 2) printf("The graph is bonded"); //
    else printf("The graph is NOT bonded");

    return 0;
}