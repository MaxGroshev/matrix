namespace graphviz {

template<typename T>
void node_t::print_node (T* data_node, std::ofstream& graphviz_strm) {
    assert(data_node != nullptr);
    assert(graphviz_strm.good());
    // std::cerr << "Here\n";
    // std::cout << shape << '\n';
    graphviz_strm << "node" << (data_node->data_) <<       " [shape      = \"" << shape
               << "\", width = 1.1, height = 1.21,  fillcolor   = \"" << fillcolor
               << "\", style = \""    << style << "\", fontcolor= \" " << fontcolor
               << "\", fontname = \"" << fontname << "\", color = \"" << color
               << "\", label = \"{"   << data_node->data_ << "}\"]\n";
}

//-----------------------------------------------------------------------------------------

template<typename T>
void edge_t::print_edge (T* node_from, T* node_to, std::ofstream& graphviz_strm) {
    graphviz_strm << "node" << node_from << " -> node" << node_to << " color = \"" << color
               << "\", style = \""    << style << "\", constraint = " << constraint
               << ", fillcolor = \""  << fillcolor << "\",   fontcolor = \"" << fontcolor
               << "\", fontname = \"" << fontname  << "\", label = \"" << label << "\"];\n";
}

//-----------------------------------------------------------------------------------------

void dump_graph_t::run_graphviz(const char* dot_dir, const char* pic_dir) {
    assert (dot_dir != nullptr && pic_dir != nullptr);
    graphviz_strm << "}\n";
    graphviz_strm.close();

    static int num_of_print = 0;
    num_of_print++;
    std::string command = "dot " + std::string(dot_dir) + " -T png -o " + pic_dir + "/tree_d"
                                 + std::to_string(num_of_print) + ".png";
    system (command.c_str());
}
}
