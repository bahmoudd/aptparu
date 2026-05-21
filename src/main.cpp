#include <iostream>
#include <string_view>
#include <vector>
#include <cstdlib>

#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#include <CLI/CLI.hpp>

using std::string;
using std::string_view;

inline constexpr string_view backend_path = BACKEND_PATH;
inline constexpr bool debug_mode = DEBUG_MODE;

int command_execute(const string_view& subcommand, 
                    const string& arguments, 
                    const std::vector<string>& packages, 
                    const string& potential_error_cause,
                    bool packages_needed = true) {
    
    string command = "";
    if (packages.empty() and packages_needed) {
        fmt::print(stderr,
                "{0} '{1}' option passed but no {2}(s) provided!\n",
                fmt::styled("ERROR:", fmt::fg(fmt::color::red) | fmt::emphasis::bold),
                subcommand,
                potential_error_cause);
                
        return 1;
    }

    if (packages_needed)
        command = fmt::format("{} {} {}", backend_path, arguments, fmt::join(packages, " "));
    else
        command = fmt::format("{} {}", backend_path, arguments);

    if (debug_mode)
        fmt::println("Command being run is {}", command);

    return system(command.c_str());
}

int main(int argc, char** argv) {
    if (debug_mode) {
        fmt::println("INFO: Debug mode activated.");
        fmt::println("INFO: Using path: {0}", backend_path);
    }

    std::vector<string> packages = {};

    CLI::App app{"A wrapper for paru/pacman for ease of use"};
    CLI::App* download = app.add_subcommand("download", "Downloads a package without installing it");
    CLI::App* install = app.add_subcommand("install", "Install a package");
    CLI::App* install_local = app.add_subcommand("install-local", "Install a local package");
    CLI::App* remove = app.add_subcommand("remove", "Remove a package");
    CLI::App* purge = app.add_subcommand("purge", "Removes a pacakage and prevents the creation of backup configuration files");
    CLI::App* remove_only = app.add_subcommand("remove-only", "Removes a package which is required by another package without deleting the dependant package");
    CLI::App* recursive_remove = app.add_subcommand("recursive-remove", "Removes a package alongside all of its dependencies and all packages that depend on the target package");
    CLI::App* search = app.add_subcommand("search", "Search for a package");
    CLI::App* find = app.add_subcommand("find", "Find an installed package");
    CLI::App* update = app.add_subcommand("update", "Updates lists of available packages but does not install/update any packages");
    CLI::App* force_update = app.add_subcommand("force-update", "Forces update even if lists of packages appear up to date");
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
    
    download->add_option("packages", packages);
    install->add_option("packages", packages);
    install_local->add_option("packages", packages);
    remove->add_option("packages", packages);
    purge->add_option("packages", packages);
    remove_only->add_option("packages", packages);
    recursive_remove->add_option("packages", packages);
    search->add_option("packages", packages);
    find->add_option("packages", packages);
    upgrade->add_option("packages", packages);
    show->add_option("packages", packages);
    show_all->add_option("packages", packages);
    app.footer("Errors may be styled differently depending on whether the error is handled by pacman/paru or aptparu. \
        Additionally, autoremove may need to be run with sudo even with paru installed because of some weird bug with paru.");
    
    CLI11_PARSE(app, argc, argv);
    string command;
    
    if (*download)
        return command_execute("download", "-Sw", packages, "package");
    else if (*install)  
        return command_execute("install", "-S", packages, "package");
    else if (*install_local) 
        return command_execute("install-local", "-U", packages, "package");
    else if (*remove) 
        return command_execute("remove", "-Rs", packages, "package");
    else if (*purge)
        return command_execute("purge", "-Rn", packages, "package");
    else if (*remove_only)
        return command_execute("remove-only", "-Rdd", packages, "package");
    else if (*recursive_remove)
        return command_execute("recursive-remote", "-Rsc", packages, "package");
    else if (*search)
        return command_execute("search", "-Ss", packages, "search string");
    else if (*find)
        return command_execute("find", "-F", packages, "search string");
    else if (*upgrade)
        return command_execute("upgrade", "-Su", packages, "package");
    else if (*show)
        return command_execute("show", "-Qi", packages, "package");
    else if (*show_all)
        return command_execute("show-all", "-Si", packages, "package");
    else if (*update)
        return command_execute("update", "-Sy", packages, "", false);
    else if (*force_update)
        return command_execute("force-update", "-Syy", packages, "", false);
    else if (*full_upgrade)
        return command_execute("full-upgrade", "-Syu", packages, "", false);
    else if (*autoclean or *clean)
        return command_execute("autoclean", "-Scc", packages, "", false);
    else if (*list_installed)
        return command_execute("list-installed", "-Qqe", packages, "", false);
    else if (*list_detailed)
        return command_execute("list-detailed", "-Qi", packages, "", false);
       
    if (*help or argc == 1) {
        fmt::println("{}", app.help());
    } else if (*version) {
        fmt::println("{}", fmt::styled(" APTPAC", fmt::emphasis::bold));
        fmt::println("{}", fmt::styled("========", fmt::emphasis::bold));
        fmt::println("A wrapper for paru/pacman for ease of use.");
        fmt::println("This project is a rewrite of Itai Nelken's project in C++ and adds a few features on top of that.");
        fmt::println("I made this project to alleviate my boredom.");
        fmt::println("Version 1.0");

        fmt::println("\nLicence: MIT\nCopyright (c) 2026 bahmoudd");
    }

    if (*autoremove) {
        if (system("test -z \"$(paru -Qdtq)\"") == 0)
            fmt::println("Nothing to autoremove.");
        else if (backend_path == "/usr/bin/paru") 
            return system("/usr/bin/paru -Qdtq | pacman -Rs -");
        else
            return system("/usr/bin/pacman -Qdtq | pacman -Rs -");
    }

    return 0;
}