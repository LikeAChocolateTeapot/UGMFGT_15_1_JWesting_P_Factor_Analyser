# Power Factor Analyser

## Overview

This project is a C-based power quality analysis tool developed in CLion using CMake. It processes CSV waveform data and computes key electrical metrics including RMS voltage/current, peak-to-peak values, DC offset, clipping detection, and voltage tolerance compliance.

The system is designed as a modular signal-processing tool with clear separation between data input, analysis, and reporting.

---

GitHub Link: https://github.com/LikeAChocolateTeapot/UGMFGT_15_1_JWesting_P_Factor_Analyser

---

## Features

* CSV-based waveform data ingestion
* RMS calculation (per phase and current)
* Peak-to-peak analysis
* DC offset computation
* Clipping detection (sensor saturation monitoring)
* Voltage tolerance compliance check (±10% of 230V)
* Automated report generation (text file output)

---

## Project Structure

```
main.c
IO_And_Logs/
    io.c
    Power_Log_Extractor.c
Waveform_Analysis/
    Compute_RMS.c
    Compute_P2P.c
    Compute_Offset.c
    clip_detection.c
```

---

## Build Instructions (CLion / CMake)

### Requirements

* CMake ≥ 4.1
* C compiler (C99 compliant)
* CLion IDE

### CMake Configuration

The project is configured to use the **C99 standard**:

```cmake
cmake_minimum_required(VERSION 4.1)
project(UGMFGT_15_1_JWesting_P_Factor_Analyser C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(UGMFGT_15_1_JWesting_P_Factor_Analyser
    main.c
    Waveform_Analysis/Compute_RMS.c
    Waveform_Analysis/Compute_P2P.c
    Waveform_Analysis/Compute_Offset.c
    Waveform_Analysis/clip_detection.c
    IO_And_Logs/io.c
    IO_And_Logs/Power_Log_Extractor.c
)

target_include_directories(UGMFGT_15_1_JWesting_P_Factor_Analyser PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Waveform_Analysis
    ${CMAKE_SOURCE_DIR}/IO_And_Logs
)
```

### Build Steps

1. Open the project in CLion
2. Allow CMake to configure automatically
3. Build using the IDE or run:

```
cmake --build cmake-build-debug
```

---

## Running the Program

1. Ensure the CSV input file path is correctly set in `main.c`
2. Run the executable
3. Output will be generated as:

```
Power_Log_Results.txt
```

4. The report will also automatically open in Notepad (Windows)

---

## Input Data Format

The program expects a CSV file with the following structure:

```
timestamp,phaseA,phaseB,phaseC,lineCurrent,frequency,powerFactor,thd
```

---

## Output

The generated report includes:

* RMS values (Phase A, B, C, Current)
* Peak-to-peak values
* DC offset values
* Clipping detection summary
* Voltage tolerance compliance check

---

## Key Design Notes

### Modular Architecture

The system is divided into three main layers:

* **IO Layer**: File handling and CSV parsing
* **Analysis Layer**: Signal processing and calculations
* **Reporting Layer**: Formatted output generation

### Standards Compliance

The project is compiled using the **C99 standard** to ensure compatibility with coursework requirements and maintain portability across compilers.

---

## Author

Joe Westing

## Version

1.0 (Coursework Submission Build)
