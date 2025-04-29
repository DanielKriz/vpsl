#include <vp/error_handling/default_error_reporter.hpp>

namespace vp {

std::string DefaultErrorReporter::getErrorString(u32 errorCode, const std::string &errorMsg) {
    // return fmt::format("Error ({}): '{}'", errorCode, errorMsg);
    return fmt::format("{} ({}): '{}'", fmt::styled("Error", fmt::fg(fmt::color::red)), errorCode, errorMsg);
}

} // namespace vp
