#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

Point *ler_vertices_do_arquivo(const char *nome_arquivo, int *num_vertices) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
    }

    fscanf(arquivo, "%d", num_vertices);

    Point *vertices = (Point *)malloc(*num_vertices * sizeof(Point));
    if (vertices == NULL) {
        printf("Erro de alocação de memória!\n");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *num_vertices; i++) {
        fscanf(arquivo, "%lf %lf", &vertices[i].x, &vertices[i].y);
    }

    fclose(arquivo);
    return vertices;
}

float calcular_area_triangulo(Point A, Point B, Point C) {
    return 0.5 * ((A.x * (B.y - C.y)) + (B.x * (C.y - A.y)) + (C.x * (A.y - B.y)));
}

double calcular_area_poligono(Point vertices[], int num_vertices) {
    double area = 0.0;
    int j;

    for (int i = 0; i < num_vertices; i++) {
        j = (i + 1) % num_vertices;
        area += (vertices[i].x * vertices[j].y) - (vertices[j].x * vertices[i].y);
    }

    area = area / 2.0;
    if (area < 0) {
        area = -area;
    }

    return area;
}

int main() {
    int num_vertices;
    Point *vertices;
    double area;

    vertices = ler_vertices_do_arquivo("vertices.txt", &num_vertices);
    if (vertices == NULL) {
        return 1;
    }

    area = calcular_area_poligono(vertices, num_vertices);
    printf("A área do polígono é: %.2lf\n", area);

    free(vertices);
    return 0;
}
