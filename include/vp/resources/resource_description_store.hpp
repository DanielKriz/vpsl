#ifndef VP_RESOURCES_RESOURCE_DESCRIPTION_STORE_HPP
#define VP_RESOURCES_RESOURCE_DESCRIPTION_STORE_HPP

#include <vp/resources/material_description.hpp>
#include <vp/resources/mesh_description.hpp>
#include <vp/resources/texture_description.hpp>
#include <vp/singleton.hpp>

#include <string>
#include <unordered_map>

namespace vp {

class ResourceManager;

class ResourceDescriptionStore : public Singleton<ResourceDescriptionStore> {
public:
    friend ResourceManager;

    void insert(const TextureDescription &textureDesc);
    void insert(const MeshDescription &meshDesc);
    void insert(const MaterialDescription &materialDesc);

    void insert(TextureDescription &&textureDesc);
    void insert(MeshDescription &&meshDesc);
    void insert(MaterialDescription &&materialDesc);

    const TextureDescription &getTexture(std::string_view name);
    const MeshDescription &getMesh(std::string_view name);
    const MaterialDescription &getMaterial(std::string_view name);

    [[nodiscard]] bool containsTexture(std::string_view name) const noexcept;
    [[nodiscard]] bool containsMesh(std::string_view name) const noexcept;
    [[nodiscard]] bool containsMaterial(std::string_view name) const noexcept;
private:
    std::unordered_map<std::string, TextureDescription> m_textures;
    std::unordered_map<std::string, MaterialDescription> m_material;
    std::unordered_map<std::string, MeshDescription> m_meshes;
};

} // namespace vp

#endif // VP_RESOURCES_RESOURCE_DESCRIPTION_STORE_HPP
