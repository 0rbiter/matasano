char HEXTABLE[2][16];
static const char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const unsigned char zero = 0x00;
static const unsigned char A = 55;
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
