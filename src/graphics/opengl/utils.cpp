#include <vp/graphics/opengl/utils.hpp>

namespace vp::gl::utils {

std::string getShaderErrorMessage(u32 desc) {
    vp::size logSize = 0;
    glGetShaderiv(desc, GL_INFO_LOG_LENGTH, &logSize);

    std::string errMsg {};
    errMsg.resize(static_cast<u32>(logSize));

    glGetShaderInfoLog(desc, logSize, nullptr, errMsg.data());
    if (glGetError() != 0) {
        throw std::runtime_error("Getting information about shader failed");
    }
    return errMsg;
}

} // namespace vp::gl::utils
