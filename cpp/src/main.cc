#include <iostream>
#include <string>
#include <vector>

#include "sudachi.h"

int main(int argc, char** argv) 
{
    const char *setting = "sudachidict/sudachi.json";
    croco::Sudachi sudachi(setting);
    auto nodes = sudachi.parseToNode("日本語を解析する。");

    for (auto &node: nodes) {
        std::cout << node.surface << "\t" 
                  << node.pos << "\t"
                  << node.normalized_form << "\t"
                  << node.dictionary_form << "\t"
                  << node.reading_form << "\n";
    }

    return 0;
}
