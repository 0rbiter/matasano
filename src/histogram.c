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
#include "tools.c"
#endif 

/* histogram.c */
#ifndef HISTOGRAM_C
#define HISTOGRAM_C
/*
 * the histogram will contain all strings to be decoded
 *  -> # of "elements" = strings to decypher
 *  -> "data" string
 *  -> "inputlength" per string
 *
 *  -> humming results "hum" keylength per string "data"
 *      -> "keys_total" number of best guessed keylengths
 *      -> "keylength[]" keylengths
 *      -> "n_editdistance[]" normalized edit distances per keylength according to "data"
 *  -> struct lang "scores"
 *      -> tested key "testkey" char
 *      -> "unciphered" decyphered data according to testkey
 *      -> "score[]" list of scores for to "unciphered"
 *
 */

struct histogram {
        char *data;
        long inputlength;
        struct humming {
                int keys_total;
                int *keylength;
                float *n_editdistance;
        } *hum;
        struct lang {
                char *testkey;
                char *unciphered;
                int score;
                float scoreboard[26];
        } *scores;
};

int resolveKeylength(struct humming **hobject, float editdistance)
{   /* this function is searching for the according keylength given a editdistance
     * in a 'struct humming'; resolving the right keys for edit distances after
     * heapsort has done it's job
     */
        long i = 0;
        while((*hobject)->n_editdistance[i] != editdistance && i <= (*hobject)->keys_total)
                i++;
        return (*hobject)->keylength[i];
}

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
                        char *data, long length, int keys_total)
{
        if(maxlength < 2)
                return -1;
        if(length/2 < maxlength)
                maxlength = length/2;
        char *temp = realloc((*hobject)->data, length);
        if(temp != NULL)
                (*hobject)->data = temp;
        else
                exit(-1);
        int temp_distance = 0;
        int kctr = 0;
        int i; // counter variable for different key lengths
        int c; // outter counter, see splitter
        float hd; // humming distance temp
        char *first = NULL; // catches first keylength worth of bits from the data
        char *second = NULL; // catch second keylength wort of bits
        struct humming *distances = malloc(sizeof(struct humming));
        distances->keylength = malloc((maxlength-1) * sizeof(int));
        distances->keys_total = keys_total;
        distances->n_editdistance = malloc((maxlength-1) * sizeof(float));
        float *sorted_ed = malloc(maxlength * sizeof(float));
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
        if(maxlength-1 < keys_total)
                printf("Error: More keylengths requested then guessed.\n");
        memset(sorted_ed, 0, maxlength * sizeof(float));
        memcpy(&sorted_ed[1], &(*distances->n_editdistance), sizeof(float) * (maxlength-1));
        heapsort(&sorted_ed, maxlength-1);
        memcpy(&(*(*hobject)->hum->n_editdistance), &sorted_ed[1], keys_total * sizeof(float));
        memcpy((*hobject)->data, data, length);
        for(kctr = 0; kctr < keys_total; kctr++) {
               (*hobject)->hum->keylength[kctr] = 
                resolveKeylength(&distances, sorted_ed[kctr+1]);
               printf("\nKeylength: %i\tEditdistance %0.5f", (*hobject)->hum->keylength[kctr],
                                                        (*hobject)->hum->n_editdistance[kctr]);
        }
        free(distances->keylength);
        free(distances->n_editdistance);
        free(distances);
        free(sorted_ed);
        return min_distance;
}

struct histogram *hist_o_init(int keys_total)
{ // elements: how many strings; keys_total = how many keylengths will be tested
        long counter;
        int i;
        struct histogram *hobject = malloc(sizeof(struct histogram));
        hobject->data = (char *) malloc(sizeof(char)); // list of input data to be deciphered

        hobject->inputlength = 0;
        hobject->hum = malloc(sizeof(struct humming));
        hobject->scores = malloc(sizeof(struct lang));
        hobject->inputlength = 0;
        hobject->hum->keys_total = keys_total; // how many keylengths
        hobject->hum->keylength = (int *) malloc(keys_total * sizeof(int));
        hobject->hum->n_editdistance = (float *) malloc(keys_total * sizeof(float));
        hobject->scores->testkey = (char *) malloc(1 * sizeof(char));
        hobject->scores->unciphered = (char *) malloc(1 * sizeof(char));
        hobject->scores->score = 0;
        for(i = 0; i < 26; i++)
                hobject->scores->scoreboard[i] = 0.0f;
                                                                // the strings according each element
                                                                //
                                                                /* according length to input string
                                                                 * since strlen() would crash on
                                                                 * bit streams containing '\0's
                                                                 */
        return hobject;
}

int hist_o_destroy(struct histogram *hobject)
{
        long counter;
        int i;
        free(hobject->data); 
        free(hobject->scores->testkey);
        free(hobject->scores->unciphered);
        free(hobject->hum->keylength);
        free(hobject->hum->n_editdistance);
        free(hobject->hum);
        free(hobject->scores);
        free(hobject);
        return 0;
}

#endif /* !HISTOGRAM_C */
