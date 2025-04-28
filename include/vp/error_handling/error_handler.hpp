#ifndef VP_ERROR_HANDLING_ERROR_HANDLER_HPP
#define VP_ERROR_HANDLING_ERROR_HANDLER_HPP

#include <string>
#include <stdexcept>

#include <vp/error_handling/error_reporter_interface.hpp>
#include <vp/error_handling/error_concept.hpp>
#include <vp/types.hpp>

namespace vp {

class ErrorHandler {
public:
    template <Error Err>
    [[noreturn]] static void report(u32 errorCode, const std::string &errorMsg) {
        if (reporter == nullptr) {
            throw std::runtime_error("The error reporter is missing");
        }

        throw Err(reporter->getErrorString(errorCode, errorMsg));
    }

    static IErrorReporter * reporter;

    // Forbid creation of this type
    ErrorHandler() = delete;
};
IErrorReporter *ErrorHandler::reporter = nullptr;

} // namespace vp

#endif // VP_ERROR_HANDLING_ERROR_HANDLER_HPP
