/* filehandler.h */
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

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

int readFile(char ***stringlist, char *path)
{
        FILE *filename;
        char *line = malloc(1);
        size_t len = 1;
        ssize_t linelength;

        puts(path);
        filename = fopen(path, "r");
        if(!filename)
                exit(-1);
        long i = 0;

        while((linelength = getline(&line, &len, filename)) != -1) {
                *stringlist = realloc(*stringlist, (i+1) * sizeof(char **));
                (*stringlist)[i] = (char *) calloc(linelength+1, sizeof(char *));
                memcpy((*stringlist)[i], line, linelength);
                (*stringlist)[i][linelength] = '\0';
                i++;
        }
        /*
        int q = 0;
        for(q=0; q < i; q++) {
                free(stringlist[q]);
        }*/
        free(line);

        fclose(filename);

        return i;
}

#endif /* !FILEHANDLER_H */
