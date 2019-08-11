cmake_minimum_required(VERSION 3.13)
project(http C)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER /root/buildroot/output/host/bin/mipsel-linux-gcc)
SET(CMAKE_CXX_COMPILER /root/buildroot/output/host/bin/mipsel-linux-c++filt)
set(CMAKE_EXE_LINKER_FLAGS -static)
#set(CMAKE_EXE_LINKER_FLAGS "-lpthread -ldl")

add_executable(http http/http.h http/http.c main.c http/http_parser.c http/http_parser.h http/krypton.c http/krypton.h main.c http/cJSON.c http/cJSON.h http/api.c http/api.h sqlite/sqlite3.c sqlite/sqlite3.h)