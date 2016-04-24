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
        .text = NULL,
};

void add_score(char *text, long length, char *key, long score) 
{
        scores.length = realloc(scores.length, (scores.elements+1) * sizeof(long));
        scores.score = realloc(scores.score, (scores.elements+1) * sizeof(long));
        scores.text = realloc(scores.text, (scores.elements+1) * sizeof(char *));
        scores.text[scores.elements] = malloc(1);
        scores.text[scores.elements] = realloc(scores.text[scores.elements], (length+1) * sizeof(char));
        scores.key = realloc(scores.key, (scores.elements+1) * sizeof(char *));
        scores.key[scores.elements] = malloc(1);
        scores.key[scores.elements] = realloc(scores.key[scores.elements], 2 * sizeof(char));
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
                free(scores.text[c]);
                free(scores.key[c]);
        }
        free(scores.text);
        free(scores.key);
        free(scores.score);
        free(scores.length);
}

void get_best()
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
        printf("\nKey: %s - Text:\t%s", scores.key[index], scores.text[index]);
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

int get_score(char *input_string, long str_length, char *key, int delimiter, float offset, int prints, int repetition_penalty)
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
        unsigned char_repr = 0;
        for(f=0; f <= str_length; f++) {

                char_repr = input_string[f];
                if((char_repr >= 65) && (char_repr <= 90)) {
                        points += 1;
                        letters_counted++;
                        score[char_repr-65]++;
                }
                else if((char_repr >= 97) &&  (char_repr <= (97+25))) {
                        points += 1;
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
                                case '@':
                                case '/':
                                case '\\':
                                        points += 1;
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
                if(myscores[l] > 90 && repetition_penalty)
                       points -=50;
        }
        points += letters_counted;
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


