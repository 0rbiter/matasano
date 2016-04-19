//#include "crypto.h"
#include "cryptodata.h"
#include "cryptodef.h"

int main()
{
        int charcount = strlen(HEXSTRING);
    	int bitcount = charcount * 4;
        printf("Hexadecimal to convert to Base64:\n");
	puts( HEXSTRING );
    	printf("\nLength (bits/chars/bytes): %i/%i/%i", bitcount, charcount, bitcount/8);
    	printf("\nSolution 1:\n");
        char *b64HS = (char*) calloc(b64length(HEXSTRING), 1);
        hexstring_encode(b64HS, HEXSTRING, strlen(HEXSTRING));
        puts(b64HS);

        puts("Convert to ASCII:");
        char *decoded_string = calloc(strlen(b64HS)/4*3+1, 1);
        string_decode(decoded_string, b64HS, strlen(b64HS));
        puts(decoded_string);

        free(decoded_string);
        free(b64HS);

        return 0;
}
