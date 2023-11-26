#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

typedef struct Node
{
    void *data;
    int distance;
} Node;

struct heap
{
    Node *node;
    int size;
    int allocated;
};

static const int HEAP_INIT_SIZE = 10;
static const int HEAP_GROWTH_RATE = 2;

heap *createHeap()
{
    heap *h = (heap *)calloc(1, sizeof(heap));
    h->size = 0;
    h->allocated = HEAP_INIT_SIZE;
    h->node = (Node *)calloc(HEAP_INIT_SIZE, sizeof(Node));
    return h;
};

void heap_swap(heap *h, int index1, int index2)
{
    Node temp = h->node[index1];
    h->node[index1] = h->node[index2];
    h->node[index2] = temp;
}

void Heapify_push(heap *h, int index)
{
    int parent = (index - 1) / 2;

    if (h->node[parent].distance > h->node[index].distance)
    {
        heap_swap(h,parent,index);
        Heapify_push(h, parent);
    }
};

void Heapify_pop(heap *h, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    if (left >= h->size || left < 0) // Checking there are nodes to right and left
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;

    // trading the node with his right or left
    // node deppending on wich is minor
    
    if (left != -1 && h->node[left].distance < h->node[index].distance)
        min = left;
    if (right != -1 && h->node[right].distance < h->node[index].distance && h->node[right].distance < h->node[left].distance)
        min = right;

    // Checking if there was a smaller node
    // and swapping it in a positive case
    if (min != index)
    {
        heap_swap(h,min,index);
        // calling the function recursively
        // to preserve the heap order
        minHeapify(h, min);
    }
};

void heap_push(heap *h, void *data, int distance)
{
    // Cheking if heap is full
    if (h->size == h->allocated)
    {
        h->allocated = (h->allocated) * HEAP_GROWTH_RATE;
        h->node = (Node *)calloc(h->allocated, sizeof(Node));
    }
    h->node[h->size].data = data;
    h->node[h->size].distance = distance;
    Heapify_push(h, h->size);
    h->size++;
    for (int i = 0; i < h->size; i++)
    {
        printf("%d\n",         h->node[i].distance);
    }
    printf("\n");
};

void *heap_pop(heap *h)
{
    Node ShortestPath;

    if (h->size == 0)
    {
        printf("\nHeap is empty.");
        return;
    }
    ShortestPath = h->node[0];
    h->node[0] = h->node[h->size - 1];
    h->size--;
    Heapify_pop(h, 0);
    return ShortestPath.data;
    for (int i = 0; i < h->size; i++)
    {
        printf("%d\n",         h->node[i].distance);
    }
    printf("\n");
};

bool heap_empty(heap *h)
{
    if (h->size == 0)
    {
        return true;
    }
    else
        return false;
};


void heap_destroy(heap *h)
{
    free(h->node);
    free(h);
};
