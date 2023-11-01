#include "utils.hpp"

//-----------------------------------------------------------------------------------------

namespace avl {

template <typename T>
class node_t {
    public:
        T key_;
        node_t<T>* left_ = nullptr;
        node_t<T>* right_ = nullptr;
        size_t height_ = 1;

        node_t(T key) : key_(key), left_(nullptr), right_(nullptr) {};
        node_t(const node_t<T>& node) : key_(node.key_), height_(node.height_) {

            if (node.left_ != nullptr) {
                left_ = new node_t<T>(*node.left_);
                ASSERT(left_ != nullptr);
            }
            if (node.right_ != nullptr) {
                right_ =  new node_t<T>(*node.right_);
                ASSERT(right_ != nullptr);
            }
        };
        node_t(node_t<T>&& node) noexcept: key_(node.key_), height_(node.height_),
                                           left_(node.left_), right_(node.right_) {
            node.right_ = nullptr;
            node.left_  = nullptr;
        }
        node_t<T>& operator= (const node_t<T>& node);
        node_t<T>& operator= (node_t<T>&& node);
        ~node_t() { delete left_; delete right_;};


        inline int find_balance_fact() {return (get_height(right_) - get_height(left_));};
        inline size_t get_height(node_t<T>* node) {if (node) return node->height_;
                                                   else return 0;};
        inline void change_height() {
            height_ = 1 + find_max(get_height(left_), get_height(right_));
        }


        inline node_t<T>* balance_subtree(T key);
        inline node_t<T>* rotate_to_left();
        inline node_t<T>* rotate_to_right();
        inline node_t<T>* insert(avl::node_t<T>* cur_node, T key);


        inline void inorder_walk();
        inline size_t get_num_of_keys_in_range(size_t l_border, size_t r_border, size_t result);
        inline void graphviz_dump(graphviz::dump_graph_t& tree_dump);
};

//-----------------------------------------------------------------------------------------

template<typename T>
node_t<T>& node_t<T>::operator= (const node_t<T>& node) {
    if (this == &node)
        return *this;

    delete left_;
    delete right_;

    key_ = node.key_;
    height_ = node.height_;
    left_ = new node_t<T> (*(node.left_));
    left_ = new node_t<T> (*(node.right_));
    return *this;
}

template<typename T>
node_t<T>& node_t<T>::operator= (node_t<T>&& node) {
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

template<typename T>
node_t<T>* node_t<T>::insert(avl::node_t<T>* cur_node, T key) {

    if (cur_node->key_ < key) {
        if (cur_node->right_ != nullptr)
            right_ = right_->insert(right_, key);
        else
            right_ = new node_t<T> (key);
    }
    else if (cur_node->key_ > key) {
        if (left_ != nullptr)
            left_ = left_->insert(left_, key);
        else
            left_ = new node_t<T> (key);
    }

    change_height();
    return balance_subtree(key);
}

//-----------------------------------------------------------------------------------------

template<typename T>
node_t<T>* node_t<T>::balance_subtree(T key) {

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

template<typename T>
node_t<T>* node_t<T>::rotate_to_left() {

    node_t<T>* root = right_;
    node_t<T>* root_left = root->left_;
    root->left_  = this;
    right_ = root_left;

    root->left_->change_height();
    root->change_height();
    return root;
}

template<typename T>
node_t<T>* node_t<T>::rotate_to_right() {

    node_t<T>* root = left_;
    node_t<T>* root_right = root->right_;
    root->right_ = this;
    left_ = root_right;

    root->right_->change_height();
    root->change_height();
    return root;
}

//-----------------------------------------------------------------------------------------

template<typename T> // IT DOES NOT WORK (TESTING VERSION)
size_t node_t<T>::get_num_of_keys_in_range(size_t l_border, size_t r_border, size_t result) {

    // std::cout << "Cur key_: " << key_ << '\n' << "Result: " << result << '\n';
    if (in_interval(l_border, r_border, key_)) {
        result++;
    }
    if (left_ != nullptr && left_->key_ >= l_border) {
        return left_->get_num_of_keys_in_range(l_border, r_border, result);
    }
    else if (right_ != nullptr && left_->key_ <= r_border) {
        return right_->get_num_of_keys_in_range(l_border, r_border, result);
    }

    return result;
}

//-----------------------------------------------------------------------------------------

template<typename T>
void node_t<T>::inorder_walk() {
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

