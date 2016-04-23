#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif

#include "filehandler.c"
#include "cryptodata.h"
#include "cryptodef.c"
#include "scoring.c"
#include "set1.c"

void s1c1();
void s1c2();
void s1c5();



long readBytes(unsigned char **buffer, char *filename)
{
        long vertical = 0;
        long horizontal = 0;
        
        long y;
        long x;

        buffer = (unsigned char **) malloc(1 * sizeof(unsigned char *));
        buffer[vertical] = (unsigned char *) malloc(1 * sizeof(unsigned char));
        buffer[vertical][horizontal] = 0;
        if(buffer == NULL)
                exit(-1);

        unsigned char **new_buffer = NULL;
        unsigned char *new_line = NULL;
       /* 
        unsigned char **old_lines = NULL;
        old_lines = (unsigned char **) malloc(1 * sizeof(unsigned char *));
        old_lines = (unsigned char *) malloc(1 * sizeof(unsigned char));
                        // backup buffer addresses
                        old_lines = (unsigned char **) malloc(vertical * sizeof(unsigned char *));
                        old_lines = (unsigned char *) malloc(1 * sizeof(unsigned char));
                        for(y = 0; y < vertical; y++)
                                for(x = 0; x < horizontal; x++)
                                        old_lines[x] = buffer[vertical][horizontal];
*/

        FILE *fp = fopen(filename, "r");
        if(!fp)
                exit(-1);

        unsigned int buf_element;
        long counter;

        while((buf_element = fgetc(fp)) != EOF){
                printf("Starting %li * %li\n", vertical, horizontal); 
                // condition for horizontal realloc (new char element)
                new_line = (unsigned char *) realloc(buffer, horizontal*sizeof(unsigned char));
                if(buffer == NULL)
                        exit(-1);
                else
                        horizontal++;
                        buffer[vertical] = new_line;
                        
                if(ferror(fp) != 0)
                        clearerr(fp);
                
                // condition for vertical realloc (new list element)
                if((buffer[vertical][horizontal] == '\0' || buffer[vertical][horizontal] == '\n')
                        && vertical != 0 && horizontal != 0) {
                        // allocate vertical (# of elements in address list)
                        
                        new_buffer = (unsigned char **) realloc(buffer, vertical*sizeof(unsigned char *));
                        if(buffer == NULL)
                                exit(-1);
                        else
                                vertical++; 
                                buffer = new_buffer;
                }
                
                buffer[vertical][horizontal] = buf_element;


        }

        if(!fclose(fp))
                exit(-1);

        for(y = 0; y < vertical; y++)
                free(new_buffer[vertical]);
        free(buffer);

        return vertical*horizontal;

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

