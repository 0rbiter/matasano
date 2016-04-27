
#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
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
        int keycounter = 0;
        int i; // counter variable for different key lengths
        int c; // outter counter, see splitter
        float hd; // humming distance temp
        char *first = NULL; // catches first keylength worth of bits from the data
        char *second = NULL; // catch second keylength wort of bits
        struct humming *distances = calloc(1, sizeof(struct humming));
        distances->keys_total = keys_total;
        distances->keylength = malloc((maxlength-1) * sizeof(int));
        distances->n_editdistance = malloc((maxlength-1) * sizeof(float));
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
        free(distances->keylength);
        free(distances->n_editdistance);
        free(distances);
        return min_distance;
}

#endif /* !TOOLS.C */
