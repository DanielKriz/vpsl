#include <vp/description/options.hpp>

namespace vp {

bool operator==(const Options &lhs, const Options &rhs) {
    return (
        lhs.isDepthTestEnabled == rhs.isDepthTestEnabled
        and lhs.isBlendingEnabled == rhs.isBlendingEnabled
        and lhs.isFaceCullingEnabled == rhs.isFaceCullingEnabled
        and lhs.frontFacePolygonMode == rhs.frontFacePolygonMode
        and lhs.backFacePolygonMode == rhs.backFacePolygonMode
        and lhs.cullingMode == rhs.cullingMode
        and lhs.frontFaceMode == rhs.frontFaceMode
        and lhs.depthFunction == rhs.depthFunction
        and lhs.srcBlendFactor == rhs.srcBlendFactor
        and lhs.dstBlendFactor == rhs.dstBlendFactor
    );
}

std::ostream &operator<<(std::ostream &os, const Options &opts) {
    os << "Is depth test enabled: " << std::boolalpha << opts.isDepthTestEnabled << std::endl;
    os << "Is blending enabled: " << std::boolalpha << opts.isBlendingEnabled << std::endl;
    os << "Is face culling enabled: " << std::boolalpha << opts.isFaceCullingEnabled << std::endl;
    os << "Front Face Polygon Mode: " << static_cast<u32>(opts.frontFacePolygonMode) << std::endl;
    os << "Back Face Polygon Mode: " << static_cast<u32>(opts.backFacePolygonMode) << std::endl;
    os << "Culling Mode: " << static_cast<u32>(opts.cullingMode) << std::endl;
    os << "Front Face Mode: " << static_cast<u32>(opts.frontFaceMode) << std::endl;
    os << "Depth Function: " << static_cast<u32>(opts.depthFunction) << std::endl;
    os << "Source Blend Factor: " << static_cast<u32>(opts.srcBlendFactor) << std::endl;
    os << "Destination Blend Factor: "<< static_cast<u32>(opts.dstBlendFactor) << std::endl;
    return os;
}

} // namespace vp
