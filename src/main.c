#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "../include/headerfiles.h"
#endif

#ifndef PROJECT_LIBS
#define PROJECT_LIBS
#include "../include/tools.h"
#include "../include/heapsort.h"
#include "../include/histogram.h"
#include "../include/set1.h"
#include "../include/cryptodata.h"
#include "../include/cryptodef.h"
#include "../include/filehandler.h"
#include "../include/scoring.h"
#endif 

int main(int argc, char **argv)
{
        /*
        s1c1();
        s1c2();
        s1c3();
        s1c4();
        s1c5();
        */

        char *filename6 = "/home/orbiter/matasano/src/challenge6keys.txt";
        struct file_o *filebuffer6 = read_bytes(filename6);
        file_o_init(filebuffer6);
        char *b64string = xmalloc(1);
        char *wholestring = get_string(&filebuffer6);
        long length;
        char *STR_XOR = xmalloc(1);
        int keys_total = 3;
        struct histogram *hist = hist_o_init(keys_total);
        length = active_b64_decode_string(&b64string, wholestring, strlen(wholestring));
        get_keylength(&hist, 20, b64string, length, keys_total);
        transpose(&hist->tdata, &hist->data, length, hist->hum->keylength[0]);
        hist->testkey = xrealloc(hist->testkey, (hist->tdata->elements + 1) * sizeof(char));
        int x;
        char ENCCHAR[] = "A\0";
        for(long c = 0; c < hist->tdata->elements; c++) {
                for(x=0; x < 256; x++) {
                        ENCCHAR[0] = x;
                        memset(STR_XOR, hist->tdata->elements, 0);
                        xor_bytes_to_string(&STR_XOR, hist->tdata->blocks[c], hist->tdata->lengths[c], ENCCHAR, 1);
                        get_score(STR_XOR, hist->tdata->lengths[c], ENCCHAR, -100, 3.0f, 0);
                }
                hist->testkey[c] = get_best();
                destroy_scores();
        }
        hist->testkey[hist->tdata->elements] = '\0';
        printf("\n");
        puts(hist->testkey);
        STR_XOR = xrealloc(STR_XOR, (hist->inputlength + 1) * sizeof(char));
        xor_bytes_to_string(&STR_XOR, hist->data, length, hist->testkey, 5);
        printf("\n\n\n");
        puts(STR_XOR);
        xfree(STR_XOR);
        xfree(wholestring);
        xfree(b64string);
        file_o_destroy(filebuffer6);
        hist_o_destroy(hist); 
        double tempf = 0;
        for(x = 0; x < 26; x++)
                tempf += pow((double) (letterscore_en[x] / 100.0), 2.0);
        printf("\n%0.5f\n\n", tempf);
}

