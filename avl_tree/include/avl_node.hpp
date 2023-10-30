#include <iostream>
#include <cmath>
#include "debug_utils.hpp"

//-----------------------------------------------------------------------------------------
template <typename T>
T find_max (const T x, const T y) {
    if (x > y) return x;
    return y;
}

namespace avl {

template <typename T>
class node_t {
    public:
        T key_;
        node_t<T>* left_;
        node_t<T>* right_;
        size_t height_ = 1;

        node_t(T key) : key_(key), left_(nullptr), right_(nullptr) {};
        // ~node_t() ;
        inline int find_balance_fact() {return (get_height(right_) - get_height(left_));};
        inline size_t get_height(node_t<T>* node) {if (node) return node->height_;
                                                   else return 0;};
        inline void change_height() {
            height_ = 1 + find_max(get_height(left_), get_height(right_));
        }
        inline node_t<T>* balance_subtree(node_t<T>* node);
        inline node_t<T>* rotate_left(node_t<T>* node);
        inline node_t<T>* rotate_right(node_t<T>* node);
        inline node_t<T>* insert(avl::node_t<T>* cur_node, T key);
        inline void graphviz_dump(graphviz::dump_graph_t& tree_dump);
};


//-----------------------------------------------------------------------------------------

template<typename T>
node_t<T>* node_t<T>::insert(avl::node_t<T>* cur_node, T key) {

    std::cout << key << cur_node->key_ <<"\n";
    if (cur_node->key_ < key) {
        if (cur_node->right_ != nullptr)
            right_ = right_->insert(right_, key);
        else
            right_ = new node_t<T> (key);
    }
    else if (cur_node->key_ > key) {
        std::cout << "Here\n";
        if (left_ != nullptr)
            left_ = left_->insert(left_, key);
        else
            left_ = new node_t<T> (key);
    }

    change_height();
    return balance_subtree(cur_node);

}

//-----------------------------------------------------------------------------------------

template<typename T>
node_t<T>* node_t<T>::balance_subtree(node_t<T>* node) {

    int delta = find_balance_fact();
    std::cout << "Delta: " << delta << '\n';
    if (delta > 1)
        return rotate_left(node);
    else if (delta < -1)
        return rotate_right(node);
    else
        return node;

}

template<typename T>
node_t<T>* node_t<T>::rotate_left(node_t<T>* node) {

    node_t<T>* root = node->right_;
    node_t<T>* root_left = root->left_;
    root->left_  = node;
    node->right_ = root_left;

    root->left_->change_height();
    root->change_height();
    return root;
}

template<typename T>
node_t<T>* node_t<T>::rotate_right(node_t<T>* node) {

    node_t<T>* root = node->left_;
    node_t<T>* root_right = root->right_;
    root->right_ = node;
    node->left_ = root_right;

    root->right_->change_height();
    root->change_height();
    return root;
}

//-----------------------------------------------------------------------------------------

template<typename T>
void node_t<T>::graphviz_dump(graphviz::dump_graph_t& tree_dump) {
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

