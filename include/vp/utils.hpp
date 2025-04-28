#ifndef VP_UTILS_HPP
#define VP_UTILS_HPP

#include <algorithm> 
#include <cctype>
#include <unordered_map>
#include <string>
#include <optional>

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
using StringMap = std::unordered_map<std::string, T>;

template <typename EnumKind>
struct StringToEnumMap {
    static std::unordered_map<std::string, EnumKind> map;
};

template <typename T>
std::unordered_map<std::string, T> StringToEnumMap<T>::map = {};

template <typename EnumKind>
std::optional<EnumKind> mapStringToEnumKind(const std::string &input) {
    const auto &map = StringToEnumMap<EnumKind>::map;
    if (auto iter = map.find(input); iter != map.end()) {
        return iter->second;
    }
    return {};
}

} // namespace vp::utils

#endif // VP_UTILS_HPP
