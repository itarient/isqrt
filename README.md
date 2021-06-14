# isqrt

This is a short example how we can compute the integer part of the square root of an integer value at run time and at compile time.

There are two implementations here. The first uses C++ temlates, the second uses pure C/C++ function style.

These implementations have two foundamental limitations.
1) They consider only unsigned data types (and no other integer types are possible).
2) The largest value from which the integer part of the square root can be computed is (2 * 0x10000) - 1 = (2 * 65536) - 1 = 131071.

# Build

mkdir build ; cd ./build
cmake ..
make

# Run

./isqrt
