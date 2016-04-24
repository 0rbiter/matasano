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

int humming_distance(char *word1, char *word2, long length)
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

int get_keylength(int maxlength, long dataindex, char *data, long length)
{
        if(maxlength < 2)
                return -1;
        int i;
        int c;
        int splitter;
        char *first = NULL;
        char *second = NULL;
        int *distances = malloc((maxlength-1) * sizeof(int));
        int min_distance = 0;
        for(i = 2; i <= maxlength; i++) {
                first = malloc(i * sizeof(char));
                second = malloc(i * sizeof(char));
                for(c = 0; c < i*2; c++) {
                        for(splitter = 0; splitter < i; splitter++) {
                                first[splitter] = data[c];
                                second[splitter] = data[c+splitter];
                        }
                }
                distances[i-2] = humming_distance(first, second, i) / i;
                free(first);
                free(second);
        }
        min_distance = 100000;
        for(i = 2; i <= maxlength; i++) {
                if(distances[i] < min_distance)
                        min_distance = distances[i];
                printf("Keylength: %i\tEdit Distance: %i\n", i, distances[i-2]);
        }
        free(distances);
        return min_distance;
}

int main(int argc, char **argv)
{
/*        s1c1();
        s1c2();
        s1c3();
        s1c4();
        s1c5();*/
        char *filename6 = "/home/orbiter/matasano/src/challenge6keys.txt";
        char *word1 = "this is a test\0";
        char *word2 = "wokka wokka!!!\0";
        //printf("%li", humming_distance(word1, word2));
        struct file_o *buffer6 = readBytes(filename6);
        file_o_init(buffer6);
        printf("%li", buffer6->elements);
        struct base64 **bbuffer = malloc((buffer6->elements+1) * sizeof(struct base64 *));

        struct keycharts *charts = malloc(1 * sizeof(struct keycharts));
        long c, length;
        for(c = 0; c < buffer6->elements; c++) {
                bbuffer[c] = malloc(1 * sizeof(struct base64));
                bbuffer[c]->input = (char*) calloc((buffer6->length[c]+2) * sizeof(char) , 1);
                length = b64_decode_string(bbuffer[c]->input, buffer6->buffer.c[c], buffer6->length[c]+1);
                if(!c) {
                        puts(bbuffer[c]->input);
                        get_keylength(4, c, bbuffer[c]->input, length);
                }
        }
        for(c = 0; c < buffer6->elements; c++) {
                free(bbuffer[c]->input);
                free(bbuffer[c]);
        }
        free(bbuffer);
        file_o_destroy(buffer6);
}

