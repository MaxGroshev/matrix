#include "ui.hpp"

//-----------------------------------------------------------------------------------------

int main() {
    avl::tree_t<int> pine{10};
    // avl::node_t<int>* node1 = new avl::node_t<int>(5);
    // avl::node_t<int>* node2 = new avl::node_t<int>(12);
    // avl::node_t<int>* node3 = new avl::node_t<int>(13);
    // avl::node_t<int>* node4 = new avl::node_t<int>(14);
    pine.insert(5);
    pine.insert(12);
    pine.insert(15);
    pine.insert(17);
    pine.insert(4);
    pine.insert(3);
    // pine.insert(18);
    pine.graphviz_dump();

    // ASSERT("\nRESULT:\n");
    // for (int i = 0; i < intersect_triangles.size(); i++) {
    //     std::cout << intersect_triangles[i] << " \n";
    // }

    return 0;
}
