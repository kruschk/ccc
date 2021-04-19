#include <cstdio>

short read_from(const char *const buf,
                const size_t length,
                const size_t index) {
    if (index < length) {
        return buf[index];
    } else {
        return -1;
    }
}

bool write_to(char *const buf,
              const size_t length,
              const size_t index,
              const char c) {
    if (index < length) {
        buf[index] = c;
        return true;
    } else {
        return false;
    }
}

int main() {
    char lower[] = "abc?e";
    char upper[] = "ABC?E";
    char *upper_ptr = upper; // Equivalent: &upper[0]
    size_t lower_length = sizeof lower/sizeof lower[0];
    size_t upper_length = sizeof upper/sizeof upper[0];

    printf("lower_length: %lu\n", lower_length);
    printf("upper_length: %lu\n", upper_length);

    printf("result: %d\n", write_to(lower, lower_length, 3, 'd'));
    printf("result: %d\n", write_to(upper_ptr, upper_length, 3, 'D'));

    char letter_d = read_from(lower, lower_length, 3);
    char letter_D = read_from(upper_ptr, upper_length, 3);

    printf("lower: %s\nupper: %s\n", lower, upper);

    printf("result: %d\n", write_to(lower, lower_length, 6, 'g'));
    printf("result: %d\n", write_to(lower, lower_length, 7, 'g'));
}
