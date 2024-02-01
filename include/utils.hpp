#pragma once


#include <raylib.h>
#include <iostream>
#include <math.h>
#include "objects.hpp"


inline Vector2 operator + (const Vector2& v1, const Vector2& v2) {
    return { v1.x + v2.x, v1.y + v2.y };
}

inline Vector2 operator - (const Vector2& v1, const Vector2& v2) {
    return { v1.x - v2.x, v1.y - v2.y };
}

inline Vector2 operator -= (const Vector2& v1, const Vector2& v2) {
    return { v1.x - v2.x, v1.y - v2.y };
}

inline Vector2 operator / (const Vector2& v1, float f) {
    return { v1.x / f, v1.y / f };
}

template <typename T>
inline void DEB(T m) {
    std::cout << m << "\n";
}

inline void DEB(const Vector2& m) {
    std::cout << m.x << " " << m.y << "\n";
}

namespace utils {

inline float length(const Vector2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

inline float distance(const Vector2& v1, const Vector2& v2) {
    return std::sqrt(
        (v1.x - v2.x) * (v1.x - v2.x) + 
        (v1.y - v2.y) * (v1.y - v2.y)
    );
}

inline Vector2 abs(const Vector2& v) {
    return {
        std::abs(v.x),
        std::abs(v.y)
    };
}

inline Vector2 max(const Vector2& v, const float& d) {
    return {
        std::max(v.x, d),
        std::max(v.y, d)
    };
}

inline float min(const float a, const float b) {
    if (a > b) return b;
    return a;
}

}
