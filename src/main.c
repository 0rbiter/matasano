#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif

#include "filehandler.c"
#include "cryptodata.h"
#include "cryptodef.c"
#include "scoring.c"
#include "set1.c"
#include "histogram.c"

void s1c1();
void s1c2();
void s1c5();

union _byte {
        char s_char;
        unsigned char u_char;
};

union _2byte {
        short int s_sh_int;
        unsigned short int u_sh_int;
        union _byte bytes[2];
};

union _4byte {
        int s_int;
        unsigned int u_int;
        long int l_int;
        float _float;
        union _byte _bytes[4];
        union _2byte _2bytes[2];
};

union _8byte {
        double _double;
        union _4byte _4bytes[2];
};

union Ptr_byte {
        char *s_char;
        unsigned char *u_char;
};

union Ptr_2byte {
        short int *s_sh_int;
        unsigned short int *u_sh_int;
        union _byte *bytes[2];
};

union Ptr_4byte {
        int *s_int;
        unsigned int *u_int;
        long int *l_int;
        float *_float;
        union _byte *_bytes[4];
        union _2byte *_2bytes[2];
};

union Ptr_8byte {
        double *_double;
        union _4byte *_4bytes[2];
};

long humming_distance(char *word1, char *word2, long length)
{
        char *word = malloc((length+1) * sizeof(char));
        int i;
        long distance = 0;
        for(i = 0; i < length; i++) {
                word[i] = word1[i] ^ word2[i];
                while(word[i]) {
                        if(word[i] & 0x01)
                                distance++;
                        word[i] >>= 1;
                }
        }
        free(word);
        return distance;
}

int get_keylength(struct histogram **hobject, int maxlength, long dataindex, char *data, long length, int keys_total)
{
        if(maxlength < 2)
                return -1;
        if(length/2 < maxlength)
                maxlength = length/2;

        int keycounter = 0;
        int i; // counter variable for different key lengths
        int c; // outter counter, see splitter
        float hd; // humming distance temp
        char *first = NULL; // catches first keylength worth of bits from the data
        char *second = NULL; // catch second keylength wort of bits
        struct humming *distances = calloc(1, sizeof(struct humming));
        distances->keys_total = keys_total;
        distances->keylength = malloc(sizeof(int));
        distances->n_editdistance = malloc(sizeof(float));
        float min_distance = 0; // catches minimum distance over all keylengths tested
        int min_key = 0; // catches minimum distance over all keylengths tested
        for(i = 2; i <= maxlength; i++) {
                first = malloc(i * sizeof(char));
                second = malloc(i * sizeof(char));
                for(c = 0; c < i; c++) {
                        first[c] = data[c];
                        second[c] = data[c+i];
                }
                hd = humming_distance(first, second, i); 
                distances->n_editdistance[i-2] = hd / i;
                distances->keylength[i-2] = i;
                free(first);
                free(second);
        }
        for(keycounter = 0; keycounter < keys_total; keycounter++) {
        }
        
        //histo_o_add(*hobject, data, length, min_key, min_distance);

        free(distances);
        return min_distance;
}

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
        while(index > 2) {
                swap(&(*heap)[1], &(*heap)[index-1], sizeof(float));
                printf("\n%0.3f - %0.3f", (*heap)[1], (*heap)[index-1]);
                buildHeap(heap, index-1);
                index--;
        }
}

int main(int argc, char **argv)
{ /*
        s1c1();
        s1c2();
        s1c3();
        s1c4();
        s1c5();*/

        /*
        char *filename6 = "/home/orbiter/matasano/src/challenge6keys.txt";
        char *word1 = "this is a test\0";
        char *word2 = "wokka wokka!!!\0";
        //printf("%li", humming_distance(word1, word2));
        struct file_o *filebuffer6 = readBytes(filename6);
        file_o_init(filebuffer6);
        printf("%li", filebuffer6->elements);
        struct base64 **b64buffer = malloc((filebuffer6->elements+1) * sizeof(struct base64 *));

        long c, length;
        float kl = 0;

        int keys_total = 3;
        struct histogram *hist = hist_o_init(filebuffer6->elements, keys_total);
        for(c = 0; c < filebuffer6->elements; c++) {
                b64buffer[c] = malloc(1 * sizeof(struct base64));
                b64buffer[c]->input = malloc(1 * sizeof(char *));
                length = active_b64_decode_string(&b64buffer[c]->input, filebuffer6->buffer.c[c], filebuffer6->length[c]+1);
                if(1) {
                        puts(b64buffer[c]->input);
                        kl = get_keylength(&hist, 20, c, b64buffer[c]->input, length, keys_total);
                        printf("Min distance: %0.2f\n", kl);
                }
        }
        for(c = 0; c < filebuffer6->elements; c++) {
                free(b64buffer[c]->input);
                free(b64buffer[c]);
        }
        free(b64buffer);
        file_o_destroy(filebuffer6);
        hist_o_destroy(&hist);
*/
        float *heap = calloc(16, sizeof(float));
        int y;
        srand((unsigned int)time(NULL));
        float a = 999.0f;
        heap[0] = 0.0f;
        printf("%i\t%.3f\n", 0, heap[0]);
        for(y = 1; y < 15; y++) {
                heap[y] = ((float) rand() / (float)(RAND_MAX)) * a;
                //printf("%i\t%.3f\n", y, heap[y]);
        }

        printf("____________________________________\n");
        buildHeap(&heap, 15);
        printf("%i\t%.3f\n", 0, heap[0]);
        for(y = 1; y < 15; y++) {
                printf("%i\t%.3f\n", y, heap[y]);
        }
        printf("____________________________________\n"); 

        heapsort(&heap, 15);
        for(y = 0; y < 15; y++) {
                printf("%i\t%.3f\n", y, heap[y]);
        }
        free(heap);
        printf("____________________________________");
        union _byte *string1 = (union _byte *) "\nAbc\0";
        float numbers[4] = { 3.54f, 1.0f, 92479.0f, -392.42333f };
        puts((char *) string1);
        int x;
        void *ptr; // = (void *) malloc(sizeof(void) * 5);
        void *ptr2;
        ptr = string1;
        ptr2 = numbers;
        for(x = 0; x < strlen((char *) string1); x++)
                printf("%c\t%c\t%f\n", string1[x].s_char, *(char *)(ptr+x), *(float *)(ptr2+(4*x)));
}

