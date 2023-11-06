#include "ui.hpp"

//-----------------------------------------------------------------------------------------

int main() {
    std::vector<size_t> result = avl_tree_ui::run_tree();
    // avl_tree_ui::run_set(std::cin);
    // pine.graphviz_dump();

    for (auto const& num : result) {
        std::cout << num << " \n";
    }

    return 0;
}
