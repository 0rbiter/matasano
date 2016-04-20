//#include "crypto.h"
#include "cryptodata.h"
#include "cryptodef.h"

char *HEXSTRING3 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

int main()
{
        /*
         * convert from string to hex/bytes and Base 64 decode it
         * */
        char *HEXSTRING = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

        printf("Hexadecimal to convert to Base64:\n");
	puts( HEXSTRING );
    	printf("\nSolution 1:\n");
        char *b64HS = (char*) calloc(b64length(HEXSTRING), 1);
        hexstring_encode_b64(b64HS, HEXSTRING, strlen(HEXSTRING));
        puts(b64HS);

        puts("Convert to ASCII:");
        char *decoded_string = calloc(strlen(b64HS)/4*3+1, 1);
        b64_decode_string(decoded_string, b64HS, strlen(b64HS));
        puts(decoded_string);

        free(decoded_string);
        free(b64HS);

        /*
         * Challenge 2, XOR 2 HEX values from input strings + Base64 decode
         */
        char *HEXSTRING1 = "1c0111001f010100061a024b53535009181c";
        char *HEXSTRING2 = "686974207468652062756C6C277320657965";

        puts("XOR these two hex strings:");
        puts(HEXSTRING1);
        puts(HEXSTRING2);

        char *xor_b64 = calloc(b64length(HEXSTRING1), 1);

        xor(xor_b64, HEXSTRING1, HEXSTRING2);
        puts(xor_b64);
  
        char *xor_string = calloc(strlen(xor_b64), 1);
        b64_decode_string(xor_string, xor_b64, strlen(xor_b64));
        puts(xor_string);

        free(xor_b64);
        free(xor_string);

        return 0;
}
