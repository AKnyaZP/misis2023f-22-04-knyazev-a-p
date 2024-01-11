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

class Editor { // Объявление класса Editor

public:
   Editor(GLFWwindow* window) : window(window) { // Конструктор класса Editor
       glfwMakeContextCurrent(window); // Установка текущего контекста GLFW
       gl3wInit(); // Инициализация gl3w
       glfwSwapInterval(1); // Установка интервала обмена буферов GLFW
       gladLoadGL(); // Загрузка функций OpenGL с помощью glad

       IMGUI_CHECKVERSION(); // Проверка версии ImGui
       ImGui::CreateContext(); // Создание нового контекста ImGui
       //ImGui::StyleColorsDark(); // Установка темного стиля для ImGui
       ImGui_ImplOpenGL3_Init("#version 330"); // Инициализация реализации ImGui для OpenGL
       ImGui_ImplGlfw_InitForOpenGL(window, true); // Инициализация реализации ImGui для GLFW
   };
   Editor(const Editor&) = default; // Конструктор копирования класса Editor
   Editor(Editor&&) = default; // Конструктор перемещения класса Editor
   ~Editor() = default; // Деструктор класса Editor
   
   void render() { // Метод render класса Editor
       ImGui::Render(); // Рендеринг ImGui
       int display_w, display_h; // Объявление переменных для ширины и высоты области дисплея
       glfwGetFramebufferSize(window, &display_w, &display_h); // Получение размеров области дисплея
       glViewport(0, 0, display_w, display_h); // Установка области просмотра
       glClearColor(0.f, 0.f, 0.3, 1.0f); // Установка цвета очистки
       glClear(GL_COLOR_BUFFER_BIT); // Очистка буфера цвета
       ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Рендеринг данных рисования ImGui

       glfwSwapBuffers(window); // Обмен буферов GLFW
   }

   
private:
   GLFWwindow* window; // Указатель на окно GLFW
};





//cmake --install . --config release --prefix C:\Users\knyaz_ayotgwn\Desktop\install_for_pe