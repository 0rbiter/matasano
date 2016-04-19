//#include "crypto.h"
#include "cryptodata.h"
#include "cryptodef.h"

int main()
{
        int charcount = strlen(HEXSTRING);
    	int bitcount = charcount * 4;
        printf("Hexadecimal to convert to Base64:\n");
	puts( HEXSTRING );
    	printf("\nLength (bits/chars/bytes): %i/%i/%i", bitcount, charcount, bitcount/8);
    	printf("\nSolution:\n");
        char *b64HS = (char*) calloc(b64length(HEXSTRING), 1);
        hexstring_encode(b64HS, HEXSTRING, strlen(HEXSTRING));
        //puts(b64HS);
        free(b64HS);

        char *vier = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
        if(strlen(vier) % 4 > 0) exit(0);
        unsigned char *dreibytes = calloc(strlen(vier)/4*3,1);
        
        int b, a;
        for(b=0; b<strlen(vier); b++) {
                a=0;
                while(vier[b] != BASE64[a] && a < 64 && vier[b] != '=')
                        a++;
                shiftArrayLeft(dreibytes, strlen(vier)/4*3, 6);
                dreibytes[strlen(vier)/4*3-1] |= a;
        }
        char *dreizeichen = calloc(strlen(vier)/4*3+1, 1);
        memcpy(dreizeichen, dreibytes, strlen(vier)/4*3);
        dreizeichen[strlen(vier)/4*3] = '\0';
        puts(vier);
        puts(dreizeichen);


        return 0;
}
