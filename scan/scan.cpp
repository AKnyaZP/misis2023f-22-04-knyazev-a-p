#include <scan.h>

int main() {
	cv::Mat image = cv::imread('image.png', cv::IMREAD_COLOR);
	if (image.empty())
		std::cerr << "file is empty";
		return -1;
}