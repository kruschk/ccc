#include <climits>
#include <cstdio>

int absolute_value(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

int main() {
  printf("The absolute value of %d is %d.\n", -10, absolute_value(-10));
  printf("The absolute value of %d is %d.\n", 0, absolute_value(0));
  printf("The absolute value of %d is %d.\n", 10, absolute_value(10));
  printf("The absolute value of %d is %d.\n", INT_MAX, absolute_value(INT_MAX));
  printf("The absolute value of %d is %d.\n", INT_MIN, absolute_value(INT_MIN));
}
