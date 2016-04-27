#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif

#ifndef PROJECT_LIBS
#define PROJECT_LIBS
#include "cryptodata.h"
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

struct s_4byte {
        union {
                float _float;
                char _char[4];
        };
};

static long _heapsize;
static struct s_4byte *sPtr1;
static struct s_4byte *sPtr2;

void xor_swap(float *one, float *two, size_t size)
{
        long i;
        sPtr1 = (struct s_4byte *) one;
        sPtr2 = (struct s_4byte *) two;
        for(i = 0; i < size; i++) {
                sPtr1->_char[i] ^= sPtr2->_char[i];
                sPtr2->_char[i] ^= sPtr1->_char[i];
                sPtr1->_char[i] ^= sPtr2->_char[i];
        }
        return;
}

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
                //swap(&(*heap)[index], &(*heap)[largest], sizeof(float));
                xor_swap(&(*heap)[index], &(*heap)[largest], sizeof(float));
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
                //swap(&(*heap)[1], &(*heap)[index-1], sizeof(float));
                xor_swap(&(*heap)[1], &(*heap)[index-1], sizeof(float));
                buildHeap(heap, index-1);
                index--;
        }
}

#endif /* !heapsort.c */
