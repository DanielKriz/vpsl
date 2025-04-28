#ifndef VP_OPENGL_TYPES_HPP
#define VP_OPENGL_TYPES_HPP

#include <glad/glad.h>

#include <bitset>

namespace vp::inline types {
    // bitdepth, signedness and overall naming from
    // https://www.khronos.org/opengl/wiki/OpenGL_Type
    using i8 = GLbyte;
    static_assert(sizeof(i8) == sizeof(GLbyte));
    static_assert(sizeof(i8) == sizeof(int8_t));

    using u8 = GLubyte;
    static_assert(sizeof(i8) == sizeof(GLubyte));
    static_assert(sizeof(i8) == sizeof(int8_t));

    using i16 = GLshort;
    static_assert(sizeof(i16) == sizeof(GLshort));
    static_assert(sizeof(i16) == sizeof(int16_t));

    using u16 = GLushort;
    static_assert(sizeof(u16) == sizeof(GLushort));
    static_assert(sizeof(u16) == sizeof(uint16_t));

    using i32 = GLint;
    static_assert(sizeof(i32) == sizeof(GLint));
    static_assert(sizeof(i32) == sizeof(int32_t));

    using u32 = GLuint;
    static_assert(sizeof(u32) == sizeof(GLuint));
    static_assert(sizeof(u32) == sizeof(uint32_t));

    using fixed = GLfixed;
    static_assert(sizeof(fixed) == sizeof(GLfixed));

    // inline float to_float(fixed value) {
    //     // This warning is known and it may only be suppresed as we cannot
    //     // cast the value to float, because then it would lose its semantics
    //     // as fixed-point number.
    //     // NOLINTNEXTLINE
    //     return value * (1 / static_cast<float>((std::numeric_limits<uint16_t>::max() + 1)));
    // }

    using i64 = GLint64;
    static_assert(sizeof(i64) == sizeof(GLint64));
    static_assert(sizeof(i64) == sizeof(int64_t));

    using u64 = GLuint64;
    static_assert(sizeof(u64) == sizeof(GLuint64));
    static_assert(sizeof(u64) == sizeof(uint64_t));

    using size = GLsizei;
    static_assert(sizeof(size) == sizeof(GLsizei), "");
    static_assert(sizeof(size) == sizeof(uint32_t));

    using enum32 = GLenum;
    static_assert(sizeof(enum32) == sizeof(uint32_t));

    using iptr = GLintptr;
    static_assert(sizeof(iptr) == sizeof(std::ptrdiff_t));
    static_assert(sizeof(iptr) == sizeof(void *));

    using sptr = GLsizeiptr;
    static_assert(sizeof(sptr) == sizeof(std::ptrdiff_t));
    static_assert(sizeof(sptr) == sizeof(void *));

    using sync = GLsync;
    static_assert(sizeof(sync) == sizeof(std::ptrdiff_t));
    static_assert(sizeof(sync) == sizeof(void *));

    using bitfield = GLbitfield;
    static_assert(sizeof(bitfield) == sizeof(uint32_t));

    // This suppresion is added due to expressiveness of this "magic number".
    // NOLINTNEXTLINE
    inline std::bitset<32> toBitset(bitfield field) { return { field }; }

    using f16 = GLhalf;
    static_assert(sizeof(f16) == sizeof(GLhalf));
    // static_assert(sizeof(f16) == sizeof(std::float16_t));

    using f32 = GLfloat;
    static_assert(sizeof(f32) == sizeof(GLfloat));
    // static_assert(sizeof(f32) == sizeof(std::float32_t));
    static_assert(sizeof(f32) == sizeof(float));

    using f64 = GLdouble;
    static_assert(sizeof(f64) == sizeof(GLdouble));
    // static_assert(sizeof(f64) == sizeof(std::float64_t));
    static_assert(sizeof(f64) == sizeof(double));

    using cf32 = GLclampf;
    static_assert(sizeof(cf32) == sizeof(GLfloat));
    // static_assert(sizeof(cf32) == sizeof(std::float32_t));
    static_assert(sizeof(cf32) == sizeof(float));

    using cf64 = GLclampd;
    namespace clamped {
        using f32 = GLclampf;
        using f64 = GLclampd;
    } // namespace clamped
    static_assert(sizeof(clamped::f32) == sizeof(GLfloat));
    // static_assert(sizeof(clamped::f32) == sizeof(std::float32_t));
    static_assert(sizeof(clamped::f32) == sizeof(float));
    static_assert(sizeof(clamped::f64) == sizeof(GLdouble));
    // static_assert(sizeof(clamped::f64) == sizeof(std::float64_t));
    static_assert(sizeof(clamped::f64) == sizeof(double));
} // namespace vp::inline types

// TODO: fix this
template <typename T>
// concept ScopedEnumType = std::is_scoped_enum_v<T>;
concept ScopedEnumType = true;

// @brief Simple conversion function for opengl enumeration types.
template <ScopedEnumType T>
vp::enum32 enum_cast(T enum_value) {
    return static_cast<vp::enum32>(enum_value);
}

#endif // VP_OPENGL_TYPES_HPP
