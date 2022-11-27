#pragma once
#include <string>
#include <type_traits>
#include "Concepts.h"


template <Arithmetic T>
std::string toString(T value) {
    return std::to_string(value);
}

template <NonArithmetic T>
std::string toString(T value) {
    return std::string(value);
}

