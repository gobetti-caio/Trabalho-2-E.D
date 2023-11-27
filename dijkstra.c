#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"
#include "vector.h"
#include "heap.h"
#include "problem.h"
#include "path.h"



Vector *visitados_construct(int size)
{
    Vector *visitados = vector_construct();

    for (int i = 0; i < size; i++)
    {
        vector_push_back(visitados, false);
    }

    return visitados;
};


/**
 * Função criada para pegar os vizinhos de um determinado nó
 * que está sendo visitado, ela checa se esse vizinho já foi viitado
 * se não foi adiciona no vetor de vizinhos
 * @param visited vetor de booleano
 * @param nodes vetor de nós que vieram do Problem
 * @param source valor do nó de origem
*/
Vector *neighborhood(Vector *visited, Vector *nodes, int source)
{
    Vector *neighbors = vector_construct();
    bool was_visited;
    int size = vector_size(nodes);


    for (int i = 0; i < size; i++)
    {
        PossiblePaths *aux = vector_get(nodes, i);
        was_visited = vector_get(visited, aux->index);

        if (aux->previous == source && was_visited == false)
        {
            vector_push_back(neighbors, aux);
        }
    }

    return neighbors;
}


/**
 * Função criada para checar se o vetor de visitados ainda
 * tem algum que não foi visitado
 * @param visited vetor de visitados
*/
bool visited_check(Vector *visited)
{
    int size = vector_size(visited);

    for (int i = 0; i < size; i++)
    {
        if(vector_get(visited, i) == false)
        {
            return false;
        }
    }
    return true;
};


Vector *solve_dijkstra(Problem *problem)
{
    Problem *p = problem;
    Vector *visited = visited_construct(p->size);
    Vector *paths = paths_construct(p->size);
    Heap *not_visited = heap_construct();

    PossiblePaths *pn;
    PossiblePaths *node_removed;
    PossiblePaths *node_path;
    PossiblePaths *origin = problem_node_construct(0, 0, 0); //nó de origem
    int node_removed_cost = 0;
    bool was_visited = true;

    heap_push(not_visited, origin, origin->origin_distance);
    
    while (visited_check(visited) == false || heap_empty(not_visited) == false)
    {
        node_removed = heap_pop(not_visited);

        if (vector_get(visited, node_removed->index) == false)
        {
            node_removed_cost = node_removed->origin_distance;

            //encontra o nó do vetor de caminhos referente ao nó removido e atualiza suas informações
            node_path = vector_get(paths, node_removed->index);
            node_path->previous = node_removed->previous;
            node_path->previous_distance = node_removed->previous_distance;
            node_path->origin_distance = node_removed->origin_distance;

            Vector *neighbors = neighborhood(visited, p->possible_paths_nodes, node_removed->index);

            // adiciona os vizinhos na heap somando o custo total pra origem
            for (int i = 0; i < vector_size(neighbors); i++)
            {
                pn = vector_get(neighbors, i);
                pn->origin_distance = pn->previous_distance + node_removed_cost;
                heap_push(not_visited, pn, pn->origin_distance);       
            }

            vector_destroy(neighbors);

            vector_set(visited, node_removed->index, &was_visited); 
        }               
    };

    vector_destroy(visited);
    heap_destroy(not_visited);
    free(origin);

    return paths;
};