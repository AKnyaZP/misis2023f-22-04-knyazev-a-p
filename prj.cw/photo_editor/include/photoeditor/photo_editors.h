/**
 * @file
 * @brief Файл photo_editors.h, содержащий класс Editor и его методы.
 */
#define IMGUI_DEFINE_MATH_OPERATORS 
#include "imgui.h" 
#include <iosfwd> 
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h" 
#define GL_SILENCE_DEPRECATION 
#define USE_IMGUI_TABLES 
#include<glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GL/gl3w.h>
#include <dialog/ImGuiFileDialog/ImGuiFileDialog.h> 
#include <opencv2/opencv.hpp> 
#include <string>
#include <random> 
#include <ctime> 
#include <algorithm> 

 /**
  * @class Editor
  * @brief Основной класс для создания приложения photoeditor
  */ 
class Editor {

public:
    /**
     * @brief Конструктор класса Editor
     * @param window Указатель на окно GLFW
     */
    Editor(GLFWwindow* window) : window(window) {
        glfwMakeContextCurrent(window);
        gl3wInit();
        glfwSwapInterval(1);
        gladLoadGL();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui_ImplGlfw_InitForOpenGL(window, true);
    };

    Editor(const Editor&) = default;
    Editor(Editor&&) = default;
    ~Editor() = default;

    void render() {
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.f, 0.f, 0.3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

private:
    GLFWwindow* window;
};

