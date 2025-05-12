#ifndef VP_DESCRIPTION_FRAME_BUFFER_DESCRIPTION_HPP
#define VP_DESCRIPTION_FRAME_BUFFER_DESCRIPTION_HPP

#include <ostream>

#include <vp/types.hpp>

namespace vp::desc {

class FrameBufferDescription final {
public:
    friend std::ostream &operator<<(std::ostream &os, const FrameBufferDescription &desc);
private:
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_FRAME_BUFFER_DESCRIPTION_HPP
