#include <string>
#include <iostream>

#include "../lib/mbox.hpp"
#include "../lib/mlog.hpp"

// Assume that user's terminal can be resized to 100x25;
constexpr uint16_t WIDTH = 100;
constexpr uint16_t HEIGHT = 25;
extern bool ignore_size = false;

struct state {
};

// Initialize the emulator
state setup(std::string path) {

}

void advance(state &state) {

}