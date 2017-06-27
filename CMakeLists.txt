cmake_minimum_required(VERSION 3.7)
project(filler)

set(CMAKE_C_STANDARD 99)

file(GLOB filler_SRC "*.c" "*.h" "libft/*.c" "libft/*.h" "libft/ft_printf/*.c" )
add_executable(filler ${filler_SRC})
target_link_libraries(filler ${CMAKE_SOURCE_DIR}/libft.a)