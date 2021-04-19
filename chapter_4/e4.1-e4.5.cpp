#include <cstddef>
#include <iostream>
#include <sys/time.h>

static unsigned global_id = 0;

struct TimerClass {
private:
    timeval timestamp;
    unsigned id;
    char name;
public:
    // 1. Constructor
    TimerClass(const char a) : id{ global_id }, name{ a }, timestamp{ } {
        global_id++;
        gettimeofday(&timestamp, NULL);

        std::cout << "construct ";
        print(this);
        std::cout << '\n';
    }

    // 2. Destructor
    ~TimerClass() {
        if ('\0' != name) {
            timeval current_time, age;
            gettimeofday(&current_time, NULL);
            timersub(&current_time, &timestamp, &age);

            std::cout << "destroy ";
            print(this);
            std::cout << ", age: ";
            print(age);
            std::cout << '\n';
        }
    }

    // 3. Copy constructor
    TimerClass(const TimerClass& other)
        : id{ global_id },
          name{ other.name },
          timestamp{ other.timestamp } {
        std::cout << "copy-construct ";
        print(this);
        std::cout << "\n\tfrom ";
        print(other);
        std::cout << '\n';

        global_id++;
    }

    // 4. Move constructor
    TimerClass(TimerClass&& other) noexcept : id{ global_id },
                                              name{ other.name },
                                              timestamp{ other.timestamp } {
        std::cout << "move-construct ";
        print(this);
        std::cout << "\n\tfrom ";
        print(other);
        std::cout << '\n';

        global_id++;
        other.name = '\0';
        other.timestamp = {};
    }

    // 3. Copy-assignment operator
    TimerClass& operator=(const TimerClass& other) {
        std::cout << "copy-assign ";
        print(this);
        std::cout << "\n\tfrom ";
        print(other);
        std::cout << '\n';

        if (this == &other) {
            return *this;
        }
        name = other.name;
        timestamp = other.timestamp;
        return *this;
    }

    // 4. Move-assignment operator
    TimerClass& operator=(TimerClass&& other) noexcept {
        std::cout << "move-assign ";
        print(this);
        std::cout << "\n\tfrom ";
        print(other);
        std::cout << '\n';

        if (this == &other) {
            return *this;
        }
        name = other.name;
        timestamp = other.timestamp;
        other.name = '\0';
        other.timestamp = {};
        return *this;
    }

    void print(const TimerClass& tc) const {
        std::cout << "id: " << tc.id << ", name: " << tc.name << ", " << "timestamp: ";
        print(tc.timestamp);
    }

    void print(const TimerClass *tc) const {
        print((const TimerClass&)*tc);
    }

    void print(const timeval& tv) const {
        std::cout << tv.tv_sec  << " s + " << tv.tv_usec << " us";
    }

    void print(void) const {
        print(this);
    }
};

int main() {
    TimerClass tca{ 'a' };
    TimerClass tcb{ 'b' };
    TimerClass tcc{ tca };
    tcb = tca;
    TimerClass tcd{ std::move(tca) };
    TimerClass tce{ 'e' };
    tce = std::move(tcb);
}
