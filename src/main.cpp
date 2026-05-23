#include <iostream>
#include <string_view>
#include <vector>
#include <cstdlib>

#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#include <CLI/CLI.hpp>

#include "./main.hpp"

using std::string;
using std::string_view;

inline constexpr string_view backend_path = BACKEND_PATH;
inline constexpr bool debug_mode = DEBUG_MODE;

int main(int argc, char** argv) {
    if (debug_mode) {
        log_info("Debug mode activated.");
        log_debug(fmt::format("Macro BACKEND_PATH set to: {}", backend_path));
    }

    std::vector<string> packages = {};
    std::vector<string> ignore_packages = {};

    CLI::App app{"A wrapper for paru/pacman for ease of use"};
    CLI::App* download = app.add_subcommand("download", "Downloads a package without installing it");
    CLI::App* install = app.add_subcommand("install", "Install a package");
    CLI::App* install_local = app.add_subcommand("install-local", "Install a local package");
    CLI::App* remove = app.add_subcommand("remove", "Remove a package");
    CLI::App* purge = app.add_subcommand("purge", "Removes a package, dependencies not required by any other package, and prevents the creation of backup configuration files");
    CLI::App* remove_group = app.add_subcommand("remove-group", "Removes a package group e.g. gnome");
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
    CLI::App* list = app.add_subcommand("list", "Same as list-installed");
    CLI::App* list_detailed = app.add_subcommand("list-detailed", "Lists all installed packages in great detail");
    CLI::App* help = app.add_subcommand("help", "Shows this help")->silent();
    CLI::App* version = app.add_subcommand("version", "Shows version and about information")->silent();
    
    if (debug_mode)
        log_debug("Successfully initialised application and subcommands!");
    
    download->add_option("packages", packages);
    install->add_option("packages", packages);
    install_local->add_option("packages", packages);
    remove->add_option("packages", packages);
    purge->add_option("packages", packages);
    remove_group->add_option("packages", packages);
    remove_only->add_option("packages", packages);
    recursive_remove->add_option("packages", packages);
    search->add_option("packages", packages);
    find->add_option("packages", packages);
    upgrade->add_option("packages", packages);
    show->add_option("packages", packages);
    show_all->add_option("packages", packages);
    app.footer("Errors may be styled differently depending on whether the error is handled by pacman/paru or aptparu. \
        Additionally, autoremove may need to be run with sudo even with paru installed because of some weird bug with paru.");
    
    app.allow_windows_style_options(false);
    
    install->add_option("--ignore", ignore_packages, "Ignore certain packages when installing/upgrading");
    upgrade->add_option("--ignore", ignore_packages, "Ignore certain packages when installing/upgrading");
    full_upgrade->add_option("--ignore", ignore_packages, "Ignore certain packages when installing/upgrading");

    CLI11_PARSE(app, argc, argv);
    if (debug_mode) {
        log_debug(fmt::format("packages set to: {}", packages));
        log_debug(fmt::format("ignore_packages set to: {}", ignore_packages));
    } 
    string command = "";
    
    if (*download)
        return command_execute("download", "-Sw", packages, "package");
    else if (*install_local) 
        return command_execute("install-local", "-U", packages, "package");
    else if (*remove) 
        return command_execute("remove", "-Rs", packages, "package");
    else if (*purge)
        return command_execute("purge", "-Rns", packages, "package");
    else if (*remove_group)
        return command_execute("remove-group", "-Rsu", packages, "package");
    else if (*remove_only)
        return command_execute("remove-only", "-Rdd", packages, "package");
    else if (*recursive_remove)
        return command_execute("recursive-remote", "-Rsc", packages, "package");
    else if (*search)
        return command_execute("search", "-Ss", packages, "search string");
    else if (*find)
        return command_execute("find", "-F", packages, "search string");
    else if (*show)
        return command_execute("show", "-Qi", packages, "package");
    else if (*show_all)
        return command_execute("show-all", "-Si", packages, "package");
    else if (*update)
        return command_execute("update", "-Sy", packages, "", false);
    else if (*force_update)
        return command_execute("full-upgrade", "-Syu", packages, "", false);
    else if (*autoclean or *clean)
        return command_execute("autoclean", "-Scc", packages, "", false);
    else if (*list_installed or *list)
        return command_execute("list-installed", "-Qqe", packages, "", false);
    else if (*list_detailed)
        return command_execute("list-detailed", "-Qi", packages, "", false);

    if (*help or argc == 1) {
        fmt::println(stderr,
                    "{} \aNo subcommand provided! (use -h for help)",
                    fmt::styled("ERROR:", fmt::fg(fmt::color::red) | fmt::emphasis::bold));
        return 1;
    } else if (*version) {
        fmt::println("{}", fmt::styled(" APTPAC", fmt::emphasis::bold));
        fmt::println("{}", fmt::styled("========", fmt::emphasis::bold));
        fmt::println("A wrapper for paru/pacman for ease of use.");
        fmt::println("This project is a rewrite of Itai Nelken's project in C++ and adds a few features on top of that.");
        fmt::println("I made this project to alleviate my boredom.");
        fmt::println("Version 1.0");

        fmt::println("\nLicence: MIT\nCopyright (c) 2026 bahmoudd");
    }
    if (*install) {
        string to_run = join_command_and_packages_and_ignore_packages(backend_path, "-S", packages, ignore_packages);
        system(to_run.c_str()); 
    } else if (*upgrade) {
        string to_run = join_command_and_packages_and_ignore_packages(backend_path, "-Su", packages, ignore_packages);
        system(to_run.c_str());
    } else if (*full_upgrade) {
        string to_run = join_command_and_packages_and_ignore_packages(backend_path, "-Syu", packages, ignore_packages);
        system(to_run.c_str());
    } else if (*autoremove) {
        if (backend_path == "/usr/bin/paru") {
            if (system("test -z \"$(paru -Qdtq)\"") == 0)
                fmt::println("Nothing to autoremove.");
            return system("/usr/bin/paru -Qdtq | pacman -Rs -");
        } else {
            if (system("test -z \"$(pacman -Qdtq)\"") == 0)
                fmt::println("Nothing to autoremove.");
            
            return system("/usr/bin/pacman -Qdtq | pacman -Rs -");
        }
    }

    return 0;
}

