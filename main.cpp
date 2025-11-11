#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/View.h>
#include <filament/Camera.h>
#include <filament/Skybox.h>
#include <filament/Viewport.h>
#include <utils/EntityManager.h>

using namespace filament;
using namespace utils;

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Filament + SDL2 Minimal Example",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    // Get native X11 window handle
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    void* nativeWindow = (void*)wmInfo.info.x11.window;

    Engine* engine = Engine::create();
    SwapChain* swapChain = engine->createSwapChain(nativeWindow);
    Renderer* renderer = engine->createRenderer();

    Scene* scene = engine->createScene();
    View* view = engine->createView();

    Entity cameraEntity = EntityManager::get().create();
    Camera* camera = engine->createCamera(cameraEntity);
    view->setCamera(camera);
    view->setScene(scene);

    Skybox* skybox = Skybox::Builder().color({0.1f, 0.2f, 0.4f, 1.0f}).build(*engine);
    scene->setSkybox(skybox);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        view->setViewport({0, 0, (uint32_t)width, (uint32_t)height});

        if (renderer->beginFrame(swapChain)) {
            renderer->render(view);
            renderer->endFrame();
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    // Cleanup
    engine->destroy(skybox);
    engine->destroy(view);
    engine->destroy(scene);
    engine->destroy(renderer);
    engine->destroy(swapChain); // destroy swap chain like normal
    Engine::destroy(&engine);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
