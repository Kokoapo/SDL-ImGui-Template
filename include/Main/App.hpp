#ifndef APP_HPP
#define APP_HPP

#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class App {
protected:
    SDL_Window* windowPtr;
    SDL_Renderer* rendererPtr;
    SDL_Texture* texturePtr;

    int width, height;
    bool running;

    void SetupInit(const char *title, Uint32 flags);
    void SetupDraw();
    void CriarImGui();
    void Render();

    virtual void Start(ImGuiIO& io);
    virtual void UpdateEvent(ImGuiIO& io, SDL_Event e);
    virtual void Update(ImGuiIO& io);
    virtual void Draw();
    virtual void LateUpdate(ImGuiIO& io);
    virtual void End(ImGuiIO& io);
public:
    App(int width, int height, const char *title, Uint32 flags);
    ~App();
    void Run();
};

#endif