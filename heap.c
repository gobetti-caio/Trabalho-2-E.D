#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"


typedef struct Node
{
    void *data;
    int distance;
}Node;

struct heap {
    Node *node;
    int size;
    int allocated;
};

static const int HEAP_INIT_SIZE = 10;
static const int HEAP_GROWTH_RATE = 2;

heap *createHeap()
{
    heap* h = (heap*)calloc(1,sizeof(heap));
    h->size = 0;
    h->allocated = HEAP_INIT_SIZE;
    h->node = (Node *)calloc(HEAP_INIT_SIZE, sizeof(Node));
    return h;
};

void Heapify_push(heap* h, int index)
{
        int parent = (index - 1) / 2;
    
        if (h->node[parent].distance > h->node[index].distance) {
            Node temp = h->node[parent];
            h->node[parent] = h->node[index];
            h->node[index] = temp;

            //calling the function recursively
            // util the node hit it rigth spot
            Heapify_push(h, parent);                                     
        }
};

void heap_push(heap *h, void *data, int distance)
{
// Cheking if heap is full
    if (h->size == h->allocated) {
        h->allocated = (h->allocated)*HEAP_GROWTH_RATE;
        h->node = (Node*)calloc(h->allocated, sizeof(Node));
    } 
    h->node[h->size].data  = data;
    h->node[h->size].distance = distance;
    Heapify_push(h,h->size); 
    h->size++;  
}

bool heap_empty(heap *h)
{
    if(h->size ==0)
    {
        return true;
    }
    else return false;
}

void *heap_pop(heap* h)
{
    Node ShortestPath;
 
     if (h->size == 0) {
        printf("\nHeap is empty.");
        return;
    }
    ShortestPath = h->node[0];
    h->node[0] = h->node[h->size - 1];
    h->size--;
    Heapify_pop(h,0); 
    return ShortestPath.data;
}

void Heapify_pop(heap* h, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;
 
    // Checking there are nodes to right and left 
    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;
 
    // trading the node with his right or left
    // node deppending on wich is minor
    if (left != -1 && h->node[left].distance < h->node[index].distance)
        min = left;
    if (right != -1 && h->node[right].distance < h->node[index].distance && h->node[right].distance<h->node[left].distance)
        min = right;
 
    // Checking if there was a smaller node 
    //and swapping it in a positive case
    if (min != index) {
        Node temp = h->node[min];
        h->node[min] = h->node[index];
        h->node[index] = temp;
 
        // calling the function recursively
        // to preserve the heap order
        minHeapify(h, min);
    }
}

void heap_destroy(heap* h)
{
    free(h->node);
    free(h);
    }