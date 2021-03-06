#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "../include/headerfiles.h"
#endif

#ifndef PROJECT_LIBS
#define PROJECT_LIBS
#include "../include/cryptodata.h"
#include "../include/cryptodef.h"
#include "../include/filehandler.h"
#include "../include/scoring.h"
#endif 

void separate()
{
        puts("\n\n###############################################################################");
}
void s1c1() {
        separate();
        /*
         * convert from string to hex/bytes and Base 64 decode it
         * */
        char *HEXSTRING = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
        printf("\nChallenge 1\nHexadecimal to convert to Base64:\n");
	puts(HEXSTRING);
    	printf("\nSolution:\n");
        char *b64HS = (char*) xcalloc(b64length(HEXSTRING), 1);
        hexstring_encode_b64(b64HS, HEXSTRING, strlen(HEXSTRING));
        puts(b64HS);
        puts("Convert to ASCII:");
        char *decoded_string = xcalloc(strlen(b64HS)/4*3+1, 1);
        b64_decode_string(decoded_string, b64HS, strlen(b64HS));
        puts(decoded_string);
        xfree(decoded_string);
        xfree(b64HS);
}

void s1c2() {
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
        char *xor_b64 = xcalloc(b64length(HEXSTRING1), 1);
        xor_hexstrings(xor_b64, HEXSTRING1, HEXSTRING2);
        puts(xor_b64);
        puts("\nBase64 decoded:");
        char *xor_string = xcalloc(strlen(xor_b64), 1);
        b64_decode_string(xor_string, xor_b64, strlen(xor_b64));
        puts(xor_string);
        xfree(xor_b64);
        xfree(xor_string);
}

void s1c3()
{
        separate();
        /*
         * Challenge 3, XOR 2 HEX values with different length from input strings,
         * and print HEX string
         */
        char HEXSTRING3[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736\0";
        char SINGLECHAR[] = "A\0";
        char *STRING3 = xmalloc(1 * sizeof(char));
        int i, c;
        printf("Challenge 3\nfind the single byte to decrypt:\n");
        puts(HEXSTRING3);
        long str_length = hexstr_to_string(&STRING3, HEXSTRING3);
        char *NEWSTRING = xmalloc(1 * sizeof(char));
        for(i=0; i < 256; i++) {
                SINGLECHAR[0] = (char) i;
                xor_bytes_to_string(&NEWSTRING, STRING3, str_length, SINGLECHAR, 1);
                get_score(NEWSTRING, str_length, SINGLECHAR, -1000, 2.0f, 0);
        }
        get_best();
        destroy_scores();
        xfree(NEWSTRING);
        xfree(STRING3);
}


void s1c4()
{
        separate();
        /*
         * Challenge 4: read all keys from ../src/challenge4keys.txt and put them in strings
         * use xor encryption and try different chars, run them through scoring
         * profit!
         * */
        printf("Challenge 4\nread 60 keys from file and find the encryption character\nand the according line");
        printf("\n");
        char ENCCHAR[] = "A\0";
        char filename[] = "/home/uniscon169/matasano/src/challenge4keys.txt";
        char *STR_STRING = xmalloc(1);
        char *STR_XOR = xmalloc(1);
        long lines = 0;
        int x;
        long length1;
        struct file_o *buffer1 = read_bytes(filename);
        file_o_init(buffer1);
        for(lines = 0; lines < buffer1->elements; lines++) {
                length1 = hexstr_to_string(&STR_STRING, buffer1->buffer.c[lines]);
                for(x=0; x < 256; x++) {
                        ENCCHAR[0] = x;
                        xor_bytes_to_string(&STR_XOR, STR_STRING, length1, ENCCHAR, 1);
                        get_score(STR_XOR, length1, ENCCHAR, 70, 2.0f, 0);
                }
        }
        printf("\nNumber of actions: %li", lines*x);
        get_best();
        destroy_scores();
        file_o_destroy(buffer1);
        xfree(STR_STRING);
        xfree(STR_XOR); 
}


void s1c5() {
        separate();
        /*
         * Challenge 5
         */
        printf("Challenge 5\nXOR this text with the 3 character key:\n");
        char *STRING4 = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
        puts(STRING4);
        printf("\n");

        char *STR_KEY5 = "ICE";
        printf("Key: %s\n", STR_KEY5);

        char *xor_string2 = xcalloc(strlen(STRING4)+1, 1);
        char *xor_hexstring = xcalloc(strlen(STRING4)*2+1, 1);
        //xor_strings(xor_string2, STRING4, STR_KEY5);
        xor_bytes_to_string(&xor_string2, STRING4, strlen(STRING4), STR_KEY5, 3);
        bits_to_hexchar(xor_hexstring, xor_string2);
        puts("Solution:");
        puts(xor_hexstring);

        xfree(xor_hexstring);
        xfree(xor_string2);
        separate();
}

