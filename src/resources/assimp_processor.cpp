#include <vp/graphics/vertex.hpp>
#include <vp/resources/assimp_processor.hpp>
#include <vp/types.hpp>

#include <fmt/core.h>
#include <spdlog/spdlog.h>

namespace vp::assimp {

const aiScene *importSceneFromFile(const std::filesystem::path &path) {
    Assimp::Importer importer;
    const aiScene *pScene = importer.ReadFile(
        path,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
    );

    spdlog::info("Loading mesh from file: {}", path.string());

    const bool isSceneComplete = not static_cast<bool>(pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE);
    const bool hasRootNode = pScene->mRootNode != nullptr;

    if (pScene == nullptr or not isSceneComplete or not hasRootNode) {
        throw std::runtime_error(
            fmt::format("reading model failed with message: '{}'", importer.GetErrorString())
        );
    }
    return pScene;
}

std::vector<gl::Vertex> processMesh(aiMesh *pMesh, const aiScene *pScene) {
    std::vector<gl::Vertex> vertices;
    vertices.reserve(pMesh->mNumVertices);
    for (u32 i = 0u; i < pMesh->mNumVertices; ++i) {
        auto &vertex = vertices.emplace_back();
        vertex.position = toVector(pMesh->mVertices[i]);
        vertex.normal = toVector(pMesh->mNormals[i]);
#if 0
        vertex.uv = TODO
#endif
        vertex.tangent = toVector(pMesh->mTangents[i]);
        vertex.bitangent = toVector(pMesh->mBitangents[i]);
    }
}

glm::vec3 toVector(const aiVector3D *vec) {
    return { vec->x, vec->y, vec->z };
}

glm::vec3 toVector(const aiVector3D &vec) noexcept {
    return { vec.x, vec.y, vec.z };
}

} // namespace vp::assimp
