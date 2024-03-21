#pragma once
#include <iostream>
#include <string>

//-----------------------------------------------------------------------------------------

class mx_exception : public std::runtime_error {
    public:
        enum class MX_ERR {
            WRONG_SIZES = -1,
        };

        mx_exception(std::string err_msg) : std::runtime_error(err_msg) {};
        mx_exception(MX_ERR err) : std::runtime_error("ERROR") {
            switch(err) {
                case(MX_ERR::WRONG_SIZES):
                    std::runtime_error("Different size of matrixes\n");
                    std::cerr << -1;
                    break;
            }
        };
};
