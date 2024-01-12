/**
 * @file
 * @brief Файл image.h, содержащий класс Image и его методы.
 */

#include <opencv2/opencv.hpp> /**< Включаем библиотеку OpenCV для работы с изображениями */
#include <string> /**< Включаем стандартный класс string для работы со строками */
#include <iosfwd> /**< Включаем заголовочный файл iosfwd для работы с потоками ввода-вывода */
#include <GL/gl3w.h> /**< Включаем библиотеку gl3w для работы с OpenGL */
#include <memory> /**< Включаем заголовочный файл memory для работы с умными указателями */

 /**
  * @brief Класс Image для работы с изображениями.
  */
class Image {
public:
    Image() {} /**< Конструктор по умолчанию */
    Image(const Image&) = default; /**< Конструктор копирования */
    Image(Image&&) = default; /**< Конструктор перемещения */
    ~Image() = default; /**< Деструктор */

    float saturation = 1.0f; /**< Параметры изображения: насыщенность */
    float hue = 1.0f; /**< Оттенок */
    float exposition = 1.0f; /**< Экспозиция */
    float colorful_temperature = 1.0f; /**< Цветовая температура */
    float contrast = 1.0f; /**< Контраст */
    float sharpness = 0.0f; /**< Острота */
    float brightness = 1.0f; /**< Яркость */
    int blur = 1; /**< Размытие */

    /**
     * @brief Метод для установки параметров изображения по умолчанию.
     */
    void default_method() {
        saturation = default_saturation;
        hue = default_hue;
        exposition = default_exposition;
        colorful_temperature = default_colorful_temperature;
        contrast = default_contrast;
        sharpness = default_sharpness;
        brightness = default_brightness;
        blur = default_blur;
    }

    /**
     * @brief Структура для освобождения памяти, занимаемой cv::Mat.
     */
    struct MatDeleter {
        void operator()(cv::Mat* mat) const {
            mat->release();
            delete mat;
        }
    };

    /**
     * @brief Метод для создания изображения.
     * @param file_name Путь к файлу изображения.
     * @return Изображение, загруженное из файла.
     */
    cv::Mat create_image(std::string file_name) {
        auto image = std::unique_ptr<cv::Mat, MatDeleter>(new cv::Mat(cv::imread(file_name.c_str())));
        if (image->empty()) {
            std::cerr << "Не удалось открыть изображение.\n";
            return {};
        }

        std::unique_ptr<float> sharp = std::make_unique<float>(sharpness);
        *sharp *= 7.0f;

        cv::addWeighted(*image, 0.5, *image, brightness - 0.5, 0.0, *image);

        cv::cvtColor(*image, *image, cv::COLOR_BGR2RGB);

        auto contrast_image = std::unique_ptr<cv::Mat, MatDeleter>(new cv::Mat(cv::Mat::zeros(image->size(), image->type())));
        image->convertTo(*contrast_image, -1, contrast, 0);

        std::vector<cv::Mat> rgb_ct;
        cv::split(*contrast_image, rgb_ct);
        if (colorful_temperature > 1.0f) {
            rgb_ct[0] *= colorful_temperature;
        }
        /**
         * @brief Применяет цветовую температуру к каналу изображения, если цветовая температура меньше 1.0f.
         */
        else if (colorful_temperature < 1.0f) {
            rgb_ct[0] *= (colorful_temperature);
        }

        /**
         * @brief Слияние каналов обратно в изображение.
         */
        cv::merge(rgb_ct, *image);

        /**
         * @brief Преобразование изображения из RGB в HSV.
         */
        cv::cvtColor(*image, *image, cv::COLOR_RGB2HSV);

        /**
         * @brief Создание вектора для хранения каналов изображения.
         */
        std::vector<cv::Mat> hsv_channels;

        /**
         * @brief Разделение изображения на каналы.
         */
        cv::split(*image, hsv_channels);

        /**
         * @brief Применение оттенка к каналу изображения.
         */
        hsv_channels[0] *= hue;

        /**
         * @brief Применение насыщенности к каналу изображения.
         */
        hsv_channels[1] *= saturation;

        /**
         * @brief Применение экспозиции к каналу изображения.
         */
        hsv_channels[2] *= exposition;

        /**
         * @brief Слияние каналов обратно в изображение.
         */
        cv::merge(hsv_channels, *image);

        /**
         * @brief Преобразование изображения из HSV в RGB.
         */
        cv::cvtColor(*image, *image, cv::COLOR_HSV2RGB);

        /**
         * @brief Применение размытия к изображению.
         */
        cv::blur(*image, *image, cv::Size(blur, blur));

        /**
         * @brief Матрица для фильтрации изображения.
         */
        float matr[9]{
           -0.0375f - 0.05f * *sharp, -0.0375f - 0.05f * *sharp, -0.0375f - 0.05f * *sharp,
           -0.0375f - 0.05f * *sharp, 1.3f + 0.4f * *sharp, -0.0375f - 0.05f * *sharp,
           -0.0375f - 0.05f * *sharp, -0.0375f - 0.05f * *sharp, -0.0375f - 0.05f * *sharp
        };

        /**
         * @brief Создание матрицы фильтра.
         */
        cv::Mat kernel_matrix = cv::Mat(3, 3, CV_32FC1, &matr);

        /**
         * @brief Применение фильтра к изображению.
         */
        cv::filter2D(*image, *image, 32, kernel_matrix);

        /**
         * @brief Преобразование изображения из RGB в RGBA.
         */
        cv::cvtColor(*image, *image, cv::COLOR_RGB2RGBA);

        /**
         * @brief Освобождение памяти, занятой параметром остроты.
         */
        sharp.release();

        /**
         * @brief Возвращение измененного изображения.
         */
        return *image;
    }

