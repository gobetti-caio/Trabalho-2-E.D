typedef void *data_type;

typedef struct heap heap;

heap *heap_construct();

void heap_push(heap *h, void *data, int priority);

bool heap_empty(heap *h);

void *heap_pop(heap *h);

void heap_destroy(heap* h);

