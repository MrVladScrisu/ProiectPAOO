#include "Dream.h"
#include <cstring>
#include <utility> 

static unsigned int& id_counter() { static unsigned int c = 1; return c; }
unsigned int Dream::next_id() { return id_counter()++; }

Dream::Dream(const char* txt) : text_(nullptr), size_(0), id_(next_id()) {
    std::cout << "[Dream] constructor(const char*)\n";
    if (txt) {
        size_ = std::strlen(txt);
        text_ = new char[size_ + 1];
        std::memcpy(text_, txt, size_ + 1);
    }
}

Dream::Dream() : text_(nullptr), size_(0), id_(next_id()) {
    std::cout << "[Dream] default constructor\n";
}

// COPY
Dream::Dream(const Dream& other): text_(nullptr), size_(other.size_), id_(other.id_){

    std::cout << "[Dream] copy constructor (deep copy)\n";
    if (other.text_) {
        text_ = new char[size_ + 1];
        std::memcpy(text_, other.text_, size_ + 1);
    }
}

Dream& Dream::operator=(const Dream& other) {
    std::cout << "[Dream] copy assign (copy-and-swap)\n";
    if (this == &other) return *this; // self-assignment check

    Dream temp(other);
    swap(temp); //schimb starea lui this cu copia temporara
    return *this; 
}


// MOVE
Dream::Dream(Dream&& other) noexcept : text_(other.text_), size_(other.size_), id_(other.id_) {
    std::cout << "[Dream] move constructor (steal)\n";
    other.text_ = nullptr; other.size_ = 0; other.id_ = 0;
}

Dream& Dream::operator=(Dream&& other) noexcept {
    std::cout << "[Dream] move assign\n";
    if (this != &other) {
        swap(other); // fur resursele si other ramane cu ce aveam noi
    }
    return *this;
}

void Dream::swap(Dream& other) noexcept {
    using std::swap;
    swap(text_, other.text_);
    swap(size_, other.size_);
    swap(id_,   other.id_); 
}

Dream::~Dream() {
    std::cout << "[Dream] destructor -> delete[] text_\n";
    delete[] text_;
}

const char* Dream::text() const { return text_ ? text_ : ""; }
std::size_t Dream::size() const { return size_; }

void Dream::set_text(const char* txt) {
    delete[] text_; text_ = nullptr; size_ = 0;
    if (txt) {
        size_ = std::strlen(txt);
        text_ = new char[size_ + 1];
        std::memcpy(text_, txt, size_ + 1);
    }
}
