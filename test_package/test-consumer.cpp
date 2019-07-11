#include <decimal.h>

int main() {
    auto a = decimal::decimal<2>{5};
    auto b = decimal::decimal<4>{7.23};
    auto c = a + 5;
    return 0;
}
