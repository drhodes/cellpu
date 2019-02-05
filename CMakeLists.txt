cmake_minimum_required(VERSION 3.9.0)
project(cellpu) # set the project name

add_definitions("-std=c++17") # is this for any flags?

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # where is cmake_binary_dir?
conan_basic_setup() # what is a basic setup?


file(GLOB cellpu_SRC
    "./src/*.hh"
    "./src/*.cc"
    )

add_executable(sim ${cellpu_SRC})
target_link_libraries(sim ${CONAN_LIBS}) # where is this defined?
