// scan_gui.h : Include file for standard system include files,
// or project specific include files.

#include<iostream>
#include <opencv2/opencv.hpp>
#include <string>
//#include "dialog/ImGuiFileDialog/ImGuiFileDialog.h"
// TODO: Reference additional headers your program requires here.

class Image {
public:
    Image() {}
    Image(const Image&) = default;
    Image(Image&&) = default;
    ~Image() = default;


private:
    std::string image_path;
};