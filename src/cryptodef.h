
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
long b64length(char *pre_decode_STRING)
{
        int addition = 0;
        if(strlen(pre_decode_STRING) % 6 > 0)
                addition = 4;
        return (long) strlen(pre_decode_STRING) / 6  * 4 + addition + 1;
}


void buildHexTable()
{
        int i;
        for(i=0; i<16; i++) {
                if(i<10)
                        HEXTABLE[0][i] = zeroChar + i;
                else
                        HEXTABLE[0][i] = A + i;
                HEXTABLE[1][i] = zero + i;
        }
}

void shiftArrayLeft(unsigned char *input, int size, int shift)
{
        int i, s;
        unsigned char carry = zero;
        for(s=shift; s>0; s--) {
                for(i=0; i<(size); i++) {
                        if(i+1 != size)
                                carry = (input[i+1] & 0x80) >> 7;
                        else
                                carry = zero;                     
                        input[i] = carry | (input[i] << 1);
                }
        }
}
unsigned char charTo4Bits(char input, unsigned int leftorright)
{
        if(HEXTABLE[0][0] != '0') buildHexTable();
        int i;
        for(i=0; i<16; i++)
                if(toupper(input) == HEXTABLE[0][i])
                        break;

        if(leftorright % 2 == 0)
                return HEXTABLE[1][i] << 4;
        else
                return HEXTABLE[1][i];
}

void stringToBytes(unsigned char *buffer, char *input)
{
        if(strlen(input) % 2 > 0) {
                printf("Error - string length is odd. 2 hex needed to fill a byte!");
                exit(-1);
        }
        int a = 0;
        int i = 0;
        while(input[a] != '\0') {
                buffer[i] |= charTo4Bits(input[a], a);
                a++;
                if(a % 2 == 0 && a != 0) i++;
        }
}

void bytesToB64(char *b64_string, unsigned char *buffer, long b64len, long bufferlen)
{
        int equalsigncount = 0;
        long inputlength = bufferlen*2;
        long outputlength = (inputlength / 6  *4); //96 -> 64, 48 -> 24 etc.
        if(inputlength % 6 > 0) {
                outputlength += 4;
                equalsigncount = inputlength % 6;
        }

        int i = 0;

        for(i=0; i<b64len; i++) {
                b64_string[i] = BASE64[(buffer[0] >> 2)];
                shiftArrayLeft(buffer, bufferlen, 6);
        }
        if(equalsigncount > 0) {
                int b;
                for(b=(3-equalsigncount/2); b>0; b--) {
                        b64_string[b64len-b] = equalsign;
                }
        }
        b64_string[b64len-1] = '\0';
}


void string_decode(char *input, long inputlength)
{
        struct base64 *xobject = malloc(sizeof(struct base64));
        xobject->inputlength = inputlength;
        xobject->b64_string = (char*) calloc(xobject->inputlength+1, 1);
        xobject->ascii_string = (char*) calloc(xobject->inputlength/4*3+1, 1);
        memcpy(xobject->b64_string, input, inputlength);

        char *tempchar = calloc(5, 1);
        tempchar[4] = '\0';
        long i, j = 0;
        for(i=1; i <= inputlength/4; i++) {
                memcpy(tempchar, xobject->b64_string+4*i, 4);
        }
        printf("Test:\n");
        puts(tempchar);
        printf("\nEnd!\n");


}

void hexstring_encode(char *output, char *input, long inputlength)
{
        if(inputlength % 2 != 0) {
                printf("too short");
                exit(-1);
        }
        
        struct base64 *dobject = malloc(sizeof(struct base64)); 
        dobject->inputlength = strlen(input);
        dobject->input = input;
        dobject->bytebuffer = (unsigned char*) calloc(dobject->inputlength/2, 1);
        dobject->b64_string = (char*) calloc(b64length(dobject->input), 1);


        dobject->bytebuffer = realloc(dobject->bytebuffer, dobject->inputlength/2);
        stringToBytes(dobject->bytebuffer, dobject->input);
        bytesToB64(dobject->b64_string, dobject->bytebuffer, b64length(dobject->input), dobject->inputlength/2);

        memcpy(output, dobject->b64_string, b64length(dobject->input));
        string_decode(dobject->b64_string, strlen(dobject->b64_string));

        free(dobject->bytebuffer);
        free(dobject->b64_string);
        free(dobject);
}

