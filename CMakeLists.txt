cmake_minimum_required(VERSION 3.30)
project(cscan C)

set(CMAKE_C_STANDARD 11)

add_executable(cscan cscan.c
        scanners/tcp_scan.c
        scanners/tcp_scan.h
        scanners/cscan.h)
