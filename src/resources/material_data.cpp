#include <vp/resources/material_data.hpp>

namespace vp {
MaterialData::MaterialData(
    glm::vec3 ambient,
    glm::vec3 specular,
    glm::vec3 diffuse,
    glm::vec3 emissive,
    f32 shininess
) : m_ambient(ambient), m_specular(specular), m_diffuse(diffuse)
  , m_emmisive(emissive), m_shininess(shininess) {}

void MaterialData::setAmbient(glm::vec3 value) noexcept {
    m_ambient = value;
}

void MaterialData::setSpecular(glm::vec3 value) noexcept {
    m_specular = value;
}

void MaterialData::setEmissive(glm::vec3 value) noexcept {
    m_emmisive = value;
}

void MaterialData::setDiffuse(glm::vec3 value) noexcept {
    m_diffuse = value;
}

void MaterialData::setShininess(f32 value) noexcept {
    m_shininess = value;
}

const glm::vec3 &MaterialData::getAmbient() const noexcept {
    return m_ambient;
}

const glm::vec3 &MaterialData::getSpecular() const noexcept {
    return m_specular;
}

const glm::vec3 &MaterialData::getEmissive() const noexcept {
    return m_emmisive;
}

const glm::vec3 &MaterialData::getDiffuse() const noexcept {
    return m_diffuse;
}

f32 MaterialData::getShininess() const noexcept {
    return m_shininess;
}

} // namespace vp
