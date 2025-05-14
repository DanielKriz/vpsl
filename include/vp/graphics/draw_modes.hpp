#ifndef VP_GRAPHICS_DRAW_MODES_HPP
#define VP_GRAPHICS_DRAW_MODES_HPP

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {

enum class DrawMode : u8 {
    Points,
    LineStrip,
    LineLoop,
    Lines,
    LineStripAdjacency,
    LinesAdjacency,
    TriangleStrip,
    TriangleFan,
    Triangles,
    TriangleStripAdjacency,
    TrianglesAdjacency,
    Patches,
};

struct DrawCommand {
    DrawMode mode { DrawMode::Triangles };
    u64 count { 0 };
};

template <>
inline utils::StringViewMap<DrawMode> utils::StringToEnumMap<DrawMode>::map = {
    { "points" , DrawMode::Points },
    { "line_strip" , DrawMode::LineStrip },
    { "line_loop" , DrawMode::LineLoop },
    { "lines" , DrawMode::Lines },
    { "line_strip_adjacency" , DrawMode::LineStripAdjacency },
    { "lines_adjacency" , DrawMode::LinesAdjacency },
    { "triangle_strip" , DrawMode::TriangleStrip },
    { "triangle_fan" , DrawMode::TriangleFan },
    { "triangles" , DrawMode::Triangles },
    { "triangle_strip_adjacency" , DrawMode::TriangleStripAdjacency },
    { "triangles_adjacency" , DrawMode::TrianglesAdjacency },
    { "patches" , DrawMode::Patches },
};

} // namespace vp

#endif // VP_GRAPHICS_DRAW_MODES_HPP
