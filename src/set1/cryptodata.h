#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#endif

/* cryptodata.h */
#ifndef CRYPTODATA_H
#define CRYPTODATA_H

char HEXTABLE[2][16];
static const char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const unsigned char zero = 0x00;
static const char A = 65;
static const unsigned char a = 97;
static const unsigned char zeroChar = 48;

char equalsign = '=';

const int MAX_ALLOC_ERRORS = 10;

struct base64 {
        char *input;
        long inputlength;
        unsigned char *bytebuffer;
        long bytelength;
        char *b64_string;
        unsigned char *ascii_string;
} base64;

#endif /* !CRYPTODATA_H */
