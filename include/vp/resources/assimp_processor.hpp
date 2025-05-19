#ifndef VP_RESOURCES_ASSIMP_PROCESSOR_HPP
#define VP_RESOURCES_ASSIMP_PROCESSOR_HPP

#include <vp/graphics/vertex.hpp>
#include <vp/types.hpp>

#include <filesystem>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/texture.h>
#include <glm/glm.hpp>

namespace vp::assimp {

class Processor {
public:
    void importSceneFromFile(const std::filesystem::path &path);
    std::vector<gl::Vertex> processMesh();

private:
    Assimp::Importer m_importer;
    const aiScene *m_pScene;
};

glm::vec3 toVector(const aiVector3D *vec);
glm::vec3 toVector(const aiVector3D &vec) noexcept;
glm::vec2 textureCoordinatesToVector(const aiVector3D *vec, u64 coord) noexcept;

} // namespace vp::assimp

#endif // VP_RESOURCES_ASSIMP_PROCESSOR_HPP

