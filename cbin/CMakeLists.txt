cmake_minimum_required(VERSION 3.4)
project(cbin C)
set(CMAKE_C_STANDARD 99)


add_subdirectory("vendor/endianness")

add_library(${PROJECT_NAME} "src/cbin/reader.c" "src/cbin/reader.h" src/cbin/common.h src/cbin/writer.c src/cbin/writer.h)
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_link_libraries(${PROJECT_NAME} PRIVATE endianness)

include(CheckTypeSize)


function(cbin_assert_size name size)
    check_type_size(${name} ${name}_size LANGUAGE C)
    if(NOT ${name}_size EQUAL ${size})
        message(FATAL_ERROR "Size of ${name} is ${${name}_size} but expected ${size}")
    endif()
endfunction()

cbin_assert_size("int8_t" 1)
cbin_assert_size("uint8_t" 1)
cbin_assert_size("int16_t" 2)
cbin_assert_size("uint16_t" 2)
cbin_assert_size("int32_t" 4)
cbin_assert_size("uint32_t" 4)
cbin_assert_size("int64_t" 8)
cbin_assert_size("uint64_t" 8)
cbin_assert_size("float" 4)
cbin_assert_size("double" 8)
