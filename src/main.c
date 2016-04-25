#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif

#include "filehandler.c"
#include "cryptodata.h"
#include "cryptodef.c"
#include "scoring.c"
#include "set1.c"

void s1c1();
void s1c2();
void s1c5();

struct keycharts {
        long *index;
        int *distance;
        int *keylength;
};

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

float get_keylength(int maxlength, long dataindex, char *data, long length)
{
        if(maxlength < 2)
                return -1;
        if(length/2 < maxlength)
                maxlength = length/2;
        int i; // counter variable for different key lengths
        int c; // outter counter, see splitter
        float hd; // humming distance temp
        char *first = NULL; // catches first keylength worth of bits from the data
        char *second = NULL; // catch second keylength wort of bits
        float *distances = calloc((maxlength-1), sizeof(float));
        float min_distance = 0; // catches minimum distance over all keylengths tested
        for(i = 2; i <= maxlength; i++) {
                first = malloc(i * sizeof(char));
                second = malloc(i * sizeof(char));
                for(c = 0; c < i; c++) {
                        first[c] = data[c];
                        second[c] = data[c+i];
                }
                hd = humming_distance(first, second, i); 
                distances[i-2] = hd / i;
                free(first);
                free(second);
        }
        min_distance = 100000;
        for(i = 2; i <= maxlength; i++) {
                if(distances[i-2] < min_distance)
                        min_distance = distances[i-2];
        }
        free(distances);
        return min_distance;
}

int main(int argc, char **argv)
{ /*
        s1c1();
        s1c2();
        s1c3();
        s1c4();
        s1c5();*/
        char *filename6 = "/home/orbiter/matasano/src/challenge6keys.txt";
        char *word1 = "this is a test\0";
        char *word2 = "wokka wokka!!!\0";
        //printf("%li", humming_distance(word1, word2));
        struct file_o *filebuffer6 = readBytes(filename6);
        file_o_init(filebuffer6);
        printf("%li", filebuffer6->elements);
        struct base64 **b64buffer = malloc((filebuffer6->elements+1) * sizeof(struct base64 *));

        struct keycharts *charts = malloc(1 * sizeof(struct keycharts));
        long c, length;
        float kl = 0;
        for(c = 0; c < filebuffer6->elements; c++) {
                b64buffer[c] = malloc(1 * sizeof(struct base64));
                b64buffer[c]->input = malloc(1 * sizeof(char *));
                length = active_b64_decode_string(&b64buffer[c]->input, filebuffer6->buffer.c[c], filebuffer6->length[c]+1);
                if(1) {
                        puts(b64buffer[c]->input);
                        kl = get_keylength(20, c, b64buffer[c]->input, length);
                        printf("Minimum Distance: %0.2f\n", kl);
                }
        }
        for(c = 0; c < filebuffer6->elements; c++) {
                free(b64buffer[c]->input);
                free(b64buffer[c]);
        }
        free(charts);
        free(b64buffer);
        file_o_destroy(filebuffer6);
}

