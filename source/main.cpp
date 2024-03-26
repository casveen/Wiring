#include <iostream>
#include "wiring.hpp"

int main(int, char**){
    std::cout << "Hello, from Wiring!\n";

    Wiring<4> w;
    w.connect(0,2);
    w.connect(1,3);
    w.connect(2,3);

    const bool* connections = w.get_connections(0);
    for (int i=0; i<4; i++) {
        std::cout << connections[i] << " ";
    }



}
