#ifndef VP_BUILDER_INTERFACE_HPP
#define VP_BUILDER_INTERFACE_HPP

namespace vp {

// template <typename T>
class IBuilder {
public:
    virtual ~IBuilder() = default;
    virtual void build() const noexcept = 0;
    virtual void reset() noexcept = 0;
private:
};

} // namespace vp

#endif // VP_BUILDER_INTERFACE_HPP
