Reposity Structure

|--Root
|    | -- Component Circuits
|    | -- DevGroundM
|    | -- LIAM
|    | -- MATLAB
|    | -- assets
|    | -- base-firmware
|    | -- test
|    | LICENSE
|    | README
|    | CONTRIBUTING.md --> THIS FILE

Initial Description:

Component Circuits
    - This subdirectory contains documents with diagrams representing sensor schematics and how they are interfaced with the board

DevGroundM
    - This subdirectory contains the html file for the webpage hosted by the vehicle during initialization and flight setup

LIAM
    - This subdirectory contains the code for the LIAM sub project. Lightweight Intelligent Aerial Mapper is an internal project aimed at developing advanced onboard autonomous flight planning and navigation algorithms for HIVE platform vehicles

assets
    - This subdirectory contains assets related to the development of the drone such as datasheets and research papers used for the Navigation and Control Algorithms

base-firmware
    - This subdirectory contains the main source files for the vehicle firmware. It is an ESP-IDF project built with Cmake. 

test
    - This subdirectory contains all the test and sample code written and tested before addition to main firmware source files. This is where a lot of work is done debugging and it contains a separate ESP-IDF project in order to test drivers on the board.

    |--test
    |   |
    |   | -- PID
    |   | -- PTAM
    |   | -- WingOutputs
    |   | -- atmegaChipTesting
    |   | -- server
    |   |   | --server-test (ESP-IDF Project)
    |   | -- statemachine
    |   | README

