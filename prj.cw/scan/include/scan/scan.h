// scan_gui.h : Файл включения для стандартных системных файлов включения или проектно-специфических файлов включения.

#include<iostream> // Включение библиотеки iostream для операций ввода/вывода
#include <opencv2/opencv.hpp> // Включение библиотеки OpenCV для обработки изображений
#include <string> // Включение библиотеки string для манипуляции строками
#include <tesseract/baseapi.h> // Включение библиотеки Tesseract для оптического распознавания символов (OCR)
#include <leptonica/allheaders.h> // Включение библиотеки Leptonica для обработки изображений
#include <fstream> // Включение библиотеки fstream для работы с файлами
//#include "dialog/ImGuiFileDialog/ImGuiFileDialog.h" // Закомментировано по какой-то причине
// TODO: Ссылка на дополнительные заголовочные файлы, которые требуются вашей программе, здесь.

class Image {
public:
    // Конструктор класса Image, который принимает путь к изображению в качестве аргумента
    Image(const std::string& imagePath) : image_path(imagePath) {}
    Image(const Image&) = default; // Копирующий конструктор
    Image(Image&&) = default; // Перемещающий конструктор
    ~Image() = default; // Деструктор

    void image_scan() {
        cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR); // Чтение изображения

        // Проверка успешной загрузки изображения
        if (img.empty()) {
            std::cerr << "Изображение не найдено.\n";
            return;
        }

        cv::Mat gray; // Объявление объекта Mat для графического изображения
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); // Преобразование изображения в оттенки серого

        // Применение размытия Гаусса
        cv::Mat blurred;
        cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

        // Сохранение оригинального изображения
        cv::Mat orig = img.clone();

        // Отображение результата
        cv::imshow("Сканированный документ", orig);
        cv::waitKey(0);

    }

    void image_ocr() {
        std::ofstream file("C:/Users/knyaz_ayotgwn/source/repos/misis2023f-22-04-knyazev-a-p/prj.cw/scan/output.txt"); // Открытие файла для записи
        if (!file) {
            std::cerr << "Failed to open file for writing\n";
        }

        std::cout << "image downloading... \n";
        // Загрузка изображения
        cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
        if (img.empty()) {
            std::cerr << "Error! The image was not loaded \n";
        }
        else
            std::cout << "Done \n";

        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); // Преобразование изображения в оттенки серого
        cv::Mat blurred;
        cv::GaussianBlur(img, img, cv::Size(5, 5), 0); // Применение размытия Гаусса

        std::cout << "image proccessing \n";
        tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI(); // Создание нового экземпляра TessBaseAPI
        // Инициализация tesseract-ocr с английским и русским языками
        if (api->Init("C:/Users/knyaz_ayotgwn/source/repos/misis2023f-22-04-knyazev-a-p/prj.cw/scan/train", "rus+eng")) {
            fprintf(stderr, "Failed to initialize tesseract.\n");
            exit(1);
        }

        // Установка данных изображения
        api->SetImage((uchar*)img.data, img.cols, img.rows, img.channels(), img.step);

        api->SetRectangle(0, 0, img.cols, img.rows);

        // Получение результата OCR
        char* outText = api->GetUTF8Text();
        std::cout << "OCR has done its job successfully. You can see the result in the output.txt file";
        file << "OCR Output:\n" << outText << "\n";

        // Clean up
        api->End();
        delete[] outText;
        delete api;
        file.close();

    }

private:
    std::string image_path;
};