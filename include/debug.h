#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef _DEBUG_
#include <iostream>
#include <string>


template<class T>
void debug(const T t, const std::string var_name="-", const std::string end="\n", const size_t level=1) {
    std::string indent = "";
    for (size_t i = 0; i < level; i++) {
        indent += " ";
    }
    
    if (var_name != "-") {
        std::cout << "[DEBUG (" << var_name << ")]:";
    }
    else {
        std::cout << "[DEBUG]:";
    }
    
    std::cout << indent << t << end;
}

#else

template<class T>
void debug(const T t, const std::string var_name="-", const std::string end="\n", const size_t level=1) {}

#endif
#endif
