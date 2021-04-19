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
    Calculator calculator{ Operation::Subtract };
    printf("f(%d, %d) = %d\n", a, b, calculator.calculate(a, b));
    return 0;
}
