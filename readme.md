# Matrixes
- This program helps to do basic operations with matrixes

## Required programs:

-  Cmake version  3.21


# Install and run
```
> git clone git@github.com:MaxGroshev/matrix.git
> mkdir build
> cd build
> cmake ..
> make

```
#### How to find best order for chain multiplication

> ./matrix/mx_order

#### How to mul matrix with best order

> ./matrix/mx_mul

# Tests
Required programs:

- Python
- Google tests


#### How to run unit tests?
```
> ./tests/unit_tests
```
---

#### How to run end to end tests?
Run this command from top project directory
```
> python ./tests/end_to_end_tests/e2e_test.py

```
---

# Test generator
Required programs:
python
```
> python3 ./tests/end_to_end_tests/chain_test_generator.py

```
 - -c  [--count] sets count of matrixes
 - -m[--mode] set mode of generator("o" - generate order; "mxo" - generate order and matrix)
 - -f [--file] sets name of file for data

#### How to run debug mode?
- go to  ./CMakeLists.txt
- change CMAKE_BUILD_TYPE "Release" to "Debug"

---
