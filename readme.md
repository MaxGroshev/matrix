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
> ./matrix/matrix

```

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
> python3 ./tests/end_to_end_tests/test_generator.py

```
 - -s  [--size] sets size of squre matrix of elements in test
 - -det[--deteminant] set determinant of matrix
 - -d  [--diaposon] sets diaposon of elems in matrix
 - -t  [--transpose] additionally transpose and change columns of matrix
 - -f [--file] sets name of file for data

#### How to run debug mode?
- go to  ./CMakeLists.txt
- change CMAKE_BUILD_TYPE "Release" to "Debug"

---
