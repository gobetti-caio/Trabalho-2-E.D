#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"
#include "vector.h"
#include "heap.h"
#include "problem.h"
#include "path.h"

/**
 * Função criada para pegar os vizinhos de um determinado nó
 * que está sendo visitado, ela checa se esse vizinho já foi viitado
 * se não foi adiciona no vetor de vizinhos
 * @param visited vetor de booleano
 * @param nodes vetor de nós que vieram do Problem
 * @param source valor do nó de origem
 */
Vector *find_neighbors(Vector *paths, Vector *possible_paths, int prev)
{
    Vector *neighbors = vector_construct();
    int was_visited;
    int size = vector_size(possible_paths);

    for (int i = 0; i < size; i++)
    {
        PossiblePaths *aux = vector_get(possible_paths, i);
        was_visited = vector_get(paths, aux->index);

        if (aux->previous == prev && was_visited == false)
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
bool visited_check(Vector *paths)
{
    int size = vector_size(paths);
    PossiblePaths *pp;

    for (int i = 0; i < size; i++)
    {
        pp = vector_get(paths, i);
        if (pp->index == 0)
        {
            return false;
        }
        else if (pp->origin_distance == 0)
        {
            return false;
        }
    }
    return true;
};

// FUNÇOES MINHAS

void update_path(Vector *paths, PossiblePaths *node_removed)
{
    // Taking advantage of the index of the vector we update the infomrmation of each node
    PossiblePaths *node_path;
    node_path = vector_get(paths, node_removed->index);
    node_path->previous = node_removed->previous;
    node_path->previous_distance = node_removed->previous_distance;
    node_path->origin_distance = node_removed->origin_distance;
}

void update_heap(PossiblePaths *node_removed, Vector *visited, Problem *p, Heap *not_visited)
{
    Vector *neighbors = fing_neighbors(visited, p->possible_paths_nodes, node_removed->index);
    PossiblePaths *pn;
    int node_removed_cost;
    for (int i = 0; i < vector_size(neighbors); i++)
    {
        node_removed_cost = node_removed->origin_distance;
        pn = vector_get(neighbors, i);
        pn->origin_distance = pn->previous_distance + node_removed_cost;
        heap_push(not_visited, pn, pn->origin_distance);
    }
    vector_destroy(neighbors);
}

Vector *solve_dijkstra(Problem *problem)
{
    Problem *p = problem;
    Vector *visited = visited_construct(p->size);
    Vector *paths = paths_construct(p->size);
    Heap *not_visited = heap_construct();

    PossiblePaths *node_removed;
    PossiblePaths *origin = problem_node_construct(0, 0, 0); // nó de origem
    bool was_visited = true;

    heap_push(not_visited, origin, origin->origin_distance);

    while (visited_check(visited) == false || heap_empty(not_visited) == false)
    {
        node_removed = heap_pop(not_visited);

        if (vector_get(paths, node_removed->index) == 0)
        {
            void update_path(Vector * paths, PossiblePaths * node_removed);

            void update_heap(PossiblePaths * node_removed, Vector * visited, Problem * p, Heap * not_visited);

            vector_set(visited, node_removed->index, &was_visited);
        }
        else if (vector_get(paths, node_removed->origin_distance) == 0)
        {
            void update_path(Vector * paths, PossiblePaths * node_removed);

            void update_heap(PossiblePaths * node_removed, Vector * visited, Problem * p, Heap * not_visited);

            vector_set(visited, node_removed->index, &was_visited);
        }
    };

    heap_destroy(not_visited);
    free(origin);

    return paths;
};