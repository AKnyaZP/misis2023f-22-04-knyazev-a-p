#include <include/scan/scan.h>
#include <Windows.h>
#include <cstdlib>

int main() {
	setlocale(LC_ALL, "Russian");
	//std::string image_path = std::string(ASSETS_PATH) + "images_for_scan/RF.jpg";
	Image image("C:/Users/knyaz_ayotgwn/source/repos/misis2023f-22-04-knyazev-a-p/prj.cw/scan/images_for_scan/RF.jpg");
	image.image_scan();
	image.image_ocr();
	return 0;
}     