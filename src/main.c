#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif

#include "filehandler.h"
#include "cryptodata.h"
#include "cryptodef.h"
#include "scoring.h"
#include "set1.c"

void s1c1();
void s1c2();
void s1c5();

long readBytes(unsigned char **bufindex, char *filename)
{
        long bufsize = 1024;
        long prebuf = 8;
        if(bufindex != NULL) {
                bufindex = NULL;
        }
        bufindex = malloc(1);
        *bufindex[0] = calloc(bufsize, sizeof(unsigned char));
        unsigned char *tmp_adr;
        unsigned char **tmp_ptr;;
        long el_number = 1;

        FILE *fp = fopen(filename, "r");
        if(!fp)
                exit(-1);

        unsigned int buf;
        do {
                if(bufsize+1 % prebuf == prebuf) {
       
                        printf("Jetzt!");
                        tmp_ptr = realloc(bufindex, el_number);
                        if(tmp_ptr == NULL)
                                continue;
                        else {
                                bufindex = tmp_ptr;
                                el_number++;
                        }

                        tmp_adr = realloc(bufindex, bufsize+prebuf);
                        if(tmp_adr == NULL)
                                continue;
                        else
                                *bufindex = tmp_adr;
                        
                }
                if(ferror(fp) != 0)
                        clearerr(fp);
                bufsize++;
                *bufindex[bufsize-prebuf] = buf;
        } while((buf = fgetc(fp)) != EOF);

        if(!fclose(fp))
                exit(-1);
        free(tmp_ptr);
        free(tmp_adr);
        free(bufindex);
        free(*bufindex);
        return bufsize; 

}

int main(int argc, char **argv)
{
        separate();
        /*
         * Challenge 3, XOR 2 HEX values with different length from input strings,
         * and print HEX string
         */
        //char HEXSTRING3[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736\0";
        char HEXSTRING3[] = "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f\0";
        char *STRING3 = calloc(strlen(HEXSTRING3)/2+1, 1);
        char SINGLECHAR[] = "A\0";
        int i, c;
        printf("Challenge 3\nfind the single byte to decrypt:\n");
        puts(HEXSTRING3);
        printf("\n");
        
        hexstringToString(STRING3, HEXSTRING3);
        puts(STRING3);
        long str_length = ownlen(STRING3);
        char *NEWSTRING = calloc(str_length+1, 1);

        print_en_scores();

        for(i=53; i < 54; i++) {
                SINGLECHAR[0] = i;
                xor_strings(NEWSTRING, STRING3, SINGLECHAR);
                get_score(NEWSTRING, strlen(NEWSTRING), SINGLECHAR, -330, 3.0f, 0, 0);
              
        }

        free(NEWSTRING);
        free(STRING3);
        separate();
        
        /*
         * read all keys from ../src/challenge4keys.txt and put them in strings
         * use xor encryption and try different chars, run them through scoring
         * profit!
         * */
        printf("Challenge 4\nread 60 keys from file and find the encryption character\nand the according line");
        printf("\n");
        char ENCCHAR[] = "A\0";
        char filename[] = "/home/orbiter/matasano/src/challenge4keys.txt";
        unsigned char **stringlist = NULL; 
        char *STR_STRING = NULL;
        char *STR_XOR = NULL;
        char TEST1[100] = "";
        long linecount = 0;
        long SIZEOFSTRING = 0;
        long charcounter = 0;

        readBytes(stringlist, filename);

/*
        if((linecount = readFile(&stringlist, filename)) != -1) {
                int k; 
                print_en_scores();
                for(k=0; k < linecount; k++) { 
                        SIZEOFSTRING = ownlen(stringlist[k]);
                }
        }
        long q;
        for(q=0; q < linecount+1; q++) {
                free(stringlist[q]);
        }
        free(stringlist);
        free(STR_STRING);
        free(STR_XOR); 
        */
}

