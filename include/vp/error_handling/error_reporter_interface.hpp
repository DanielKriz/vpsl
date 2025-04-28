#ifndef VP_ERROR_HANDLING_ERROR_REPORTER_INTERFACE_HPP
#define VP_ERROR_HANDLING_ERROR_REPORTER_INTERFACE_HPP

#include <string>

#include <vp/types.hpp>

namespace vp {

struct IErrorReporter {
    virtual ~IErrorReporter() = default;
    virtual std::string getErrorString(u32 errorCode, const std::string &errorMsg) = 0;
};

} // namespace vp

#endif // VP_ERROR_HANDLING_ERROR_CONCEPT_HPP
