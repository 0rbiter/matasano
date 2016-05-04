#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "../include/headerfiles.h"
#endif

#ifndef PROJECT_LIBS
#define PROJECT_LIBS
#include "../include/histogram.h"
#include "../include/heapsort.h"
#endif 

/* histogram.c */
#ifndef HISTOGRAM_C
#define HISTOGRAM_C

void build_bs_english()
{
        english = xmalloc(sizeof(struct betterscore));
        english->score_elements =  1;
        english->number_of_signs = 26;
        memcpy(english->signs, letters, 26);
        english->testkey = NULL;
        english->freq = (float **) xmalloc(sizeof(float *));
        english->freq[0] = (float *) xmalloc(26 * sizeof(float));
        memcpy(english->freq[0], en_scores, 26);
        english->counted_letters = (long *) xmalloc(sizeof(long));
        english->counted_letters[0] = 0;
        english->ncoefficiant = (float *) xmalloc(sizeof(float));
        calc_normalized_coe(&english, 0);
};

void get_std_freq (float **sobj)
{       // calculates the standard coefficiant of 1/26th per letter in a-z
        for(int i = 0; i < 26; i++)
                (*sobj)[i] = (float) 1 / 26;
        return;
}

long calc_letter_frequency(float **freqs, char *data, long datalen)
{
        long lettercount = 0;
        for(long i = 0; i <= datalen; i++) {
                if(data[i] >= 32 && data[i] <= 122) {
                        if(data[i] >= 97) {
                                lettercount++;
                                (*freqs)[data[i] - 97]++;
                        } else if(data[i] >= 65 && (data)[i] <= 90) {
                                (*freqs)[data[i] - 65]++;
                                lettercount++;
                        }

                }
        }
        return lettercount;
}
void calc_normalized_coe(struct betterscore *sbuf, long element)
{       /* calculating the normalized coefficiant of the tdata block associated
         * to be applied to ncoefficiant of the tdata block associated
         */
        float result = 0;
        for(int i = 0; i < sbuf->number_of_signs; i++)
                result += pow(sbuf->freq[element][i] / 100, 2);
        sbuf->ncoefficiant[element] = result / (1 / sbuf->number_of_signs);
        return;
}

struct histogram *hist_o_init(int keys_total)
{ // elements: how many strings; keys_total = how many keylengths will be tested
        long counter;
        int i;
        struct histogram *hobject = xmalloc(sizeof(struct histogram));
        hobject->data = (char *) xmalloc(sizeof(char)); // list of input data to be deciphered
        hobject->tdata = xmalloc(sizeof(struct transposed));
        hobject->inputlength = 0;
        hobject->hum = xmalloc(sizeof(struct humming));
        hobject->hum->keys_total = keys_total; // how many keylengths
        hobject->hum->keylength = (int *) xmalloc(keys_total * sizeof(int));
        hobject->hum->n_editdistance = (float *) xmalloc(keys_total * sizeof(float));
        hobject->scores = NULL;
        return hobject;
}

int hist_o_destroy(struct histogram *hobject)
{
        long counter;
        int i;
        if(hobject->scores != NULL)
               score_o_destroy(hobject->scores, hobject->tdata->elements);
        for(i = 0; i < hobject->tdata->elements; i++)
                xfree(hobject->tdata->blocks[i]);
        xfree(hobject->tdata->blocks);
        xfree(hobject->tdata->lengths);
        xfree(hobject->tdata);
        xfree(hobject->data); 
        xfree(hobject->hum->keylength);
        xfree(hobject->hum->n_editdistance);
        xfree(hobject->hum);
        xfree(hobject);
        return 0;
}

struct betterscore *score_o_init(long blockcount)
{
        struct betterscore *out = (struct betterscore *) xmalloc(blockcount * sizeof(struct betterscore));
        for(long i = 0; i < blockcount; i++) {
                out[i].score_elements =  0;
                out[i].number_of_signs = 26;
                memcpy(out[i].signs, letters, 26);
                out[i].testkey = (char *) xmalloc(sizeof(char));
                out[i].freq = (float **) xmalloc(sizeof(float *));
                out[i].freq[0] = NULL;
                //memset(out[i].freq[0], 0.0f, 26);
                //get_std_freq(&out[i].freq[0]);
                out[i].counted_letters = (long *) xmalloc(sizeof(long));
                out[i].counted_letters[0] = 0;
                out[i].ncoefficiant = (float *) xmalloc(sizeof(float));
                out[i].ncoefficiant[0] = 0.0f;
                //calc_normalized_coe(&out, 0);
        }
        return out;
}

void score_o_destroy(struct betterscore *sobj, long blockcount)
{
        for(long b = 0; b < blockcount; b++) {
                if(sobj[b].score_elements == 0)
                        sobj[b].score_elements = 1;
                for(long i = 0; i < sobj[b].score_elements; i++) {
                        xfree(sobj[b].freq[i]);
                }
                xfree(sobj[b].testkey);
                xfree(sobj[b].freq);
                xfree(sobj[b].counted_letters);
                xfree(sobj[b].ncoefficiant);
        }
        xfree(sobj);
}

