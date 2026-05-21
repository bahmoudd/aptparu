# aptparu

`aptparu` is a fun side project I'm doing in my spare time to help me alleviate my boredom. I guess it can also be used to people switching from Debian and its forks to Arch and its forks, and anyone who is switching to Linux and is using an Arch-based distro.

It is a wrapper for pacman/paru and works about the same as the `apt` package. 

This project is inspired by [Itai Nelken's repo](https://github.com/Itai-Nelken/aptpac). I challenged myself to rewrite his entire codebase in C++.

This project is written solely in C++.

## Note

Note that paru is an optional dependency. Compiling without paru installed will make aptparu use pacman as a backend. To be able to access the AUR with aptparu, paru must be installed before compiling aptparu.

This project is not affiliated with the aptpac repo or any other similarly-named projects in any way. 

## Planned usage

```

A wrapper for paru/pacman for ease of use

./aptparu [OPTIONS] [SUBCOMMANDS]

OPTIONS:
  -h,     --help              Print this help message and exit

SUBCOMMANDS:
  install                     Install a package
  install-local               Install a local package
  remove                      Remove a package
  purge                       Removes a pacakage and prevents the creation of backup
                              configuration files
  search                      Search for a package
  find                        Find an installed package
  update                      Updates lists of available packages but does not install/update
                              any packages
  force-update                Forces update even if lists of packages appear up to date
  upgrade                     Updates a local package
  full-upgrade                Update + Upgrade
  autoclean                   Cleans up all local caches
  clean                       Same as autoclean
  autoremove                  Removes orphaned packages
  show                        Shows information about a package that is installed
  show-all                    Shows information about a package that may not be installed
  list-installed              Lists all installed packages
  list-detailed               Lists all installed packages in great detail
  help                        Shows this help
  version                     Shows version and about information

Errors may be styled differently depending on whether the error is handled by
pacman/paru or aptparu. Additionally, autoremove may need to be run with sudo
even with paru installed because of some weird bug with paru.
```

## Planned configs

Debug mode! In order to enable debug mode, you must run `meson setup build -Dbuildtype=debugoptimized` instead of the meson command shown below. Nothing for actual configuration files yet :(

## Installation

```
sudo pacman -S meson ninja git gcc
git clone https://github.com/bahmoudd/aptparu.git
cd aptparu
meson setup build -Dbuildtype=release
cd build && ninja && sudo ninja install
```

Make sure not to delete the build directory so you can uninstall later on if you wish.

## Uninstallation

```
cd ~/aptparu/build
sudo ninja uninstall
rm -rf ~/aptparu
```