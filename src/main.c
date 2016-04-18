#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matasano.h"
#include <ctype.h>

// static prevents from conflicts with other files
char *HEXSTRING = "1C0111001F010100061A024B53535009181C";
char *HEXSTRING2 = "686974207468652062756C6C277320657965";
char *HEXSTRING3 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
char *HEXSTRING4 = "1B37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

int main()
{
    printf("\n XOR w/o B64 decoding against single character:\n");

    char *SINGLE = (char *) calloc(2, sizeof(char));
    char SINGLEAR[1] = { 0x00 };
    int i=0;
    for(i=0; i<255; i++)
    {
        SINGLEAR[0] = i;
        memcpy(SINGLE, SINGLEAR, 1);
        SINGLE[1] = '\0';
        //xor(HEXSTRING4, SINGLE);
    }
/*
    puts( HEXSTRING4 );
    SINGLEAR[0] += 66;
    memcpy(SINGLE, SINGLEAR, 1);
    SINGLE[1] = '\0';
    puts( SINGLE );
    puts( xor(HEXSTRING4, SINGLE) );i */
    xor(HEXSTRING, HEXSTRING2);
    free(SINGLE);
    return 0;
}
