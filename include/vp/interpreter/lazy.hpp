#pragma once

#include <concepts>
#include <unordered_map>
#include <functional>
#include <string>

#include <vp/builder_graph/objects/program_object.hpp>
#include <vp/builder_graph/objects/shader_object.hpp>

namespace vp {

template <typename T>
concept LazyReferencable = std::derived_from<T, ProgramObject> or std::derived_from<T, ShaderObject>;

template <typename T>
class LazyReference {
public:
    void populate();
private:
    std::reference_wrapper<T> m_reference;
};

template <typename T>
class Lazy {

public:
    static std::unordered_map<std::string, LazyReference<T>> store;

    Lazy<T>() {
    }
};

} // namespace vp
