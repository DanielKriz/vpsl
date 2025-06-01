#ifndef VP_DESCRIPTION_DESCRIPTION_STORE_HPP
#define VP_DESCRIPTION_DESCRIPTION_STORE_HPP

#include <string>
#include <unordered_map>

namespace vp::desc {

template <typename T>
class DescriptionStore {
public:
    DescriptionStore() = default;
    DescriptionStore(const DescriptionStore &other) = default;
    DescriptionStore(DescriptionStore &&other) noexcept = default;
    DescriptionStore& operator=(const DescriptionStore &other) = default;
    DescriptionStore& operator=(DescriptionStore &&other) = default;
    virtual ~DescriptionStore() = default;

    T *emplace(const std::string &name) {
        if (m_descriptions.contains(name)) {
            return &m_descriptions[name];
        }
        return &m_descriptions.emplace(name, T{}).first->second;
    }

    void insert(const std::string &name, const T &description) {
        if (m_descriptions.contains(name)) {
            return;
        }
        m_descriptions.emplace(name, description);
    }

    const T &getDescription(const std::string &name) const {
        return m_descriptions.at(name);
    }

    T &getDescription(const std::string &name) {
        return m_descriptions.at(name);
    }

    const T &operator[](const std::string &name) const {
        return getDescription(name);
    }

    T &operator[](const std::string &name) {
        return getDescription(name);
    }

    [[nodiscard]] bool contains(const std::string &name) const noexcept {
        return m_descriptions.contains(name);
    }

    void clear() {
        m_descriptions.clear();
    }

private:
    std::unordered_map<std::string, T> m_descriptions;
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_DESCRIPTION_STORE_HPP
