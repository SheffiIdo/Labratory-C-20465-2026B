cmake_minimum_required(VERSION 4.1)
project(Labratory_C C)

set(CMAKE_C_STANDARD 90) # This mimics the -ansi flag
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

add_executable(remove_blanks maman11/remove_blanks/remove_blanks.c)
add_executable(turn_on maman11/turn_on/turn_on.c)
add_executable(mycomp maman22/mycomp/mycomp.c maman22/mycomp/complex.c
        maman22/mycomp/mycomp.h)
target_link_libraries(mycomp m)