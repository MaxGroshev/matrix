#include <iostream>
#include "debug_utils.hpp"


//-----------------------------------------------------------------------------------------

namespace avl {

template <typename T>
class node_t {
    public:
        T data_;
        node_t<T>* left_;
        node_t<T>* right_;
        size_t height_;

        node_t(T data) : data_(data), left_(nullptr), right_(nullptr) {};
        // ~node_t() ;
        inline void graphviz_dump(graphviz::dump_graph_t& tree_dump);
};

template<typename T>
void node_t<T>::graphviz_dump(graphviz::dump_graph_t& tree_dump) {
    // std::cout << tree_dump.graph_node->shape << '\n';
    tree_dump.graph_node.print_node(this, tree_dump.graphviz_strm);

    if (left_ != nullptr)
    {
        tree_dump.graph_edge.fillcolor = "#7FC7FF";
        tree_dump.graph_edge.color     = "#7FC7FF";
        tree_dump.graph_edge.print_edge(this, left_, tree_dump.graphviz_strm);
        left_->graphviz_dump(tree_dump);
    }
    if (right_ != nullptr)
    {
        tree_dump.graph_edge.fillcolor = "#DC143C";
        tree_dump.graph_edge.color     = "#DC143C";
        tree_dump.graph_edge.print_edge(this, right_, tree_dump.graphviz_strm);
        right_->graphviz_dump(tree_dump);
    }
}
}

