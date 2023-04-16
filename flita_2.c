#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int vertices, edges;
    char** matrix;
} mtrx;

void read_dim(int* vertices, int* edges) {
    char transit;
    FILE *matrix = fopen("matrix.txt", "r");
    for (*vertices = 0; !feof(matrix); (*vertices)++) {
        for (*edges = 0; !feof(matrix); (*edges)++) {
            fscanf(matrix, "%c", &transit);
            if (transit == ' ') (*edges)--;
            if (transit == '\n') break;
        }
    }
    fclose(matrix);
}

void read_matrix(int vertices, int edges, char** graph_matrix){
    char transit[8];
    FILE *matrix = fopen("matrix.txt", "r");
    for (int i = 0; i < vertices && !feof(matrix); i++)
        for (int j = 0; j < edges && !feof(matrix); j++){
            fscanf(matrix, "%s ", &transit);
            graph_matrix[i][j] = (char)atoi(transit);
        }
    fclose(matrix);
}

void write_dot (int vertices, int edges, char** graph_matrix){
    FILE *dot_file = fopen("graph.dot", "w");

    fprintf(dot_file, "digraph G {\n");

    for (int i = 0; i < edges; i++) {
        for (int j = 0; j < vertices; j++) {
            if (graph_matrix[j][i] != 0) {
            
                int direction = graph_matrix[j][i] < 0 ? -1 : 1;
                int label = graph_matrix[j][i] * direction;

                int k = j + 1;
                for (k; k < vertices; k++)
                    if(graph_matrix[k][i] != 0) break;
                
                if (k == vertices) k = j;
                
                if (direction > 0)
                    fprintf(dot_file, "\t%c -> %c [label = %d];\n", j + 'a', k + 'a', label);
                else
                    fprintf(dot_file, "\t%c -> %c [label = %d];\n", k + 'a', j + 'a', label);

                break;
            }
        }
    }
    
    fprintf(dot_file, "}");
    fclose(dot_file);
}

int main() {

    mtrx graph;

    read_dim(&graph.vertices, &graph.edges); 

    graph.matrix = (char**)malloc(sizeof(char*) * graph.edges);
    for(int i = 0; i < graph.edges; i++){
        graph.matrix[i] = (char*)malloc(sizeof(char) * graph.vertices);
    }

    read_matrix(graph.vertices, graph.edges, graph.matrix);

    write_dot(graph.vertices, graph.edges, graph.matrix);

    system("copy graph.dot C:\\Graphviz\\bin & cd C:\\Graphviz\\bin & dot.exe -Tpng graph.dot -o graph.png & move graph.png C:\\c");

    return 0;
}