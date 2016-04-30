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
        long f;
        puts(hist->data);
        for(c = 0; c < keys_total; c++)
                printf("\t%i\t\t%0.5f\n", hist->hum->keylength[c], hist->hum->n_editdistance[c]);
        transpose(&hist->tdata, &hist->data, length, hist->hum->keylength[0]);
        free(wholestring);
        free(b64string);
        file_o_destroy(filebuffer6);
        hist_o_destroy(hist); 

}

