/* cryptodef.h */
#ifndef CRYPTODEF_H
#define CRYPTODEF_H
void stringToUpper(char *buffer);
long b64length(char *pre_decode_STRING);
long ownlen(char *input);
void buildHexTable();
void shiftArrayLeft(unsigned char *input, int size, int shift);
void shift_char_array_left(char *input, int size, int shift);
unsigned char charTo4Bits(char input, unsigned int leftorright);
void bitsToHexchar(char *output, char *input);
long active_b64_decode_string(char **output, char *input, long inputlength);
long hexstringToString(char **buffer, char *input);
void hexstringToBytes(unsigned char *buffer, char *input);
void bytesToB64(char *b64_string, unsigned char *buffer, long b64len, long bufferlen);
long b64_decode_string(char *output, char *input, long inputlength);
void hexstring_encode_bytes(unsigned char *output, char *input, long inputlength);
void hexstring_encode_b64(char *output, char *input, long inputlength);
void equal_xor_hexstrings(unsigned char* output, char *input1, char *input2, long length);
int xor_bytes_to_string(char **output, char *input1, long longer, char *input2, long shorter);
void xor_strings(char *output, char *input1, char *input2);
void xor_hexstrings(char *output, char *input1, char *input2);
#endif /* !CRYPTODEF_H */
