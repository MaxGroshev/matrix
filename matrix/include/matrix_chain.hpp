#pragma once
#include <limits>
#include "matrix_oper.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix {

template<typename T>
class chain_t {
    private:
        std::vector<T>   matrixes;
        std::vector<int> mx_sizes;
        std::vector<int> mul_order;

        T mx_mul(const imatrix_t<std::pair<int, int>>& cache, int i, int j) const;
    public:
        chain_t(std::vector<int> order) : mx_sizes(order) {} //bad but fast for order_tests avoid of sys_calls when create mx
        chain_t() {};

        T mul() const;
        T naive_mul() const;
        void push_back(T& matrix) {
            if (matrixes.empty()) {
                mx_sizes.push_back(matrix.column_size_);
            }
            else if (mx_sizes.back() != matrix.column_size_) {
                throw mx_exception("Incorrect size of matrix:"
                                   "Impossible to add in chain\n");
            }

            mx_sizes.push_back(matrix.row_size_);
            try {
                matrixes.push_back(matrix);
            } catch (...) {
                mx_sizes.pop_back();
                throw mx_exception("ERROR of inseting of matrix");
            }

        }
        T top() const {
            return matrixes.back();
        }
        void pop_back() {
            matrixes.pop_back();
            if (matrixes.empty()) {
                mx_sizes.pop_back();
                mx_sizes.pop_back();
            }
        }
        int size() const {
            return matrixes.size();
        }
        std::vector<int> get_mul_order() const {
            return mul_order;
        }

        int  get_num_of_mul(imatrix_t<std::pair<int, int>>& cache, int i, int j) const;
        void find_mul_order();
        void find_best_order(const imatrix_t<std::pair<int, int>>& cache, int i, int j);
};

//-----------------------------------------------------------------------------------------

template<typename T>
T chain_t<T>::naive_mul() const {
    if (matrixes.size() <= 1)
        return matrixes.back();

    T mx = matrixes[0];
    for (int i = 0; i < matrixes.size() - 1; i++) {
        mx = mx * matrixes[i + 1];
    }
    return mx;
}

template<typename T>
T chain_t<T>::mul() const {
    int chain_size = size();
    imatrix_t<std::pair<int, int>> cache {chain_size + 1, chain_size + 1, {-1, -1}};
    get_num_of_mul(cache, 1, chain_size);
    return mx_mul (cache, 1, chain_size);
}

template<typename T>
void chain_t<T>::find_mul_order() {
    int chain_size = mx_sizes.size();
    imatrix_t<std::pair<int, int>> cache {chain_size, chain_size, {-1, -1}};
    get_num_of_mul(cache, 1, chain_size);
    find_best_order(cache, 1, chain_size - 1);
}

template<typename T>
int chain_t<T>::get_num_of_mul(imatrix_t<std::pair<int, int>>& cache, int i, int j) const {
    if (i == j)
        return 0;
    if (cache[i][j].first != -1) {
        return cache[i][j].first;
    }

    cache[i][j].first = std::numeric_limits<int>::max();
    for (int k = i; k < j; ++k) {
        int val1 = get_num_of_mul(cache, i, k);
        int val2 = get_num_of_mul(cache, k + 1, j) +
                   mx_sizes[i - 1] *
                   mx_sizes[k] *
                   mx_sizes[j];
        int val = val1 + val2;

        const int prev_ij = cache[i][j].first;
        cache[i][j].first = std::min(cache[i][j].first, val);
        if (prev_ij > cache[i][j].first) {
            cache[i][j].second = k;
        }
    }
    return cache[i][j].first;
}

template<typename T>
void chain_t<T>::find_best_order(const imatrix_t<std::pair<int, int>>& cache, int i, int j) {
    if (i == j)
        return;

    int k_iter =  cache[i][j].second;
    mul_order.push_back(k_iter - 1);
    find_best_order(cache, k_iter + 1, j);
    find_best_order(cache, i, k_iter);
}

template<typename T>
T chain_t<T>::mx_mul(const imatrix_t<std::pair<int, int>>& cache, int i, int j) const {
    if (i == j) {
        return matrixes[i - 1];
    }
    else if (j - i == 1)
        return (matrixes[i - 1] * matrixes[j - 1]);

    int k_iter = cache[i][j].second;
    return mx_mul(cache, i, k_iter) * mx_mul(cache, k_iter + 1, j);
}
}

