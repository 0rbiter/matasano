#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
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
        long elements;
        char **data;
        long *inputlength;
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

struct histogram *hist_o_init(long elements, int keys_total)
{ // elements: how many strings; keys_total = how many keylengths will be tested
        long counter;
        int i;
        struct histogram *hobject = malloc(sizeof(struct histogram));
        hobject->elements = elements; // max elements

        hobject->data = (char **) malloc(elements * sizeof(char *)); // list of input data to be deciphered

        hobject->inputlength = (long *) malloc(elements * sizeof (long));
        hobject->hum = malloc(elements * sizeof(struct humming));
        hobject->scores = malloc(elements * sizeof(struct lang));
        for(counter = 0; counter < elements; counter++) {
                //hobject->data[counter] = (char *) malloc(1 * sizeof(char)); 
                hobject->inputlength[counter] = 0;
                hobject->hum[counter].keys_total = keys_total; // how many keylengths
                hobject->hum[counter].keylength = (int *) malloc(keys_total * sizeof(int));
                hobject->hum[counter].n_editdistance = (float *) malloc(keys_total * sizeof(float));
                hobject->scores[counter].testkey = (char *) malloc(1 * sizeof(char));
                hobject->scores[counter].unciphered = (char *) malloc(1 * sizeof(char));
                hobject->scores[counter].score = 0;
                for(i = 0; i < 26; i++)
                        hobject->scores[counter].scoreboard[i] = 0.0f;
        }
                                                                // the strings according each element
                                                                //
                                                                /* according length to input string
                                                                 * since strlen() would crash on
                                                                 * bit streams containing '\0's
                                                                 */
        return hobject;
}



int hist_o_destroy(struct histogram **hobject)
{
        long counter;
        int i;
        for(counter = 0; counter < (*hobject)->elements; counter++) {
                free((*hobject)->data[counter]); 
                free((*hobject)->scores[counter].testkey);
                free((*hobject)->scores[counter].unciphered);
                free((*hobject)->hum[counter].keylength);
                free((*hobject)->hum[counter].n_editdistance);
        }
        free((*hobject)->data); // list of input data to be deciphered
        free((*hobject)->inputlength);
        free((*hobject)->hum);
        free((*hobject)->scores);
        free((*hobject));
        return 0;
}

#endif /* !HISTOGRAM_C */
