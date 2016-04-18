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
    if(HEXTABLE[0][0] != '0') printf("Loaded Hextable - this shouldn't happen!"); buildHexTable();
    int i, a = 0;
    for(i=0; i<16; i++)
    {
        if(toupper(input) == HEXTABLE[0][i])
        {
            a = i;
            break;
        }
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
    char *boutput = (char *) calloc(length+1, sizeof(char));
    boutput[length] = '\0';
    int i, i2 = 0;
    unsigned char x1, x2;
    for(i=0; i<(length/2); i++)
    {
        i2 = (i+1)*2;
   //     printf("Inputbytes: %i\n", i);
        x1 = inputbytes[i] >> 4;
        x2 = inputbytes[i] & 0x0F;
        if(x1 > 0 && x2 > 0 && x1 < 16 && x2 < 16)
        {
            boutput[i2-2] = HEXTABLE[0][inputbytes[i] >> 4];
            boutput[i2-1] = HEXTABLE[0][inputbytes[i] & 0x0F];
        }
    }
    return boutput;
}



unsigned char *charsToBytes(char *input, long length)
{
    int i;
    unsigned char *coutput = (unsigned char *) calloc(1, 1);
    if(length>1) {
        free(coutput);
        coutput = (unsigned char *) calloc(length/2, 1);
        //coutput = realloc(coutput, length/2);
    }
    int counter = 0;
    if(length>1)
    {
        for(i=0; i<(length/2); i++)
        {
            printf("counter: %i -- i: %i -- length: %lu -- length/2: %lu\n", counter, i, length, length/2);
            coutput[i] |= charTo4Bits(input[counter], counter);
            counter++;
            coutput[i] |= charTo4Bits(input[counter], counter);
            counter++;
        }
    }
    else if(length == 1)
    {
        coutput[0] |= charTo4Bits(input[0], 0);
        coutput[0] |= charTo4Bits(input[0], 1);
    }
    else
    {
        printf("Error in charsToBytes - length might be <= 0\n");
    }
    return coutput;
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
        //bytebuffer1 = charsToBytes(input1, strlen(input1));
        //bytebuffer2 = charsToBytes(input2, strlen(input2));
        memcpy(bytebuffer1, charsToBytes(input1, strlen(input1)), strlen(input1));
        memcpy(bytebuffer2, charsToBytes(input2, strlen(input2)), strlen(input2));
        
        for(i=0; i<inputlength; i++)
        {
            byteoutput[i] = bytebuffer1[i] ^ bytebuffer2[i];
        }

        output = BytesToChar(byteoutput, inputlength);
    }
    else if(strlen(input1) > strlen(input2) && strlen(input2) == 1)
    {    
        byteoutput = realloc(byteoutput, inputlength);
    
        //bytebuffer1 = charsToBytes(input1, strlen(input1));
        //bytebuffer2 = charsToBytes(input2, 1);
        memcpy(bytebuffer1, charsToBytes(input1, strlen(input1)), strlen(input1));
        memcpy(bytebuffer2, charsToBytes(input2, 1), 1);
        for(i=0; i<inputlength/2; i++)
        {
            byteoutput[i] = bytebuffer1[i] ^ bytebuffer2[0];
        }
        output = BytesToChar(byteoutput, inputlength/2);
    }
    free(bytebuffer1);
    free(bytebuffer2);
    free(byteoutput);
    bytebuffer1 = NULL;
    bytebuffer2 = NULL;
    byteoutput = NULL;
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
    memcpy(bytebuffer, charsToBytes(input, strlen(input)), strlen(input));
    
    for(i=0; i<length; i++)
    {
        output[i] = BASE64[bytebuffer[0] >> 2];
        shiftArrayLeft(bytebuffer, inputlength, 6);
        if((i>=length-1-(fillercount/2)) && fillercount > 0) output[i] = filler;
    }

    free(bytebuffer);
    return output;
}

