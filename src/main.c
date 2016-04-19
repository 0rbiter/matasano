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
    	printf("\nSolution:\n");
        char *b64HS = (char*) calloc(b64length(HEXSTRING), 1);
        decode(b64HS, HEXSTRING, strlen(HEXSTRING));
        puts(b64HS);
        free(b64HS);
        return 0;
}
