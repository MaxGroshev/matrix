#include "avl_node.hpp"

//-----------------------------------------------------------------------------------------

namespace avl {

template<typename T>
class tree_t final {
    public:
        node_t<T>* root_;
    public:
        tree_t(T key) {
            root_ = new node_t(key);
            ASSERT(root_ != nullptr);
        };
        tree_t(const tree_t<T>& tree) {
            root_ = new node_t<T> (*(tree.root_));
            ASSERT(root_ != nullptr);
        };
        tree_t(tree_t<T>&& tree) noexcept {
            root_ = tree.root_;
            tree.root_ = nullptr;
            ASSERT(root_ != nullptr);
        };
        tree_t<T>& operator= (const tree_t<T>& tree);
        tree_t<T>& operator= (tree_t<T>&& tree);
        ~tree_t() { delete root_;};


        inline void insert(T key);
        inline size_t get_num_of_keys_in_range(size_t l_border, size_t r_border);
        inline void inorder_walk() const;
        inline void graphviz_dump() const;

};

//-----------------------------------------------------------------------------------------

template<typename T>
tree_t<T>& tree_t<T>::operator= (const tree_t<T>& tree) {
    if (this == &tree)
        return *this;

    delete root_;
    root_ = new node_t<T> (*(tree.root_));
    return *this;
}

template<typename T>
tree_t<T>&tree_t<T>::operator= (tree_t<T>&& tree) {
    if (this == &tree)
        return *this;

    delete root_;
    root_ = tree.root_;
    tree.root_ = nullptr;
    return *this;
}

//-----------------------------------------------------------------------------------------

template<typename T>
void tree_t<T>::insert(T key) {
    root_ = root_->insert(root_, key);
}

template<typename T>
size_t tree_t<T>::get_num_of_keys_in_range(size_t l_border, size_t r_border) {
    size_t result = 0;
    return root_->get_num_of_keys_in_range(l_border, r_border, result);
}

//-----------------------------------------------------------------------------------------

template<typename T>
void tree_t<T>::inorder_walk() const {
    root_->inorder_walk();
    std::cout << "\n";
}

template<typename T>
void tree_t<T>::graphviz_dump() const {
    graphviz::dump_graph_t tree_dump("../graph_lib/tree_dump.dot"); //make boost::program_options
    root_->graphviz_dump(tree_dump);
    tree_dump.run_graphviz("../graph_lib/tree_dump.dot", "../graph_lib");
}

}
