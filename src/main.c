#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matasano2.h"
#include <ctype.h>

// static prevents from conflicts with other files
//char *HEXSTRING = "1C0111001F010100061A024B53535009181C0F0F0F";
char *HEXSTRING = "1C";
char *HEXSTRING2 = "686974207468652062756C6C277320657965";
char *HEXSTRING3 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

int main()
{
	int charcount = strlen(HEXSTRING);
	int bitcount = charcount * 4;
	
    printf("Hexadecimal to convert to Base64:\n");
	puts( HEXSTRING );
	puts( HEXSTRING2 );
	puts( HEXSTRING3 );
	printf("\nLength (bits/chars/bytes): %i/%i/%i", bitcount, charcount, bitcount/8);
    
	printf("\nSolution:\n");
    
    int addition = 0;
    if(strlen(HEXSTRING) % 6 > 0) addition = 4;
    char* b64HS = (char*) calloc(strlen(HEXSTRING) / 3 * 2 + addition + 1, 1);
    b64HS[strlen(HEXSTRING)/3*2] = '\0';

    decode(b64HS, HEXSTRING, strlen(HEXSTRING));
    puts(b64HS);

    free(b64HS);
    return 0;
}
