cmake_minimum_required(VERSION 3.30)
project(fed LANGUAGES C)

set(CMAKE_C_STANDARD_23 ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -pedantic
)

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE 
        PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)