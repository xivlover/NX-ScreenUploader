file(GLOB_RECURSE
        ALL_CXX_SOURCE_FILES
        *.c *.cpp *.cc *.h *.hpp)

find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    add_custom_target(
            clang_format
            COMMAND /usr/bin/clang-format
            -i
            -style=file
            ${ALL_CXX_SOURCE_FILES})
endif ()
