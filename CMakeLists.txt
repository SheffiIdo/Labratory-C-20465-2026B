cmake_minimum_required(VERSION 4.1)
project(Labratory_C C)

set(CMAKE_C_STANDARD 90) # This mimics the -ansi flag
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

add_executable(remove_blanks maman11/remove_blanks/remove_blanks.c)
add_executable(turn_on maman11/turn_on/turn_on.c)
add_executable(mycomp maman22/mycomp/mycomp.c maman22/mycomp/complex.c
        maman22/mycomp/mycomp.h)
target_link_libraries(mycomp m)
add_executable(seek maman23/seek/seek.c maman23/seek/seek.h)

# --- Maman 14: Final Assembler ---
add_executable(assembler
        "maman14/assembler/Source files/assembler.c"
        "maman14/assembler/Source files/preproc.c"
        "maman14/assembler/Source files/first_pass.c"
        "maman14/assembler/Source files/parser.c"
        "maman14/assembler/Source files/symbol_table.c"
        "maman14/assembler/Source files/macro_table.c"
        "maman14/assembler/Source files/errors.c"
        "maman14/assembler/Source files/utils.c"
)

# --- Maman 14: First Pass Tester ---
add_executable(test_first_pass
        "maman14/assembler/Source files/test_driver.c"
        "maman14/assembler/Source files/first_pass.c"
        "maman14/assembler/Source files/parser.c"
        "maman14/assembler/Source files/symbol_table.c"
        "maman14/assembler/Source files/errors.c"
        "maman14/assembler/Source files/utils.c"
)