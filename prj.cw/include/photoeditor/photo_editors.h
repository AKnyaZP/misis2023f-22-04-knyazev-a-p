/**
 * @file
 * @brief Файл photo_editors.h, содержащий класс Editor и его методы.
 */
#define IMGUI_DEFINE_MATH_OPERATORS // Определение математических операторов для ImGui
#include "imgui.h" // Подключение библиотеки ImGui
#include <iosfwd> // Подключение заголовочного файла iosfwd для работы с потоками ввода-вывода
#include "imgui_impl_glfw.h" // Подключение заголовочного файла imgui_impl_glfw.h для интеграции ImGui с GLFW
#include "imgui_impl_opengl3.h" // Подключение заголовочного файла imgui_impl_opengl3.h для интеграции ImGui с OpenGL
#define GL_SILENCE_DEPRECATION // Определение макроса для подавления предупреждений об устаревших функциях OpenGL
#define USE_IMGUI_TABLES // Определение макроса для использования таблиц ImGui
#include<glad/glad.h> // Подключение библиотеки glad для управления функциями OpenGL
#include <GLFW/glfw3.h> // Подключение библиотеки GLFW для создания окон и обработки ввода
#include <GL/gl3w.h> // Подключение библиотеки gl3w для загрузки функций OpenGL
#include <dialog/ImGuiFileDialog/ImGuiFileDialog.h> // Подключение библиотеки ImGuiFileDialog для диалоговых окон файлового менеджера
#include <opencv2/opencv.hpp> // Подключение библиотеки OpenCV для работы с изображениями
#include <string> // Подключение стандартного класса string для работы со строками
#include <random> // Подключение библиотеки random для генерации случайных чисел
#include <ctime> // Подключение библиотеки ctime для работы со временем
#include <algorithm> // Подключение библиотеки algorithm для работы с алгоритмами

/**
 * Объявление класса Editor
 */
class Editor {

public:
    /**
     * Конструктор класса Editor
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

    /**
     * Конструктор копирования класса Editor
     */
    Editor(const Editor&) = default;

    /**
     * Конструктор перемещения класса Editor
     */
    Editor(Editor&&) = default;

    /**
     * Деструктор класса Editor
     */
    ~Editor() = default;

    /**
     * Метод render класса Editor
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
     * Указатель на окно GLFW
     */
    GLFWwindow* window;
};





//cmake --install . --config release --prefix C:\Users\knyaz_ayotgwn\Desktop\install_for_pe