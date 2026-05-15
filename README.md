# aptparu

`aptparu` is a fun side project I'm doing in my spare time to help me alleviate my boredom. I guess it can also be used to people switching from Debian and its forks to Arch and its forks, and anyone who is switching to Linux and is using an Arch-based distro.

It is a wrapper for pacman/paru and works about the same as the `apt` package. 

This project is inspired by [Itai Nelken's repo](https://github.com/Itai-Nelken/aptpac). I challenged myself to rewrite his entire codebase in C++.

This project is written solely in C++.

## Note

This project is not affiliated with the aptpac repo or any other similarly-named projects in any way. 

## Planned usage

```
USAGE
    aptpac [option] [package]
    EXAMPLE: aptparu search clang

AVAILABLE OPTIONS
    install
        Install a package
    install-local
        Install a local package
    remove
        Remove a package
    purge
        Removes a package and prevents the creation of backup configuration files*
    search
        Search for a package
    find
        Find an installed package
    update
        Updates lists of available packages but does not install/update any packages
    upgrade
        Updates a local package
    full-upgrade
        Update + Upgrade
    autoclean
        Cleans up all local caches
    clean
        Same as autoclean
    autoremove  
        Removes orphaned* packages
    show 
        Shows information about a package that is installed
    show-all
        Shows information about a package that may not be installed
    list-installed
        Lists all installed packages
    list-detailed
        Lists all installed packages in great detail
    help 
        Shows this help
    version 
        Shows version and about information
    

options are not case-sensitive 

* - Orphaned packages are packages that were installed to satisfy the dependencies
of another application and are now no longer needed as dependencies were changed 
or the package(s) needing them were removed.
```

## Planned configs

None yet, unfortunately. I plan to have some debug mode.

## Installation

First, install the necessary packages to compile aptparu
```
pacman -S cmake base-devel git gcc
```

Then, clone the repo
```
$ git clone https://github.com/bahmoudd/aptparu/
```

Enter the directory and create a separate build directory
```
$ cd aptparu && mkdir build && cd build
```

Then, compile the package:
```
$ cmake -DCMAKE_BUILD_TYPE=Release .. && make
```

Then, install it:
```
make install
```

Make sure not to delete the build directory so you can uninstall later on if you wish.

## Uninstallation

First, enter the build directory:
```
$ cd ~/aptparu/build
```

Then uninstall:
```
make uninstall
```

Clean up residue folders:
```
rm -rf ~/aptparu
```