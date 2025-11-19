#include "DreamCalendar.h"
#include <iostream>

int main() {
    std::cout << "=== Dream Calendar ===\n";

    DreamCalendar cal("Noiembrie");

    Dream v1("Am visat ca zbor peste o mare cu valuri.");
    unsigned int id12 = cal.add_copy(mkdate(2025,11,12), v1); // COPY

    cal.add_move(mkdate(2025,11,13),
                 Dream("Am visat un oras cu oglinzi infinite.")); // MOVE

    cal.list();

    cal.reschedule(mkdate(2025,11,12), id12, mkdate(2025,11,15)); // MOVE

    auto newId = cal.duplicate(mkdate(2025,11,15), id12, mkdate(2025,11,20)); // COPY+MOVE
    if (newId) std::cout << "Duplicated dream newId=" << *newId << "\n";

    cal.list();

    std::cout << "=== End ===\n";
    return 0;
}
