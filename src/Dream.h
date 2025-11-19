#pragma once
#include <cstddef>
#include <iostream>

class Dream {
    char* text_;
    std::size_t size_;
    unsigned int id_;
    static unsigned int next_id();

public:
    explicit Dream(const char* txt);
    Dream();

    // COPY
    Dream(const Dream& other);
    Dream& operator=(const Dream& other);

    // MOVE
    Dream(Dream&& other) noexcept;
    Dream& operator=(Dream&& other) noexcept;

    ~Dream();

    const char* text() const;
    std::size_t size() const;
    unsigned int id() const { return id_; }
    void set_text(const char* txt);

    // pentru copy-and-swap
    void swap(Dream& other) noexcept;
};
