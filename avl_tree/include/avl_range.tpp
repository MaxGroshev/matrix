namespace avl {

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

template<typename T, typename key_type>
node_t<T, key_type>* node_t<T, key_type>::upper_bound(key_type key) const {
    if (key_ < key) {
        if (right_ != nullptr)
            return right_->upper_bound(key);
        else
            return this;
    }
    else if (key_ > key) {
        if (left_ != nullptr)
            left_->upper_bound(key);
        // else
            // left_ = new node_t<T> (key, data);
    }
    else {
        return this;
    }
}

template<typename T, typename key_type>
node_t<T, key_type>* node_t<T, key_type>::lower_bound(key_type key) const {
    // return root_->lower_bound(key);
    return nullptr;
}

//-----------------------------------------------------------------------------------------

template<typename T, typename key_type>
size_t node_t<T, key_type>::define_node_rang(size_t key_rang) const {
    // size_t rang = left_->size_ + 1;
    // node_t
    return 1;
}

}