int command_execute(const string_view& subcommand, 
                    const string& arguments, 
                    const std::vector<string>& packages, 
                    const string& potential_error_cause,
                    bool packages_needed) {
    
    string command = "";
    if (packages.empty() and packages_needed) {
        log_error(fmt::format("'{0}' option passed but no {1}(s) provided!\n", subcommand, potential_error_cause));
                
        return 1;
    }

    if (packages_needed)
        command = fmt::format("{} {} {}", backend_path, arguments, fmt::join(packages, " "));
    else
        command = fmt::format("{} {}", backend_path, arguments);

    if (debug_mode)
        log_debug(fmt::format("Command being run is {}", command));

    return system(command.c_str());
}

void log_error(const string& message) {
    fmt::println(stderr,
                 "{} {}",
                 fmt::styled("ERROR:", fmt::fg(fmt::color::red) | fmt::emphasis::bold),
                 message);
}

void log_debug(const string& message) {
    fmt::println("DEBUG: {}", message);
}

void log_info(const string& message) {
    fmt::println("{} {}",
                 fmt::styled("INFO:", fmt::fg(fmt::color::cyan)),
                 message);
}

string join_command_and_packages_and_ignore_packages(const std::string_view& command,
                                                     const std::string& subcommand, 
                                                     const std::vector<std::string>& packages, 
                                                     const std::vector<std::string>& ignore_packages) {
    string joined_packages = fmt::format("{}", fmt::join(packages, " "));
    string joined_ignore_packages = fmt::format("{}", fmt::join(ignore_packages, " "));
    if (subcommand == "-Syu")
        return fmt::format("{} {} --ignore {}", command, subcommand, joined_ignore_packages);
    if (ignore_packages.empty())
        return fmt::format("{} {} {}", command, subcommand, joined_packages);
    return fmt::format("{} {} {} --ignore {}", command, subcommand, joined_packages, joined_ignore_packages);
}