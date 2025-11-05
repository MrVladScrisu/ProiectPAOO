# DreamPOC (OOP – Proof of Concept)
- Încapsulare (membri private + getteri)
- Inițializatori în constructori
- Destructor care eliberează heap
- Copy constructor (deep copy)
- Move constructor (steal)

## Build (din directorul principal)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/DreamPOC
