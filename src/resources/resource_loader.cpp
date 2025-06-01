#include <vp/resources/assimp_processor.hpp>
#include <vp/resources/resource_loader.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fmt/core.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#include <iostream>

namespace vp {

void ResourceLoader::loadTexture(const std::string &name, const std::filesystem::path &path) {
    if (not isTextureFileType(path.extension().c_str())) {
        throw std::runtime_error(
            fmt::format("Texture '{}' is not valid file type", path.c_str())
        );
    }

    m_threadPool.enqueueJob([path, name]() {
        loadTextureJob(name, path);
    });
}

void ResourceLoader::loadMaterial(const std::string &name, const std::filesystem::path &path) {
    if (not isMaterialFileType(path.extension().c_str())) {
        throw std::runtime_error(
            fmt::format("Material '{}' is not valid file type", path.c_str())
        );
    }

    m_threadPool.enqueueJob([path, name]() {
        loadMaterialJob(name, path);
    });
}

void ResourceLoader::loadMesh(const std::string &name, const std::filesystem::path &path) {
    if (not isMeshFileType(path.extension().c_str())) {
        throw std::runtime_error(
            fmt::format("Mesh '{}' is not valid file type", path.c_str())
        );
    }

    m_threadPool.enqueueJob([path, name]() {
        loadMeshJob(name, path);
    });
}

void ResourceLoader::waitForFinish() {
    while (m_threadPool.isBusy()) {}
    m_threadPool.stop();
}

void ResourceLoader::terminateLoading() {
}

bool ResourceLoader::isTextureFileType(std::string_view extension) noexcept {
    static const std::unordered_set<std::string_view> validExtensions = {
        ".png",
        ".jpg",
        ".jpeg",
    };
    return validExtensions.contains(extension);
}

bool ResourceLoader::isMaterialFileType(std::string_view extension) noexcept {
    static const std::unordered_set<std::string_view> validExtensions = {
        ".mtl",
    };
    return validExtensions.contains(extension);
}

bool ResourceLoader::isMeshFileType(std::string_view extension) noexcept {
    std::cout << extension << std::endl;
    static const std::unordered_set<std::string_view> validExtensions = {
        ".obj",
    };
    return validExtensions.contains(extension);
}

void ResourceLoader::loadTextureJob(
    const std::string &name,
    const std::filesystem::path &path
) {
    spdlog::debug("Loading texture '{}' found at {}", name, path.c_str());

    auto &store = ResourceStore::getInstance();
    SDL_Surface *pSurf = IMG_Load(path.c_str());
    if (pSurf == nullptr) {
        throw std::runtime_error(
            fmt::format("Texture '{}' from '{}' could not be loaded", name, path.c_str())
        );
    }
    store.storeTexture(name, Texture(pSurf));
}

void ResourceLoader::loadMaterialJob(
    const std::string &name,
    const std::filesystem::path &path
) {
    spdlog::debug("Loading Material '{}' found at {}", name, path.c_str());
}

void ResourceLoader::loadMeshJob(
    const std::string &name,
    const std::filesystem::path &path
) {
    spdlog::debug("Loading mesh '{}' found at {}", name, path.c_str());

    assimp::Processor processor;
    processor.importSceneFromFile(path);
    auto vertices = processor.processMesh();
    ResourceStore::getInstance().storeMesh(name, MeshData(vertices));
}

} // namespace vp
