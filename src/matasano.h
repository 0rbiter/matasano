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
    unsigned char *output = (unsigned char *) calloc(length/2, sizeof(unsigned char));
    
    int counter = 0;
    for(i=0; i<(length/2); i++)
    {
        output[i] |= charTo4Bits(input[counter], counter);
        counter++;
        output[i] |= charTo4Bits(input[counter], counter);
        counter++;
    }
    return output;
}

void shiftArrayLeft(unsigned char *input, int size, int shift)
{
    int i, s;
    unsigned char carry = 0x00f;
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
    unsigned char *bytebuffer = calloc(inputlength, sizeof(unsigned char));
    char *output = calloc(length+1, sizeof(char));
    buildHexTable();
    bytebuffer = charsToBytes(input);
    
    output[0] = BASE64[bytebuffer[0] >> 2];
    shiftArrayLeft(bytebuffer, inputlength, 6);
    
    for(i=1; i<length; i++)
    {
        output[i] = BASE64[bytebuffer[0] >> 2];
        shiftArrayLeft(bytebuffer, inputlength, 6);
    }
    free(bytebuffer);
    return output;
}

