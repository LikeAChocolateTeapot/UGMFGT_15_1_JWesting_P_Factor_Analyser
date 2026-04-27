# Power Factor Analyser

## Overview

This project is a C-based power quality analysis tool developed in CLion using CMake. It processes CSV waveform data and computes key electrical metrics including RMS voltage/current, peak-to-peak values, DC offset, clipping detection, and voltage tolerance compliance.

The system is designed as a modular signal-processing pipeline with clear separation between data input, analysis, and reporting.

\---

## Features

* CSV-based waveform data ingestion
* RMS calculation (per phase and current)
* Peak-to-peak analysis
* DC offset computation
* Clipping detection (sensor saturation monitoring)
* Voltage tolerance compliance check (±10% of 230V)
* Automated report generation (text file output)

\---

## Project Structure

```
main.c
IO\_And\_Logs/
    io.c
    Power\_Log\_Extractor.c
Waveform\_Analysis/
    Compute\_RMS.c
    Compute\_P2P.c
    Compute\_Offset.c
    clip\_detection.c
```

\---

## Build Instructions (CLion / CMake)

### Requirements

* CMake >= 4.1
* C compiler
* CLion IDE

### CMake Configuration

The project uses the following CMake configuration:

```cmake
cmake\_minimum\_required(VERSION 4.1)
project(UGMFGT\_15\_1\_JWesting\_P\_Factor\_Analyser C)

set(CMAKE\_C\_STANDARD 11)

add\_executable(UGMFGT\_15\_1\_JWesting\_P\_Factor\_Analyser
    main.c
    Waveform\_Analysis/Compute\_RMS.c
    Waveform\_Analysis/Compute\_P2P.c
    Waveform\_Analysis/Compute\_Offset.c
    Waveform\_Analysis/clip\_detection.c
    IO\_And\_Logs/io.c
    IO\_And\_Logs/Power\_Log\_Extractor.c
)

target\_include\_directories(UGMFGT\_15\_1\_JWesting\_P\_Factor\_Analyser PRIVATE
    ${CMAKE\_SOURCE\_DIR}
    ${CMAKE\_SOURCE\_DIR}/Waveform\_Analysis
    ${CMAKE\_SOURCE\_DIR}/IO\_And\_Logs
)
```

### Build Steps

1. Open project in CLion
2. Let CMake configure automatically
3. Build project using Build button or:

```
   cmake --build cmake-build-debug
   ```

\---

## Running the Program

1. Ensure the CSV input file path is correctly set in `main.c`
2. Run the executable
3. Output will be generated as:

```
   Power\_Log\_Results.txt
   ```

4. The report will also automatically open in Notepad (Windows)

\---

## Input Data Format

The program expects a CSV file with the following structure:

```
timestamp,phaseA,phaseB,phaseC,lineCurrent,frequency,powerFactor,thd
```

\---

## Output

The generated report includes:

* RMS values (Phase A, B, C, Current)
* Peak-to-peak values
* DC offset values
* Clipping detection summary
* Voltage tolerance compliance check

\---

## Key Design Notes

### Modular Architecture

The system is divided into:

* IO Layer: file handling and CSV parsing
* Analysis Layer: DSP calculations
* Reporting Layer: formatted output generation

### Function Pointer Usage

RMS computation uses function pointers to generalise signal extraction across multiple channels.

\---

## Author

Joe Westing

## Version

1.0 (Coursework Submission Build)

