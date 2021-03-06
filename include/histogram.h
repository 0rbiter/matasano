/* histogram.h */
#ifndef HISTOGRAM_H
#define HISTOGRAM_H
static const char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
static const float en_scores[26] = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.361, 0.150, 1.974, 0.074 };

static struct betterscore *english;

struct histogram {
        char *data;
        long inputlength;
        struct transposed {
                long elements;
                long *lengths;
                char **blocks;
        } *tdata;
        struct hamming {
                int keys_total;
                int *keylength;
                float *n_editdistance;
        } *ham;
        struct betterscore {
                long score_elements;
                int number_of_signs;
                char signs[26];
                char *testkey;
                float **freq;
                long *counted_letters;
                float *ncoefficiant;
        } *scores;
};
void get_std_freq (float **sobj);
long calc_letter_frequency(float **freqs, char *data, long datalen);
void calc_normalized_coe(struct betterscore *sbuf, long element);
void build_bs_english();
struct betterscore *score_o_init(long blockcount);
void score_o_destroy(struct betterscore *sobj, long blockcount);
void add_betterscore(struct histogram **hobj, long block, char *decrypted, char key);
void transpose(struct histogram **hist, struct transposed **tobject, char **inputstring, long length, int divisor);
int resolve_keylength(struct hamming **hobject, float editdistance);
long hamming_distance(char *word1, char *word2, long length);
int get_keylength(struct histogram **hobject, int maxlength, char *data, long length, int keys_total);
struct histogram *hist_o_init(int keys_total);
int hist_o_destroy(struct histogram *hobject);
#endif /* !HISTOGRAM_H */
