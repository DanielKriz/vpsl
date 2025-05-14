#include <vp/graphics/context_cache.hpp>

namespace vp::gl {

Options ContextCache::copyState() const noexcept {
    return *m_pCurrentOptions;
}

void ContextCache::enableDepthTest(bool enable) noexcept {
    if (m_pCurrentOptions->isDepthTestEnabled == enable) {
        return;
    }

    if (enable) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    m_pCurrentOptions->isDepthTestEnabled = enable;
}

void ContextCache::enableBlending(bool enable) noexcept {
    if (m_pCurrentOptions->isBlendingEnabled == enable) {
        return;
    }

    if (enable) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }

    m_pCurrentOptions->isBlendingEnabled = enable;

}

void ContextCache::enableFaceCulling(bool enable) noexcept {
    if (m_pCurrentOptions->isFaceCullingEnabled == enable) {
        return;
    }

    if (enable) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }

    m_pCurrentOptions->isFaceCullingEnabled = enable;
}

void ContextCache::setPolygonMode(PolygonMode mode) noexcept {
    if (m_pCurrentOptions->frontFacePolygonMode == mode
        and m_pCurrentOptions->backFacePolygonMode == mode) {
        return;
    }

    if (mode == PolygonMode::Fill) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (mode == PolygonMode::Line) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    m_pCurrentOptions->frontFacePolygonMode = mode;
    m_pCurrentOptions->backFacePolygonMode = mode;
}

void ContextCache::setPolygonMode(Face face, PolygonMode mode) noexcept {
    if (face == Face::Back) {
        if (m_pCurrentOptions->frontFacePolygonMode == mode) {
            return;
        }

        if (mode == PolygonMode::Fill) {
            glPolygonMode(GL_FRONT, GL_FILL);
        } else if (mode == PolygonMode::Line) {
            glPolygonMode(GL_FRONT, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT, GL_POINT);
        }

        m_pCurrentOptions->frontFacePolygonMode = mode;
    } else {
        if (m_pCurrentOptions->backFacePolygonMode == mode) {
            return;
        }

        if (mode == PolygonMode::Fill) {
            glPolygonMode(GL_BACK, GL_FILL);
        } else if (mode == PolygonMode::Line) {
            glPolygonMode(GL_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_BACK, GL_POINT);
        }

        m_pCurrentOptions->backFacePolygonMode = mode;
    }
}

void ContextCache::setCullingMode(CullingMode mode) noexcept {
    if (m_pCurrentOptions->cullingMode == mode) {
        return;
    }

    if (mode == CullingMode::Front) {
        glCullFace(GL_FRONT);
    } else if (mode == CullingMode::Back) {
        glCullFace(GL_BACK);
    } else {
        glCullFace(GL_FRONT_AND_BACK);
    }

    m_pCurrentOptions->cullingMode = mode;
}

void ContextCache::setFrontFaceMode(FrontFaceMode mode) noexcept {
    if (m_pCurrentOptions->frontFaceMode == mode) {
        return;
    }

    if (mode == FrontFaceMode::CW) {
        glFrontFace(GL_CW);
    } else {
        glCullFace(GL_CCW);
    }

    m_pCurrentOptions->frontFaceMode = mode;
}

void ContextCache::setDepthFunction(DepthFunction func) noexcept {
    if (m_pCurrentOptions->depthFunction == func) {
        return;
    }

    if (func == DepthFunction::Never) {
        glDepthFunc(GL_NEVER);
    } else if (func == DepthFunction::Less) {
        glDepthFunc(GL_LESS);
    } else if (func == DepthFunction::Equal) {
        glDepthFunc(GL_EQUAL);
    } else if (func == DepthFunction::LessEqual) {
        glDepthFunc(GL_LEQUAL);
    } else if (func == DepthFunction::Greater) {
        glDepthFunc(GL_GREATER);
    } else if (func == DepthFunction::GreaterEqual) {
        glDepthFunc(GL_GEQUAL);
    } else if (func == DepthFunction::NotEqual) {
        glDepthFunc(GL_NOTEQUAL);
    } else if (func == DepthFunction::Always) {
        glDepthFunc(GL_ALWAYS);
    }

    m_pCurrentOptions->depthFunction = func;
}

void ContextCache::setSrcBlendFactor(BlendingFactor factor) noexcept {
    // TODO
}

void ContextCache::setDstBlendFactor(BlendingFactor factor) noexcept {
    // TODO
}

} // namespace vp::gl
