# Matrixes
- This program helps to do basic operations with matrixes

## Required programs:

-  Cmake version  3.21


# Install
```
> git clone git@github.com:MaxGroshev/matrix.git
> mkdir build
> cd build
> cmake ..
> make
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

<h1 align="center">3 LEVEL</a></h1>

### This level is about copy on write matrixes and operations with them

## How to run prog and compare perfomance on test of raising to power of matrix

> ./matrix/mx_lazy


## How to run end to end tests?
Run this command from top project directory
```
> python ./tests/end_to_end_tests/cow_e2e_test.py

```
# Test generator
Required programs:
python
```
> python3 ./tests/end_to_end_tests/mx_power_gen.py

```
 - -p  [--power] sets power of matrixes
 - -s  [--size] sets size of matrixes
 - -dat [--data] sets name of file for data
 - -ans [--ans] sets name of file for answers



<h1 align="center">2 LEVEL</a></h1>

### This level is about actions wirh chains of matrixes and searching of best order of multiplications


## How to find best order for chain multiplication

> ./matrix/mx_order

## How to mul matrix with best order

> ./matrix/mx_mul




## How to run end to end tests?
Run this command from top project directory
```
> python ./tests/end_to_end_tests/e2e_test.py

```
# Test generator
Required programs:
python
```
> python3 ./tests/end_to_end_tests/chain_test_generator.py

```
 - -c  [--count] sets count of matrixes
 - -m[--mode] set mode of generator("o" - generate order; "mxo" - generate order and matrix)
 - -f [--file] sets name of file for data

