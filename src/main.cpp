#include <App.hpp>

class Program : public App {
private:

protected:
    void Update(ImGuiIO &io) override {
        ImGui::Begin("Window");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

public:
    Program(int width, int height, const char *title, Uint32 flags) : App(width, height, title, flags) {}
};

int main(int argc, char *argv[])
{
    Program p(800, 600, "Program", SDL_WINDOW_SHOWN);
    p.Run();

    return 0;
}