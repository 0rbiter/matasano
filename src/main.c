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

long humming_distance(char *word1, char *word2)
{
        char *word = malloc(strlen(word1)+1);
        int i;
        long distance = 0;
        for(i = 0; i < strlen(word1); i++) {
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
        long c;
        for(c = 0; c < buffer6->elements; c++) {
                bbuffer[c] = malloc(1 * sizeof(struct base64));
                bbuffer[c]->input = (char*) calloc((buffer6->length[c]+2) * sizeof(char) , 1);
                b64_decode_string(bbuffer[c]->input, buffer6->buffer.c[c], buffer6->length[c]+1);
                //printf("\n%li\t%li\t%s", buffer6->length[c], strlen(buffer6->buffer.c[c]), buffer6->buffer.c[c]);
                puts(bbuffer[c]->input);
        }
        
        for(c = 0; c < buffer6->elements; c++) {
                free(bbuffer[c]->input);
                free(bbuffer[c]);
        }
        free(bbuffer);
        file_o_destroy(buffer6);
}

