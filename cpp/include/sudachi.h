#ifndef SUDACHI_H
#define SUDACHI_H

#include <stdlib.h>

#ifdef __cplusplus
#include <string>
#include <vector>

extern "C" {
#endif /* __cplusplus */

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

#ifdef __cplusplus
} // extern "C"

namespace croco {

class Sudachi {
public:
    typedef struct _node_t {
        std::string surface;
        std::string pos;
        std::string normalized_form;
        std::string dictionary_form;
        std::string reading_form;
    } node_t;

private:
    TokenizerHandle _tokenizer;

public:
    Sudachi(const char* setting) {
        _tokenizer = new_tokenizer(setting);
    }
    ~Sudachi() {
        if (nullptr != _tokenizer) {
            free_tokenizer(_tokenizer);
        }
    }
    std::vector<node_t> parseToNode(const std::string input);
}; // class Sudachi

/**
 * 解析
 *
 * @access public
 * @param  const std::string input
 * @return std::vector<Sudachi::node_t>
 */
inline std::vector<Sudachi::node_t> Sudachi::parseToNode(const std::string input)
{
    MorphemesHandle morphemes = parse_tokenizer(_tokenizer, input.c_str());
    int size = size_morpheme_list(morphemes);

    std::vector<Sudachi::node_t> result;
    for (int idx = 0; size > idx; idx++) {
        sudachi_node_t *node = get_node(morphemes, idx);
        std::string data(node->data);
        result.push_back({
            data.substr(0, node->surface),
            data.substr(node->surface, node->pos),
            data.substr(node->surface + node->pos, node->normalized_form),
            data.substr(node->surface + node->pos + node->normalized_form, node->dictionary_form),
            data.substr(node->surface + node->pos + node->normalized_form + node->dictionary_form, node->reading_form)
        });
        free_node(node);
    }
    free_morpheme_list(morphemes);

    return result;
}

} // namespace croco
#endif /* __cplusplus */

#endif /* SUDACHI_H */
