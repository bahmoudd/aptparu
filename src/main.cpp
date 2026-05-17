#include <iostream>
#include <fmt/base.h>
#include <cstdlib>
#include <string_view>

using std::string;

inline constexpr std::string_view backend_path = BACKEND_PATH;

int main(int argc, char** argv) {
    fmt::print("Using path: {0}", backend_path);

    return 0;
}