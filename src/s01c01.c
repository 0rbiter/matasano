#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matasano.h"
#include <ctype.h>

// static prevents from conflicts with other files
char *HEXSTRING = "1C0111001F010100061A024B53535009181C0F";
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
    puts( decode(HEXSTRING) );
    puts( decode(HEXSTRING2) );

    puts( decode(HEXSTRING3) );
    return 0;
}
