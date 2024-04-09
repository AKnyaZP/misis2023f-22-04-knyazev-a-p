#include <opencv2/opencv.hpp> 
#include <string> 
#include <iosfwd> 
#include <GL/gl3w.h> 
#include <memory> 

 /**
  * @brief Класс Image для работы с изображениями.
  */
class Image {
public:
    Image() = default;
    Image(const Image&) = default; 
    Image(Image&&) = default; 
    ~Image() = default; 

    float saturation = 1.0f;
    float hue = 1.0f; 
    float exposition = 1.0f; 
    float colorful_temperature = 1.0f; 
    float contrast = 1.0f; 
    float sharpness = 0.0f; 
    float brightness = 1.0f; 
    int blur = 1; 

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
     * @struct MatDeleter
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

        else if (colorful_temperature < 1.0f) {
            rgb_ct[0] *= (colorful_temperature);
        }

        cv::merge(rgb_ct, *image);
        cv::cvtColor(*image, *image, cv::COLOR_RGB2HSV);

        std::vector<cv::Mat> hsv_channels;

        cv::split(*image, hsv_channels);

        hsv_channels[0] *= hue;
        hsv_channels[1] *= saturation;
        hsv_channels[2] *= exposition;

        cv::merge(hsv_channels, *image);
        cv::cvtColor(*image, *image, cv::COLOR_HSV2RGB);
        cv::blur(*image, *image, cv::Size(blur, blur));

        float matr[9]{
           -0.0375f - 0.05f * *sharp, -0.0375f - 0.05f * *sharp, -0.0375f - 0.05f * *sharp,
           -0.0375f - 0.05f * *sharp, 1.3f + 0.4f * *sharp, -0.0375f - 0.05f * *sharp,
           -0.0375f - 0.05f * *sharp, -0.0375f - 0.05f * *sharp, -0.0375f - 0.05f * *sharp
        };

        cv::Mat kernel_matrix = cv::Mat(3, 3, CV_32FC1, &matr);

        cv::filter2D(*image, *image, 32, kernel_matrix);
        cv::cvtColor(*image, *image, cv::COLOR_RGB2RGBA);

        sharp.release();

        return *image;
    }

    /**
     * @brief Метод для создания текстуры из изображения.
     * @param result_image_rgba Изображение, которое нужно преобразовать в текстуру.
     * @return Текстура, созданная из изображения.
     */
    ImTextureID create_texture(cv::Mat result_image_rgba) {
        GLuint texture_id; /// ID текстуры
        glGenTextures(1, &texture_id); /// Генерация ID текстуры

        glBindTexture(GL_TEXTURE_2D, texture_id); /// Привязка текстуры

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /// Установка параметров текстуры
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, result_image_rgba.cols, result_image_rgba.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, result_image_rgba.data); // Загрузка данных изображения в текстуру

        ImTextureID texture = (void*)(intptr_t)texture_id; /// Создание текстуры

        return texture; /// Возвращение текстуры
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
    float default_saturation = 1.0f;
    float default_hue = 1.0f;
    float default_exposition = 1.0f; 
    float default_colorful_temperature = 1.0f;
    float default_contrast = 1.0f; 
    float default_sharpness = 0.0f; 
    float default_brightness = 1.0f; 
    int default_blur = 1; 
};








