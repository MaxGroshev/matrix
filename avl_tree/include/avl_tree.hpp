#include "avl_node.hpp"

//-----------------------------------------------------------------------------------------

namespace avl {

template<typename T, typename key_type = int>
class tree_t final {
    public:
        node_t<T, key_type>* root_;
    public:
        tree_t(key_type key, T data) {
            root_ = new node_t(key, data);
            ASSERT(root_ != nullptr);
        };
        tree_t(const tree_t<T, key_type>& tree) {
            root_ = new node_t<T> (*(tree.root_));
            ASSERT(root_ != nullptr);
        };
        tree_t(tree_t<T>&& tree) noexcept {
            root_ = tree.root_;
            tree.root_ = nullptr;
            ASSERT(root_ != nullptr);
        };
        tree_t<T, key_type>& operator= (const tree_t<T, key_type>& tree);
        tree_t<T, key_type>& operator= (tree_t<T, key_type>&& tree);
        ~tree_t() {
            // delete root_;
            std::stack<node_t<T, key_type>*> nodes;
            nodes.push(root_);
            node_t<T, key_type>* front = nullptr;
            while(!nodes.empty()) {
                front = nodes.top();
                nodes.pop();
                if (front != nullptr) { //case of deleteing after move constr
                    if (front->left_ != nullptr) {
                        nodes.push(front->left_);

                    }
                    if (front->right_ != nullptr) {
                        nodes.push(front->right_);
                    }
                }
                front->left_ = nullptr;  //to not delete children recursively as node has
                front->right_ = nullptr; //ability to be destructed recursively
                delete front;
            }
        };

        inline void insert(key_type key, T data);
        inline size_t get_num_of_keys_in_range(size_t l_border, size_t r_border);
        inline void inorder_walk() const;
        inline void store_inorder_walk(std::vector<T>* storage) const;
        inline void graphviz_dump() const;

};

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
tree_t<T, key_type>& tree_t<T, key_type>::operator= (const tree_t<T, key_type>& tree) {
    if (this == &tree)
        return *this;

    delete root_;
    root_ = new node_t<T, key_type> (*(tree.root_));
    return *this;
}

template<typename T, typename key_type>
tree_t<T, key_type>&tree_t<T, key_type>::operator= (tree_t<T, key_type>&& tree) {
    if (this == &tree)
        return *this;

    delete root_;
    root_ = tree.root_;
    tree.root_ = nullptr;
    return *this;
}

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
void tree_t<T, key_type>::insert(key_type key, T data) {
    root_ = root_->insert(root_, key, data);
}

template<typename T, typename key_type>
size_t tree_t<T, key_type>::get_num_of_keys_in_range(size_t l_border, size_t r_border) {
    size_t result = 0;
    return root_->get_num_of_keys_in_range(l_border, r_border, result);
}

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
void tree_t<T, key_type>::inorder_walk() const {
    root_->inorder_walk();
    std::cout << "\n";
}

template<typename T, typename key_type>
void tree_t<T, key_type>::store_inorder_walk(std::vector<T>* storage) const {
    root_->store_inorder_walk(storage);
    std::cout << "\n";
}

template<typename T, typename key_type>
void tree_t<T, key_type>::graphviz_dump() const {
    graphviz::dump_graph_t tree_dump("../graph_lib/tree_dump.dot"); //make boost::program_options
    root_->graphviz_dump(tree_dump);
    tree_dump.run_graphviz("../graph_lib/tree_dump.dot", "../graph_lib");
}

}
