#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif

#include "filehandler.h"
#include "cryptodata.h"
#include "cryptodef.h"
#include "scoring.h"

void separate()
{
        puts("\n\n###############################################################################");
}

int main(int argc, char **argv)
{



        separate();
        /*
         * convert from string to hex/bytes and Base 64 decode it
         * */
        char *HEXSTRING = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

        printf("\nChallenge 1\nHexadecimal to convert to Base64:\n");
	puts(HEXSTRING);
    	printf("\nSolution:\n");
        char *b64HS = (char*) calloc(b64length(HEXSTRING), 1);
        hexstring_encode_b64(b64HS, HEXSTRING, strlen(HEXSTRING));
        puts(b64HS);

        puts("Convert to ASCII:");
        char *decoded_string = calloc(strlen(b64HS)/4*3+1, 1);
        b64_decode_string(decoded_string, b64HS, strlen(b64HS));
        puts(decoded_string);

        free(decoded_string);
        free(b64HS);

        separate();
        /*
         * Challenge 2, XOR 2 HEX values from input strings + Base64 decode
         */
        char *HEXSTRING1 = "1c0111001f010100061a024b53535009181c";
        char *HEXSTRING2 = "686974207468652062756C6C277320657965";
        puts("Challenge 2\nXOR these two hex strings & base64 decode it:");
        puts(HEXSTRING1);
        puts(HEXSTRING2);
        puts("\nXOR'd:");
        char *xor_b64 = calloc(b64length(HEXSTRING1), 1);
        xor_hexstrings(xor_b64, HEXSTRING1, HEXSTRING2);
        puts(xor_b64);
        puts("\nBase64 decoded:");
        char *xor_string = calloc(strlen(xor_b64), 1);
        b64_decode_string(xor_string, xor_b64, strlen(xor_b64));
        puts(xor_string);
        free(xor_b64);
        free(xor_string);

        separate();
        /*
         * Challenge 3, XOR 2 HEX values with different length from input strings,
         * and print HEX string
         */
        char HEXSTRING3[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736\0";
        char *STRING3 = calloc(strlen(HEXSTRING3)/2+1, 1);
        char SINGLECHAR[] = "A\0";
        int i, c;
        printf("Challenge 3\nfind the single byte to decrypt:\n");
        puts(HEXSTRING3);
        printf("\n");
        
        hexstringToString(STRING3, HEXSTRING3);
        long str_length = ownlen(STRING3);
        char *NEWSTRING = calloc(str_length+1, 1);

        print_en_scores();

        for(i=0; i < 256; i++) {
                SINGLECHAR[0] = i;
                xor_strings(NEWSTRING, STRING3, SINGLECHAR);
                get_score(NEWSTRING, strlen(NEWSTRING), SINGLECHAR, 530, 3.0f, 0, 0);
              
        }

        free(NEWSTRING);
        free(STRING3);
        separate();
        
        /*
         * Challenge 5
         */
        printf("Challenge 5\nXOR this text with the 3 character key:\n");
        char *STRING4 = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
        puts(STRING4);
        printf("\n");

        char *STRING5 = "ICE";
        puts("Key:");
        puts(STRING5);
        printf("\n");

        char *xor_string2 = calloc(strlen(STRING4)+1, 1);
        char *xor_hexstring = calloc(strlen(STRING4)*2+1, 1);
        xor_strings(xor_string2, STRING4, STRING5);
        bitsToHexchar(xor_hexstring, xor_string2);
        puts("Solution:");
        puts(xor_hexstring);

        free(xor_hexstring);
        free(xor_string2);
        
        separate();
        /*
         * read all keys from ../src/challenge4keys.txt and put them in strings
         * use xor encryption and try different chars, run them through scoring
         * profit!
         * */
        printf("Challenge 5\nread 60 keys from file and find the encryption character\nand the according line");
        printf("\n");
        char ENCCHAR[] = "A\0";
        char filename[] = "/home/orbiter/matasano/src/challenge4keys.txt";
        char **stringlist = NULL;
        char *STR_STRING = malloc(1);
        unsigned char TMP_STRING[30]; // = malloc(1);
        char *STR_XOR = malloc(1);
        long linecount = 0;
        long SIZEOFSTRING = 0;
        long charcounter = 0;

        if((linecount = readFile(&stringlist, filename)) != -1) {
                int k, ki; 
                print_en_scores();
                for(k=0; k < linecount; k++) {
                        SIZEOFSTRING = ownlen(stringlist[k]);
                        STR_STRING = realloc(STR_STRING, SIZEOFSTRING/2+1);
                        STR_STRING[SIZEOFSTRING/2] = '\0';
                        hexstringToString(STR_STRING, stringlist[k]);
                        if(STR_STRING == NULL)
                                exit(-1);
                        
                        STR_XOR = realloc(STR_XOR, SIZEOFSTRING/2+1);
                        if(STR_XOR == NULL)
                                exit(-1);
                        STR_XOR[SIZEOFSTRING/2] = '\0';

                        for(charcounter=0; charcounter < 256; charcounter++) {
                                ENCCHAR[0] = charcounter;
                                xor_strings(STR_XOR, STR_STRING, ENCCHAR);
                                //get_score(STR_XOR, SIZEOFSTRING/2, ENCCHAR, 400, 9.0f, 0, 1);
                        }
                }
        }
        long q;
        for(q=0; q < linecount+1; q++) {
                free(stringlist[q]);
        }
        free(stringlist);
        free(STR_STRING);
        free(STR_XOR);
}
