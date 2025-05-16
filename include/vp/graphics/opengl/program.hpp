#ifndef VP_GRAPHICS_OPENGL_PROGRAM_HPP
#define VP_GRAPHICS_OPENGL_PROGRAM_HPP

#include <utility>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <string>

#include <glad/glad.h>

#include <vp/types.hpp>
#include <vp/graphics/opengl/object.hpp>
#include <vp/graphics/opengl/utils.hpp>
#include <vp/graphics/opengl/shader.hpp>
#include <vp/graphics/opengl/uniform.hpp>
#include <vp/graphics/opengl/texture.hpp>
#include <vp/graphics/draw_modes.hpp>

namespace vp::gl::opengl {

class Program : public opengl::Object {
public:
    Program();
    ~Program() override;

    template <typename T>
    Program &setUniform(const std::string &name, T value) {
        if (auto it = m_uniformCache.find(name); it != m_uniformCache.end()) {
            auto &uniform = it->second;
            uniform.set<T>(value);
        } else {
            auto location = glGetUniformLocation(m_descriptor, name.data());
            Uniform uniform = Uniform(name, location);
            m_uniformCache.insert({name, uniform});
            uniform.set<T>(value);
        }
        return *this;
    }

#if 0
    void draw() {
#if 0
        static enum32 textureUnits[] = { GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2 };
        for (u32 i = 0u; i < m_textures.size(); ++i) {
            auto &textureUniform = m_textures[i];
            glActiveTexture(textureUnits[i]);
            glBindTexture(GL_TEXTURE_2D, textureUniform.second.get());
            setUniform<i32>(textureUniform.first, static_cast<i32>(i));
        }
#endif
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
#else
    void draw() const;
#endif

    Program &attachShader(Shader &shader);
    Program &detachShader(Shader &shader);
    Program &link();
    void use() const;

    void populateAttributes();
    void populateUniforms();

    void addTextureFromDescription(const desc::TextureDescription &desc);
    void addTexture(Texture &texture);

    void setDrawCommand(const DrawCommand &command);

private:
    std::unordered_map<std::string, Uniform> m_uniformCache;
    std::vector<Texture> m_textures;
    std::optional<DrawCommand> m_drawCommand;
};

} // namespace vp::gl::opengl

#endif // VP_GRAPHICS_OPENGL_PROGRAM_HPP
