/* heapsort.c */
#ifndef HEAPSORT_C
#define HEAPSORT_C
struct s_4byte {
        union {
                float _float;
                char _char[4];
        };
};
static long _heapsize;
static struct s_4byte *sPtr1;
static struct s_4byte *sPtr2;
void swap(void *one, void *two, size_t size);
void xor_swap(float *one, float *two, size_t size);
long heap_left(long index);
long heap_right(long index);
void heapify(float **heap, long heapsize, long index);
void buildHeap(float **heap, long heapsize);
void heapsort(float **heap, long heapsize);
#endif /* !heapsort.c */
