/**
 * @file
 * @brief Файл photo_editors.cpp, содержащий класс int main(), в котором и реализовано приложение.
 */
#include <include/photoeditor/photo_editors.h>
#include <include/image/image.h>
#include <flags.cpp>

int main()
{
    /**
    * @brief Инициализирует библиотеку GLFW и проверяет, была ли инициализация успешной
    */
    if (!glfwInit())
        return -1;

    /**
     * @brief Устанавливает версию OpenGL для контекста окна
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /**
     * @brief Устанавливает профиль OpenGL для контекста окна
     */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /**
     * @brief Разрешает изменение размера окна
     */
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    /**
     * @brief Создает новое окно с заданными параметрами
     */
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Photo Editor", NULL, NULL);

    /**
     * @brief Проверяет, было ли создание окна успешным
     */
    if (window == NULL)
        return 1;

    /**
     * @brief Создает новый экземпляр редактора с созданным окном
     */
    Editor editor(window);

    /**
     * @brief Получает доступ к объекту ввода/вывода ImGui
     */
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    /**
     * @brief Устанавливает флаги окна ImGui
     */
    ImGuiWindowFlags windowflag = 0;
    windowflag |= ImGuiWindowFlags_NoBackground;
    windowflag |= ImGuiWindowFlags_NoTitleBar;
    windowflag |= ImGuiWindowFlags_MenuBar;
    windowflag |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    /**
     * @brief Устанавливает масштаб шрифта ImGui
     */
    io.FontGlobalScale = 2.0f;

    /**
     * @brief Создает новые экземпляры классов Flag и Image
     */
    Flag flag;
    Image image;

    /**
     * @brief Устанавливает фильтры файлов для диалоговых окон
     */
    const char* filters = "Image files (*.jpg){.jpg}";

    /**
     * @brief Создает новую строку для хранения пути к файлу
     */
    static std::string filePathName = "";

    /**
     * @brief Инициализирует флаги для управления параметрами и диалогами
     */
    flag.sl_par = false;
    flag.t_par = false;
    flag.dialog = false;
    flag.flag_for_save_dialog = false;
    flag.flag_for_tool = false;
    flag.if_image_is_open = false;
    flag.flag_success = false;


    while (!glfwWindowShouldClose(window))
    {
        /**
 * @brief Опрашивает системные события
 */
        glfwPollEvents();

        /**
         * @brief Подготавливает ImGui для нового кадра OpenGL
         */
        ImGui_ImplOpenGL3_NewFrame();

        /**
         * @brief Подготавливает ImGui для нового кадра GLFW
         */
        ImGui_ImplGlfw_NewFrame();

        /**
         * @brief Подготавливает ImGui для нового кадра
         */
        ImGui::NewFrame();

        /**
         * @brief Устанавливает следующую позицию окна ImGui
         */
        ImGui::SetNextWindowPos({ 0, 0 });

        /**
         * @brief Устанавливает следующий размер окна ImGui
         */
        ImGui::SetNextWindowSize({ 1920, 1080 });


        /**
         * @brief создаём окно ImGui
         */
        ImGui::Begin("PhotoEditor (Main window)", NULL, windowflag);

        /**
         * @brief создаём меню-бар и кнопки для него
         */
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("file")) {
                if (ImGui::MenuItem("Open...", "Ctrl+O")) {

                    flag.dialog = true;
                }

                if (ImGui::MenuItem("Save", "Ctrl+S")) { flag.flag_for_save_dialog = true; }

                if (ImGui::MenuItem("Close", "Ctrl+W")) { flag.flag_for_tool = true; }



                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("settings")) {
                if (ImGui::MenuItem("Sliders parametres", "Ctrl+P")) {
                    flag.t_par = false;
                    flag.sl_par = true;
                }

                if (ImGui::MenuItem("Text parametres", "Ctrl + T")) {
                    flag.sl_par = false;
                    flag.t_par = true;
                }
                if (ImGui::MenuItem("Default value for parametres", "Ctrl + L")) {
                    image.default_method();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }


        /**
         * реализовываем горячие клавиши
         */
        if ((ImGui::IsKeyDown(ImGuiKey_RightCtrl) || ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) && ImGui::IsKeyDown(ImGuiKey_O)) {
            flag.dialog = true;
        }

        if ((ImGui::IsKeyDown(ImGuiKey_RightCtrl) || ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) && ImGui::IsKeyDown(ImGuiKey_S))
        {
            flag.flag_for_save_dialog = true;
        }

        if ((ImGui::IsKeyDown(ImGuiKey_RightCtrl) || ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) && ImGui::IsKeyDown(ImGuiKey_W)) {
            flag.flag_for_tool = true;
        }

        if ((ImGui::IsKeyDown(ImGuiKey_RightCtrl) || ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) && ImGui::IsKeyDown(ImGuiKey_P)) {
            flag.t_par = false;
            flag.sl_par = true;
        }

        if ((ImGui::IsKeyDown(ImGuiKey_RightCtrl) || ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) && ImGui::IsKeyDown(ImGuiKey_T)) {
            flag.sl_par = false;
            flag.t_par = true;
        }

        if ((ImGui::IsKeyDown(ImGuiKey_RightCtrl) || ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) && ImGui::IsKeyDown(ImGuiKey_L)) {
            image.default_method();
        }

        /**
         * создание диалогового окна для открытия изображения .jpg 
         */
        if (flag.dialog) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose a File", filters, ".", 1, nullptr, ImGuiFileDialogFlags_Modal);
            flag.dialog = false;
        }

        ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".jpg", ImVec4(0.0f, 1.0f, 1.0f, 0.9f));

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey", ImGuiFileDialogFlags_ConfirmOverwrite | ImGuiWindowFlags_NoCollapse))
        {

            if (ImGuiFileDialog::Instance()->IsOk())
            {
                filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            }

            ImGuiFileDialog::Instance()->Close();
        }
        


        std::string file_name = filePathName;
        /**
         * реализовываем ползунки, для установки значений параметров изображений
         */
        if ((flag.sl_par)) {

            ImGui::SetCursorPos(ImVec2(10, (ImGui::GetWindowHeight()) / 3));

            ImGui::PushItemWidth(500);
            ImGui::BeginGroup();

            ImGui::Text("Sliders parametres");

            (ImGui::SliderFloat("Saturation", &image.saturation, 0.0f, 2.0f));

            (ImGui::SliderFloat("Hue", &image.hue, 0.0f, 2.0f));

            (ImGui::SliderFloat("Exposition", &image.exposition, 0.0f, 2.0f));

            ImGui::SliderFloat("Colorful temperature", &image.colorful_temperature, 0.0f, 2.0f);

            ImGui::SliderFloat("Contrast", &image.contrast, 0.0f, 2.0f);

            ImGui::SliderFloat("noise reduction/Sharpness", &image.sharpness, -2.0f, 2.0f);

            (ImGui::SliderFloat("Brightness", &image.brightness, 0.0f, 2.0f));

            ImGui::SliderInt("Blurred", &image.blur, 1, 20);


            ImGui::EndGroup();
            ImGui::PopItemWidth();
        }

        /**
         * реализовываем текстовые поля, для установки значений параметров изображений
         */
        if (!(flag.sl_par) && (flag.t_par)) {
            ImGui::SetCursorPos(ImVec2(10, (ImGui::GetWindowHeight()) / 3));

            ImGui::PushItemWidth(500);
            ImGui::BeginGroup();

            ImGui::Text("Text parametres");

            ImGui::InputFloat("Saturation", &image.saturation);

            ImGui::InputFloat("Hue", &image.hue);

            ImGui::InputFloat("Exposition", &image.exposition);

            ImGui::InputFloat("Colorful temperature", &image.colorful_temperature);

            ImGui::InputFloat("Contrast", &image.contrast);

            ImGui::InputFloat("Noise reduction/Sharpness", &image.sharpness);

            ImGui::InputFloat("Brightness", &image.brightness);

            ImGui::InputInt("Blurred", &image.blur);

            ImGui::EndGroup();
            ImGui::PopItemWidth();
        }


        ImGui::SetCursorPos(ImVec2(((ImGui::GetWindowWidth()) / 3), ((ImGui::GetWindowHeight()) / 3) - 50));

        if (file_name != "") {

            if (image.blur <= 0) {
                image.blur = 1;
            }
            /**
            * Начинает новую область окна ImGui с заголовком "Image". Флаг ImGuiWindowFlags_NoCollapse гарантирует, что окно не может быть свернуто.
            */
            ImGui::Begin("Image", NULL, ImGuiWindowFlags_NoCollapse);
            /**
             * Выводит изображение на экран. Метод create_texture используется для создания текстуры изображения, а метод show_image_imgui - для отображения этой текстуры.
             */
            image.show_image_imgui(image.create_texture(image.create_image(file_name)));
            /**
            * Устанавливает флаг if_image_is_open в true, указывая, что изображение открыто.
            */
            flag.if_image_is_open = true;
            /**
            * Заканчивает область окна, которую мы начали ранее.
            */
            ImGui::End();

        }

        if (flag.flag_for_tool && flag.if_image_is_open) {
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x / 2.0f, ImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMax().y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

            ImGui::SetNextWindowPos(ImVec2(100, 200));
            /**
            * Открывает всплывающее окно под названием "Notification(exit)".
            */
            ImGui::OpenPopup("Notification(exit)", ImGuiWindowFlags_NoResize);
        }

        else if (flag.flag_for_tool && !flag.if_image_is_open)
            return 0;

        if (flag.flag_for_tool) {
            /**
            * Начинает модальное всплывающее окно под названием "Notification(exit)".
            */
            (ImGui::BeginPopupModal("Notification(exit)"));
            ImGui::Text("Are you sure you want to leave");
            ImGui::Separator();

            if (ImGui::Button("Exit")) {
                return 0;
            }

            if (ImGui::Button("Save")) {
                flag.flag_for_save_dialog = true;
                flag.flag_for_tool = false;
            }

            if (ImGui::Button("Close notification")) {
                flag.flag_for_tool = false;
            }
            /**
            * Закрываем модальное всплывающее окно под названием "Notification(exit)".
            */
            ImGui::EndPopup();

        }

        if (flag.flag_for_save_dialog) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFolderDlg", "Choose Folder", nullptr, ".");
            // Отображаем диалоговое окно сохранения файла  
        }
        /**
         * Проверяем, отображается ли диалоговое окно для выбора папки. Если да, то выполняются действия внутри этого блока кода.
         */
        if (ImGuiFileDialog::Instance()->Display("ChooseFolderDlg")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                /**
               * Получаем полный путь к выбранному файлу.
               */
                std::string FPName = ImGuiFileDialog::Instance()->GetFilePathName();

                std::time_t currentTime = std::time(nullptr);
                std::tm* localTime = std::localtime(&currentTime);

                /**
                * Преобразуем локальное время в строку формата "ГГГГ-ММ-ДД_чч-мм".
                */
                char dateTimeString[20];
                std::strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d_%H-%M", localTime);

                /**
                * Создаём имя файла, добавляя к дате и времени суффикс "_photo_editor_image.jpg".
                */
                std::string saveFileName = std::string(dateTimeString) + "_photo_editor_image.jpg";

                /**
                * Сохраняем изображение в выбранную папку с созданным именем файла.
                */
                cv::imwrite(FPName + "/" + saveFileName, image.RGBAtoBGR(image.create_image(file_name)));
                flag.flag_success = true;
            }
            /**
            * Закрываем диалоговое окно для выбора папки.
            */
            ImGuiFileDialog::Instance()->Close();
            flag.flag_for_save_dialog = false;

        }

        /**
         * Проверяем, были ли операция успешной и не отображается ли диалоговое окно для выбора папки. Если оба условия выполняются, то открывается всплывающее окно с сообщением о успешном сохранении.
         */
        if (flag.flag_success == true && flag.flag_for_save_dialog == false) {
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x / 2.0f, ImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMax().y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

            ImGui::OpenPopup("Notification(save)");
        }

        /**
         * Проверяем, была ли операция успешной. Если да, то открывается модальное всплывающее окно с сообщением о успешном сохранении.
         */
        if (flag.flag_success) {
            (ImGui::BeginPopupModal("Notification(save)"));
            ImGui::Text("Image is save successful");
            ImGui::Separator();

            if (ImGui::Button("OK")) {
                flag.flag_success = false;
            }
            ImGui::EndPopup();
        }
        /**
         * Заканчиваем область окна, которую мы начали ранее.
         */
        ImGui::End();
        /**
         * рендерим приложение
         */
        editor.render();
    }
    /**
     * Завершаем работу с библиотеками ImGui.
     */
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
