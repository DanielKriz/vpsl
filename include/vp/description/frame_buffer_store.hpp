#ifndef VP_DESCRIPTION_FRAME_BUFFER_STORE_HPP
#define VP_DESCRIPTION_FRAME_BUFFER_STORE_HPP

#include <vp/description/description_store.hpp>
#include <vp/description/frame_buffer_description.hpp>
#include <vp/singleton.hpp>
#include <vp/types.hpp>

namespace vp::desc {

class FrameBufferStore final : 
    public Singleton<FrameBufferStore>,
    public DescriptionStore<FrameBufferDescription> {
public:
    friend Singleton<FrameBufferStore>;

    FrameBufferStore(const FrameBufferStore &other) = delete;
    FrameBufferStore(FrameBufferStore &&other) noexcept = delete;
    FrameBufferStore& operator=(const FrameBufferStore &other) = delete;
    FrameBufferStore& operator=(FrameBufferStore &&other) = delete;
    ~FrameBufferStore() override = default;

private:
    FrameBufferStore() = default;
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_FRAME_BUFFER_STORE_HPP
