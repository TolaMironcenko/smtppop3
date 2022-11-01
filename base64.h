#ifndef _BASE64_H
#define _BASE64_H
int Base64decode_len(const char *bufcoded);
int Base64decode(char *bufplain, const char *bufcoded);
int Base64encode(char *encoded, const char *string, int len);
#endif 
