project('aptparu', 'cpp', default_options : 'cpp_std=c++17')

cmake = import('cmake')

fmt_dep = dependency('fmt')
argparse_proj = cmake.subproject('argparse', cmake_options : '-Wno-dev')
argparse_dep = argparse_proj.dependency('argparse')

buildtype = get_option('buildtype')

if buildtype == 'debug' or buildtype == 'debugoptimized'
    add_project_arguments('-DDEBUG_MODE=true', language : 'cpp')
else
    add_project_arguments('-DDEBUG_MODE=false', language : 'cpp')
endif

paru = find_program('paru', '/usr/bin/paru', required : false)
pacman = find_program('pacman', '/usr/bin/pacman', required : true)

if paru.found()
    add_project_arguments('-DBACKEND_PATH="@0@"'.format(paru.full_path()), language : 'cpp')
else
    add_project_arguments('-DBACKEND_PATH="@0@"'.format(pacman.full_path()), language : 'cpp')
endif

executable('aptparu', 'src/main.cpp', dependencies: [fmt_dep, argparse_dep], install : true)