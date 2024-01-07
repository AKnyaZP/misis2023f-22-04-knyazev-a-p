#include <scan.h>
#include <Windows.h>
int main() {
	//setlocale(LC_ALL, "Russian");
	Image image("C:/Users/knyaz_ayotgwn/source/repos/misis2023f-22-04-knyazev-a-p/scan/images_for_scan/english_text.jpg");
	image.image_scan();
	image.image_ocr();
	return 0;
}  