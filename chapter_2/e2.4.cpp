#include <cstdio>

enum class Operation {
    Add,
    Subtract,
    Multiply,
    Divide,
};

struct Calculator {
private:
    Operation operation;
public:
    Calculator(Operation op) {
        operation = op;
    }

    int calculate(int a, int b) {
        switch (operation) {
            case Operation::Add:
                return a + b;
                break;
            case Operation::Subtract:
                return a - b;
                break;
            case Operation::Multiply:
                return a*b;
                break;
            case Operation::Divide:
                return a/b;
                break;
            default:
                return 0;
        }
    }
};

int main(void) {
    int a{ 6 };
    int b{ 9 };
    Calculator c_add(Operation::Add);
    Calculator c_sub = { Operation::Subtract };
    Calculator c_mul{ Operation::Multiply };
    Calculator c_div = Calculator(Operation::Divide);
    printf("+(%d, %d) = %d\n", a, b, c_add.calculate(a, b));
    printf("-(%d, %d) = %d\n", a, b, c_sub.calculate(a, b));
    printf("*(%d, %d) = %d\n", a, b, c_mul.calculate(a, b));
    printf("/(%d, %d) = %d\n", a, b, c_div.calculate(a, b));
    return 0;
}