    /**
     * @brief Метод для создания текстуры из изображения.
     * @param result_image_rgba Изображение, которое нужно преобразовать в текстуру.
     * @return Текстура, созданная из изображения.
     */
    ImTextureID create_texture(cv::Mat result_image_rgba) {
        GLuint texture_id; // ID текстуры
        glGenTextures(1, &texture_id); // Генерация ID текстуры

        glBindTexture(GL_TEXTURE_2D, texture_id); // Привязка текстуры

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Установка параметров текстуры
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, result_image_rgba.cols, result_image_rgba.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, result_image_rgba.data); // Загрузка данных изображения в текстуру

        ImTextureID texture = (void*)(intptr_t)texture_id; // Создание текстуры

        return texture; // Возвращение текстуры
    }

    /**
     * @brief Метод для отображения изображения в ImGui.
     * @param texture Текстура изображения, которое нужно отобразить.
     */
    void show_image_imgui(ImTextureID texture) {
        ImGui::Image(texture, ImGui::GetWindowSize());
    }

    /**
     * @brief Метод для удаления текстуры.
     * @param texture_id ID текстуры, которую нужно удалить.
     */
    void kill_texture(GLuint texture_id) {
        glDeleteTextures(1, &texture_id);
    }

    /**
     * @brief Метод для преобразования изображения из формата RGBA в BGR.
     * @param result_image_rgba Изображение, которое нужно преобразовать.
     * @return Изображение в формате BGR.
     */
    cv::Mat RGBAtoBGR(cv::Mat result_image_rgba) {
        cv::cvtColor(result_image_rgba, result_image_rgba, cv::COLOR_RGBA2BGR); // Преобразование изображения
        return result_image_rgba; // Возвращение изображения
    }

private:
    float default_saturation = 1.0f; /**< Значения по умолчанию для параметров изображения: насыщенность */
    float default_hue = 1.0f; /**< Оттенок */
    float default_exposition = 1.0f; /**< Экспозиция */
    float default_colorful_temperature = 1.0f; /**< Цветовая температура */
    float default_contrast = 1.0f; /**< Контраст */
    float default_sharpness = 0.0f; /**< Острота */
    float default_brightness = 1.0f; /**< Яркость */
    int default_blur = 1; /**< Размытие */
};








