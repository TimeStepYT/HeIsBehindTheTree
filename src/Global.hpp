#pragma once

#include <random>

namespace global {
    inline std::mt19937 mt{std::random_device{}()};
}