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
void set_buffersize(long vertical, long horizontal);
int file_o_init(struct file_o *obj);
int file_o_destroy(struct file_o *obj);
struct file_o *read_bytes(char *filename);
long get_strlen(struct file_o **fobject);
char *get_string(struct file_o **fobject);
long get_filesize(char *path);
#endif /* !FILEHANDLER_H */
