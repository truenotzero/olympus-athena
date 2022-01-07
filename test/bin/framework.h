#include <stdio.h>

/*
 * Declare a test
 * Return value:
 * 0 = Pass
 * Other = Fail
 */
typedef int (*test_func_t)();

struct test {
  char *name;
  test_func_t f;
};

#define REGISTER_TESTS()                                                       \
  struct test *register_tests() {                                              \
    static struct test tests[] = {

#define TEST(t) {#t, &t},

#define END_TESTS()                                                            \
  { "", 0 }                                                                    \
  }                                                                            \
  ;                                                                            \
  return tests;                                                                \
  }

/*
 * Do initialization before executing tests
 */
void init();

/*
 * Register all tests to run here
 * Do not use this function directly!
 * Do it like so:
 * REGISTER_TESTS()
 * TEST(test_1)
 * .
 * .
 * .
 * TEST(test_n)
 * END_TESTS()
 */
struct test *register_tests();
void end();

int main(int argc, char *argv[]) {
  init();
  struct test *tests = register_tests();

  int num_tests;
  for (num_tests = 0; tests[num_tests].f; ++num_tests)
    ;

  int ret = 0;
  for (int i = 0; tests[i].f; ++i) {
    printf("[%02d/%02d] %s\t=> ", i + 1, num_tests, tests[i].name);
    int t = tests[i].f();
    if (t == 0) {
      printf("Pass!\n");
    } else {
      printf("Fail (%d)\n", t);
      ret = t;
      break;
    }
  }

  end();
  return ret;
}