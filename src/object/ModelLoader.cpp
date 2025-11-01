#include "object/ModelLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"


/**

    struct Vertex:
        v3 pos
        v3 normal;
        v2 texcoord;


    def processMesh(t_mesh, materials):
        material = materials[t_mesh.material_id]

        list<Vertex> vertices = getVertices(t_mesh) // vbo -> vao

        Mesh mesh = new Mesh(vertices, material)

        return mesh

    def processMaterial(t_material):
        m = new Material(t_material)
        return m

    t_meshes, t_materials = LoadObj()

    meshes = []
    materials = []

    for (t_material : t_materials) {
        m = processMaterial(t_maaterial);
        materials.push_back(m)
    }

    for (t_mesh : t_meshes) {
        Mesh mesh = processMesh(t_mesh, materials)

        model.addMesh(mesh)
    }

 */

ModelLoader::ModelLoader(const char* name) {
    std::string inputfile = std::string("../assets/models/obj/") + name;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str(), "../assets/models/obj/");

    if (!err.empty()) std::cerr << "Err: " << err << std::endl;
    if (!ret) throw std::runtime_error("Failed to load OBJ file!");

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            // Position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)
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

            //  UV coordinates (if exist)
            if (index.texcoord_index >= 0) {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }
    }
}

Model ModelLoader::Load() {
    auto vbo = make_ref(new VertexBuffer(vertices.data(), vertices.size() * sizeof(float), {{ElementType::Float, 3}, {ElementType::Float, 3}, {ElementType::Float, 2}}));
    auto vao = make_ref(new VertexArray(vbo));
    return Model(vao);
}
