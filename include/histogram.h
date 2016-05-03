/* histogram.h */
#ifndef HISTOGRAM_H
#define HISTOGRAM_H
struct histogram {
        char *data;
        long inputlength;
        struct transposed {
                long elements;
                long *lengths;
                char **blocks;
        } *tdata;
        struct humming {
                int keys_total;
                int *keylength;
                float *n_editdistance;
        } *hum;
        char *testkey;
};
void transpose(struct transposed **tobject, char **inputstring, long length, int divisor);
int resolve_keylength(struct humming **hobject, float editdistance);
long humming_distance(char *word1, char *word2, long length);
int get_keylength(struct histogram **hobject, int maxlength, char *data, long length, int keys_total);
struct histogram *hist_o_init(int keys_total);
int hist_o_destroy(struct histogram *hobject);
#endif /* !HISTOGRAM_H */
