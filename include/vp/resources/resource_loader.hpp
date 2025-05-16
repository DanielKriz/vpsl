#ifndef VP_RESOURCE_LOADER_HPP
#define VP_RESOURCE_LOADER_HPP

#include <vp/resources/resource_store.hpp>
#include <vp/resources/thread_pool.hpp>
#include <vp/resources/resource_kind.hpp>
#include <vp/singleton.hpp>

#include <filesystem>

namespace vp {

class ResourceLoader {
public:
    void loadTexture(const std::string &name, const std::filesystem::path &path);
    void loadMaterial(const std::string &name, const std::filesystem::path &path);
    void loadMesh(const std::string &name, const std::filesystem::path &path);
    void terminateLoading();
    void waitForFinish();
private:
    static bool isTextureFileType(std::string_view extension) noexcept;
    static bool isMaterialFileType(std::string_view extension) noexcept;
    static bool isMeshFileType(std::string_view extension) noexcept;

    static void loadTextureJob(const std::string &name, const std::filesystem::path &path);
    static void loadMaterialJob(const std::string &name, const std::filesystem::path &path);
    static void loadMeshJob(const std::string &name, const std::filesystem::path &path);

    ThreadPool m_threadPool;
};

} // namespace vp

#endif // VP_RESOURCE_LOADER_HPP
