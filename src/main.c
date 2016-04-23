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

typedef union {
        unsigned char *ui;
        char *c;
        int *i;
} _line;

typedef union {
        unsigned char **ui;
        char **c;
        int **i;
} _chunk;

struct file_o {
        long *length; // list of lengths per line; last element is value of -1
        _chunk buffer;
        long elements; // not used?
};

int file_o_init(struct file_o *obj)
{
        if(obj->length == NULL || obj->buffer.ui == NULL)
                return 1;
        obj->elements = 0;
        while(obj->length[obj->elements++] >= 0);
        obj->elements--;
        return 0;
}
int file_o_destroy(struct file_o *obj)
{
        long i = 0;
        while(obj->length[i] != -1) {
                free(obj->buffer.i[i++]);
        }
        free(obj->buffer.i);
        free(obj->length);
        free(obj);
        return 0;
}

struct file_o *readBytes(char *filename)
{
        FILE *fp = fopen(filename, "r");
        if(!fp)
                exit(-1);
        unsigned int buf_element;
        long counter;

        long vertical = 0;
        long horizontal = 0;
        unsigned char **new_buffer = NULL;
        unsigned char *new_line = NULL;

        unsigned char **buffer = NULL; 
        buffer = (unsigned char **) malloc(1 * sizeof(unsigned char *));
        buffer[vertical] = (unsigned char *) malloc(1 * sizeof(unsigned char));
        buffer[vertical][horizontal] = 0;
        if(buffer[0] == NULL)
                exit(-1);
        if(buffer == NULL)
                exit(-1);
        long *new_lll = NULL;
        long *linelengthlist = NULL;
        new_lll = (long *) malloc(1*sizeof(long));
        if(new_lll == NULL)
                exit(-1);
        else
                linelengthlist = new_lll;
        linelengthlist[0] = 0;
        while((buf_element = fgetc(fp)) != EOF) {
                buffer[vertical][horizontal] = buf_element;
                // condition for vertical realloc (new list element)
                if(buffer[vertical][horizontal] == '\0' || buffer[vertical][horizontal] == '\n') {
                        buffer[vertical][horizontal] = '\0';
                        // allocate vertical (# of elements in address list)
                        new_buffer = (unsigned char **) realloc(buffer, (vertical+2)*sizeof(unsigned char*));
                        if(new_buffer == NULL)
                                exit(-1);
                        else {
                                buffer = new_buffer;
                                new_lll = (long *) realloc(linelengthlist, (vertical+2)*sizeof(long));
                                if(new_lll == NULL)
                                        exit(-1);
                                else {
                                        linelengthlist = new_lll;
                                        horizontal = -1;
                                        vertical++;
                                        buffer[vertical] = NULL;
                                }
                        }
                }
                // create space for a new char
                // will be buffer increments later on!
                new_line = (unsigned char *) realloc(buffer[vertical], (horizontal+2)*sizeof(unsigned char));
                if(new_line == NULL)
                        exit(-1);
                else {
                        buffer[vertical] = new_line;
                        linelengthlist[vertical] = horizontal;
                        horizontal++;
                }
                if(ferror(fp) != 0)
                        clearerr(fp);
        }
        long y;
        long x;
        free(buffer[vertical]);
        struct file_o *result = (struct file_o *) malloc(sizeof(struct file_o));
        result->length = linelengthlist;
        result->buffer.ui = buffer;
        for(y = 0; y < vertical; y++) {
                result->buffer.ui[y] = buffer[y];
                for(x = 0; x <= linelengthlist[y]; x++) {
                        result->buffer.ui[y][x] = buffer[y][x];
                }
        }
        if(fclose(fp) != 0)
                exit(-1);
        return result;
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
        char *STR_STRING = NULL;
        char *STR_XOR = NULL;
        long lines = 0;
        long chars = 0;
        long SIZEOFSTRING = 0;
        long charcounter = 0;

        struct file_o *buffer1 = readBytes(filename);
        int j = file_o_init(buffer1);
        for(lines = 0; lines < buffer1->elements; lines++) {
                printf("%li  ", buffer1->length[lines]);
                puts(buffer1->buffer.c[lines]);
        }
        printf("\n%i", j);
        file_o_destroy(buffer1);
        free(STR_STRING);
        free(STR_XOR); 
}

