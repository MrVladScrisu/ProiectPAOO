#pragma once
#include "Dream.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <optional>
#include <utility>
#include <cstdio>

inline std::string mkdate(int y, int m, int d) {
    char buf[16];
    std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", y, m, d);
    return std::string(buf);
}

class DreamCalendar {
    std::unordered_map<std::string, std::vector<Dream>> days_;
    std::string name_;

    static std::optional<std::size_t> index_of_id(std::vector<Dream>& v, unsigned int id) {
        for (std::size_t i = 0; i < v.size(); ++i) if (v[i].id() == id) return i;
        return std::nullopt;
    }

public:
    explicit DreamCalendar(std::string name) : name_(std::move(name)) {}

    // COPY
    unsigned int add_copy(const std::string& day, const Dream& d) {
        std::cout << "[Calendar:" << name_ << "] add_copy -> push_back(const T&)\n";
        auto& vec = days_[day];
        vec.push_back(d);             // COPY
        return vec.back().id();
    }

    // MOVE
    void add_move(const std::string& day, Dream&& d) {
        std::cout << "[Calendar:" << name_ << "] add_move -> push_back(T&&)\n";
        days_[day].push_back(std::move(d));  // MOVE
    }

    // MOVE
    bool reschedule(const std::string& fromDay, unsigned int dreamId, const std::string& toDay) {
        auto it = days_.find(fromDay);
        if (it == days_.end()) return false;
        auto idx = index_of_id(it->second, dreamId);
        if (!idx) return false;
        std::cout << "[Calendar:" << name_ << "] reschedule id=" << dreamId
                  << " " << fromDay << " -> " << toDay << " (MOVE)\n";
        days_[toDay].push_back(std::move(it->second[*idx])); // MOVE
        it->second.erase(it->second.begin() + *idx);
        return true;
    }

    // COPY (+MOVE în vectorul țintă)
    std::optional<unsigned int> duplicate(const std::string& fromDay, unsigned int dreamId, const std::string& toDay) {
        auto it = days_.find(fromDay);
        if (it == days_.end()) return std::nullopt;
        auto idx = index_of_id(it->second, dreamId);
        if (!idx) return std::nullopt;
        Dream copy = it->second[*idx];        // COPY
        days_[toDay].push_back(std::move(copy)); // MOVE
        return days_[toDay].back().id();
    }

    void list() const {
        std::cout << "== Calendar \"" << name_ << "\" ==\n";
        for (const auto& [day, vec] : days_) {
            std::cout << "  " << day << " (" << vec.size() << ")\n";
            for (const auto& d : vec) {
                std::cout << "    - id=" << d.id() << " | " << d.text()
                          << " (size=" << d.size() << ")\n";
            }
        }
    }
};
