#include <vp/description/buffer_store.hpp>

namespace vp::desc {

BufferDescription *BufferStore::emplace(const std::string &nameOfBuffer) {
}

void BufferStore::insert(const std::string &nameOfBuffer, BufferDescription &desc) {
}

const BufferDescription &BufferStore::getDescription(const std::string &nameOfBuffer) const {
}

BufferDescription &BufferStore::getDescription(const std::string &nameOfBuffer) {
}

const BufferDescription &BufferStore::operator[](const std::string &nameOfBuffer) const {
}

BufferDescription &BufferStore::operator[](const std::string &nameOfBuffer) {
}

bool BufferStore::contains(const std::string &nameOfBuffer) const noexcept {
}

} // namespace vp::desc
