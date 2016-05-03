#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *xcalloc(size_t items, size_t size)
{
        void *tmp = calloc(items, size);
        if(tmp != NULL)
                return tmp;
        else {
                fprintf(stderr, "Error: could not allocate memory");
                printf("Error: could not allocate memory");
                exit(-1);
        }
}

void *xmalloc(size_t size)
{
        void *tmp = calloc(size, 1);
        if(tmp != NULL)
                return tmp;
        else {
                fprintf(stderr, "Error: could not allocate memory");
                printf("Error: could not allocate memory");
                exit(-1);
        }
}

void *xrealloc(void *rbuf, size_t size)
{
        void *tmp = realloc(rbuf, size);
        if(tmp != NULL) {
                return tmp;
        }
        else {
                fprintf(stderr, "Error: could not allocate memory");
                printf("Error: could not allocate memory");
                exit(-1);
        }
}

void xfree(void *fbuf)
{
        free(fbuf);
        fbuf = NULL;
}
