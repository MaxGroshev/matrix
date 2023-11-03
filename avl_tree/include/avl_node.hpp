#include "utils.hpp"
#include <stack>

//-----------------------------------------------------------------------------------------

namespace avl {

template <typename T, typename key_type = int>
class node_t {
    public:
        key_type key_;
        T data_;
        node_t<T, key_type>* left_ = nullptr;
        node_t<T, key_type>* right_ = nullptr;
        size_t height_ = 1;


        node_t(key_type key, T data) : key_(key), data_(data) {};
        node_t(const node_t<T, key_type>& node) : key_(node.key_), data_(node.data_),
                                                                   height_(node.height_) {
            if (node.left_ != nullptr) {
                left_ = new node_t<T, key_type>(*node.left_);
                ASSERT(left_ != nullptr);
            }
            if (node.right_ != nullptr) {
                right_ =  new node_t<T, key_type>(*node.right_);
                ASSERT(right_ != nullptr);
            }
        };
        node_t(node_t<T>&& node) noexcept: key_(node.key_), data_(node.data_),
                  height_(node.height_), left_(node.left_), right_(node.right_) {
            node.right_ = nullptr;
            node.left_  = nullptr;
        }
        node_t<T, key_type>& operator= (const node_t<T, key_type>& node);
        node_t<T, key_type>& operator= (node_t<T, key_type>&& node);
        ~node_t() {
            delete right_;
            delete left_;
        }


        inline int find_balance_fact() {return (get_height(right_) - get_height(left_));};
        inline size_t get_height(node_t<T, key_type>* node) {if (node) return node->height_;
                                                   else return 0;};
        inline void change_height() {
            height_ = 1 + find_max(get_height(left_), get_height(right_));
        }


        inline node_t<T, key_type>* balance_subtree(T key);
        inline node_t<T, key_type>* rotate_to_left();
        inline node_t<T, key_type>* rotate_to_right();
        inline node_t<T, key_type>* insert(avl::node_t<T, key_type>* cur_node, T data, key_type key);


        inline void inorder_walk();
        inline void store_inorder_walk(std::vector<T>* storage);
        inline void distance(int l_bound, int u_bound, size_t* result);
        inline void graphviz_dump(graphviz::dump_graph_t& tree_dump);
};

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
node_t<T, key_type>& node_t<T, key_type>::operator= (const node_t<T, key_type>& node) {
    if (this == &node)
        return *this;

    delete left_;
    delete right_;

    key_ = node.key_;
    height_ = node.height_;
    data_ = node.data_;
    left_ = new node_t<T> (*(node.left_));
    left_ = new node_t<T> (*(node.right_));
    return *this;
}

template<typename T, typename key_type>
node_t<T, key_type>& node_t<T, key_type>::operator= (node_t<T, key_type>&& node) {
    if (this == &node)
        return *this;

    delete left_;
    delete right_;

    left_ = node.left_;
    right_ = node.right_;
    key_ = node.key_;
    height_ = node.height_;

    node.right_ = nullptr;
    node.left_  = nullptr;
    return *this;
}

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
node_t<T, key_type>* node_t<T, key_type>::insert(avl::node_t<T, key_type>* cur_node, T data,
                                                                            key_type key) {

    if (cur_node->key_ < key) {
        if (cur_node->right_ != nullptr)
            right_ = right_->insert(right_, key, data);
        else
            right_ = new node_t<T> (key, data);
    }
    else if (cur_node->key_ > key) {
        if (left_ != nullptr)
            left_ = left_->insert(left_, key, data);
        else
            left_ = new node_t<T> (key, data);
    }

    change_height();
    return balance_subtree(key);
}

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
node_t<T, key_type>* node_t<T, key_type>::balance_subtree(T key) {

    int delta = find_balance_fact();
    if (delta > 1) {
        if (key < right_->key_) { //complicated condition
            right_ = right_->rotate_to_right();
        }
        return rotate_to_left();
    }
    else if (delta < -1) {
        if (key > left_->key_) {
            left_ = left_->rotate_to_left();
        }
        return rotate_to_right();
    }
    else
        return this;
}

template<typename T, typename key_type>
node_t<T, key_type>* node_t<T, key_type>::rotate_to_left() {

    node_t<T>* root = right_;
    node_t<T>* root_left = root->left_;
    root->left_  = this;
    right_ = root_left;

    root->left_->change_height();
    root->change_height();
    return root;
}

template<typename T, typename key_type>
node_t<T, key_type>* node_t<T, key_type>::rotate_to_right() {

    node_t<T>* root = left_;
    node_t<T>* root_right = root->right_;
    root->right_ = this;
    left_ = root_right;

    root->right_->change_height();
    root->change_height();
    return root;
}

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
void node_t<T, key_type>::distance(int l_bound, int u_bound, size_t* result) {
    // static int cnt = 0;
    // std::cout << "Cur key_: " << key_ << '\n' << "Result: " << *result <<  ' ' << cnt <<'\n';
    // cnt++;
    if (in_interval(l_bound, u_bound, key_)) {
        (*result)++;
    }
    if (left_ != nullptr && key_ >= l_bound) {
        left_->distance(l_bound, u_bound, result);
    }
    if (right_ != nullptr && key_ <= u_bound) {
        right_->distance(l_bound, u_bound, result);
    }
}

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
void node_t<T, key_type>::inorder_walk() {
    std::cout << " ( ";
    if (left_ != nullptr) {
        left_->inorder_walk();
    }
    std::cout << key_;
    if (right_ != nullptr) {
        right_->inorder_walk();
    }
    std::cout << " ) ";
}

template<typename T, typename key_type>
void node_t<T, key_type>::store_inorder_walk(std::vector<T>* storage) {
    if (left_ != nullptr) {
        left_->store_inorder_walk(storage);
    }
    storage->push_back(key_);
    if (right_ != nullptr) {
        right_->store_inorder_walk(storage);
    }
}

template<typename T, typename key_type>
void node_t<T, key_type>::graphviz_dump(graphviz::dump_graph_t& tree_dump) {
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

