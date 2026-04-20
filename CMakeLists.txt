cmake_minimum_required(VERSION 4.1)
project(UGMFGT_15_1_JWesting_P_Factor_Analyser C)

set(CMAKE_C_STANDARD 11)

add_executable(UGMFGT_15_1_JWesting_P_Factor_Analyser main.c
        Compute_RMS.h
        Compute_RMS.c
        io.h
        io.c
        Compute_P2P.c
        Compute_P2P.h
        Compute_P2P.c
        Compute_Offset.c
        Compute_Offset.h)
