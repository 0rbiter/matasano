/* SCORING.H */
#ifndef SCORING_H
#define SCORING_H
static const float letterscore_en[26] = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.361, 0.150, 1.974, 0.074 };
static struct {
        long elements;
        long *length;
        long *score;
        char **key;
        union {
                char **text;
                unsigned char **bytes;
        };
} scores = {
        .elements = 0,
        .length = NULL,
        .score = NULL,
        .key = NULL,
        .text = NULL,
};
void add_score(char *text, long length, char *key, long score) ;
void destroy_scores();
char get_best();
void print_en_scores();
long get_score(char *input_string, long str_length, char *key, int delimiter, float offset, int prints);
#endif /* !SCORING.H */
