#ifndef VP_CONTEXT_HPP
#define VP_CONTEXT_HPP

namespace vp {

struct ContextCache;

class Context {
public:
    friend ContextCache;
    void updateContext(const Context &ctx);
private:
};

// This structure is used as an optimization, if some option is already enabled
// it does not make sense to waste precious calls on re-enabling it.
struct ContextCache {
    void updateCache(const Context &ctx);
};

} // namespace context

#endif // VP_CONTEXT
