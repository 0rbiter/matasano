#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif


#ifndef PROJECT_LIBS
#define PROJECT_LIBS
#include "cryptodata.h"
#include "filehandler.c"
#include "cryptodef.c"
#include "scoring.c"
#include "set1.c"
#include "histogram.c"
#include "heapsort.c"
#include "tools.c"
#endif 

int main(int argc, char **argv)
{ /*
        s1c1();
        s1c2();
        s1c3();
        s1c4();
        s1c5();

    */    
        char *filename6 = "/home/orbiter/matasano/src/challenge6keys.txt";
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
        
        /*
         * Heapsort Testing ere
         */

        long l_heapsize = 5001;
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

        /* 
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
                */
}

