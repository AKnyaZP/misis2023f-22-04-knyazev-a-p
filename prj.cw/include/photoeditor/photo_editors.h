/**
 * @file
 * @brief ���� photo_editors.h, ���������� ����� Editor � ��� ������.
 */
#define IMGUI_DEFINE_MATH_OPERATORS // ����������� �������������� ���������� ��� ImGui
#include "imgui.h" // ����������� ���������� ImGui
#include <iosfwd> // ����������� ������������� ����� iosfwd ��� ������ � �������� �����-������
#include "imgui_impl_glfw.h" // ����������� ������������� ����� imgui_impl_glfw.h ��� ���������� ImGui � GLFW
#include "imgui_impl_opengl3.h" // ����������� ������������� ����� imgui_impl_opengl3.h ��� ���������� ImGui � OpenGL
#define GL_SILENCE_DEPRECATION // ����������� ������� ��� ���������� �������������� �� ���������� �������� OpenGL
#define USE_IMGUI_TABLES // ����������� ������� ��� ������������� ������ ImGui
#include<glad/glad.h> // ����������� ���������� glad ��� ���������� ��������� OpenGL
#include <GLFW/glfw3.h> // ����������� ���������� GLFW ��� �������� ���� � ��������� �����
#include <GL/gl3w.h> // ����������� ���������� gl3w ��� �������� ������� OpenGL
#include <dialog/ImGuiFileDialog/ImGuiFileDialog.h> // ����������� ���������� ImGuiFileDialog ��� ���������� ���� ��������� ���������
#include <opencv2/opencv.hpp> // ����������� ���������� OpenCV ��� ������ � �������������
#include <string> // ����������� ������������ ������ string ��� ������ �� ��������
#include <random> // ����������� ���������� random ��� ��������� ��������� �����
#include <ctime> // ����������� ���������� ctime ��� ������ �� ��������
#include <algorithm> // ����������� ���������� algorithm ��� ������ � �����������

/**
 * ���������� ������ Editor
 */
class Editor {

public:
    /**
     * ����������� ������ Editor
     * @param window ��������� �� ���� GLFW
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

    /**
     * ����������� ����������� ������ Editor
     */
    Editor(const Editor&) = default;

    /**
     * ����������� ����������� ������ Editor
     */
    Editor(Editor&&) = default;

    /**
     * ���������� ������ Editor
     */
    ~Editor() = default;

    /**
     * ����� render ������ Editor
     */
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
    /**
     * ��������� �� ���� GLFW
     */
    GLFWwindow* window;
};





//cmake --install . --config release --prefix C:\Users\knyaz_ayotgwn\Desktop\install_for_pe