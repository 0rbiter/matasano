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
#include "heapsort.c"
#include "histogram.c"
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
        char *b64string = malloc(1);
        char *wholestring = getString(&filebuffer6);
        long c, length;

        int keys_total = 3;
        struct histogram *hist = hist_o_init(keys_total);
        length = active_b64_decode_string(&b64string, wholestring, strlen(wholestring));
        get_keylength(&hist, 20, b64string, length, keys_total);
        transpose(&hist->tdata, &hist->data, length, hist->hum->keylength[0]);
       /* 
        for(lines = 0; lines < buffer1->elements; lines++) {
                length1 = hexstringToString(&STR_STRING, buffer1->buffer.c[lines]);
                for(x=0; x < 256; x++) {
                        ENCCHAR[0] = x;
                        xor_bytes_to_string(&STR_XOR, STR_STRING, length1, ENCCHAR, 1);
                        get_score(STR_XOR, length1, ENCCHAR, 70, 2.0f, 0);
                }
        }
        printf("\nNumber of actions: %li", lines*x);
        get_best();
        destroy_scores();
*/
        free(wholestring);
        free(b64string);
        file_o_destroy(filebuffer6);
        hist_o_destroy(hist); 

}

