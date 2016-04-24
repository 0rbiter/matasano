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

int main(int argc, char **argv)
{
        separate();
        /*
         * Challenge 3, XOR 2 HEX values with different length from input strings,
         * and print HEX string
         */

        
        char HEXSTRING3[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736\0";
        char SINGLECHAR[] = "A\0";
        char *STRING3 = malloc(1 * sizeof(char));
        int i, c;
        printf("Challenge 3\nfind the single byte to decrypt:\n");
        puts(HEXSTRING3);
        long str_length = hexstringToString(&STRING3, HEXSTRING3);
        char *NEWSTRING = malloc(1 * sizeof(char));
        for(i=0; i < 256; i++) {
                SINGLECHAR[0] = i;
                xor_bytes_to_string(&NEWSTRING, STRING3, str_length, SINGLECHAR, 1);
                get_score(NEWSTRING, str_length, SINGLECHAR, 50, 2.0f, 0, 1);
        }
        get_best();
        destroy_scores();
        free(NEWSTRING);
        free(STRING3);
        separate();
        /*
         * read all keys from ../src/challenge4keys.txt and put them in strings
         * use xor encryption and try different chars, run them through scoring
         * profit!
         * */
        
        printf("Challenge 4\nread 60 keys from file and find the encryption character\nand the according line");
        printf("\n");
        char ENCCHAR[] = "A\0";
        char filename[] = "/home/orbiter/matasano/src/challenge4keys.txt";
        char *STR_STRING = malloc(1);
        char *STR_XOR = malloc(1);
        long lines = 0;
        int x;
        long length1;

        struct file_o *buffer1 = readBytes(filename);
        file_o_init(buffer1);
        
        for(lines = 0; lines < buffer1->elements; lines++) {
                length1 = hexstringToString(&STR_STRING, buffer1->buffer.c[lines]);
                for(x=53; x < 54; x++) {
                        ENCCHAR[0] = x;
                        xor_bytes_to_string(&STR_XOR, STR_STRING, length1, ENCCHAR, 1);
                        get_score(STR_XOR, length1, ENCCHAR, 70, 2.0f, 1, 1);
                }
        }
        printf("\nNumber of actions: %li", lines*x);
        get_best();
        destroy_scores();
        
        file_o_destroy(buffer1);
        free(STR_STRING);
        free(STR_XOR); 
}

