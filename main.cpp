#include <filament/Engine.h>
#include <filament/Scene.h>
#include <filament/View.h>
#include <filament/Renderer.h>
#include <filament/Camera.h>
#include <filament/LightManager.h>
#include <filament/RenderableManager.h>
#include <filament/VertexBuffer.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>

#include <filament/math/float3.h>
#include <filament/math/mat4.h>

#include <utils/EntityManager.h>
#include <utils/Entity.h>

#include <iostream>
#include <vector>

using namespace filament;
using namespace filament::math;
using namespace utils;

struct Vertex {
    float3 position;
    float3 color;
};

int main() {
    // Create Filament engine
    Engine* engine = Engine::create();

    // Scene and camera
    Scene* scene = engine->createScene();
    Camera* camera = engine->createCamera(Entity());
    View* view = engine->createView();
    view->setScene(scene);
    view->setCamera(camera);

    // Simple triangle geometry
    std::vector<Vertex> vertices = {
        {{0.0f, 0.5f, 0.0f}, {1, 0, 0}},
        {{-0.5f, -0.5f, 0.0f}, {0, 1, 0}},
        {{0.5f, -0.5f, 0.0f}, {0, 0, 1}}
    };
    std::vector<uint16_t> indices = {0, 1, 2};

    VertexBuffer* vb = VertexBuffer::Builder()
        .vertexCount(vertices.size())
        .bufferCount(1)
        .attribute(VertexAttribute::POSITION, 0, VertexBuffer::AttributeType::FLOAT3, offsetof(Vertex, position))
        .attribute(VertexAttribute::COLOR, 0, VertexBuffer::AttributeType::FLOAT3, offsetof(Vertex, color))
        .build(*engine);

    vb->setBufferAt(*engine, 0, VertexBuffer::BufferDescriptor(vertices.data(), vertices.size() * sizeof(Vertex), nullptr, nullptr));

    IndexBuffer* ib = IndexBuffer::Builder()
        .indexCount(indices.size())
        .bufferType(IndexBuffer::IndexType::USHORT)
        .build(*engine);

    ib->setBuffer(*engine, IndexBuffer::BufferDescriptor(indices.data(), indices.size() * sizeof(uint16_t), nullptr, nullptr));

    // Material (unlit)
    Material* material = Material::Builder()
        .package(nullptr, 0) // no material file
        .build(*engine);
    MaterialInstance* matInstance = material->createInstance();

    // Renderable
    Entity renderable = EntityManager::get().create();
    RenderableManager::Builder(1)
        .boundingBox({{-1, -1, -1}, {1, 1, 1}})
        .geometry(0, RenderableManager::PrimitiveType::TRIANGLES, ib, vb)
        .material(0, matInstance)
        .build(*engine, renderable);
    scene->addEntity(renderable);

    // Light
    Entity light = EntityManager::get().create();
    LightManager::Builder(LightManager::Type::SUN)
        .color({1, 1, 1})
        .intensity(100000)
        .direction({0, -1, -1})
        .build(*engine, light);
    scene->addEntity(light);

    std::cout << "Offscreen PBR setup complete.\n";

    // Normally here you would render to a RenderTarget offscreen
    // For simplicity, we skip actual framebuffer writing

    // Cleanup
    engine->destroy(materialInstance);
    engine->destroy(material);
    engine->destroy(vb);
    engine->destroy(ib);
    engine->destroy(renderable);
    engine->destroy(light);
    engine->destroy(camera);
    engine->destroy(view);
    engine->destroy(scene);
    Engine::destroy(&engine);

    return 0;
}