void add_betterscore(struct histogram **hobj, long block, char *decrypted, char key)
{
        long elements = (*hobj)->scores[block].score_elements;
        (*hobj)->scores[block].testkey = xrealloc((*hobj)->scores[block].testkey, elements + 1); 
        (*hobj)->scores[block].testkey[elements] = key;
        (*hobj)->scores[block].freq = (float **) xrealloc((*hobj)->scores[block].freq,
                                        (elements + 1) * sizeof(float *));
        (*hobj)->scores[block].freq[elements] = NULL;
        (*hobj)->scores[block].freq[elements] = (float *) xrealloc((*hobj)->scores[block].freq[elements], 26 * sizeof(float));
        memset((*hobj)->scores[block].freq[elements], 0.0f, 26);
        (*hobj)->scores[block].counted_letters = (long *) xrealloc(
                                                        (*hobj)->scores[block].counted_letters,
                                                        sizeof(long) * (elements + 1));
        (*hobj)->scores[block].counted_letters[elements] = calc_letter_frequency(
                                                                &(*hobj)->scores[block].freq[elements],
                                                                decrypted, 
                                                                (*hobj)->tdata->lengths[block]);
        (*hobj)->scores[block].ncoefficiant = (float *) xrealloc(
                                                        (*hobj)->scores[block].ncoefficiant,
                                                        sizeof(float) * (elements + 1));
        calc_normalized_coe(&(*hobj)->scores[block], elements);
        (*hobj)->scores[block].score_elements++;
}
/*
        struct betterscore {
                long score_elements;
                int number_of_signs;
                char signs[26];
                char *testkey;
                float **freq;
                long *counted_letters;
                float *ncoefficiant;
        } *scores; */

void transpose(struct histogram **hist, struct transposed **tobject, char **inputstring, long length, int divisor)
{
        int i, o, c;
        long templength = length;
        (*tobject)->elements = divisor;
        (*tobject)->lengths = xmalloc(length/divisor * sizeof(long));
        (*tobject)->blocks = xmalloc(length/divisor * sizeof(char *));
        for(i = 0; i < divisor; i++) {
                (*tobject)->blocks[i] = xcalloc(length/divisor, sizeof(char));
                (*tobject)->lengths[i] = length / divisor;
        }
        o = 0;
        c = 0;
        while(length-1 >= c+i) {
                for(i = 0; i < divisor; i++) {
                        (*tobject)->blocks[i][o] = (*inputstring)[c+i];
                }
                o++;
                c += divisor;
        }
        (*hist)->scores = score_o_init((*tobject)->elements);
        return;
}

int resolve_keylength(struct humming **hobject, float editdistance)
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
        /* this function is calculating humming distances for different keylength given the encrypted data
         * sorting by keylength and return the minimum edit distance found
         */
        char *word = xmalloc((length+1) * sizeof(char));
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
        xfree(word);
        word = NULL;
        return distance;
}

int get_keylength(struct histogram **hobject, int maxlength, char *data, long length, int keys_total)
{
        if(maxlength < 2)
                return -1;
        if(length/2 < maxlength)
                maxlength = length/2;
        (*hobject)->data = xrealloc((*hobject)->data, length);
        int temp_distance = 0;
        int kctr = 0;
        int i; // counter variable for different key lengths
        int c; // outter counter, see splitter
        float hd; // humming distance temp
        char *first = NULL; // catches first keylength worth of bits from the data
        char *second = NULL; // catch second keylength wort of bits
        struct humming *distances = xmalloc(sizeof(struct humming));
        distances->keylength = xmalloc((maxlength-1) * sizeof(int));
        distances->keys_total = keys_total;
        distances->n_editdistance = xmalloc((maxlength-1) * sizeof(float));
        float *sorted_ed = xmalloc(maxlength * sizeof(float));
        float min_distance = 0; // catches minimum distance over all keylengths tested
        int min_key = 0; // catches minimum distance over all keylengths tested
        char temp_byte;
        for(i = 2; i <= maxlength; i++) {
                first = xmalloc(i * sizeof(char));
                second = xmalloc(i * sizeof(char));
                for(c = 0; c < i; c++) {
                        temp_byte = data[c];
                        first[c] = temp_byte;
                        temp_byte = data[c+i];
                        second[c] = temp_byte;
                }
                hd = humming_distance(first, second, i); 
                distances->n_editdistance[i-2] = hd / i;
                distances->keylength[i-2] = i;
                xfree(first);
                first = NULL;
                xfree(second);
                second = NULL;
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
                resolve_keylength(&distances, sorted_ed[kctr+1]);
               printf("\nKeylength: %i\tEditdistance %0.5f", (*hobject)->hum->keylength[kctr],
                                                        (*hobject)->hum->n_editdistance[kctr]);
        }
        xfree(distances->keylength);
        distances->keylength = NULL;
        xfree(distances->n_editdistance);
        distances->n_editdistance = NULL;
        xfree(distances);
        distances = NULL;
        xfree(sorted_ed);
        sorted_ed = NULL;
        return min_distance;
}

#endif /* !HISTOGRAM_C */
