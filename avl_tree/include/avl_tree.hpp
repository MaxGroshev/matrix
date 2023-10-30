#include "avl_node.hpp"

//-----------------------------------------------------------------------------------------

namespace avl {

template<typename T>
class tree_t final {
    private:
        node_t<T>* root_;
        bool is_balanced = true; //prob unneccessary

    public:
        tree_t(T key) {
            root_ = new node_t(key);
        };
        ~tree_t() { delete root_;};

        inline void insert(T key);
        inline void graphviz_dump() const;

};

//-----------------------------------------------------------------------------------------

template<typename T>
void tree_t<T>::insert(T key) {
    root_ = root_->insert(root_, key);
    //assert(new_root != nullptr);
    // std::cout << new_root->key_;
}

//-----------------------------------------------------------------------------------------

template<typename T>
void tree_t<T>::graphviz_dump() const {
    graphviz::dump_graph_t tree_dump("../graph_lib/tree_dump.dot"); //make boost::program_options
    root_->graphviz_dump(tree_dump);
    tree_dump.run_graphviz("../graph_lib/tree_dump.dot", "../graph_lib");
}

}
