#ifndef VP_RESOURCES_TEXTURE_DESCRIPTION_HPP
#define VP_RESOURCES_TEXTURE_DESCRIPTION_HPP

#include <filesystem>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {

enum class TextureFormat {
    Unknown,
};

enum class TextureKind {
    Unknown,
};

class TextureDescription {
public:
    void setFormat(TextureFormat format) noexcept;
    void setKind(TextureKind kind) noexcept;

    [[nodiscard]] const TextureFormat &getFormat() noexcept;
    [[nodiscard]] const TextureKind &getKind() noexcept;

    [[nodiscard]] bool isValid() const noexcept;
private:
    TextureFormat m_format {TextureFormat::Unknown };
    TextureKind m_kind { TextureKind::Unknown };
    std::filesystem::path m_path;
};

template <>
inline utils::StringViewMap<TextureFormat> utils::StringToEnumMap<TextureFormat>::map = {
};

template <>
inline utils::StringViewMap<TextureKind> utils::StringToEnumMap<TextureKind>::map = {
};

} // namespace vp

#endif // VP_RESOURCES_TEXTURE_DESCRIPTION_HPP
