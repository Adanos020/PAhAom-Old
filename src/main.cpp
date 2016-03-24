#include "program/program.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));
    auto p = new rr::Program();

    delete p;
    return 0;
}
