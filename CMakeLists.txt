cmake_minimum_required(VERSION 3.16)
project(LitePdfLib)

# Setup the Targoman CMake build system
include(./3rdParty/TargomanCMake/targoman.cmake)
tg_setup_buildsystem_paths()

# Global compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

tg_add_library(dla
    STATIC
    libsrc/dla.cpp
)
tg_add_library_headers(dla
    PUBLIC_HEADER
    libsrc/dla.h
)

tg_process_all_targets()

add_executable(test_DLA
    tests/test.cpp
)
target_link_directories(test_DLA PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/litepdf/lib)
target_link_libraries(test_DLA
    dla
    fpdfapi
    fdrm
    fpdfdoc
    fpdftext
    fxcodec
    fxcrt
    fxge    
)
target_include_directories(test_DLA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/litepdf/include)