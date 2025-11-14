#include "config.hpp"

#include <minIni.h>

#include "project.h"

// Configuration file path
static constexpr const char* CONFIG_PATH =
    "sdmc:/config/" APP_TITLE "/config.ini";

// Helper: read a string value with an upper bound of maxlen characters
static std::string ini_get_string(const char* section, const char* key,
                                  const char* default_value,
                                  size_t maxlen = 256) {
    std::string result(maxlen, '\0');
    int len = ini_gets(section, key, default_value, result.data(), maxlen,
                       CONFIG_PATH);
    if (len > 0) {
        result.resize(len);
    } else {
        result = default_value;
    }
    return result;
}

bool Config::refresh() {
    // Read upload destination toggles
    m_telegramEnabled = ini_getbool("general", "telegram", 1, CONFIG_PATH) != 0;
    m_ntfyEnabled = ini_getbool("general", "ntfy", 0, CONFIG_PATH) != 0;

    // Read Telegram configuration from [telegram] section
    m_telegramBotToken = ini_get_string("telegram", "bot_token", "undefined");
    m_telegramChatId = ini_get_string("telegram", "chat_id", "undefined");
    m_telegramApiUrl =
        ini_get_string("telegram", "api_url", "https://api.telegram.org");
    m_telegramUploadScreenshots =
        ini_getbool("telegram", "upload_screenshots", 1, CONFIG_PATH) != 0;
    m_telegramUploadMovies =
        ini_getbool("telegram", "upload_movies", 1, CONFIG_PATH) != 0;

    // Read Telegram upload mode: compressed, original, or both (default:
    // compressed)
    std::string telegramUploadModeStr =
        ini_get_string("telegram", "upload_mode", "compressed");
    if (telegramUploadModeStr == "compressed") {
        m_telegramUploadMode = UploadMode::Compressed;
    } else if (telegramUploadModeStr == "original") {
        m_telegramUploadMode = UploadMode::Original;
    } else if (telegramUploadModeStr == "both") {
        m_telegramUploadMode = UploadMode::Both;
    } else {
        m_telegramUploadMode = UploadMode::Compressed;  // Fallback default
    }

    // Read Ntfy configuration from [ntfy] section
    m_ntfyUrl = ini_get_string("ntfy", "url", "https://ntfy.sh");
    m_ntfyTopic = ini_get_string("ntfy", "topic", "");
    m_ntfyToken = ini_get_string("ntfy", "token", "");
    m_ntfyPriority = ini_get_string("ntfy", "priority", "default");
    m_ntfyUploadScreenshots =
        ini_getbool("ntfy", "upload_screenshots", 1, CONFIG_PATH) != 0;
    m_ntfyUploadMovies =
        ini_getbool("ntfy", "upload_movies", 0, CONFIG_PATH) != 0;

    m_keepLogs = ini_getbool("general", "keep_logs", 0, CONFIG_PATH) != 0;

    // Read check interval (seconds), default 3s, minimum 1s
    m_checkIntervalSeconds =
        (int)ini_getl("general", "check_interval", 3, CONFIG_PATH);
    if (m_checkIntervalSeconds < 1) {
        m_checkIntervalSeconds = 1;
    }

    return true;
}

std::string_view Config::getTelegramBotToken() const noexcept {
    return m_telegramBotToken;
}

std::string_view Config::getTelegramChatId() const noexcept {
    return m_telegramChatId;
}

std::string_view Config::getTelegramApiUrl() const noexcept {
    return m_telegramApiUrl;
}

std::string_view Config::getNtfyUrl() const noexcept { return m_ntfyUrl; }

std::string_view Config::getNtfyTopic() const noexcept { return m_ntfyTopic; }

std::string_view Config::getNtfyToken() const noexcept { return m_ntfyToken; }

std::string_view Config::getNtfyPriority() const noexcept {
    return m_ntfyPriority;
}
