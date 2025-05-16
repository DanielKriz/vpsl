#include <vp/resources/resource_loader.hpp>
#include <vp/resources/resource_store.hpp>

#include <spdlog/spdlog.h>

namespace vp {

ResourceStore::ResourceStore() : m_searchPaths{ "." } {
    m_pLoader = std::make_unique<ResourceLoader>();
}

void ResourceStore::addMesh(const std::string &name, const Path &path, bool isLazy) {
    addResource(ResourceKind::Mesh, name, path, isLazy);
}

void ResourceStore::addMaterial(const std::string &name, const Path &path, bool isLazy) {
    addResource(ResourceKind::Material, name, path, isLazy);
}

void ResourceStore::addTexture(const std::string &name, const Path &path, bool isLazy) {
    addResource(ResourceKind::Texture, name, path, isLazy);
}

bool ResourceStore::containsMesh(const std::string &name) const noexcept {
    return m_presentMeshes.contains(name);
}

bool ResourceStore::containsTexture(const std::string &name) const noexcept {
    return m_presentTextures.contains(name);
}

bool ResourceStore::containsMaterial(const std::string &name) const noexcept {
    return m_presentMaterials.contains(name);
}

Mesh &ResourceStore::getMesh(const std::string &name) {
    auto mesh = m_meshes.find(name);
    if (mesh == m_meshes.end()) {
        throw std::runtime_error(
            fmt::format("Resource store does not contain mesh with name '{}'", name)
        );
    }
    return mesh->second;
}

Texture &ResourceStore::getTexture(const std::string &name) {
    auto texture = m_textures.find(name);
    if (texture == m_textures.end()) {
        throw std::runtime_error(
            fmt::format("Resource store does not contain texture with name '{}'", name)
        );
    }
    return texture->second;
}

Material &ResourceStore::getMaterial(const std::string &name) {
    auto material = m_materials.find(name);
    if (material == m_materials.end()) {
        throw std::runtime_error(
            fmt::format("Resource store does not contain material with name '{}'", name)
        );
    }
    return material->second;
}

void ResourceStore::addResource(
    ResourceKind kind,
    const std::string &name,
    const Path &path,
    bool isLazy
) {
    using enum ResourceKind;
    for (const auto &searchPath : m_searchPaths) {
        const auto filepath = searchPath / path;
        if (std::filesystem::exists(filepath)) {
            if (isLazy) {
                m_textures[name];
                m_cachedRequests.emplace(kind, name, filepath);
                spdlog::debug("enquing a job for '{}' at {}", name, filepath.c_str());
                return;
            }

            spdlog::debug("directly loading '{}' at {}", name, filepath.c_str());
            if (kind == Texture) {
                m_presentTextures.insert(name);
                m_pLoader->loadTexture(name, filepath);
                return;
            }

            if (kind == Mesh) {
                m_presentMeshes.insert(name);
                m_pLoader->loadMesh(name, filepath);
                return;
            } 

            if (kind == Material) {
                m_presentMaterials.insert(name);
                m_pLoader->loadMaterial(name, filepath);
                return;
            }
            throw std::runtime_error("Unknown resource kind to add to the store");
        }
        spdlog::debug("Did not find resource given by {}", filepath.c_str());
    }
    throw std::runtime_error(
        fmt::format("Could not find resource given by {}", path.c_str())
    );
}

void ResourceStore::addSearchPath(const std::filesystem::path &path) {
    m_searchPaths.insert(path);
}

void ResourceStore::terminateLoading() {
    m_pLoader->terminateLoading();
}

void ResourceStore::evaluateLazyResources() {
    spdlog::debug("Evaluating {} lazy entries in the store", m_cachedRequests.size());
    while (not m_cachedRequests.empty()) {
        LoadRequest req = m_cachedRequests.front();
        m_cachedRequests.pop();
        if (req.type == ResourceKind::Texture) {
            m_pLoader->loadTexture(req.name, req.path);
        } else if (req.type == ResourceKind::Material) {
            m_pLoader->loadMaterial(req.name, req.path);
        } else if (req.type == ResourceKind::Mesh) {
            m_pLoader->loadMesh(req.name, req.path);
        } else {
            throw std::runtime_error("Unknow kind of resource to be evaluated");
        }
    }
}

void ResourceStore::waitForFinish() const {
    m_pLoader->waitForFinish();
}

void ResourceStore::clear() {
    std::scoped_lock<std::mutex> textureLock { m_textureMutex };
    std::scoped_lock<std::mutex> materialLock { m_textureMutex };
    std::scoped_lock<std::mutex> meshLock { m_textureMutex };
    m_textures.clear();
    m_materials.clear();
    m_meshes.clear();
    m_searchPaths.clear();

    std::queue<LoadRequest> empty;
    std::swap(m_cachedRequests, empty);

    m_searchPaths.emplace(".");
}

void ResourceStore::storeMesh(const std::string &name, Mesh &&mesh) {
    spdlog::debug("Storing mesh with name: '{}'", name);

}

void ResourceStore::storeMaterial(const std::string &name, Material &&material) {
    spdlog::debug("Storing material with name: '{}'", name);

}

void ResourceStore::storeTexture(const std::string &name, Texture &&texture) {
    std::scoped_lock<std::mutex> lock { m_textureMutex };
    spdlog::debug("Storing texture with name: '{}'", name);
    auto entry = m_textures.find(name);
    if (entry != m_textures.end()) {
        entry->second.setData(texture.shareData());
    } else {
        m_textures.emplace(name, texture);
    }
}

const std::set<std::filesystem::path> &ResourceStore::getSearchPaths() const noexcept {
    return m_searchPaths;
}

} // namespace vp
