#include <scan_gui.h>

int main()
{
    ImFont* pFont = io.Fonts->AddFontFromFileTTF("Roboto-Regular.ttf",
        10.0f, NULL,
        ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    // Инициализация GLFW
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1200, 800, "ScanGui", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Инициализация ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Инициализация стилей и платформы
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Главный цикл приложения
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Начало нового кадра ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Создание окна ImGui
        ImGui::Begin("Choose a picture to work with");

        // Добавление содержимого в окно

        ImGui::Text(u8"текст");

        if (ImGui::Button("Click on me!")) {
            ImGui::Text("The button is pressed");
        }
        ImGui::End();

        // Рендеринг окна ImGui
        glClearColor(0.00f, 0.00f, 0.00f, 0.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Освобождение памяти и завершение работы
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
