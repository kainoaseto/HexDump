cmake_minimum_required(VERSION 3.6)
project(HexDump)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c hexdump.c hexdump.h)
add_executable(HexDump ${SOURCE_FILES})