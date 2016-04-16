#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matasano.h"

// static prevents from conflicts with other files
char *HEXSTRING = "1c0111001f010100061a024b53535009181c";
char *HEXSTRING2 = "686974207468652062756c6c277320657965";
int main()
{
	int charcount = strlen(HEXSTRING);
	int bitcount = charcount * 4;
	char *BCOMP_STRING;
	printf("Hexadecimal to convert to Base64:\n");
	puts( HEXSTRING );
	printf("\nLength (bits/chars/bytes): %i/%i/%i", bitcount, charcount, bitcount/8);
	printf("\nTesting Modulo 6 %c6 times 1 Hex = 3 Bytes%c: ", (unsigned int) 40, (unsigned int) 41);

	char *tempStr;
	if ((strlen(HEXSTRING) % 6) > 0) {
		printf("ERROR - filling up with 0 bytes");
		BCOMP_STRING = b64_FILLER(HEXSTRING);
	}
	else
	{
		printf("OK - continuing with Base64 encoding");
		BCOMP_STRING = HEXSTRING;
	}
	printf("\nUsing:\n");
	puts( BCOMP_STRING );
	printf("\nSolution:\n");
	puts( b64_encode(BCOMP_STRING) );
	
	return 0;
}
