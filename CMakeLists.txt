cmake_minimum_required(VERSION 3.26)
project(todo-app C)

set(CMAKE_C_STANDARD 11)

if(UNIX)
    find_package(PostgreSQL REQUIRED)
    if (PostgreSQL_FOUND)
        include_directories(${PostgreSQL_INCLUDE_DIRS})
        set(PATH_POSTGRESQL ${PostgreSQL_LIBRARIES})
    else()
        message(FATAL_ERROR "PostgreSQL not found. Please make sure it's installed and in your system's PATH.")
    endif()
else()
    message(FATAL_ERROR "Operating system not supported yet.")
endif()

add_executable(todo src/main.c src/psql.c)
target_link_libraries(todo ${PATH_POSTGRESQL})

target_include_directories(todo PRIVATE include)

target_compile_options(todo PRIVATE -Wall -Wextra -Werror)
