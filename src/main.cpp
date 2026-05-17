#include <iostream>
#include <fmt/base.h>
#include <string_view>
#include <argparse/argparse.hpp>

using std::string;
using argparse::ArgumentParser;

inline constexpr std::string_view backend_path = BACKEND_PATH;
inline constexpr bool debug_mode = DEBUG_MODE;

int main(int argc, char** argv) {
    if (debug_mode) {
        fmt::println("Debug mode activated.");
        fmt::println("Using path: {0}", backend_path);
    }

    ArgumentParser program("aptparu");
    
    ArgumentParser install_command("install");
    ArgumentParser install_local_command("install-local");
    ArgumentParser remove_command("remove");
    ArgumentParser purge_command("purge");
    ArgumentParser find_command("find");
    ArgumentParser update_command("update");
    ArgumentParser upgrade_command("upgrade");
    ArgumentParser full_upgrade_command("full-upgrade");
    ArgumentParser autoclean_command("autoclean");
    ArgumentParser clean_command("clean");
    ArgumentParser autoremove_command("autoremove");
    ArgumentParser list_installed_command("list-installed");
    ArgumentParser show_command("show");
    ArgumentParser show_all_command("show-all");
    ArgumentParser list_detailed_command("list-detailed");
    ArgumentParser help_command("help");
    ArgumentParser version_command("version");
    
    install_command.add_description("Install a package");
    install_command.add_argument("packages")
                   .help("Packages to be installed")
                   .remaining();

    install_local_command.add_description("Install a local package");
    install_local_command.add_argument("packages")
                   .help("Local packages to be installed")
                   .remaining();

    remove_command.add_description("Remove a package");
    remove_command.add_argument("packages")
                   .help("Packages to be removed")
                   .remaining();

    purge_command.add_description("Removes a package and prevents the creation of backup configuration files");
    purge_command.add_argument("packages")
                 .help("Packages to be purged")
                 .remaining(); 
 
    find_command.add_description("Find an installed package");
    find_command.add_argument("packages")
                 .help("Packages to be found")
                 .remaining();
 
    update_command.add_description("Updates lists of available packages but does not install/update any packages");
    
    upgrade_command.add_description("Updates a local package");
    upgrade_command.add_argument("packages")
                 .help("Packages to be purged")
                 .remaining();
    
    full_upgrade_command.add_description("Update + Upgrade");
    autoclean_command.add_description("Cleans up all local caches");
    clean_command.add_description("Same as autoclean");
    autoremove_command.add_description("Removes all orphaned packages");
    list_installed_command.add_description("Lists all installed packages");
    list_detailed_command.add_description("Lists all installed packages in great detail");
    help_command.add_description("Shows this help");
    version_command.add_description("Shows version and about information");

    show_command.add_description("Shows information about a package that is installedj");
    show_command.add_argument("packages")
                 .help("Packages to be shown information on")
                 .remaining();
    
    show_all_command.add_description("Shows information about a package that may not being installed");
    show_all_command.add_argument("packages")
                 .help("Packages to be shown information on")
                 .remaining();

    program.add_epilog("options are case-sensitive\n\n* - Orphaned packages are packages that were installed to satisfy the\n\
dependencies of another application and are now no longer needed as dependencies\n\
were changed or the package(s) needing them were removed.");
    
    program.add_subparser(install_command);
    program.add_subparser(install_local_command);
    program.add_subparser(remove_command);
    program.add_subparser(purge_command);
    program.add_subparser(find_command);
    program.add_subparser(update_command);
    program.add_subparser(upgrade_command);
    program.add_subparser(full_upgrade_command);
    program.add_subparser(autoclean_command);
    program.add_subparser(clean_command);
    program.add_subparser(autoremove_command);
    program.add_subparser(list_installed_command);
    program.add_subparser(show_command);
    program.add_subparser(show_all_command);
    program.add_subparser(list_detailed_command);
    program.add_subparser(help_command);
    program.add_subparser(version_command);
    
    program.parse_args(argc, argv);
        
    program.add_argument("-h", "--help")
        .action([&program](const std::string& s) {
            std::cout << program.help().str(); // Print custom help
            exit(0);
        })
        .default_value(false)
        .implicit_value(true)
        .help("Show custom help message and exit");
    return 0;
}
