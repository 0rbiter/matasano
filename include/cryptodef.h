/* cryptodef.h */
#ifndef CRYPTODEF_H
#define CRYPTODEF_H
void string_to_upper(char *buffer);
long b64length(char *pre_decode_STRING);
long ownlen(char *input);
void build_hextable();
void shift_array_left(unsigned char *input, int size, int shift);
void shift_char_array_left(char *input, int size, int shift);
unsigned char char_to_4bits(char input, unsigned int leftorright);
void bits_to_hexchar(char *output, char *input);
long active_b64_decode_string(char **output, char *input, long inputlength);
long hexstr_to_string(char **buffer, char *input);
void hexstr_to_bytes(unsigned char *buffer, char *input);
void bytes_to_b64(char *b64_string, unsigned char *buffer, long b64len, long bufferlen);
long b64_decode_string(char *output, char *input, long inputlength);
void hexstring_encode_bytes(unsigned char *output, char *input, long inputlength);
void hexstring_encode_b64(char *output, char *input, long inputlength);
void equal_xor_hexstrings(unsigned char* output, char *input1, char *input2, long length);
int xor_bytes_to_string(char **output, char *input1, long longer, char *input2, long shorter);
void xor_strings(char *output, char *input1, char *input2);
void xor_hexstrings(char *output, char *input1, char *input2);
#endif /* !CRYPTODEF_H */
