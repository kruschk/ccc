#include <cstdio>

struct Element {
private:
public:
    Element *previous{};
    Element *next{};
    char prefix[2];
    short operating_number;

    void insert_before(Element *new_element) {
        if (this->previous) {
            this->previous->next = new_element;
        }
        new_element->previous = this->previous;
        new_element->next = this;
        this->previous = new_element;
    }

    void insert_after(Element *new_element) {
        if (this->next) {
            this->next->previous = new_element;
        }
        new_element->previous = this;
        new_element->next = this->next;
        this->next = new_element;
    }
};

int main() {
    Element trooper1, trooper2, trooper3;

    trooper1.prefix[0] = 'T';
    trooper1.prefix[1] = 'K';
    trooper1.operating_number = 421;
    trooper2.prefix[0] = 'F';
    trooper2.prefix[1] = 'N';
    trooper2.operating_number = 2187;
    trooper3.prefix[0] = 'L';
    trooper3.prefix[1] = 'S';
    trooper3.operating_number = 005;

    trooper1.insert_after(&trooper3);
    trooper3.insert_before(&trooper2);

    for (Element *cursor = &trooper1; cursor; cursor = cursor->next) {
        printf("Storm Trooper %c%c-%d\n",
               cursor->prefix[0],
               cursor->prefix[1],
               cursor->operating_number);
    }
    for (Element *cursor = &trooper3; cursor; cursor = cursor->previous) {
        printf("Storm Trooper %c%c-%d\n",
               cursor->prefix[0],
               cursor->prefix[1],
               cursor->operating_number);
    }
}
