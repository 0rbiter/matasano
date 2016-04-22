#ifndef STANDARD_LIBS
#define STANDARD_LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#endif

/* scoring.h */
#ifndef SCORING_H
#define SCORING_H
        
static const float letterscore_en[26] = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.361, 0.150, 1.974, 0.074 };

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

int get_score(char *input_string, long str_length, char *key, int delimiter, float offset)
{
        float score[26];
        unsigned long letters_counted = 0;
        long f;
        if(offset == 0)
                offset = 3;
        int l = 0;
        long points = 0;
        float myscores[26];

        for(l=0; l < 26; l++) {
                myscores[l] = 0;
                score[l] = 0;
        }
        letters_counted = 0;
        points = 0;
        for(f=0; f < str_length; f++) {
                if(input_string[f] == ' ') {
                        printf("");
                        points += 3;
                        }
                if(input_string[f] >= 65 && input_string[f] <= 90) {
                        points += 1;
                        letters_counted++;
                        score[input_string[f]-65]++;
                }
                else if(input_string[f] >= 97 &&  input_string[f] <= 97+25) {
                        points += 1;
                        letters_counted++;
                        score[input_string[f]-97]++;
                }

        }



        for(l=0; l < 26; l++) {
                myscores[l] = score[l]/letters_counted;
                myscores[l] = 100 * myscores[l];
                if(letterscore_en[l]-offset <= myscores[l] ^ letterscore_en[l]+offset <= myscores[l]) {
                        points += 10;
                }
        }
        points += letters_counted/5;
        if(points > delimiter) {
                puts(input_string);
                for(l=0; l < 26; l++) {
                        if(l % 6 == 0 && l != 0)
                                printf("\n");
                        printf("%c %.2f\t", 65+l, myscores[l]);
                }
                printf("\nPoints gained: %li \t\tLetters counted: %li\t\tKey: ", points, letters_counted);
                fputs(key, stdout);
                printf("\n");
        }
        return points;
}

#endif /* !SCORING_H */
