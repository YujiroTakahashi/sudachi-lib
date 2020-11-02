#ifndef SUDACHI_H
#define SUDACHI_H

#include <stdlib.h>

typedef struct _sudachi_node {
    size_t surface;
    size_t pos;
    size_t normalized_form;
    size_t dictionary_form;
    size_t reading_form;
    char *data;
} sudachi_node_t;

typedef void *TokenizerHandle;
typedef void *MorphemesHandle;

TokenizerHandle new_tokenizer(const char *path);
void free_tokenizer(TokenizerHandle handle);
MorphemesHandle parse_tokenizer(TokenizerHandle handle, const char *input);
int size_morpheme_list(MorphemesHandle handle);
void free_morpheme_list(MorphemesHandle handle);
sudachi_node_t *get_node(MorphemesHandle handle, const int idx);
void free_node(sudachi_node_t *node);

#endif /* SUDACHI_H */
