#include "uci.h"
#include <iostream>
#include <sstream>
void uci_loop() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "uci") {
            std::cout << "id name Astra\n";
            std::cout << "id author Kumaran\n";
            std::cout << "uciok\n";
        }
        else if (line == "isready") {
            std::cout << "readyok\n";
        }
        else if (line == "quit") {
            break;
        }
    }
}
