#include <scan.h>

int main() {
	cv::Mat image = cv::imread("images_for_scan/example.png", cv::IMREAD_COLOR);
	cv::imshow("image", image);
}