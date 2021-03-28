#pragma once
#include <string>
#include <cassert>

inline constexpr size_t codepointSize(uint8_t lb) {
    if ((lb & 0x80) == 0) // lead bit is zero, must be a single ascii
        return 1;
    if ((lb & 0xE0) == 0xC0) // 110x xxxx
        return 2;
    if ((lb & 0xF0) == 0xE0) // 1110 xxxx
        return 3;
    if ((lb & 0xF8) == 0xF0) // 1111 0xxx
        return 4;

    assert(("Can't detect length of codepoint", false));
    return 1; // To avoid getting stuck in an endless loop.
}

inline size_t utf8_strlen(std::string::const_iterator begin, std::string::const_iterator end) {
    size_t length{0};

    while (begin != end) {
        const size_t cpSize = codepointSize(*begin);
        ++length;
        std::advance(begin, cpSize);
    }

    return length;
}

inline auto utf8_next(std::string::const_iterator it) {
    const size_t cpSize = codepointSize(*it);
    return it+cpSize;
}