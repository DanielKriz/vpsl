#ifndef VP_DESCRIPTION_PROGRAM_DESCRIPTION_HPP
#define VP_DESCRIPTION_PROGRAM_DESCRIPTION_HPP

#include <vector>

#include <vp/description/attribute_description.hpp>
#include <vp/description/buffer_description.hpp>
#include <vp/description/buffer_store.hpp>
#include <vp/description/frame_buffer_description.hpp>
#include <vp/description/frame_buffer_store.hpp>
#include <vp/description/options.hpp>
#include <vp/description/shader_code.hpp>
#include <vp/description/texture_description.hpp>
#include <vp/graphics/context_options.hpp>
#include <vp/graphics/draw_modes.hpp>
#include <vp/resources/mesh_description.hpp>
#include <vp/resources/material_data.hpp>
#include <vp/resources/texture.hpp>
#include <vp/types.hpp>

namespace vp::desc {

/// Forward declarations:
class ProgramDescriptionBuilder;

/// @brief Description of a shader program.
///
/// Description of a shader program with all resources that are needed for correct runtime. This
/// includes textures, buffers, reference to mesh and framebuffer and shader codes.
class ProgramDescription final {
public:
    /// The only way to insert values into a program is through a builder.
    friend ProgramDescriptionBuilder;

    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] const std::string &getName() const noexcept;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] const std::vector<TextureDescription> &getTextures() const noexcept;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] const std::vector<MaterialData *> &getMaterialDescriptions() const noexcept;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] const std::vector<BufferDescription *> &getBufferDescriptions() const noexcept;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] const std::vector<ShaderCode *> &getShaderCodes() const noexcept;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] const Options &getOptions() const;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] bool hasFrameBuffer() const;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] bool hasMesh() const;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] const FrameBufferDescription &getFrameBufferDescription() const;
    /// @brief Getter for the name of a program.
    /// @returns A name of the program.
    [[nodiscard]] const MeshDescription &getMeshDescription() const;

    [[nodiscard]] const DrawCommand &getDrawCommand() const;
    [[nodiscard]] bool hasDrawCommand() const noexcept;

private:
    /// @brief Name of the program.
    std::string m_name;
    /// @brief A vector of pointer to textures that shall be stored in texture store
    std::vector<TextureDescription> m_textures;
    /// @brief A vector of pointers to materials that shall be stored in material store
    std::vector<MaterialData *> m_materials;
    /// @brief A vector of pointers to buffers that shall be stored in buffer store
    std::vector<BufferDescription *> m_buffers;
    /// @brief A vector of pointers to shader codes that shall be stored in shader code store
    std::vector<ShaderCode *> m_shaderCodes;
    /// @brief A pointer to framebuffer that shall be stored in framebuffer store
    FrameBufferDescription *m_pFrameBuffer;
    /// @brief A pointer to mesh that shall be stored in mesh store
    MeshDescription *m_pMesh;
    /// @brief Options that shall be applied to this program.
    Options m_options;

    std::optional<DrawCommand> m_drawCommand;
};

/// @brief Builder for the ProgramDescription class.
class ProgramDescriptionBuilder final {
public:
    /// @brief Adds a texture to the program.
    /// Textures are bound in order in which they are added to the descriptor.
    ///
    /// @param desc Texture description that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &addTexture(TextureDescription &desc);
    ProgramDescriptionBuilder &addTexture(u32 location, Texture *pTexture);
    ProgramDescriptionBuilder &addTexture(u32 location, Texture &texture);

    /// @brief Sets name of the program.
    /// @param name A name that should be set as the name of the program.
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setName(const std::string &name);

    /// @brief Sets name of the program to an unique ID.
    ///
    /// Programs have to have a name to provide a namespace for shaders that are
    /// declared inside of such a program. If no name is described by some clause, then it
    /// is possible to set the name to a unique ID.
    ///
    /// @returns A reference to this builder
    ProgramDescriptionBuilder &setNameFromID();

    /// @brief Creates a name of the shader that is enclosed in constructed program's namespace.
    /// @param originalName A name of the shader without a namespace.
    /// @returns A name of the shader in program's namespace.
    [[nodiscard]] std::string createShaderName(const std::string &originalName) const;

    /// @brief Adds a buffer to the program.
    /// @param desc Buffer description that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &addBuffer(BufferDescription &desc);

    /// @brief Adds a material to the program.
    /// @param desc Material description that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &addMaterial(MaterialData &desc);

    /// @brief Sets a mesh to the program
    /// @param desc Mesh description that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setMesh(MeshDescription &desc);

    /// @brief Adds a shader code to the program.
    /// @param code shader code that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &addShaderCode(ShaderCode &code);

    ProgramDescriptionBuilder &setOptions(const Options &opts);

    ProgramDescriptionBuilder &setDrawCommand(DrawMode mode, u64 count);

    /// @brief Sets the polygon mode to program's context.
    /// @param mode Polygon mode value.
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setOption(gl::PolygonMode mode);

    /// @brief Sets the polygon mode to either front, back or both faces to program's context.
    /// @param mode Polygon mode value.
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setOption(gl::Face face, gl::PolygonMode mode);

    /// @brief Sets the culling mode to program's context.
    /// @param mode Polygon mode value.
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setOption(gl::CullingMode mode);

    /// @brief Sets the front face mode to program's context.
    /// @param mode Polygon mode value.
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setOption(gl::FrontFaceMode mode);

    /// @brief Sets the blending mode either source or destination to program's context.
    /// @param mode Polygon mode value.
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setOption(gl::BlendingFactor factor, bool isToSource);

    /// @brief Sets the polygon mode to program's context.
    /// @param mode Polygon mode value.
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setOption(gl::DepthFunction mode);

    /// @param desc Texture description that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &enableDepthTest(bool isEnabled);

    /// @param desc Texture description that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &enableFaceCulling(bool isEnabled);

    /// @param desc Texture description that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &enableBlending(bool isEnabled);

    /// @param desc Texture description that should be added to the program
    /// @returns A reference to this builder.
    ProgramDescriptionBuilder &setFrameBuffer(FrameBufferDescription &desc);

    ProgramDescriptionBuilder &reset();

    /// @brief Builds the desired program description.
    /// The builder cannot be used for building any further.
    ///
    /// @returns An rvalue reference to built program description.
    ProgramDescription &&build();
private:
    /// @brief An internal program description.
    ProgramDescription m_programDesc;
    bool m_isNameSet { false };
    inline static u64 m_id { 0 };
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_PROGRAM_DESCRIPTION_HPP
