#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <X11/Xlib.h>
#undef Success   // Fix X11 macro conflict

#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/View.h>
#include <filament/Camera.h>
#include <filament/Material.h>
#include <filament/RenderableManager.h>
#include <filament/TransformManager.h>
#include <filament/VertexBuffer.h>
#include <filament/IndexBuffer.h>

#include <utils/EntityManager.h>
#include <utils/Entity.h>
#include <filament/MaterialInstance.h>

#include <iostream>
#include <vector>
#include <cstddef>

using namespace filament;
using namespace utils;

struct Vertex {
    float position[3];
    float normal[3];
};

int main() {
    // SDL initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    SDL_Window* window = SDL_CreateWindow("Filament PBR",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_VULKAN);

    // Filament engine and scene
    Engine* engine = Engine::create();
    Scene* scene = engine->createScene();
    View* view = engine->createView();
    Renderer* renderer = engine->createRenderer();

    Camera* camera = engine->createCamera(EntityManager::get().create());
    view->setCamera(camera);
    view->setScene(scene);

    // Load material
    FILE* f = fopen("default.filamat", "rb");
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    std::vector<uint8_t> matData(size);
    fread(matData.data(), 1, size, f);
    fclose(f);

    Material* material = Material::Builder().package(matData.data(), matData.size()).build(*engine);
    MaterialInstance* matInstance = material->getDefaultInstance();
    matInstance->setParameter("baseColor", math::float3{1.0f, 0.0f, 0.0f});
    matInstance->setParameter("metallic", 0.0f);
    matInstance->setParameter("roughness", 0.5f);
    matInstance->setParameter("reflectance", 0.5f);

    // Triangle vertices
    std::vector<Vertex> vertices(3);
    vertices[0] = {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    vertices[1] = {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    vertices[2] = {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}};

    std::vector<uint32_t> indices = {0, 1, 2};

    VertexBuffer* vb = VertexBuffer::Builder()
        .vertexCount(vertices.size())
        .attribute(VertexAttribute::POSITION, 0, VertexBuffer::AttributeType::FLOAT3, offsetof(Vertex, position))
        .build(*engine);

    vb->setBufferAt(*engine, 0, VertexBuffer::BufferDescriptor(vertices.data(), vertices.size() * sizeof(Vertex)));

    IndexBuffer* ib = IndexBuffer::Builder()
        .indexCount(indices.size())
        .bufferType(IndexBuffer::IndexType::UINT)
        .build(*engine);

    ib->setBuffer(*engine, IndexBuffer::BufferDescriptor(indices.data(), indices.size() * sizeof(uint32_t)));

    // Create entity
    Entity triangle = EntityManager::get().create();
    RenderableManager::Builder(1)
        .boundingBox({{-1,-1,-1},{1,1,1}})
        .material(0, matInstance)
        .geometry(0, RenderableManager::PrimitiveType::TRIANGLES, vb, ib)
        .build(*engine, triangle);

    scene->addEntity(triangle);

    // Main loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) running = false;
        renderer->render(view);
    }

    Engine::destroy(&engine);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
