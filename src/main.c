#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// static prevents from conflicts with other files
char *HEXSTRING = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
static const char *BASE64CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";


char *b64_encode(char *TEMPSTRING)
{
	int a,b,c;
	char _CHARS[5];
	int buffersize = strlen(TEMPSTRING)/4;
	unsigned long lBuffer[buffersize];
	char *OUT_STR;
	b = 0;
	for (a=0; a<(strlen(TEMPSTRING)); a+=4)
	{
		memcpy(_CHARS, &TEMPSTRING[a*sizeof(char)], 4);
		_CHARS[4] = '\0';
		//puts( _CHARS );
		lBuffer[b] = (unsigned long) strtol(_CHARS, NULL, 16);
		//printf("%lu\n", lBuffer[b]);
		b++;
	}

	/* the HEX string has for example 96 signs, they are converted by the for loop above
	into 24 unsigned long values á 2 bytes each and take up 48bytes in this example.
	Therefore the buffersize aka items in the Base64 list á 1 byte each must be 48 / 3 * 4
	or 96 / 6 * 4 */

	unsigned int b64buffersize = strlen(TEMPSTRING) / 6 * 4;
	unsigned char iBase64[b64buffersize];

	// fancy bitshifting and bit-wise operations over here to extract the 6 bits per Base64 sign
	unsigned int d = 0;
	for (c=0; c<(strlen(TEMPSTRING) / 4); c+=3)
	{
		iBase64[d] = lBuffer[c] >> 10;
		iBase64[d+1] = lBuffer[c] >> 4 & 0x003f;
		iBase64[d+2] = ((lBuffer[c] & 0x000f) << 2) ^ (lBuffer[c+1] >> 14);
		iBase64[d+3] = (lBuffer[c+1] >> 8) & 0x003f;
		
		iBase64[d+4] = (lBuffer[c+1] >> 2) & 0x003f;
		iBase64[d+5] = ((lBuffer[c+1] & 0x0003) << 4) ^ (lBuffer[c+2] >> 12);
		iBase64[d+6] = (lBuffer[c+2] >> 6) & 0x003f;
		iBase64[d+7] = lBuffer[c+2] & 0x003f;
	
		d = d + 8;
	}
	for (c=0; c<b64buffersize; c++)
	{
		printf("%c", BASE64CODES[iBase64[c]]);
	}
	//strncpy(OUT_STR, _CHARS, strlen(_CHARS));
	//return OUT_STR;
	return "";
}

char *b64_FILLER(char *TEMPSTRING)
{
	int FillByteCount = 6 - (strlen(TEMPSTRING) % 6);
	char *OUT_STR = malloc((strlen(TEMPSTRING) + FillByteCount));	
	strncpy(OUT_STR, TEMPSTRING, strlen(TEMPSTRING));
	printf("\n%lu", strlen(OUT_STR));
	int i;
	for (i=0; i<(strlen(OUT_STR)+1); i++)
	{
		//printf("%i", i);
		if (OUT_STR[i] == '\0' && FillByteCount != 0) {
			OUT_STR[i] = '0';
			FillByteCount--;
		}
	}
	return OUT_STR;
}

int main()
{
	int charcount = strlen(HEXSTRING);
	int bitcount = charcount * 4;
	char *BCOMP_STRING;
	printf("Hexadecimal to convert to Base64:\n");
	puts( HEXSTRING );
	printf("\nLength (bits/chars/bytes): %i/%i/%i", bitcount, charcount, bitcount/8);
	printf("\nTesting Modulo 6 %c6 times 1 Hex = 3 Bytes%c: ", (unsigned int) 40, (unsigned int) 41);

	char *tempStr;
	if ((strlen(HEXSTRING) % 6) > 0) {
		printf("ERROR - filling up with 0 bytes");
		BCOMP_STRING = b64_FILLER(HEXSTRING);
	}
	else
	{
		printf("OK - continuing with Base64 encoding");
		BCOMP_STRING = HEXSTRING;
	}
	printf("\nUsing:\n");
	puts( BCOMP_STRING );
	printf("\nSolution:\n");
	puts( b64_encode(BCOMP_STRING) );
	
	return 0;
}
