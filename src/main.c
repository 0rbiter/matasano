#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matasano.h"
#include <ctype.h>

// static prevents from conflicts with other files
char *HEXSTRING = "1C0111001F010100061A024B53535009181C";
char *HEXSTRING2 = "686974207468652062756C6C277320657965";
char *HEXSTRING3 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
char HEXTABLE[2][16];

static const char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void buildHexTable()
{
    unsigned char zero = 0x00;
    unsigned char A = 55;
    unsigned char zeroChar = 48;
    int i;
    for(i=0; i<16; i++)
    {
        if(i<10)
        {
            HEXTABLE[0][i] = zeroChar + i;
        }
        else
        {
            HEXTABLE[0][i] = A + i;
        }
        HEXTABLE[1][i] = zero + i;
    }


}

unsigned char charTo4Bits(char input, unsigned int leftorright)
{
    int i = 0;
    while(HEXTABLE[0][i] != toupper(input))
    {
        i++;
    }

    if(leftorright % 2 == 0)
    {
        return HEXTABLE[1][i] << 4;
    }
    else
    {
        return HEXTABLE[1][i]; 
    }
}

unsigned char *charsToBytes(char *input)
{
    int i;
    int length = strlen(input);
    unsigned char *output = malloc(length/2 * sizeof(char));
    for(i=0; i<length; i++)
    {
        output[i] = 0x00;
    }

    for(i=0; i<(length); i++)
    {
        output[i/2] |= charTo4Bits(input[i], i);
    }
    return output;
}

void shiftArrayLeft(unsigned char *input, int size, int shift)
{
    int i, s;
    unsigned char carry = 0x00;
    for(s=shift; s>0; s--)
    {
        for(i=0; i<(size); i++)
        {
            carry = (input[i+1] & 0x80) >> 7;
            input[i] = carry | (input[i] << 1);
        }
    }
}

char *decode(char *input)
{
    int i;
    int inputlength = strlen(input)/2;
    int length = inputlength/3*4;
    unsigned char *bytebuffer = malloc(inputlength-1 * sizeof(char));
    char *output = malloc(length * sizeof(char));
    buildHexTable();
    bytebuffer = charsToBytes(input);
    
    output[0] = BASE64[bytebuffer[0] >> 2];
    shiftArrayLeft(bytebuffer, inputlength, 6);
    
    for(i=1; i<length; i++)
    {
        output[i] = BASE64[bytebuffer[0] >> 2];
        shiftArrayLeft(bytebuffer, length, 6);
    }
    return output;
}

int main()
{
	int charcount = strlen(HEXSTRING);
	int bitcount = charcount * 4;
	
    printf("Hexadecimal to convert to Base64:\n");
	puts( HEXSTRING );
	puts( HEXSTRING2 );
	printf("\nLength (bits/chars/bytes): %i/%i/%i", bitcount, charcount, bitcount/8);
    
	printf("\nSolution:\n");
    //puts( decode(HEXSTRING) );
    puts( decode(HEXSTRING3) );
    return 0;
}
