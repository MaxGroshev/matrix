#include "ui.hpp"

//-----------------------------------------------------------------------------------------

int main() {
    avl::tree_t<int> pine{1};
    pine.graphviz_dump();
    ASSERT("\nRESULT:\n");
    // for (int i = 0; i < intersect_triangles.size(); i++) {
    //     std::cout << intersect_triangles[i] << " \n";
    // }

    return 0;
}
