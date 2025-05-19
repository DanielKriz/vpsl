#include <vp/resources/mtl_import.hpp>

#include <fstream>

namespace vp::mtl {

namespace {

glm::vec3 toVector(std::stringstream &ss) {
    f32 x;
    f32 y;
    f32 z;
    ss >> x >> y >> z;
    return { x, y, z };
}

} // namespace

MaterialData import(std::istream &is) {
    MaterialData data {};
    std::string line {};

    while (std::getline(is, line)) {
        std::stringstream ss(line);
        std::string identifier{};
        ss >> identifier;
        if (identifier == "Ns") {
            f32 shininess {};
            ss >> shininess;
            data.setShininess(shininess);
        } else if (identifier == "Ka") {
            data.setAmbient(toVector(ss));
        } else if (identifier == "Kd") {
            data.setDiffuse(toVector(ss));
        } else if (identifier == "Ks") {
            data.setSpecular(toVector(ss));
        } else if (identifier == "Ke") {
            data.setEmissive(toVector(ss));
        } 
    }

    return data;
}

MaterialData importFromFile(const std::filesystem::path &path) {
    std::ifstream fin { path };
    if (not fin.is_open()) {
        throw std::runtime_error("TODO");
    }

    return import(fin);
}

} // namespace vp::mtl
