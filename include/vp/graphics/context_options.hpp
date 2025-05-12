#ifndef VP_GRAPHICS_CONTEXT_OPTIONS_HPP
#define VP_GRAPHICS_CONTEXT_OPTIONS_HPP

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp::gl {

enum class PolygonMode : u8 {
    Point,
    Line,
    Fill,
};

enum class CullingMode : u8 {
    Front,
    Back,
    FrontAndBack,
};

enum class Face : u8 {
    Front,
    Back,
};

enum class FrontFaceMode : u8 {
    CW,
    CCW,
};

enum class BlendingFactor : u8 {
    Zero,
    One,
    SourceColor,
    OneMinusSourceColor,
    DestinationColor,
    OneMinusDestinationColor,
    SourceAlpha,
    OneMinusSourceAlpha,
    DestinationAlpha,
    OneMinusDestinationAlpha,
    ConstantColor,
    OneMinusConstantColor,
    ConstantAlpha,
    OneMinusConstantAlpha,
    SourceAlphaSaturate,
};

enum class DepthFunction : u8 {
    Never,
    Less,
    Equal,
    LessEqual,
    Greater,
    GreaterEqual,
    NotEqual,
    Always,
};

template <typename T>
concept GraphicsOptionEnumKind = std::is_same_v<T, PolygonMode>
                              or std::is_same_v<T, CullingMode>
                              or std::is_same_v<T, FrontFaceMode>
                              or std::is_same_v<T, BlendingFactor>
                              or std::is_same_v<T, DepthFunction>;

} // namespace vp::gl

namespace vp {

template <>
inline utils::StringViewMap<gl::PolygonMode> utils::StringToEnumMap<gl::PolygonMode>::map = {
    { "point" , gl::PolygonMode::Point },
    { "line" , gl::PolygonMode::Line },
    { "fill" , gl::PolygonMode::Fill },
};

template <>
inline utils::StringViewMap<gl::CullingMode> utils::StringToEnumMap<gl::CullingMode>::map = {
    { "front" , gl::CullingMode::Front },
    { "back" , gl::CullingMode::Back },
    { "front_and_back" , gl::CullingMode::FrontAndBack },
};

template <>
inline utils::StringViewMap<gl::FrontFaceMode> utils::StringToEnumMap<gl::FrontFaceMode>::map = {
    { "cw" , gl::FrontFaceMode::CW },
    { "ccw" , gl::FrontFaceMode::CCW },
};

template <>
inline utils::StringViewMap<gl::BlendingFactor> utils::StringToEnumMap<gl::BlendingFactor>::map = {
    { "zero" , gl::BlendingFactor::Zero },
    { "one" , gl::BlendingFactor::One },
    { "source_color" , gl::BlendingFactor::SourceColor },
    { "one_minus_source_color" , gl::BlendingFactor::OneMinusSourceColor },
    { "destination_color" , gl::BlendingFactor::DestinationColor },
    { "one_minus_destination_color" , gl::BlendingFactor::OneMinusDestinationColor },
    { "source_alpha" , gl::BlendingFactor::SourceAlpha },
    { "one_minus_source_alpha" , gl::BlendingFactor::OneMinusSourceAlpha },
    { "destination_alpha" , gl::BlendingFactor::DestinationAlpha },
    { "one_minus_destination_alpha" , gl::BlendingFactor::OneMinusDestinationAlpha },
    { "constant_color" , gl::BlendingFactor::ConstantColor },
    { "one_minus_constant_color" , gl::BlendingFactor::OneMinusConstantColor },
    { "constant_alpha" , gl::BlendingFactor::ConstantAlpha },
    { "one_minus_constant_alpha" , gl::BlendingFactor::OneMinusConstantAlpha },
    { "source_alpha_saturate" , gl::BlendingFactor::SourceAlphaSaturate },
};

template <>
inline utils::StringViewMap<gl::DepthFunction> utils::StringToEnumMap<gl::DepthFunction>::map = {
    { "never" , gl::DepthFunction::Never },
    { "less" , gl::DepthFunction::Less },
    { "ls" , gl::DepthFunction::Less },
    { "equal" , gl::DepthFunction::Equal },
    { "eq" , gl::DepthFunction::Equal },
    { "less_equal" , gl::DepthFunction::LessEqual },
    { "leq" , gl::DepthFunction::LessEqual },
    { "greater" , gl::DepthFunction::Greater },
    { "gt" , gl::DepthFunction::Greater },
    { "greater_equal" , gl::DepthFunction::GreaterEqual },
    { "geq" , gl::DepthFunction::GreaterEqual },
    { "not_equal" , gl::DepthFunction::NotEqual },
    { "neq" , gl::DepthFunction::NotEqual },
    { "always" , gl::DepthFunction::Always },
};

} // namespace vp

#endif // VP_GRAPHICS_CONTEXT_OPTIONS_HPP
