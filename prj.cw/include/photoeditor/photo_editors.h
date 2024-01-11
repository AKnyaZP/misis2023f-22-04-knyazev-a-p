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

class Editor { // ���������� ������ Editor

public:
   Editor(GLFWwindow* window) : window(window) { // ����������� ������ Editor
       glfwMakeContextCurrent(window); // ��������� �������� ��������� GLFW
       gl3wInit(); // ������������� gl3w
       glfwSwapInterval(1); // ��������� ��������� ������ ������� GLFW
       gladLoadGL(); // �������� ������� OpenGL � ������� glad

       IMGUI_CHECKVERSION(); // �������� ������ ImGui
       ImGui::CreateContext(); // �������� ������ ��������� ImGui
       //ImGui::StyleColorsDark(); // ��������� ������� ����� ��� ImGui
       ImGui_ImplOpenGL3_Init("#version 330"); // ������������� ���������� ImGui ��� OpenGL
       ImGui_ImplGlfw_InitForOpenGL(window, true); // ������������� ���������� ImGui ��� GLFW
   };
   Editor(const Editor&) = default; // ����������� ����������� ������ Editor
   Editor(Editor&&) = default; // ����������� ����������� ������ Editor
   ~Editor() = default; // ���������� ������ Editor
   
   void render() { // ����� render ������ Editor
       ImGui::Render(); // ��������� ImGui
       int display_w, display_h; // ���������� ���������� ��� ������ � ������ ������� �������
       glfwGetFramebufferSize(window, &display_w, &display_h); // ��������� �������� ������� �������
       glViewport(0, 0, display_w, display_h); // ��������� ������� ���������
       glClearColor(0.f, 0.f, 0.3, 1.0f); // ��������� ����� �������
       glClear(GL_COLOR_BUFFER_BIT); // ������� ������ �����
       ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // ��������� ������ ��������� ImGui

       glfwSwapBuffers(window); // ����� ������� GLFW
   }

   
private:
   GLFWwindow* window; // ��������� �� ���� GLFW
};





//cmake --install . --config release --prefix C:\Users\knyaz_ayotgwn\Desktop\install_for_pe