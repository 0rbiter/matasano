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

char *BytesToChar(unsigned char *inputbytes, int length)
{
    char *output = (char *) calloc((length/2)+1, sizeof(char));
    int i, i2 = 0;
    for(i=0; i<(length/2); i++)
    {
        i2 = (i+1)*2;
        //printf("Left: %i -- Right: %i\n",  (int) inputbytes[i] >> 4, (int) (inputbytes[i] & 0x0F));
        //printf("i: %i -- i2(1/2): %i/%i\n", i, i2-2, i2-1);
        output[i2-2] = HEXTABLE[0][inputbytes[i] >> 4];
        output[i2-1] = HEXTABLE[0][inputbytes[i] & 0x0F];
    }
    return output;
}



unsigned char *charsToBytes(char *input, long length)
{
    int i;
    printf("Break 1\n");
    unsigned char *output = (unsigned char *) calloc(1, sizeof(unsigned char));
    printf("Break 2\n");
    if(length>1) output = (unsigned char *) realloc(output, length/2+1);
    printf("Break 3\n");
    int counter = 0;
    if(length>1)
    {
        for(i=0; i<(length/2); i++)
        {
            output[i] |= charTo4Bits(input[counter], counter);
            counter++;
            output[i] |= charTo4Bits(input[counter], counter);
            counter++;
        }
    }
    else if(length == 1)
    {
        output[0] |= charTo4Bits(input[0], 0);
        output[0] |= charTo4Bits(input[0], 1);
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

char *xor(char *input1, char *input2)
{
    int inputlength = strlen(input1);
    int i;

    unsigned char *bytebuffer1 = calloc(inputlength, sizeof(unsigned char));
    unsigned char *bytebuffer2 = calloc(inputlength, sizeof(unsigned char));
    unsigned char *byteoutput = calloc(inputlength, sizeof(unsigned char));
    char *output = calloc(inputlength*2+1, sizeof(char));

    buildHexTable();
    if(strlen(input2) == strlen(input1)) {
        bytebuffer1 = charsToBytes(input1, strlen(input1));
        bytebuffer2 = charsToBytes(input2, strlen(input2));

        for(i=0; i<inputlength; i++)
        {
            byteoutput[i] = bytebuffer1[i] ^ bytebuffer2[i];
        }

        free(bytebuffer1);
        free(bytebuffer2);
        output = BytesToChar(byteoutput, inputlength);
    }
    else if(strlen(input1) > strlen(input2) && strlen(input2) == 1)
    {    
        byteoutput = realloc(byteoutput, inputlength);
        output = realloc(output, (inputlength*2)+1);
        bytebuffer1 = charsToBytes(input1, strlen(input1));
        bytebuffer2 = charsToBytes(input2, 1);
        for(i=0; i<inputlength; i++)
        {
            byteoutput[i] = bytebuffer1[i] ^ bytebuffer2[0];
        }
        free(bytebuffer1);
        free(bytebuffer2);
        output = BytesToChar(byteoutput, inputlength);
    }
    return output;
}

char *decode(char *input)
{
    int i, fc;
    int inputlength = strlen(input)/2;
    
    int fillercount = strlen(input)%6;
    char filler = '=';

    int length;
    if(fillercount == 0) length = (inputlength/3*4);
    else length = (inputlength/3*4)+4;

    unsigned char *bytebuffer = calloc(inputlength, sizeof(unsigned char));
    char *output = calloc(length+1, sizeof(char));
    buildHexTable();
    bytebuffer = charsToBytes(input, strlen(input));
    
    for(i=0; i<length; i++)
    {
        output[i] = BASE64[bytebuffer[0] >> 2];
        shiftArrayLeft(bytebuffer, inputlength, 6);
        if((i>=length-1-(fillercount/2)) && fillercount > 0) output[i] = filler;
    }

    free(bytebuffer);
    return output;
}

