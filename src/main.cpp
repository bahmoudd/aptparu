#include <iostream>
#include <fmt/base.h>
#include <fmt/color.h>
#include <string_view>
#include <CLI/CLI.hpp>
#include <vector>

using std::string;

inline constexpr std::string_view backend_path = BACKEND_PATH;
inline constexpr bool debug_mode = DEBUG_MODE;

int print_error_message(const string& command, bool cause_of_error_is_lack_of_packages_passed = true) {
    string error_cause = "package";
    if (not cause_of_error_is_lack_of_packages_passed)
        error_cause = "search string";
    fmt::print(stderr,
               "{0} '{1}' option passed but no {2}(s) provided!\n",
               fmt::styled("ERROR:", fmt::fg(fmt::color::red) | fmt::emphasis::bold),
               command,
               error_cause);
            
    return 1;
}


int main(int argc, char** argv) {
    if (debug_mode) {
        fmt::println("Debug mode activated.");
        fmt::println("Using path: {0}", backend_path);
    }

    std::vector<string> packages;

    CLI::App app{"A wrapper for paru/pacman for ease of use"};
    CLI::App* install = app.add_subcommand("install", "Install a package");
    CLI::App* install_local = app.add_subcommand("install-local", "Install a local package");
    CLI::App* remove = app.add_subcommand("remove", "Remove a package");
    CLI::App* purge = app.add_subcommand("purge", "Removes a pacakage and prevents the creation of backup configuration files");
    CLI::App* search = app.add_subcommand("search", "Search for a package");
    CLI::App* find = app.add_subcommand("find", "Find an installed package");
    CLI::App* update = app.add_subcommand("update", "Updates lists of available packages but does not install/update any packages");
    CLI::App* upgrade = app.add_subcommand("upgrade", "Updates a local package");
    CLI::App* full_upgrade = app.add_subcommand("full-upgrade", "Update + Upgrade");
    CLI::App* autoclean = app.add_subcommand("autoclean", "Cleans up all local caches");
    CLI::App* clean = app.add_subcommand("clean", "Same as autoclean");
    CLI::App* autoremove = app.add_subcommand("autoremove", "Removes orphaned packages");
    CLI::App* show = app.add_subcommand("show", "Shows information about a package that is installed");
    CLI::App* show_all = app.add_subcommand("show-all", "Shows information about a package that may not be installed");
    CLI::App* list_installed = app.add_subcommand("list-installed", "Lists all installed packages");
    CLI::App* list_detailed = app.add_subcommand("list-detailed", "Lists all installed packages in great detail");
    CLI::App* help = app.add_subcommand("help", "Shows this help")->silent();
    CLI::App* version = app.add_subcommand("version", "Shows version and about information")->silent();

    install->add_option("packages", packages);
    install_local->add_option("packages", packages);
    remove->add_option("packages", packages);
    purge->add_option("packages", packages);
    search->add_option("packages", packages);
    find->add_option("packages", packages);
    upgrade->add_option("packages", packages);
    show->add_option("packages", packages);
    show_all->add_option("packages", packages);
    
    CLI11_PARSE(app, argc, argv);
    
    if (*install and packages.empty()) 
        return print_error_message("install");
    else if (*install_local and packages.empty()) 
        return print_error_message("install-local");
    else if (*remove and packages.empty()) 
        return print_error_message("remove");
    else if (*purge and packages.empty())
        return print_error_message("purge");
    else if (*search and packages.empty())
        return print_error_message("search", false);
    else if (*find and packages.empty())
        return print_error_message("find", false);
    else if (*upgrade and packages.empty())
        return print_error_message("upgrade");
    else if (*show and packages.empty())
        return print_error_message("show");
    else if (*show_all and packages.empty())
        return print_error_message("show-all");

    return 0;
}

