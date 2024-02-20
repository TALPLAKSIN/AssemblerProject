cmake_minimum_required(VERSION 3.23)
project(M1 C)

set(CMAKE_C_STANDARD 90)

add_executable(M1 main.c McrList.h FileMethod.c FileMethod.h OpenMcr.c OpenMcr.h TagList.c TagList.h)
