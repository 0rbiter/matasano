#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "../include/headerfiles.h"
#endif

#ifndef PROJECT_LIBS
#define PROJECT_LIBS
#include "../include/cryptodata.h"
#endif
/* cryptodef.c */
#ifndef CRYPTODEF_C
#define CRYPTODEF_C

void stringToUpper(char *buffer)
{
        while(*buffer)
        {
                *buffer = toupper(*buffer);
                buffer++;
        }
}

long b64length(char *pre_decode_STRING)
{
        int addition = 0;
        if(strlen(pre_decode_STRING) % 6 > 0)
                addition = 4;
        return (long) strlen(pre_decode_STRING) / 6  * 4 + addition + 1;
}

long ownlen(char *input)
{
        long charc = 0;
        while(input[charc] != '\0' || input[charc] != '\n') {
                charc++;
        }
        return charc;
}

void buildHexTable()
{
        int i;
        for(i=0; i<16; i++) {
                if(i<10)
                        HEXTABLE[0][i] = zeroChar + i;
                else
                        HEXTABLE[0][i] = 55 + i;
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

void shift_char_array_left(char *input, int size, int shift)
{
        int i, s;
        char carry = zero;
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

void bitsToHexchar(char *output, char *input)
{
        if(HEXTABLE[0][0] != '0') buildHexTable();
        long c;
        long o = 0;
        for(c=0; c < strlen(input); c++) {
                output[o] = HEXTABLE[0][input[c] >> 4];
                o++;
                output[o] = HEXTABLE[0][input[c] & 0x0F];
                o++;
        }
        output[strlen(input)*2] = '\0';
}

long active_b64_decode_string(char **output, char *input, long inputlength)
{
        char *temp;
        temp = (char *) realloc(*output, (inputlength/4*3+1) * sizeof(char));
        if(temp != NULL) 
                *output = temp;
        else
                exit(-1);
        if(inputlength % 4 > 0) {
                printf("Error, inputlength is not suitable for base64 decoding: %li", inputlength);
                exit(-1);
        }
        long b, a;
        for(b=0; b<inputlength; b++) {
                a=0;
                while(input[b] != BASE64[a] && a < 64 && input[b] != '=')
                        a++;
                shift_char_array_left((*output), inputlength/4*3, 6);
                (*output)[inputlength/4*3-1] |= a;
        }
        (*output)[inputlength/4*3] = '\0';
        return inputlength/4*3;
}
long hexstringToString(char **buffer, char *input)
{
        if(strlen(input) % 2 > 0) {
                printf("Error - string length is odd. 2 hex needed to fill a byte!");
                exit(-1);
        }
        char *tmp;
        tmp = (char *) realloc(*buffer, (strlen(input)/2+1) * sizeof(char));
        if(tmp != NULL)
                *buffer = tmp;
        else
                exit(-1);
        long a;
        long i = 0;
        for(a = 0; a < strlen(input); a+=2) {
                (*buffer)[i] = 0x00;
                (*buffer)[i] |= charTo4Bits(input[a], a);
                (*buffer)[i] |= charTo4Bits(input[a+1], a+1);
                i++;
        }
        (*buffer)[strlen(input)/2] = '\0';
        return strlen(input)/2;
}
void hexstringToBytes(unsigned char *buffer, char *input)
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


long b64_decode_string(char *output, char *input, long inputlength)
{
        struct base64 *xobject = malloc(sizeof(struct base64));
        xobject->inputlength = inputlength;
        xobject->b64_string = (char*) calloc(xobject->inputlength+1, 1);
        xobject->ascii_string = (unsigned char*) calloc(xobject->inputlength/4*3, 1);
        memcpy(xobject->b64_string, input, inputlength);
        if(inputlength % 4 > 0) {
                printf("Error, inputlength is not suitable for base64 decoding: %li", inputlength);
                exit(-1);
        }
        long b, a;
        for(b=0; b<inputlength; b++) {
                a=0;
                while(xobject->b64_string[b] != BASE64[a] && a < 64 && xobject->b64_string[b] != '=')
                        a++;
                shiftArrayLeft(xobject->ascii_string, inputlength/4*3, 6);
                xobject->ascii_string[inputlength/4*3-1] |= a;
        }
        memcpy(output, xobject->ascii_string, inputlength/4*3);
        output[inputlength/4*3] = '\0';
        free(xobject->b64_string);
        xobject->b64_string = NULL;
        free(xobject->ascii_string);
        xobject->ascii_string = NULL;
        free(xobject);
        xobject = NULL;
        return inputlength/4*3;
}



void hexstring_encode_bytes(unsigned char *output, char *input, long inputlength)
{
        if(inputlength % 2 != 0) {
                printf("too short");
                exit(-1);
        }
        
        struct base64 *dobject = malloc(sizeof(struct base64)); 
        dobject->inputlength = strlen(input);
        dobject->input = input;
        dobject->bytebuffer = (unsigned char*) calloc(dobject->inputlength/2, 1);
        //dobject->b64_string = (char*) calloc(b64length(dobject->input), 1);
        dobject->bytebuffer = realloc(dobject->bytebuffer, dobject->inputlength/2);
        hexstringToBytes(dobject->bytebuffer, dobject->input);
        memcpy(output, dobject->bytebuffer, inputlength/2);
        free(dobject->bytebuffer);
        dobject->bytebuffer = NULL;
        free(dobject);
        dobject = NULL;
}

// ENCODE HEX STRING TO BYTECODE
void hexstring_encode_b64(char *output, char *input, long inputlength)
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
        hexstringToBytes(dobject->bytebuffer, dobject->input);
        bytesToB64(dobject->b64_string, dobject->bytebuffer, b64length(dobject->input), dobject->inputlength/2);

        memcpy(output, dobject->b64_string, b64length(dobject->input));

        free(dobject->bytebuffer);
        dobject->bytebuffer = NULL;
        free(dobject->b64_string);
        dobject->b64_string = NULL;
        free(dobject);
        dobject = NULL;
}

void equal_xor_hexstrings(unsigned char* output, char *input1, char *input2, long length)
{
        long c;
        unsigned char *bytes_input1 = calloc(length/2, 1);
        unsigned char *bytes_input2 = calloc(length/2, 1);

        hexstring_encode_bytes(bytes_input1, input1, length);
        hexstring_encode_bytes(bytes_input2, input2, length);

        for(c=0; c < length/2; c++)
                output[c] = bytes_input1[c] ^ bytes_input2[c];
        free(bytes_input1);
        bytes_input1 = NULL;
        free(bytes_input2);
        bytes_input2 = NULL;
}

int xor_bytes_to_string(char **output, char *input1, long longer, char *input2, long shorter)
{
        long c;
        if(longer < shorter)
                return 0;
        *output = (char *) realloc(*output, (longer+1) * sizeof(char));
        if(output == NULL)
                exit(-1);
        /*char *tmp;
        tmp = (char *) realloc(*output, (longer+1) * sizeof(char));
        if(tmp != NULL)
                *output = tmp;
        else
                exit(-1);*/
        long shortcounter=0;
        for(c=0; c < longer; c++) {
                (*output)[c] = input1[c] ^ input2[shortcounter];
                shortcounter++;
                if(shortcounter == shorter)
                        shortcounter = 0;
        }
        (*output)[longer] = '\0';
        return 1;
}
void xor_strings(char *output, char *input1, char *input2)
{
        long c, longer, shorter;
        longer = ownlen(input1);
        shorter = ownlen(input2);

        if(longer < shorter)
                exit(-1);
        char *temp = calloc(longer+1, 1);

        long shortcounter=0;
        for(c=0; c < longer; c++) {
                temp[c] = input1[c] ^ input2[shortcounter];
                shortcounter++;
                if(shortcounter >= shorter)
                        shortcounter = 0;
        }
        temp[longer] = '\0';
        memcpy(output, temp, longer+1);
        free(temp);
        temp = NULL;

}

void xor_hexstrings(char *output, char *input1, char *input2)
{
        long longlength;
        long wordlength;
        struct base64 *output_buffer = malloc(sizeof(struct base64));

        if(strlen(input1) == strlen(input2)) {
                long length = strlen(input1);
                output_buffer->bytebuffer = (unsigned char*) calloc(length/2, 1);
                output_buffer->b64_string = (char*) calloc(b64length(input1), 1);
                equal_xor_hexstrings(output_buffer->bytebuffer, input1, input2, length);
                bytesToB64(output_buffer->b64_string, output_buffer->bytebuffer, b64length(input1), length/2);

                memcpy(output, output_buffer->b64_string, b64length(input1));

                free(output_buffer->bytebuffer);
                output_buffer->bytebuffer = NULL;
                free(output_buffer->b64_string);
                output_buffer->b64_string = NULL;
                free(output_buffer);
                output_buffer = NULL;
                return;
        }
        else
                exit(0);

}

#endif /* !CRYPTODEF_C */
