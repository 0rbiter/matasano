//#include "crypto.h"
#include "cryptodata.h"
#include "cryptodef.h"

void separate()
{
        puts("\n\n###############################################################################");
}

int main()
{
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
        
        hexstringToString(STRING3, HEXSTRING3);
       
        long str_length = strlen(STRING3);
        char *NEWSTRING = calloc(str_length+1, 1);

        float letterscore[26] = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.361, 0.150, 1.974, 0.074 };
        float score[26];
        unsigned long letters_counted = 0;
        int l = 0;
        long points = 0;
        float myscores[26];

        printf("English Language scores:\n");
        for(l=0; l < 26; l++) {
                if(l % 6 == 0 && l != 0)
                        printf("\n");
                printf("%c %.2f\t", A+l, letterscore[l]);
        }
        printf("\n\n");
        for(i=0; i < 256; i++) {
                SINGLECHAR[0] = i;
                xor_strings(NEWSTRING, STRING3, SINGLECHAR);
                long f;
                for(l=0; l < 26; l++) {
                        myscores[l] = 0;
                        score[l] = 0;
                }
                letters_counted = 0;
                points = 0;
                for(f=0; f < str_length; f++) {
                        if(NEWSTRING[f] == ' ') {
                                printf("");
                                points += 3;
                                }
                        if(NEWSTRING[f] >= 65 && NEWSTRING[f] <= 90) {
                                points += 1;
                                letters_counted++;
                                score[NEWSTRING[f]-A]++;
                        }
                        else if(NEWSTRING[f] >= 97 &&  NEWSTRING[f] <= 97+25) {
                                points += 1;
                                letters_counted++;
                                score[NEWSTRING[f]-a]++;
                        }

                }


                float offset = 3;

                for(l=0; l < 26; l++) {
                        myscores[l] = score[l]/letters_counted;
                        myscores[l] = 100 * myscores[l];
                        if(letterscore[l]-offset <= myscores[l] ^ letterscore[l]+offset <= myscores[l]) {
                                points += 10;
                        }
                }
                points += letters_counted/5;
                if(points > 212) {
                        puts(NEWSTRING);
                        for(l=0; l < 26; l++) {
                                if(l % 6 == 0 && l != 0)
                                        printf("\n");
                                printf("%c %.2f\t", A+l, myscores[l]);
                        }
                        printf("\nPoints gained: %li \t\tLetters counted: %li\t\tKey: %c\n", points, letters_counted, i);
                }
              
        }

        free(NEWSTRING);
        free(STRING3);

        //for(i=0; i < strlen(NEWSTRING); i++) {
        //}
                
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
}
