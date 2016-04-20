char HEXTABLE[2][16];
static const char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char *HEXSTRING = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
char *HEXSTRING2 = "686974207468652062756C6C277320657965";
char *HEXSTRING3 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
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
