#pragma once

#include <cstddef>
#include <cstdint>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

using usize = size_t;

// #ifdef __has_include
//     #if __has_include(<array>)
//         #include <array>
//         template<typename T, usize N>
//         using Array = std::array<T, N>;
//     #endif
// #endif

// #ifdef __has_include
//     #if __has_include(<string>)
//         #include <string>
//         using String = std::string;
//     #endif
// #endif

// #ifdef __has_include
//     #if __has_include(<vector>)
//         #include <vector>
//         template<typename T>
//         using Vector = std::vector;
//     #endif
// #endif
#define Array std::array
#define String std::string
#define Vector std::vector