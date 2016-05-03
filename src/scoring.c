#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include "../include/headerfiles.h"
#endif

#ifndef CRYPTO_H
#define CRYPTO_H
#include "../include/cryptodata.h"
#endif
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

void add_score(char *text, long length, char *key, long score) 
{
        scores.length =                 xrealloc(scores.length, (scores.elements+1) * sizeof(long));
        scores.score =                  xrealloc(scores.score, (scores.elements+1) * sizeof(long));
        scores.text =                   xrealloc(scores.text, (scores.elements+1) * sizeof(char *));
        scores.text[scores.elements] =  xmalloc(1);
        scores.text[scores.elements] =  xrealloc(scores.text[scores.elements], (length+1) * sizeof(char));
        scores.key =                    xrealloc(scores.key, (scores.elements+1) * sizeof(char *));
        scores.key[scores.elements] =   xmalloc(1);
        scores.key[scores.elements] =   xrealloc(scores.key[scores.elements], 2 * sizeof(char));
        scores.length[scores.elements] = length;
        scores.score[scores.elements] = score;
        memcpy(scores.text[scores.elements], text, length+1);
        memcpy(scores.key[scores.elements], key, 2);
        scores.elements++;
}

void destroy_scores()
{
        long c;
        for(c = 0; c < scores.elements; c++) {
                xfree(scores.text[c]);
                scores.text[c] = NULL;
                xfree(scores.key[c]);
                scores.key[c] = NULL;
        }
        xfree(scores.text);
        scores.text = NULL;
        xfree(scores.key);
        scores.key = NULL;
        xfree(scores.score);
        scores.score = NULL;
        xfree(scores.length);
        scores.length = NULL;
        scores.length = NULL,
        scores.score = NULL,
        scores.key = NULL,
        scores.text = NULL,
        scores.elements = 0;
}

char get_best()
{
        if(!scores.elements) {
                printf("Error - no elements in score table\n");
        }
        long c;
        long highest = 0;
        long index = 0;
        for(c = 0; c < scores.elements; c++) {
                if(scores.score[c] > highest) {
                        index = c;
                        highest = scores.score[c];
                }
        }
        printf("\nKey: %s - Text:\t%s\n", scores.key[index], scores.text[index]);
        return *scores.key[index];
}

void print_en_scores()
{
        char l;
        printf("English Language scores:\n");
        for(l=0; l < 26; l++) {
                if(l % 6 == 0 && l != 0)
                        printf("\n");
                printf("%c %.2f\t", A+l, letterscore_en[l]);
        }
        printf("\n\n");
}

long get_score(char *input_string, long str_length, char *key, int delimiter, float offset, int prints)
{
        float score[26] = { 0 };
        long letters_counted = 0;
        long f;
        int l = 0;
        long points;
        points = 0;
        float myscores[26] = { 0 };
        char char_repr = 0;
        for(f=0; f <= str_length; f++) {
                char_repr = input_string[f];
                if((char_repr >= 65) && (char_repr <= 90)) {
                        points += 3;
                        letters_counted++;
                        score[char_repr-65]++;
                }
                else if((char_repr >= 97) &&  (char_repr <= (97+25))) {
                        points += 3;
                        letters_counted++;
                        score[char_repr-97]++;
                }
                else {
                        switch(char_repr) {
                                case ' ':
                                        points += 3;
                                case '*':
                                case '\n':
                                case '%':
                                case '$':
                                case '!':
                                case '&':
                                case '(':
                                case ')':
                                case '?':
                                case '"':
                                case '/':
                                case '\\':
                                        points -= 0;
                                case '<':
                                case '>':
                                case '@':
                                case '=':
                                case 0x01:
                                case 0x02:
                                case 0x03:
                                case 0x04:
                                case 0x05:
                                case 0x06:
                                case 0x07:
                                case 0x08:
                                case 0x09:
                                case 0x0b:
                                case 0x0c:
                                case 0x0d:
                                case 0x0e:
                                case 0x0f:
                                case '~':
                                        points -= 2;
                                default:
                                        points -= 10;
                        }
                }
        }
        for(l=0; l < 26; l++) {
                myscores[l] = score[l]/letters_counted;
                myscores[l] = 100 * myscores[l];
                if(letterscore_en[l]-offset <= myscores[l] ^ letterscore_en[l]+offset <= myscores[l]) {
                        points += 10;
                }
        }
        if(letters_counted / str_length > 50)
                points += 20;
        if(points > delimiter) {
                if(prints) {
                        puts(input_string);
                        if(prints == 2) {
                                for(l=0; l < 26; l++) {
                                        if(l % 6 == 0 && l != 0)
                                                printf("\n");
                                        printf("%c %.2f\t", 65+l, myscores[l]);
                                }
                        }
                        printf("\n\t\t\tPoints gained: %li \tLetters counted: %li\tKey: ", points, letters_counted);
                        fputs(key, stdout);
                        printf("\t%i\n", key[0]);
                }
        }
        add_score(input_string, str_length, key, points);
        return points;
}


