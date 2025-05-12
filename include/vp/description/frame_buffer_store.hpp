#ifndef VP_DESCRIPTION_FRAME_BUFFER_STORE_HPP
#define VP_DESCRIPTION_FRAME_BUFFER_STORE_HPP

#include <string>
#include <unordered_map>

#include <vp/description/frame_buffer_description.hpp>
#include <vp/singleton.hpp>
#include <vp/types.hpp>

namespace vp::desc {

class FrameBufferStore final : public Singleton<FrameBufferStore> {
public:
    FrameBufferDescription *emplace(const std::string &nameOfFrameBuffer);
    void insert(const std::string &nameOfFrameBuffer, FrameBufferDescription &desc);

    const FrameBufferDescription &getDescription(const std::string &nameOfFrameBuffer) const;
    FrameBufferDescription &getDescription(const std::string &nameOfFrameBuffer);

    const FrameBufferDescription &operator[](const std::string &nameOfFrameBuffer) const;
    FrameBufferDescription &operator[](const std::string &nameOfFrameBuffer);

    [[nodiscard]] bool contains(const std::string &nameOfFrameBuffer) const noexcept;
private:
    std::unordered_map<std::string, FrameBufferDescription> m_descriptions;
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_FRAME_BUFFER_STORE_HPP
