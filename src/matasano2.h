#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    if(HEXTABLE[0][0] != '0') buildHexTable();
    int i;
    for(i=0; i<16; i++)
    {
        if(toupper(input) == HEXTABLE[0][i]) break;
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


void shiftArrayLeft(unsigned char *input, int size, int shift)
{
    int i, s;
    unsigned char carry = 0x00f;
    for(s=shift; s>0; s--)
    {
        for(i=0; i<(size); i++)
        {
            if(i+1 != size) carry = (input[i+1] & 0x80) >> 7;
            else carry = 0x00;
            input[i] = carry | (input[i] << 1);
        }
    }
}

void decode(char* output, char* input, int inputlength)
{
    if(inputlength % 2 != 0) { printf("too short"); exit(-1); }
    int fillercount = 0;
    int outputlength = (inputlength / 6 * 4); //96 -> 64, 48 -> 24 etc.
    if(inputlength % 6 > 0) outputlength += 4; fillercount = inputlength % 6;

    printf("Inputlength: %i\n", inputlength); 
    printf("Outputlength: %i\n", outputlength); 
    unsigned char* buffer = (unsigned char*) calloc(inputlength/2, 1);
    int i, a = 0;
    char filler = '=';

    for(i=0; i<inputlength/2; i++)
    {
        buffer[i] |= charTo4Bits(input[a], a);
        a++;
        buffer[i] |= charTo4Bits(input[a], a);
        a++;
    }
    for(i=0; i<outputlength; i++)
    {
        output[i] = BASE64[(buffer[0] >> 2)];
        shiftArrayLeft(buffer, inputlength/2, 6);
    }
    if(fillercount > 0)
    {
        int b;
        for(b=0; b<=fillercount/2-2; b++)
        {
            printf("counter. %i\n", b);
            output[outputlength-1-b] = filler;
        }

    }
    free(buffer);

}
