#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "problem.h"


PossiblePaths *possible_paths_construct(int index, int previous, int previous_distance)
{
    PossiblePaths *pp = (PossiblePaths*)calloc(1,sizeof(PossiblePaths));
    pp->index = index; 
    pp-> previous = previous; 
    pp-> previous_distance = previous_distance; 
    pp-> origin_distance = 0; 

    return pp;
}


Problem *problem_construct()
{
    Problem*p = (Problem*)calloc(1,sizeof(Problem));
    p->possible_paths_nodes = vector_construct();
    p->size = 0;

    return p;
}

Problem *read_file(FILE *arq)
{


}

void problem_destroy(Problem *p)
{
    int size = vector_size(p->possible_paths_nodes);
    while(size > 0)
    {
        PossiblePaths *n = vector_get(p->possible_paths_nodes,size);
        free(n);
        size--;
    }
    vector_destroy(p->possible_paths_nodes);
    free(p);
}