#include "utils.hpp"

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

namespace {
constexpr std::string_view ALBUM_PATH = "img:/";

constexpr bool isDigitsOnly(std::string_view str) noexcept {
    return std::ranges::all_of(str,
                               [](char c) { return c >= '0' && c <= '9'; });
}

template <size_t ExpectedLen>
[[nodiscard]] bool isValidDigitPath(const fs::directory_entry& entry) noexcept {
    if (!entry.is_directory()) return false;
    const auto filename = entry.path().filename().string();
    return filename.length() == ExpectedLen && isDigitsOnly(filename);
}
}  // namespace

std::string getLastAlbumItem() {
    const std::string albumPath{ALBUM_PATH};
    if (!fs::is_directory(albumPath))
        return "<No album directory: " + albumPath + ">";

    // 找最大的年份目录
    std::string maxYear;
    for (const auto& entry : fs::directory_iterator(albumPath)) {
        if (isValidDigitPath<4>(entry)) {
            const auto path = entry.path().string();
            if (maxYear.empty() || path > maxYear) {
                maxYear = path;
            }
        }
    }
    if (maxYear.empty()) return "<No years in " + albumPath + ">";

    // 找最大的月份目录
    std::string maxMonth;
    for (const auto& entry : fs::directory_iterator(maxYear)) {
        if (isValidDigitPath<2>(entry)) {
            const auto path = entry.path().string();
            if (maxMonth.empty() || path > maxMonth) {
                maxMonth = path;
            }
        }
    }
    if (maxMonth.empty()) return "<No months in " + maxYear + ">";

    // 找最大的日期目录
    std::string maxDay;
    for (const auto& entry : fs::directory_iterator(maxMonth)) {
        if (isValidDigitPath<2>(entry)) {
            const auto path = entry.path().string();
            if (maxDay.empty() || path > maxDay) {
                maxDay = path;
            }
        }
    }
    if (maxDay.empty()) return "<No days in " + maxMonth + ">";

    // 找最大的文件
    std::string maxFile;
    for (const auto& entry : fs::directory_iterator(maxDay)) {
        if (entry.is_regular_file()) {
            const auto path = entry.path().string();
            if (maxFile.empty() || path > maxFile) {
                maxFile = path;
            }
        }
    }
    if (maxFile.empty()) return "<No screenshots in " + maxDay + ">";

    return maxFile;
}

size_t filesize(std::string_view path) {
    std::ifstream f(path.data(), std::ios::binary | std::ios::ate);
    if (!f) return 0;
    return static_cast<size_t>(f.tellg());
}

std::string url_encode(std::string_view value) {
    std::string result;
    result.reserve(value.size() * 3);  // 最坏情况预留

    constexpr std::string_view hexChars = "0123456789ABCDEF";

    for (const unsigned char c : value) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            result.push_back(c);
        } else {
            result.push_back('%');
            result.push_back(hexChars[c >> 4]);
            result.push_back(hexChars[c & 0x0F]);
        }
    }

    return result;
}
