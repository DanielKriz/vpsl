#ifndef VP_ERROR_HANDLING_DEFAULT_ERROR_REPORTER_HPP
#define VP_ERROR_HANDLING_DEFAULT_ERROR_REPORTER_HPP

#include <fmt/core.h>
#include <fmt/color.h>

#include <vp/error_handling/error_reporter_interface.hpp>

namespace vp {

class DefaultErrorReporter : public IErrorReporter {
public:
    std::string getErrorString(u32 errorCode, const std::string &errorMsg) override;
};

} // namespace vp

#endif // VP_ERROR_HANDLING_DEFAULT_ERROR_REPORTER_HPP
