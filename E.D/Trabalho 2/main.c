// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include "heap.h"
// #include "vector.h"
// #include "problem.h"
// #include "djikstra.h"
// #include "path.h"
// void print_and_destroy_paths(Vector *paths)
// {
// for (int i = 0; i < vector_size(paths); i++)
// {
// Path *path = vector_get(paths, i);
// path_print(path);
// path_destroy(path);
// }
// vector_destroy(paths);
// }
// int main()
// {
// Problem *problem_data;
// Vector *paths;
// problem_data = problem_data_read("in.txt");
// paths = djikstra_solve(problem_data);
// print_and_destroy_paths(paths);
// problem_data_destroy(problem_data);
// return 0;
// }


//TESTE DA HEAP

typedef struct
{
    int val;
    int antecessor;
} Node;
int main(){

    heap *h = heap_construct();

    if (heap_empty(h) == true)
    {
        printf("Lista vazia\n");
    }

    int tamanho = 7;

    for (int i = tamanho; i > 0; i--)
    {
        Node *a = (Node *)calloc(1, sizeof(Node));
        a->val = i;
        a->antecessor = 0;
        heap_push(h, a, a->val);
    }
}
