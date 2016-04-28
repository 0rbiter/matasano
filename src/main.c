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

        int keys_total = 3;
        struct histogram *hist = hist_o_init(filebuffer6->elements, keys_total);
        for(c = 0; c < filebuffer6->elements; c++) {
                b64buffer[c] = malloc(1 * sizeof(struct base64));
                b64buffer[c]->input = malloc(1 * sizeof(char *));
                length = active_b64_decode_string(&b64buffer[c]->input, filebuffer6->buffer.c[c], filebuffer6->length[c]+1);
                get_keylength(&hist, 20, c, b64buffer[c]->input, length, keys_total);
        }

        printf("Best %i keylength with normalized edit distances:\n", keys_total);

        long f;
        for(f = 0; f < hist->elements; f++) {
                puts(hist->data[f]);
                for(c = 0; c < keys_total; c++)
                        printf("\t%i\t\t%0.5f\n", hist->hum[f].keylength[c],
                                                        hist->hum[f].n_editdistance[c]);
        }
        printf("filebuffer6 elements: %li\nhist elements: %li", filebuffer6->elements, hist->elements);
        for(c = 0; c < filebuffer6->elements; c++) {
                free(b64buffer[c]);
        }
        free(b64buffer);
        file_o_destroy(filebuffer6);
        hist_o_destroy(&hist);
        
}

