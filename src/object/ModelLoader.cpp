#include "object/ModelLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"

ModelLoader::ModelLoader(const std::string& basedir) : basedir(basedir) {
    if (!this->basedir.ends_with("/")) this->basedir.append("/");
}

Model ModelLoader::Load(const std::string& filename) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, (basedir + filename).c_str(), basedir.c_str());

    if (!err.empty()) fprintf(stderr, "Err: %s\n", err.c_str());
    if (!ret) throw std::runtime_error("Failed to load OBJ file!");

    // materials
    std::vector<ref<Material>> materialRefs;

    for (auto& m : materials) {
        MaterialProps props;
        props.ambient = glm::vec3(m.ambient[0], m.ambient[1], m.ambient[2]);
        props.diffuse = glm::vec3(m.diffuse[0], m.diffuse[1], m.diffuse[2]);
        props.specular = glm::vec3(m.specular[0], m.specular[1], m.specular[2]);
        props.shininess = m.shininess;
        materialRefs.push_back(make_ref(new Material(props)));
    }

    Model model;

    // vertices
    for (const auto& shape : shapes) {

        std::vector<float> vertices;

        for (const auto& index : shape.mesh.indices) {
            // position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // normals
            if (index.normal_index >= 0) {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            //  uv coords
            if (index.texcoord_index >= 0) {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }

        std::vector<std::tuple<ElementType::Type, int>> layout = {
            {ElementType::Float, 3},
            {ElementType::Float, 3},
            {ElementType::Float, 2}
        };

        auto vbo = make_ref(new VertexBuffer(vertices.data(), vertices.size() * sizeof(float), layout));
        auto vao = make_ref(new VertexArray(vbo));

        int material_id = -1;
        if (!shape.mesh.material_ids.empty()) {
            material_id = shape.mesh.material_ids[0];

            for (int mat_id : shape.mesh.material_ids) {
                if (mat_id != material_id) {
                    fprintf(stderr, "Warning: material ids differ inside a shape\n");
                    break;
                }
            }
        }

        ref<Material> material;
        if (materialRefs.empty() || material_id < 0 || material_id >= (int)materialRefs.size()) material = make_ref(new Material({}));
        else material = materialRefs[material_id];

        auto mesh = make_ref(new Mesh(vao, material));
        model.AddMesh(mesh);
    }

    return model;
}
