#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif

/* heapsort.c */
#ifndef HEAPSORT_C
#define HEAPSORT_C

void swap(void *one, void *two, size_t size)
{
        char temp[size];
        memcpy(temp, one, size);
        memcpy(one, two, size);
        memcpy(two, temp, size);
}

static long _heapsize;

long heap_left(long index)
{
        return index*2;
}

long heap_right(long index)
{
        return index*2+1;
}

void heapify(float **heap, long heapsize, long index)
{
        long largest = index;
        do {
                if(heap_left(index) < heapsize)
                        if((*heap)[index] < (*heap)[heap_left(index)])
                                largest = heap_left(index);
                if(heap_right(index) < heapsize)
                                if((*heap)[largest] < (*heap)[heap_right(index)]) 
                                largest = heap_right(index);
                if(largest == index) 
                        break;
                else {
                swap(&(*heap)[index], &(*heap)[largest], sizeof(float));
                index = largest;
                }
        } while(1);
        return;
}

void buildHeap(float **heap, long heapsize)
{
        long index;
        for(index = (heapsize)/2; index >= 1; index--)
        {
                heapify(heap, heapsize, index);
        }
        return;
}

void heapsort(float **heap, long heapsize)
{
        long index = heapsize;
        buildHeap(heap, index);
        while(index > 2) {
                swap(&(*heap)[1], &(*heap)[index-1], sizeof(float));
                buildHeap(heap, index-1);
                index--;
        }
}

#endif /* !heapsort.c */
