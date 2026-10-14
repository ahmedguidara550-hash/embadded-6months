cmake_minimum_required(VERSION 3.16)
project(ringbuf C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wconversion -Werror)

# the library : just ringbuf.c
add_library(ringbuf STATIC src/ringbuf.c)
target_include_directories(ringbuf PUBLIC include)

#the demo program
add_executable(demo app/main.c)
target_link_libraries(demo PRIVATE ringbuf)