#pragma once

#include <expected>
#include <filesystem>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

[[nodiscard]] std::expected<std::string, std::string> getLastAlbumItem();
[[nodiscard]] size_t filesize(std::string_view path);
[[nodiscard]] std::string url_encode(std::string_view value);
