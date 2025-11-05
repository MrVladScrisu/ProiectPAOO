#include "Dream.h"
#include <iostream>

int main() {
    std::cout << "=== Proof of Concept: VISE ===\n";

    //Instantiem vis
    Dream v1("Am visat ca zbor peste o mare cu valuri.");

    //Copy constructor proof
    Dream v2 = v1;

    //Move constructor proof
    Dream v3 = std::move(v1); // v1 devine gol, v3 preia resursele lui v1

    std::cout << "v2: " << v2.text() << " (size=" << v2.size() << ")\n";
    std::cout << "v3: " << v3.text() << " (size=" << v3.size() << ")\n";
    std::cout << "v1 (dupa move): \"" << v1.text() << "\" (size=" << v1.size() << ")\n";

    std::cout << "=== Sfarsit POC ===\n";
    return 0;
}
