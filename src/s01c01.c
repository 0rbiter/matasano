#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matasano.h"

// static prevents from conflicts with other files
char *HEXSTRING = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

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
	
	puts( b64_encode(BCOMP_STRING) );
	unsigned int tester = 0x2349;
	printf("\n%i", tester);

/*
	char *testing = "Hello this is a test!";
	puts(testing);
	//printf("%i", isTerminated("blubber blah"));
	if (isTerminated(testing) > 0) { printf("\nokay, jetzt!"); }
*/
	return 0;
}
