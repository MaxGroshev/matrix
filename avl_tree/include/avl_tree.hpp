#include "avl_node.hpp"

//-----------------------------------------------------------------------------------------

namespace avl {

template<typename T>
class tree_t {
    private:
        node_t<T>* root_;

    public:
        tree_t(T data) {
            root_ = new node_t(data);
        };
        ~tree_t() { delete root_;};

        inline void graphviz_dump() const;

};

template<typename T>
void tree_t<T>::graphviz_dump() const {
    graphviz::dump_graph_t tree_dump("../graph_lib/tree_dump.dot"); //make boost::program_options
    root_->graphviz_dump(tree_dump);
    tree_dump.run_graphviz("../graph_lib/tree_dump.dot", "../graph_lib");
}

}
