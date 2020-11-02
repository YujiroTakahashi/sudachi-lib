#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sudachi.h"

int main(int argc, char **argv)
{
    TokenizerHandle tokenizer = new_tokenizer("sudachidict/sudachi.json");
    MorphemesHandle morphemes = NULL;
    int size;
    const char input[] = "日本語を分析する。";

    morphemes = parse_tokenizer(tokenizer, input);
    size      = size_morpheme_list(morphemes);

    for (int idx = 0; size > idx; idx++) {
        sudachi_node_t *node = get_node(morphemes, idx);
        printf("%d\t%s\n", idx, node->data);
        free_node(node);
    }

    free_morpheme_list(morphemes);
    free_tokenizer(tokenizer);

    return EXIT_SUCCESS;
}