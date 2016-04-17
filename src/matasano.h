
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// static prevents from conflicts with other files
/* static const char *BASE64CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


char *b64_encode(char *TEMPSTRING)
{
	int a,b,c;
	char _CHARS[5];

	int buffersize = strlen(TEMPSTRING)/4;

    buffersize = buffersize + (buffersize % 6);
	unsigned long lBuffer[buffersize];
	char *OUT_STR;
	b = 0;
	for (a=0; a<buffersize*4; a+=4)
	{
        if (a < strlen(TEMPSTRING))
        {
            memcpy(_CHARS, &TEMPSTRING[a*sizeof(char)], 4);
            _CHARS[4] = '\0';
        }
        else
        {
            memcpy(_CHARS, "0000", 4);
        }
        lBuffer[b] = (unsigned long) strtol(_CHARS, NULL, 16);
		printf("%s converted to: %lu\n", _CHARS, lBuffer[b]);
		b++;
	}


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
    char *RTR_STR = malloc(sizeof(char) * b64buffersize);
    for (c=0; c<b64buffersize; c++)
    {
        RTR_STR[c] = BASE64CODES[iBase64[c]];
    }
    return RTR_STR;

}

char *b64_FILLER(char *TEMPSTRING)
{
    int FillByteCount = 6 - (strlen(TEMPSTRING) % 6);
    char *OUT_STR = malloc((strlen(TEMPSTRING) + FillByteCount));	
	if ((strlen(TEMPSTRING) % 6) > 0) {
		printf("ERROR - filling up with 0 bytes");
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
    }
	else
	{
		printf("OK - continuing with Base64 encoding");
		OUT_STR = TEMPSTRING;
	}
	return OUT_STR;
} */
