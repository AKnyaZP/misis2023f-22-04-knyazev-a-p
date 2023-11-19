//#include "scan_gui.h"
//#include <iostream>
//
//int main() {
//    if (!glfwInit())
//        return -1;
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
//    GLFWwindow* window = glfwCreateWindow(1920, 1080, "DocScan", NULL, NULL);
//    if (window == NULL)
//        return 1;
//    glfwMakeContextCurrent(window);
//    gl3wInit();
//    glfwSwapInterval(1);
//    gladLoadGL();
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGui_ImplOpenGL3_Init("#version 330");
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGuiIO& io = ImGui::GetIO();
//    (void)io;
//
//    ImGuiWindowFlags windowflag = 0;
//    windowflag |= ImGuiWindowFlags_NoBackground;
//    windowflag |= ImGuiWindowFlags_NoTitleBar;
//    windowflag |= ImGuiWindowFlags_MenuBar;
//    windowflag |= ImGuiWindowFlags_NoBringToFrontOnFocus;
//    io.FontGlobalScale = 2.0f;
//
//    while (!glfwWindowShouldClose(window)) {
//        glfwPollEvents();
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//        ImGui::SetNextWindowPos({ 0, 0 });
//        ImGui::SetNextWindowSize({ 1920, 1080 });
//
//        ImGui::Begin("DocScan", NULL, windowflag);
//        if (ImGui::BeginMenuBar()) {
//            if (ImGui::MenuItem("Open...", "Ctrl+O")) {
//                std::cout << "open explorer" << std::endl;
//            }
//            if (ImGui::MenuItem("Close", "Ctrl+E")) {
//                return 0;
//            }
//        }
//        if ((ImGui::IsKeyDown(ImGuiKey_RightCtrl) || ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) && ImGui::IsKeyDown(ImGuiKey_O)) {
//            std::cout << "open explorer" << std::endl;
//        }
//        if ((ImGui::IsKeyDown(ImGuiKey_RightCtrl) || ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) && ImGui::IsKeyDown(ImGuiKey_E)) {
//            return 0;
//        }
//
//        ImGui::End();
//        ImGui::Render();
//        int display_w, display_h;
//        glfwGetFramebufferSize(window, &display_w, &display_h);
//        glViewport(0, 0, display_w, display_h);
//        glClearColor(0.f, 0.f, 0.3f, 1.0f); 
//        glClear(GL_COLOR_BUFFER_BIT);
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//        glfwSwapBuffers(window);
//    }
//
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}

#include <scan_gui.h>


int main() {
    // Initialize GLFW
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Example", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup platform/renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll events
        glfwPollEvents();

        // Start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create GUI
        ImGui::Begin("MyWindow");
        ImGui::Text("Hello, world!");
        ImGui::End();

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Cleanup GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

