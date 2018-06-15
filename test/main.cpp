#include "decimal.h"

int main() {
    auto d1 = decimal::decimal<2>{5};
    auto d2 = decimal::decimal<3>{2};
    auto d3 = decimal::decimal<2, unsigned>{9};
    //auto d4 = decimal::decimal<2, double>{9};
    auto d5 = decimal::decimal<2>{8.43};
    //auto d6 = decimal::decimal<2>{"test"};
    return 0;
}
