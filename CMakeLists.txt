cmake_minimum_required(VERSION 4.1)
project(UGMFGT_15_1_JWesting_P_Factor_Analyser C)

set(CMAKE_C_STANDARD 11)

add_executable(UGMFGT_15_1_JWesting_P_Factor_Analyser main.c
        Power_Log_Extraction.h
        Power_Log_StructDef.h)
