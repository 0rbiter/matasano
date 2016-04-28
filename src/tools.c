
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
/* tools.c */
#ifndef TOOLS_C
#define TOOLS_C

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

int get_keylength(struct histogram **hobject, int maxlength, 
                        long dataindex, char *data, long length, int keys_total)
{
        if(maxlength < 2)
                return -1;
        if(length/2 < maxlength)
                maxlength = length/2;
        int temp_distance = 0;
        int keycounter = 0;
        int i; // counter variable for different key lengths
        int c; // outter counter, see splitter
        float hd; // humming distance temp
        char *first = NULL; // catches first keylength worth of bits from the data
        char *second = NULL; // catch second keylength wort of bits
        struct humming *distances = malloc(sizeof(struct humming));
        distances->keylength = malloc((maxlength-1) * sizeof(int));
        distances->keys_total = keys_total;
        distances->n_editdistance = malloc((maxlength-1) * sizeof(float));
        float min_distance = 0; // catches minimum distance over all keylengths tested
        int min_key = 0; // catches minimum distance over all keylengths tested
        char temp_byte;
        for(i = 2; i <= maxlength; i++) {
                first = malloc(i * sizeof(char));
                second = malloc(i * sizeof(char));
                for(c = 0; c < i; c++) {
                        temp_byte = data[c];
                        first[c] = temp_byte;
                        temp_byte = data[c+i];
                        second[c] = temp_byte;
                }
                hd = humming_distance(first, second, i); 
                distances->n_editdistance[i-2] = hd / i;
                distances->keylength[i-2] = i;
                free(first);
                free(second);
        }
        // min heapsort the editdistances
        heapsort(&(distances->n_editdistance), maxlength-1);
        
        if(maxlength-1 < keys_total)
                printf("Error: More keylengths requested then guessed.\n");
        (*hobject)->data[dataindex] = data;
        for(keycounter = 0; keycounter < keys_total; keycounter++) {
               (*hobject)->hum[dataindex].keylength[keycounter] = distances->keylength[keycounter];
               (*hobject)->hum[dataindex].n_editdistance[keycounter] = distances->n_editdistance[keycounter];

        }
        free(distances->keylength);
        free(distances->n_editdistance);
        free(distances);
        return min_distance;
}

#endif /* !TOOLS.C */
