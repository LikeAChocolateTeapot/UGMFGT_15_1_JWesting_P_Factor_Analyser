cmake_minimum_required(VERSION 4.1)
project(UGMFGT_15_1_JWesting_P_Factor_Analyser C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(UGMFGT_15_1_JWesting_P_Factor_Analyser
    main.c
    Waveform_Analysis/Compute_RMS.c
    Waveform_Analysis/Compute_P2P.c
    Waveform_Analysis/Compute_Offset.c
    IO_And_Logs/io.c
    IO_And_Logs/Power_Log_Extractor.c
        Waveform_Analysis/clip_detection.c
        Waveform_Analysis/clip_detection.h
)

target_include_directories(UGMFGT_15_1_JWesting_P_Factor_Analyser PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Waveform_Analysis
    ${CMAKE_SOURCE_DIR}/IO_And_Logs
)