#include <stdio.h>
#include <stdlib.h>
#define INT_MIN -2147483647

typedef struct Heap{
    int tree[1000];
    int size;
} Heap;

void insert(Heap* heap, int item);
int extractMin(Heap* heap);
void heapify(Heap* heap, int index);
Heap* buildHeap();
void deleteHeap(Heap* heap);


void swap(int *x, int* y){
    int z = *x;
    *x = *y;
    *y = z;
    return;
}

void insert(Heap* heap, int item)
{
    int size = heap -> size + 1;
    heap -> size = size;

    heap -> tree[size] = item;

    int child = size;
    int parent = (size - 1) / 2;

    while(heap -> tree[parent] > heap -> tree[child]){
        swap(&heap->tree[parent], &heap->tree[child]);
        child = parent; parent = (parent - 1) / 2;
    }

    return;
}

int extractMin(Heap* heap)
{
    if(heap -> size == -1){
        printf("Heap is empty.\n");
        return INT_MIN;
    }
    int ret = heap->tree[0];

    int size = heap -> size - 1;
    heap -> size = size;
    
    heap -> tree[0] = heap -> tree[size + 1];

    heapify(heap, 0);

    return ret;
}

void heapify(Heap* heap, int index)
{
    int parent = index;
    int left_child = parent * 2 - 1;
    int right_child = parent * 2;

    if(left_child > heap->size){
    }
    else if (right_child > heap->size){
        if(heap->tree[left_child] < heap->tree[parent])
            swap(&heap->tree[left_child], &heap->tree[right_child]);
    }
    else{ // both children are exist
        int smaller_child =
            heap->tree[left_child] < heap->tree[right_child] ?
            left_child : right_child;
        
        if(heap->tree[smaller_child] < heap->tree[parent]){
            swap(&heap->tree[smaller_child], &heap->tree[parent]);
            heapify(heap, smaller_child);
        }
    }
    return;
}

Heap* buildHeap()
{
    int N;
    printf("Enter the number of inputs : ");
    scanf_s("%d", &N);
    if(N == 0) return NULL;
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap -> size = N-1;

    printf("Enter the numbers below\n");
    for(int i = 0; i < N; ++i)
        scanf_s("%d", &heap->tree[i]);
    
    for(int curr = (N-2) / 2;curr >= 0; --curr){
        heapify(heap, curr);
    }

    return heap;
}

void deleteHeap(Heap* heap)
{
    free(heap);
    return;
}

void printCommands()
{
    printf("\n");
    printf("1. Insert a item.\n");
    printf("2. Extract Minimum from Heap.\n");
    printf("3. Delete a Heap.\n");
}

int main(void){

    int command = 0;
    while(command != 2){
        printf("1. Build a Heap.\n");
        printf("2. Exit Program.\n");
        scanf_s(" %d", &command);
        if(command == 1){
            int command2 = 0;
            Heap* heap = buildHeap();
            printf("\n ** Minheap is created **\n");

            while(command2 != 3){
                printCommands();
                scanf_s(" %d", &command2);

                if(command2 == 1){ // Insert
                    int item;
                    printf("Insert : ");
                    scanf_s("%d", &item);
                    insert(heap, item);
                }
                else if (command2 == 2){ // Extract
                    int extracted = extractMin(heap);
                    if(extracted != INT_MIN){
                        printf("Extracted %d\n", extracted);
                    }
                }
                else if (command2 == 3){ // Delete
                    deleteHeap(heap);
                }
            }
        }
    }
}