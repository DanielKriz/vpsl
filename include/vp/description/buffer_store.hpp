#ifndef VP_DESCRIPTION_BUFFER_STORE_HPP
#define VP_DESCRIPTION_BUFFER_STORE_HPP

#include <string>
#include <unordered_map>

#include <vp/description/buffer_description.hpp>
#include <vp/singleton.hpp>
#include <vp/types.hpp>

namespace vp::desc {

class BufferStore final : public Singleton<BufferStore> {
public:
    friend Singleton<BufferStore>;

    BufferStore(const BufferStore &other) = delete;
    BufferStore(BufferStore &&other) noexcept = delete;
    BufferStore& operator=(const BufferStore &other) = delete;
    BufferStore& operator=(BufferStore &&other) = delete;
    ~BufferStore() = default;

    BufferDescription *emplace(const std::string &nameOfBuffer);
    void insert(const std::string &nameOfBuffer, BufferDescription &desc);

    const BufferDescription &getDescription(const std::string &nameOfBuffer) const;
    BufferDescription &getDescription(const std::string &nameOfBuffer);

    const BufferDescription &operator[](const std::string &nameOfBuffer) const;
    BufferDescription &operator[](const std::string &nameOfBuffer);

    [[nodiscard]] bool contains(const std::string &nameOfBuffer) const noexcept;

    void clear();
private:
    BufferStore() = default;

    std::unordered_map<std::string, BufferDescription> m_descriptions;
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_BUFFER_STORE_HPP
