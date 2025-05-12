#include <vp/description/frame_buffer_store.hpp>

namespace vp::desc {

FrameBufferDescription *FrameBufferStore::emplace(const std::string &nameOfFrameBuffer) {
}

void FrameBufferStore::insert(const std::string &nameOfFrameBuffer, FrameBufferDescription &desc) {
}

const FrameBufferDescription &FrameBufferStore::getDescription(
    const std::string &nameOfFrameBuffer
) const {

}

FrameBufferDescription &FrameBufferStore::getDescription(const std::string &nameOfFrameBuffer) {

}

const FrameBufferDescription &FrameBufferStore::operator[](
    const std::string &nameOfFrameBuffer
) const {

}

FrameBufferDescription &FrameBufferStore::operator[](const std::string &nameOfFrameBuffer) {

}

bool FrameBufferStore::contains(const std::string &nameOfFrameBuffer) const noexcept {

}

} // namespace vp::desc
