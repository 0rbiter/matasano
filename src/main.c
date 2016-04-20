//#include "crypto.h"
#include "cryptodata.h"
#include "cryptodef.h"

int main()
{
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
