#ifndef VP_RESOURCES_RESOURCE_STORE_HPP
#define VP_RESOURCES_RESOURCE_STORE_HPP

#include <vp/resources/resource_kind.hpp>
#include <vp/singleton.hpp>
#include <vp/resources/load_request.hpp>
#include <vp/resources/texture.hpp>

#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>

namespace vp {

class Mesh{};
class Material{};

class ResourceLoader;

class ResourceStore : public Singleton<ResourceStore> {
public:
    friend Singleton<ResourceStore>;
    friend ResourceLoader;

    using Path = std::filesystem::path;

    ResourceStore(const ResourceStore &other) = delete;
    ResourceStore(ResourceStore &&other) noexcept = delete;
    ResourceStore& operator=(const ResourceStore &other) = delete;
    ResourceStore& operator=(ResourceStore &&other) = delete;
    ~ResourceStore() = default;

    void addMesh(const std::string &name, const Path &path, bool isLazy = true);
    void addMaterial(const std::string &name, const Path &path, bool isLazy = true);
    void addTexture(const std::string &name, const Path &path, bool isLazy = true);
    void addResource(ResourceKind kind, const std::string &name, const Path &path, bool isLazy = true);

    [[nodiscard]] bool containsMesh(const std::string &name) const noexcept;
    [[nodiscard]] bool containsTexture(const std::string &name) const noexcept;
    [[nodiscard]] bool containsMaterial(const std::string &name) const noexcept;

    Mesh &getMesh(const std::string &name);
    Texture &getTexture(const std::string &name);
    Material &getMaterial(const std::string &name);

    void addSearchPath(const std::filesystem::path &path);
    [[nodiscard]] const std::set<std::filesystem::path> &getSearchPaths() const noexcept;

    void terminateLoading();
    void evaluateLazyResources();
    void waitForFinish() const;
    void clear();
private:
    ResourceStore();

    void storeMesh(const std::string &name, Mesh &&mesh);
    void storeMaterial(const std::string &name, Material &&material);
    void storeTexture(const std::string &name, Texture &&texture);

    std::unordered_map<std::string, Texture> m_textures;
    std::unordered_map<std::string, Mesh> m_meshes;
    std::unordered_map<std::string, Material> m_materials;
    std::mutex m_textureMutex;
    std::mutex m_meshMutex;
    std::mutex m_materialMutex;

    std::unique_ptr<ResourceLoader> m_pLoader;

    std::set<std::filesystem::path> m_searchPaths;
    std::unordered_set<std::string> m_presentTextures;
    std::unordered_set<std::string> m_presentMeshes;
    std::unordered_set<std::string> m_presentMaterials;
    std::queue<LoadRequest> m_cachedRequests;
};

} // namespace vp

#endif // VP_RESOURCES_RESOURCE_STORE_HPP
