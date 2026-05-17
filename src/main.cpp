#include <iostream>
#include <fmt/base.h>
#include <string_view>

using std::string;

inline constexpr std::string_view backend_path = BACKEND_PATH;
inline constexpr bool debug_mode = DEBUG_MODE;

int main(int argc, char** argv) {
    if (debug_mode) {
        fmt::println("Debug mode activated.");
        fmt::println("Using path: {0}", backend_path);
    }

    return 0;
}