#pragma once
#include <cstddef>
#include <cstring>
#include <iostream>

class Dream {
    char* text_;
    std::size_t size_;

public:
    explicit Dream(const char* txt) : text_(nullptr), size_(0) {
        std::cout << "[Dream] constructor(const char*)\n";
        if (txt) {
            size_ = std::strlen(txt);
            text_ = new char[size_ + 1];
            std::memcpy(text_, txt, size_ + 1);
        }
    }

    Dream() : text_(nullptr), size_(0) {
        std::cout << "[Dream] default constructor\n";
    }

    Dream(const Dream& other) : text_(nullptr), size_(other.size_) {
        std::cout << "[Dream] copy constructor (deep copy)\n";
        if (other.text_) {
            text_ = new char[size_ + 1];
            std::memcpy(text_, other.text_, size_ + 1);
        }
    }

    Dream(Dream&& other) noexcept : text_(other.text_), size_(other.size_) {
        std::cout << "[Dream] move constructor (steal)\n";
        other.text_ = nullptr;
        other.size_ = 0;
    }

    Dream& operator=(const Dream& other) {
        std::cout << "[Dream] copy assign\n";
        if (this == &other) return *this;
        delete[] text_;
        size_ = other.size_;
        if (other.text_) {
            text_ = new char[size_ + 1];
            std::memcpy(text_, other.text_, size_ + 1);
        } else {
            text_ = nullptr;
        }
        return *this;
    }

    Dream& operator=(Dream&& other) noexcept {
        std::cout << "[Dream] move assign\n";
        if (this == &other) return *this;
        delete[] text_;
        text_ = other.text_;
        size_ = other.size_;
        other.text_ = nullptr;
        other.size_ = 0;
        return *this;
    }

    ~Dream() {
        std::cout << "[Dream] destructor -> delete[] text_\n";
        delete[] text_;
    }

    const char* text() const { return text_ ? text_ : ""; }
    std::size_t size() const { return size_; }
};
