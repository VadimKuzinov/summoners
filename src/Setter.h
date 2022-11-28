#pragma once
#include <string>
#include <tuple>
#include <vector>
#include "toString.h"
#include <iostream>
#include <sstream>


template <typename T, typename... Args>
void setImpl(T& t, const std::tuple<Args...>& tuple, const std::string& name, const std::string& value) {
    std::apply(
        [&t, &name, &value](auto&&... pairs) {
            (((std::string(pairs.second) == name) && (std::istringstream(value) >> t.*pairs.first)), ...);
        }, tuple
    );
}

template <typename T, typename... Args>
auto serializeImpl(T& t, const std::tuple<Args...>& tuple) {
    std::vector<std::pair<std::string, std::string>> result;
    std::apply(
        [&result, &t](auto&&... pairs) {
            (result.push_back({toString(t.*pairs.first), pairs.second}), ...);
        }, tuple
    );
    return result;
}

