#ifndef VP_DESCRIPTION_BUFFER_DESCRIPTION_HPP
#define VP_DESCRIPTION_BUFFER_DESCRIPTION_HPP

#include <ostream>
#include <vp/types.hpp>

namespace vp::desc {

class BufferDescription final {
public:
    constexpr explicit BufferDescription(u64 size, u64 bindingPoint)
        : m_size(size), m_bindingPoint(bindingPoint) {
            if (m_size == 0) {
                throw std::runtime_error("The size of buffer cannot be 0");
            }
        };
    friend std::ostream &operator<<(std::ostream &os, const BufferDescription &desc);
    friend constexpr bool operator==(const BufferDescription &lhs, const BufferDescription &rhs) {
        return lhs.m_size == rhs.m_size and lhs.m_bindingPoint == rhs.m_bindingPoint;
    }
private:
    u64 m_size;
    u64 m_bindingPoint;
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_BUFFER_DESCRIPTION_HPP
