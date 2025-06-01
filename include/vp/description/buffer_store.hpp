#ifndef VP_DESCRIPTION_BUFFER_STORE_HPP
#define VP_DESCRIPTION_BUFFER_STORE_HPP

#include <vp/description/buffer_description.hpp>
#include <vp/description/description_store.hpp>
#include <vp/singleton.hpp>
#include <vp/types.hpp>

namespace vp::desc {

class BufferStore final :
    public Singleton<BufferStore>,
    public DescriptionStore<BufferDescription> {
public:
    friend Singleton<BufferStore>;

    BufferStore(const BufferStore &other) = delete;
    BufferStore(BufferStore &&other) noexcept = delete;
    BufferStore& operator=(const BufferStore &other) = delete;
    BufferStore& operator=(BufferStore &&other) = delete;
    ~BufferStore() override = default;
private:
    BufferStore() = default;
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_BUFFER_STORE_HPP
