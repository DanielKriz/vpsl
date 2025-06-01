#include <vp/graphics/vertex.hpp>
#include <vp/resources/assimp_processor.hpp>
#include <vp/types.hpp>

#include <fmt/core.h>
#include <glm/gtc/constants.hpp>
#include <spdlog/spdlog.h>

namespace vp::assimp {

void Processor::importSceneFromFile(const std::filesystem::path &path) {
    m_pScene = m_importer.ReadFile(
        path,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
    );

    spdlog::info("Loading mesh from file: {}", path.string());

    const bool isSceneComplete = not static_cast<bool>(m_pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE);
    const bool hasRootNode = m_pScene->mRootNode != nullptr;
    if (m_pScene == nullptr or not isSceneComplete or not hasRootNode) {
        throw std::runtime_error(
            fmt::format("reading model failed with message: '{}'", m_importer.GetErrorString())
        );
    }
}

std::vector<gl::Vertex> Processor::processMesh() {
    if (m_pScene->mRootNode->mNumChildren <= 0) {
        throw std::runtime_error("Scene does not contain anything");
    }

    aiNode *pNode = m_pScene->mRootNode->mChildren[0];

    if (pNode->mNumMeshes <= 0) {
        throw std::runtime_error("Scene does not contain any meshes");
    }

    aiMesh *pMesh = m_pScene->mMeshes[pNode->mMeshes[0]];

    std::vector<gl::Vertex> vertices;
    vertices.reserve(pMesh->mNumVertices);
    for (u32 i = 0u; i < pMesh->mNumVertices; ++i) {
        auto &vertex = vertices.emplace_back();
        vertex.position = toVector(pMesh->mVertices[i]);
        vertex.normal = toVector(pMesh->mNormals[i]);
        vertex.uv = textureCoordinatesToVector(pMesh->mTextureCoords[0], i);
        vertex.tangent = toVector(pMesh->mTangents[i]);
        vertex.bitangent = toVector(pMesh->mBitangents[i]);
    }
    return vertices;
}

glm::vec3 toVector(const aiVector3D *vec) {
    return { vec->x, vec->y, vec->z };
}

glm::vec3 toVector(const aiVector3D &vec) noexcept {
    return { vec.x, vec.y, vec.z };
}

glm::vec2 textureCoordinatesToVector(const aiVector3D *vec, u64 coord) noexcept {
    if (vec == nullptr) {
        return glm::zero<glm::vec2>();
    }
    return { 
        vec[coord].x,
        vec[coord].y,
    };
}

} // namespace vp::assimp
