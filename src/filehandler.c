#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "headerfiles.h"
#endif

/* filehandler.h */
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

static long horizontal_bufsize = 64;
static long vertical_bufsize = 512;

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

void set_buffersize(long vertical, long horizontal)
{
        if(vertical != 0)
                vertical_bufsize = vertical;
        if(horizontal != 0)
                horizontal_bufsize = horizontal;
}

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
                        if(vertical % vertical_bufsize <= 1) {
                                // allocate vertical (# of elements in address list)
                                new_buffer = (unsigned char **) realloc(buffer, (vertical+vertical_bufsize+2)*sizeof(unsigned char*));
                                if(new_buffer == NULL)
                                        exit(-1);
                                else {
                                        buffer = new_buffer;
                                        new_lll = (long *) realloc(linelengthlist, (vertical+vertical_bufsize+2)*sizeof(long));
                                        if(new_lll == NULL)
                                                exit(-1);
                                        else {
                                                linelengthlist = new_lll;
                                        }
                                }
                        }
                        horizontal = -1;
                        vertical++;
                        buffer[vertical] = NULL;
                }
                // create space for a new char
                // will be buffer increments later on!
                if(horizontal % horizontal_bufsize <= 1) {
                        new_line = (unsigned char *) realloc(buffer[vertical], (horizontal+horizontal_bufsize+2)*sizeof(unsigned char));
                        if(new_line == NULL)
                                exit(-1);
                        else {
                                buffer[vertical] = new_line;
                        }
                }
                linelengthlist[vertical] = horizontal;
                horizontal++;
                if(ferror(fp) != 0)
                        clearerr(fp);
        }
        long y;
        long x;
        // resize alloc'd buffer to needed space
        // first: cleanup all pre-alloc'd lines
        for(y = 0; y < (vertical+1); y++) {
                new_line = (unsigned char *) realloc(buffer[y], (linelengthlist[y]+2)*sizeof(unsigned char));
                if(new_line == NULL)
                        exit(-1);
                else {
                        buffer[y] = new_line;
                }
        }
        // second: resize list of lines
        new_buffer = (unsigned char **) realloc(buffer, (vertical+1)*sizeof(unsigned char*));
        if(new_buffer == NULL)
                exit(-1);
        else {
                buffer = new_buffer;
                new_lll = (long *) realloc(linelengthlist, (vertical+1)*sizeof(long));
                if(new_lll == NULL)
                        exit(-1);
                else {
                        linelengthlist = new_lll;
                }
        }

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

long getStringLength(struct file_o **fobject)
{
        int i;
        long sum_lengths = 0;
        for(i = 0; i < (*fobject)->elements; i++) 
                        sum_lengths += (*fobject)->length[i]+1;
        return sum_lengths;
}

char *getString(struct file_o **fobject)
{
        int i, j;
        long sum_lengths = 0;
        char *output = malloc((getStringLength(&(*fobject)) + 1) * sizeof(char));
        for(i = 0; i < (*fobject)->elements; i++) {
                for(j = 0; j < (*fobject)->length[i]+1; j++) {
                        output[sum_lengths+j] = (*fobject)->buffer.c[i][j];
                }
                sum_lengths += (*fobject)->length[i]+1;
        }
        output[sum_lengths] = '\0';
        return output;
}

long getFilesize(char *path)
{
        FILE *filename;
        filename = fopen(path, "r");
        if(!filename)
                exit(-1);
        fseek(filename, 0L, SEEK_END);
        long sz = ftell(filename);
        fseek(filename, 0L, SEEK_SET);
        fclose(filename);
        return sz;
}

#endif /* !FILEHANDLER_H */
