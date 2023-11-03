#include "./ui.hpp"

//-----------------------------------------------------------------------------------------

namespace avl_tree_ui {

std::vector<size_t> test_user_data(std::istream & in_strm) {
    avl::tree_t<int, int> pine;
    std::set<int> enemy_set;
    char type_of_data = '\0';
    int  data = 0;
    int l_bound = 0;
    int u_bound = 0;

    std::vector<size_t> result;
    for (int i = 0; !in_strm.eof(); i++) {
        in_strm >> type_of_data;
        if (type_of_data == 'k') {
            in_strm >> data;
            pine.insert(data, data);
            enemy_set.insert(data);
        }
        else if (type_of_data == 'q') {
            in_strm >> l_bound >> u_bound;

            auto start_time = chrono_cur_time ();
            result.push_back(pine.distance(l_bound, u_bound));
            auto end_time = chrono_cur_time ();
            std::cerr << "Run time: " <<(end_time - start_time) / 0.1ms  << '\n';

            start_time = chrono_cur_time ();
            range_query(enemy_set, l_bound, u_bound);
            end_time = chrono_cur_time ();
            std::cerr << "Run time: " <<(end_time - start_time) / 0.1ms  << '\n';
        }
        type_of_data = '\0'; //bad idea
    }

    // pine.graphviz_dump();

    return result;
}

}
