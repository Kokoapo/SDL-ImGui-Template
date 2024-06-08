#include <App.hpp>

void App::SetupInit(const char* title, Uint32 flags) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        exit(-1);
 
    windowPtr = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        flags
    );

    if(!windowPtr) {
        SDL_Quit();
        exit(-1);
    }

    rendererPtr = SDL_CreateRenderer(windowPtr, -1, 0);

    if (!rendererPtr) {
        SDL_DestroyWindow(windowPtr);
        SDL_Quit();
        exit(-1);
    }

    texturePtr = SDL_CreateTexture(rendererPtr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

    // ImGui Init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplSDL2_InitForSDLRenderer(
        windowPtr,
        rendererPtr
    );
    ImGui_ImplSDLRenderer2_Init(rendererPtr);
}

void App::SetupDraw() {
    SDL_SetRenderDrawBlendMode(rendererPtr, SDL_BLENDMODE_NONE);
    
    SDL_SetRenderTarget(rendererPtr, texturePtr);
    SDL_SetRenderDrawBlendMode(rendererPtr, SDL_BLENDMODE_NONE);
    SDL_SetTextureBlendMode(texturePtr, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(rendererPtr, 0, 0, 0, 0);
    SDL_RenderFillRect(rendererPtr, NULL);

    Draw();
    SDL_SetRenderTarget(rendererPtr, NULL);

    SDL_SetRenderDrawBlendMode(rendererPtr, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(texturePtr, SDL_BLENDMODE_ADD);
    SDL_RenderCopy(rendererPtr, texturePtr, NULL, NULL);
    SDL_SetRenderDrawBlendMode(rendererPtr, SDL_BLENDMODE_NONE);   
}

App::App(int width, int height, const char *title, Uint32 flags) {
    this->width = width;
    this->height = height;

    SetupInit(title, flags);
}

App::~App() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyTexture(texturePtr);
    SDL_DestroyRenderer(rendererPtr);
    SDL_DestroyWindow(windowPtr);
    SDL_Quit();
}

void App::CriarImGui() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void App::Render() {
    SDL_SetRenderDrawColor(rendererPtr, 0, 0, 0, 0);
    SDL_RenderClear(rendererPtr);

    SetupDraw();

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(rendererPtr);
}

void App::Run() {
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    
    Start(io);

    running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT || (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(windowPtr)))
                running = false;
            UpdateEvent(io, e);
        } 

        CriarImGui();

        Update(io);

        Render();
        
        LateUpdate(io);
    }

    End(io);
}

void App::Start(ImGuiIO& io) {
    // Override Function
}

void App::UpdateEvent(ImGuiIO& io, SDL_Event e) {
    // Override Function
}

void App::Update(ImGuiIO& io) {
    // Override Function
}

void App::Draw() {
    // Override Function
}

void App::LateUpdate(ImGuiIO& io) {
    // Override Function
}

void App::End(ImGuiIO& io) {
    // Override Function
}
