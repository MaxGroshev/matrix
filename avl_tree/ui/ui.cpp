#include "./ui.hpp"

//-----------------------------------------------------------------------------------------

namespace avl_tree_ui {

std::vector<size_t> test_user_data(std::istream & in_strm) {
    avl::tree_t<int> pine{10};

    char type_of_data = '\0';
    int  data = 0;
    size_t l_border = 0;
    size_t r_border = 0;
    std::vector<size_t> result;
    for (int i = 0; !in_strm.eof(); i++) {
        in_strm >> type_of_data;
        // std::cout << "Type: " << type_of_data << '\n';
        if (type_of_data == 'k') {
            in_strm >> data;
            pine.insert(data);
        }
        else if (type_of_data == 'q') {
            in_strm >> l_border >> r_border;
            result.push_back(pine.get_num_of_keys_in_range(l_border, r_border));
        }
        type_of_data = '\0'; //bad idea
    }

    // pine.graphviz_dump();
    pine.graphviz_dump();
    avl::tree_t<int> oak{25};
    oak = std::move(pine);
    oak.graphviz_dump();
    assert(oak.root_ != nullptr);

    // std::cout << "Test: " << oak.root_->left << "\n";
    // std::cout << oak.root_->left_->left_->key_ << '\n';
    // pine.root_->left_->key_ = 52;

    return result;
}

}
