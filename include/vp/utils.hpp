#ifndef VP_UTILS_HPP
#define VP_UTILS_HPP

#include <algorithm> 
#include <cctype>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include <fmt/core.h>

namespace vp {

template <typename T>
concept EnumKind = std::is_enum_v<T>;

} // namespace vp

namespace vp::utils {

// Code for trimming comes from: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring

// trim from start (in place)
inline std::string &ltrim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !static_cast<bool>(std::isspace(ch));
    }));
    return str;
}

// trim from end (in place)
inline std::string &rtrim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !static_cast<bool>(std::isspace(ch));
    }).base(), str.end());
    return str;
}

inline std::string &trim(std::string &str) {
    return rtrim(ltrim(str));
}

inline std::string trimCopy(const std::string &str) {
    std::string copy = str;
    rtrim(ltrim(copy));
    return copy;
}

template <typename T>
using StringViewMap = std::unordered_map<std::string_view, T>;

template <typename EnumKind>
struct StringToEnumMap {
    static std::unordered_map<std::string_view, EnumKind> map;
};

template <typename T>
std::unordered_map<std::string_view, T> StringToEnumMap<T>::map = {};

template <typename EnumKind>
std::optional<EnumKind> mapStringToEnumKind(const std::string &input) {
    const auto &map = StringToEnumMap<EnumKind>::map;
    if (auto iter = map.find(input); iter != map.end()) {
        return iter->second;
    }
    return {};
}

template <typename EnumKind>
std::optional<EnumKind> mapStringToEnumKind(const std::string_view &input) {
    const auto &map = StringToEnumMap<EnumKind>::map;
    if (auto iter = map.find(input); iter != map.end()) {
        return iter->second;
    }
    return {};
}

inline bool stringToBool(const std::string &str) {
    if (str == "true") {
        return true;
    }
    if (str == "false") {
        return false;
    }
    throw std::runtime_error(fmt::format("Could not cast '{}' to boolean", str));
}

namespace debug {

template <typename T>
void printVector(const std::vector<T> &vec, const std::string &sep = ", ") {
    std::for_each(vec.begin(), vec.end() - 1, [&sep](const T &item) {
        std::cout << item << sep;
    });
    std::cout << vec.back() << std::endl;
}

} // namespace debug

} // namespace vp::utils

#endif // VP_UTILS_HPP
