cmake_minimum_required(VERSION 3.21)

project("main" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    # Forcing MSVC to use utf-8 encoding
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif(WIN32)


file(GLOB_RECURSE PROJECT_SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC "-O2")
endif()

if (DEFINED EMSCRIPTEN)
    #set(CMAKE_EXECUTABLE_SUFFIX ".html")
    add_compile_definitions("__EMSCRIPTEN__")
    target_link_options(${PROJECT_NAME} PRIVATE
        "-sMODULARIZE=1"
        "-sEXPORT_NAME='Main'"
        "-sINVOKE_RUN=0"
        "-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0"
        "-sEXPORTED_FUNCTIONS=['_main']"
        "-sEXPORTED_RUNTIME_METHODS=['callMain', 'ccall', 'cwrap']"
        "-sFORCE_FILESYSTEM=1"
        "-sUSE_SDL=2"
        "-sALLOW_MEMORY_GROWTH=1" 
        "-sASYNCIFY"
        "-O2"
    )
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/index.html
                ${CMAKE_BINARY_DIR}/index.html
        )
else()

    set(extra_flags "")
    if (NOT MSVC)
        set(extra_flags "-mconsole")
    endif()
    
    add_subdirectory("dependencies/SDL")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2-static SDL2main ${extra_flags})
endif()