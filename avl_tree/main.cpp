#include "ui.hpp"

//-----------------------------------------------------------------------------------------

int main() {
    std::vector<size_t> result = avl_tree_ui::test_user_data();
    // pine.graphviz_dump();

    for (auto const& num : result) {
        std::cout << num << " \n";
    }

    return 0;
}
