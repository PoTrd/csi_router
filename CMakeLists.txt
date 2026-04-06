cmake_minimum_required(VERSION 3.5)
add_compile_options(-fdiagnostics-color=always)
set(MINIMAL_BUILD ON)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(csi_router)
