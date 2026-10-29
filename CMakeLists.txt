cmake_minimum_required(VERSION 3.20)

project(RTDA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rtda_core
    src/core/Signal.cpp
    src/core/Dataset.cpp
    src/analysis/Statistics.cpp
    src/io/CSVImporter.cpp
    )
target_include_directories(rtda_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

add_executable(rtda
    src/app/main.cpp
    )

target_link_libraries(rtda
    PRIVATE
        rtda_core
        )

