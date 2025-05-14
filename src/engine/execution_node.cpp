#include <vp/engine/execution_node.hpp>
#include <vp/graphics/context_cache.hpp>

namespace vp {

ExecutionNode::ExecutionNode()
    : m_pProgram(std::make_shared<gl::opengl::Program>())
    , m_pOptions(std::make_unique<Options>()) {
}

void ExecutionNode::setOptions(const Options &opts) {
    *m_pOptions = opts;
}

void ExecutionNode::applyContext() const noexcept {
    using namespace gl;
    auto &cache = ContextCache::getInstance();

    auto &opts = *m_pOptions;

    cache.enableDepthTest(opts.isDepthTestEnabled);
    cache.enableBlending(opts.isDepthTestEnabled);
    cache.enableFaceCulling(opts.isDepthTestEnabled);

    if (opts.frontFacePolygonMode == opts.backFacePolygonMode) {
        cache.setPolygonMode(opts.frontFacePolygonMode);
    } else {
        cache.setPolygonMode(Face::Front, opts.frontFacePolygonMode);
        cache.setPolygonMode(Face::Back, opts.backFacePolygonMode);
    }

    cache.setCullingMode(opts.cullingMode);
    cache.setFrontFaceMode(opts.frontFaceMode);
    cache.setDepthFunction(opts.depthFunction);
    cache.setSrcBlendFactor(opts.srcBlendFactor);
    cache.setDstBlendFactor(opts.dstBlendFactor);
}

} // namespace vp
