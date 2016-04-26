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
#include "heapsort.c"

void s1c1();
void s1c2();
void s1c5();

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

int main(int argc, char **argv)
{ /*
        s1c1();
        s1c2();
        s1c3();
        s1c4();
        s1c5();*/

        /*
        char *filename6 = "/home/orbiter/matasano/src/challenge6keys.txt";
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
        long l_heapsize = 600001;
        float *heap = calloc(l_heapsize+1, sizeof(float));
        if(heap == NULL)
                exit(-1);
        int y;
        srand((unsigned int)time(NULL));
        float a = 999.0f;
        for(y = 1; y < l_heapsize; y++)
                        heap[y] = ((float) rand() / (float)(RAND_MAX)) * a;
        printf("\nRandom numbers generated. Starting heapsort\n");
        heap[0] = 0.0f;
        heapsort(&heap, l_heapsize);
        for(y = 0; y < 10; y++) {
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

