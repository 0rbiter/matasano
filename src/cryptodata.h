#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
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

union _byte {
        char s_char;
        unsigned char u_char;
};

union _2byte {
        short int s_sh_int;
        unsigned short int u_sh_int;
        union _byte bytes[2];
};

union _4byte {
        int s_int;
        unsigned int u_int;
        long int l_int;
        float _float;
        union _byte _bytes[4];
        union _2byte _2bytes[2];
};

union _8byte {
        double _double;
        union _4byte _4bytes[2];
};

union Ptr_byte {
        char *s_char;
        unsigned char *u_char;
};

union Ptr_2byte {
        short int *s_sh_int;
        unsigned short int *u_sh_int;
        union _byte *bytes[2];
};

union Ptr_4byte {
        int *s_int;
        unsigned int *u_int;
        long int *l_int;
        float *_float;
        union _byte *_bytes[4];
        union _2byte *_2bytes[2];
};

union Ptr_8byte {
        double *_double;
        union _4byte *_4bytes[2];
};

#endif /* !CRYPTODATA_H */
