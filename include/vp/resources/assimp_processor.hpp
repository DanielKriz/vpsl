#ifndef VP_RESOURCES_ASSIMP_PROCESSOR_HPP
#define VP_RESOURCES_ASSIMP_PROCESSOR_HPP

#include <vp/graphics/vertex.hpp>

#include <filesystem>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/texture.h>
#include <glm/glm.hpp>

namespace vp::assimp {

const aiScene *importSceneFromFile(const std::filesystem::path &path);
std::vector<gl::Vertex> processMesh(aiMesh *pMesh, const aiScene *pScene);

glm::vec3 toVector(const aiVector3D *vec);
glm::vec3 toVector(const aiVector3D &vec) noexcept;

} // namespace vp::assimp

#endif // VP_RESOURCES_ASSIMP_PROCESSOR_HPP

