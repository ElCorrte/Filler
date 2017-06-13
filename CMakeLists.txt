cmake_minimum_required(VERSION 3.7)
project(filler)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES filler.c filler.h main.c libft/get_next_line/get_next_line.c libft/ft_atoi.c libft/ft_strchr.c)
add_executable(filler ${SOURCE_FILES})
target_link_libraries(filler ${CMAKE_SOURCE_DIR}/libft.a)