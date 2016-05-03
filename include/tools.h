/* tools.h */
#ifndef TOOLS_H
#define TOOLS_H
void *xmalloc(size_t size);
void *xcalloc(size_t items, size_t size);
void *xrealloc(void *rbuf, size_t size);
void xfree(void *fbuf);
#endif /* !tools.h */
