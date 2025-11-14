#pragma once

#include <switch.h>

#include <string>
#include <string_view>

enum class UploadMode : uint8_t {
    Compressed = 0,  // Upload only compressed images
    Original = 1,    // Upload only original images
    Both = 2  // Upload both (try compressed first, then original on failure)
};

class Config {
   public:
    static Config& get() noexcept {
        static Config instance;
        return instance;
    }

    [[nodiscard]] bool refresh();

    // General settings
    [[nodiscard]] constexpr int getCheckIntervalSeconds() const noexcept {
        return m_checkIntervalSeconds;
    }
    [[nodiscard]] constexpr bool keepLogs() const noexcept {
        return m_keepLogs;
    }

    // Upload destination toggles
    [[nodiscard]] constexpr bool telegramEnabled() const noexcept {
        return m_telegramEnabled;
    }
    [[nodiscard]] constexpr bool ntfyEnabled() const noexcept {
        return m_ntfyEnabled;
    }

    // Telegram configuration
    [[nodiscard]] std::string_view getTelegramBotToken() const noexcept;
    [[nodiscard]] std::string_view getTelegramChatId() const noexcept;
    [[nodiscard]] std::string_view getTelegramApiUrl() const noexcept;
    [[nodiscard]] constexpr bool telegramUploadScreenshots() const noexcept {
        return m_telegramUploadScreenshots;
    }
    [[nodiscard]] constexpr bool telegramUploadMovies() const noexcept {
        return m_telegramUploadMovies;
    }
    [[nodiscard]] constexpr UploadMode getTelegramUploadMode() const noexcept {
        return m_telegramUploadMode;
    }

    // Ntfy configuration
    [[nodiscard]] std::string_view getNtfyUrl() const noexcept;
    [[nodiscard]] std::string_view getNtfyTopic() const noexcept;
    [[nodiscard]] std::string_view getNtfyToken() const noexcept;
    [[nodiscard]] std::string_view getNtfyPriority() const noexcept;
    [[nodiscard]] constexpr bool ntfyUploadScreenshots() const noexcept {
        return m_ntfyUploadScreenshots;
    }
    [[nodiscard]] constexpr bool ntfyUploadMovies() const noexcept {
        return m_ntfyUploadMovies;
    }

    bool error{false};

   private:
    Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    // Upload destination toggles
    bool m_telegramEnabled{true};
    bool m_ntfyEnabled{false};

    // Telegram configuration
    std::string m_telegramBotToken;
    std::string m_telegramChatId;
    std::string m_telegramApiUrl;
    bool m_telegramUploadScreenshots{true};
    bool m_telegramUploadMovies{true};
    UploadMode m_telegramUploadMode{UploadMode::Compressed};

    // Ntfy configuration
    std::string m_ntfyUrl;
    std::string m_ntfyTopic;
    std::string m_ntfyToken;
    std::string m_ntfyPriority;
    bool m_ntfyUploadScreenshots{true};
    bool m_ntfyUploadMovies{false};

    // General settings
    bool m_keepLogs{false};
    int m_checkIntervalSeconds{
        3};  // Check interval (seconds), default 3s, minimum 1s
};
