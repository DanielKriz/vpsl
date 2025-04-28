#ifndef VP_SINGLETON_HPP
#define VP_SINGLETON_HPP

namespace vp {

template <typename T>
class Singleton {
public:
    static T& getInstance() {
        if (m_pMember == nullptr) {
            m_pMember = new T();
        }
        return *m_pMember;
    }

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
protected:
    Singleton() = default;

private:
    static T *m_pMember;
};

template <typename T>
T *Singleton<T>::m_pMember = nullptr;

} // namespace vp

#endif // VP_SINGLETON_HPP
