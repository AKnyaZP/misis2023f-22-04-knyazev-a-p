// scan_gui.h : Include file for standard system include files,
// or project specific include files.

#include<iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
//#include "dialog/ImGuiFileDialog/ImGuiFileDialog.h"
// TODO: Reference additional headers your program requires here.

class Image {
public:
    // конструктор класса Image, который принимает путь до изображения
    Image(const std::string& imagePath) : image_path(imagePath) {} 
    Image(const Image&) = default;
    Image(Image&&) = default;
    ~Image() = default;

    void image_scan() {
        cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

        // Проверьте, было ли изображение успешно загружено
        if (img.empty()) {
            std::cerr << "Image not found.\n";
            return;
        }

        // Преобразование изображения в оттенки серого
        cv::Mat gray_img;
        cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);

        // Усиление контраста изображения
        double alpha = 1.0; // Контрастное коэффициент
        double beta = 0;   // Коэффициент смещения
        cv::Mat contrast_img;
        img.convertTo(contrast_img, -1, alpha, beta);

        //// Улучшаем разрешение изображения
        //cv::Mat resized_img;
        //cv::resize(contrast_img, resized_img, cv::Size(), 2, 2, cv::INTER_LINEAR);

        /*cv::Mat noise;
        cv::randn(noise, cv::Scalar::all(0), cv::Scalar::all(20));
        cv::Mat noisyImage = contrast_img.clone();
        noisyImage += noise;*/

        cv::imshow("image", contrast_img);
        cv::waitKey(0);

    }

    void image_ocr() {
        // Загрузка изображения
        cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

        // Создание объекта tesseract
        tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();

        // Инициализация tesseract для английского языка
        if (ocr->Init(NULL, "rus+eng")) {
            fprintf(stderr, "Could not initialize tesseract.\n");
            exit(1);
        }

        // Установка изображения для распознавания
        ocr->SetImage(img.data, img.cols, img.rows, 3, img.step);

        // Получение распознанного текста
        char* text = ocr->GetUTF8Text();
        printf("OCR output:\n%s", text);

        // Освобождение ресурсов
        delete[] text;
        ocr->End();
    }

private:
    std::string image_path;
};