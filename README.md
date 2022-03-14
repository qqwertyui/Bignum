## Library for basic integer calculations

### 1. Description
Small library for integer calculations. 
At this moment it suports few basic operations which are:
- addition
- subtraction
- multiplication
- division
- modulo
- power
- square root
- absolute value
Despite memory limitations there is no limit of number size, 
integers of arbitrary length can be used.

### 2. Requirements
- C++17 compiler
- doctest (if you want to build UTs)

### 3. Build
- git clone git@github.com:qqwertyui/Bignum.git ; cd Bignum
- mkdir build ; cd build
- cmake .. -G"Unix Makefiles"     # use generator depending on your preferences
- make                            # as mentioned higher
- ./ut/TestBignumOperations.exe   # Run tests if necessary

