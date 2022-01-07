Part of the Olympus project.
============================

Athena, the Greek goddess of wisdom.

Athena provides a testing framework.

Usage
=====
1. Create a file in `bin/`.
2. `#include` the source file you want to test in said file.
3. Define the special functions `init()` and `end()`
4. Create test functions: Each test function has the signature `int test()`
5. Register the test functions like so:
```c
REGISTER_TESTS()
    TEST(test_1)
    .
    .
    .
    TEST(test_n)
END_TESTS()
```
6. Run the tests by executing `./test.sh`