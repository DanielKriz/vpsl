#ifndef VP_ERROR_HANDLING_ERROR_CONCEPT_HPP
#define VP_ERROR_HANDLING_ERROR_CONCEPT_HPP

namespace vp {

template <typename T>
concept Error = requires(T t) {
    { t.what() };
    { T("") };
};

} // namespace vp

#endif // VP_ERROR_HANDLING_ERROR_CONCEPT_HPP
