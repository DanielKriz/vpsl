#include <vp/description/buffer_description.hpp>

namespace vp::desc {

std::ostream &operator<<(std::ostream &os, const BufferDescription &desc) {
    return os << "Buffer(" << desc.m_size << ", " << desc.m_bindingPoint << ")";
}

} // namespace vp::desc
