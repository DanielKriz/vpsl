#ifndef VP_GRAPHICS_OPENGL_UNIFORM_HPP
#define VP_GRAPHICS_OPENGL_UNIFORM_HPP

#include <concepts>
#include <string>
#include <type_traits>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fmt/core.h>

#include <vp/types.hpp>

namespace vp::gl::opengl {

template <typename T>
concept MatrixType =  std::same_as<glm::mat<1, 1, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<1, 2, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<1, 3, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<1, 4, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<2, 1, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<2, 2, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<2, 3, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<2, 4, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<3, 1, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<3, 2, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<3, 3, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<3, 4, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<4, 1, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<4, 2, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<4, 3, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::mat<4, 4, typename T::value_type, glm::defaultp>, T>;

static_assert(MatrixType<glm::mat2>);
static_assert(MatrixType<glm::mat3>);
static_assert(MatrixType<glm::mat4>);
static_assert(MatrixType<glm::mat2x2>);
static_assert(MatrixType<glm::mat2x3>);
static_assert(MatrixType<glm::mat2x4>);
static_assert(MatrixType<glm::mat3x2>);
static_assert(MatrixType<glm::mat3x3>);
static_assert(MatrixType<glm::mat3x4>);
static_assert(MatrixType<glm::mat4x2>);
static_assert(MatrixType<glm::mat4x3>);
static_assert(MatrixType<glm::mat4x4>);

template <typename T>
concept VectorType =  std::same_as<glm::vec<1, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::vec<2, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::vec<3, typename T::value_type, glm::defaultp>, T>
                   or std::same_as<glm::vec<4, typename T::value_type, glm::defaultp>, T>;

static_assert(VectorType<glm::vec1>);
static_assert(VectorType<glm::vec2>);
static_assert(VectorType<glm::vec3>);
static_assert(VectorType<glm::vec4>);
static_assert(VectorType<glm::ivec1>);
static_assert(VectorType<glm::ivec2>);
static_assert(VectorType<glm::ivec3>);
static_assert(VectorType<glm::ivec4>);
static_assert(VectorType<glm::uvec1>);
static_assert(VectorType<glm::uvec2>);
static_assert(VectorType<glm::uvec3>);
static_assert(VectorType<glm::uvec4>);
static_assert(VectorType<glm::fvec1>);
static_assert(VectorType<glm::fvec2>);
static_assert(VectorType<glm::fvec3>);
static_assert(VectorType<glm::fvec4>);
static_assert(VectorType<glm::dvec1>);
static_assert(VectorType<glm::dvec2>);
static_assert(VectorType<glm::dvec3>);
static_assert(VectorType<glm::dvec4>);

template <typename T>
concept Numeric = std::integral<T> or std::floating_point<T>;

template <typename T>
concept Uniformable = Numeric<T> or MatrixType<T> or VectorType<T>;

class Uniform final {
public:
    Uniform(std::string name, i32 location)
        : m_name(std::move(name)), m_location(location) { };
    explicit Uniform(std::string name);

    // TODO: rule of five

    [[nodiscard]] i32 getLocation() const { return m_location; }

    template <Uniformable T>
    void set(T value);

    template <Numeric T>
    void set(T x, T y);

    template <Numeric T>
    void set(T x, T y, T z);

    template <Numeric T>
    void set(T x, T y, T z, T w);
private:
    std::string m_name;
    i32 m_location;
};

template<>
inline void Uniform::set<glm::vec1>(glm::vec1 value) {
    glUniform1fv(m_location, 1, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::ivec1>(glm::ivec1 value) {
    glUniform1iv(m_location, 1, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::uvec1>(glm::uvec1 value) {
    glUniform1uiv(m_location, 1, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::dvec1>(glm::dvec1 value) {
    glUniform1dv(m_location, 1, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::vec2>(glm::vec2 value) {
    glUniform2fv(m_location, 2, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::ivec2>(glm::ivec2 value) {
    glUniform2iv(m_location, 2, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::uvec2>(glm::uvec2 value) {
    glUniform2uiv(m_location, 2, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::dvec2>(glm::dvec2 value) {
    glUniform2dv(m_location, 2, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::vec3>(glm::vec3 value) {
    glUniform3fv(m_location, 3, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::ivec3>(glm::ivec3 value) {
    glUniform3iv(m_location, 3, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::uvec3>(glm::uvec3 value) {
    glUniform3uiv(m_location, 3, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::dvec3>(glm::dvec3 value) {
    glUniform3dv(m_location, 3, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::vec4>(glm::vec4 value) {
    glUniform4fv(m_location, 4, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::ivec4>(glm::ivec4 value) {
    glUniform4iv(m_location, 4, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::uvec4>(glm::uvec4 value) {
    glUniform4uiv(m_location, 4, glm::value_ptr(value));
}

template<>
inline void Uniform::set<glm::dvec4>(glm::dvec4 value) {
    glUniform4dv(m_location, 4, glm::value_ptr(value));
}

template<>
inline void Uniform::set<i32>(i32 value) {
    glUniform1i(m_location, value);
}

template<>
inline void Uniform::set<u32>(u32 value) {
    glUniform1ui(m_location, value);
}

template<>
inline void Uniform::set<f32>(f32 value) {
    glUniform1f(m_location, value);
}

template<>
inline void Uniform::set<f64>(f64 value) {
    glUniform1d(m_location, value);
}

template<>
inline void Uniform::set<i32>(i32 x, i32 y) {
    glUniform2i(m_location, x, y);
}

template<>
inline void Uniform::set<u32>(u32 x, u32 y) {
    glUniform2ui(m_location, x, y);
}

template<>
inline void Uniform::set<f32>(f32 x, f32 y) {
    glUniform2f(m_location, x, y);
}

template<>
inline void Uniform::set<f64>(f64 x, f64 y) {
    glUniform2d(m_location, x, y);
}

template<>
inline void Uniform::set<i32>(i32 x, i32 y, i32 z) {
    glUniform3i(m_location, x, y, z);
}

template<>
inline void Uniform::set<u32>(u32 x, u32 y, u32 z) {
    glUniform3ui(m_location, x, y, z);
}

template<>
inline void Uniform::set<f32>(f32 x, f32 y, f32 z) {
    glUniform3f(m_location, x, y, z);
}

template<>
inline void Uniform::set<f64>(f64 x, f64 y, f64 z) {
    glUniform3d(m_location, x, y, z);
}

template<>
inline void Uniform::set<i32>(i32 x, i32 y, i32 z, i32 w) {
    glUniform4i(m_location, x, y, z, w);
}

template<>
inline void Uniform::set<u32>(u32 x, u32 y, u32 z, u32 w) {
    glUniform4ui(m_location, x, y, z, w);
}

template<>
inline void Uniform::set<f32>(f32 x, f32 y, f32 z, f32 w) {
    glUniform4f(m_location, x, y, z, w);
}

template<>
inline void Uniform::set<f64>(f64 x, f64 y, f64 z, f64 w) {
    glUniform4d(m_location, x, y, z, w);
}

} // namespace vp::gl

#endif // VP_GRAPHICS_OPENGL_UNIFORM_HPP
