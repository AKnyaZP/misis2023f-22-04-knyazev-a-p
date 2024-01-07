// scan_gui.h : Include file for standard system include files,
// or project specific include files.

#include<iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>
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

        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

        // Применение размытия
        cv::Mat blurred;
        cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

        // Сохранение исходного изображения
        cv::Mat orig = img.clone();

        // Отображение результата
        cv::imshow("Scanned Document", orig);
        cv::waitKey(0);

    }

    void image_ocr() {
        std::ofstream file("C:/Users/knyaz_ayotgwn/source/repos/misis2023f-22-04-knyazev-a-p/scan/output.txt");
        if (!file) {
            std::cerr << "Unable to open file for writing\n";
        }

        std::cout << "download image... \n";
        // Загрузка изображения
        cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
        if (img.empty()) {
            std::cerr << "Error! Image wasn't loaded \n";
        }
        else
            std::cout << "Done \n";

        std::cout << "image processing \n";
        tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
        // Initialize tesseract-ocr with English and Russian languages
        if (api->Init(NULL, "rus+eng")) {
            fprintf(stderr, "Could not initialize tesseract.\n");
            exit(1);
        }

        // Set image data
        api->SetImage((uchar*)img.data, img.cols, img.rows, img.channels(), img.step);

        // Get OCR result
        char* outText = api->GetUTF8Text();
        printf("OCR output:\n%s", outText);
        file << "OCR output:\n" << outText << "\n";

        // Clean up
        api->End();
        delete[] outText;
        delete api;
        file.close();

    }

private:
    std::string image_path;
};