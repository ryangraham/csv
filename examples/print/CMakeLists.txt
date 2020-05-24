cmake_minimum_required(VERSION 3.10)
project(print LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(csv CONFIG REQUIRED)
message("csv: ${csv}")
include_directories(${csv})

add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} csv::csv)

add_custom_target(run
    COMMAND print
    DEPENDS print
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
