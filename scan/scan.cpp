﻿#include <scan.h>
int main() {
	Image image("C:/Users/knyaz_ayotgwn/source/repos/misis2023f-22-04-knyazev-a-p/scan/images_for_scan/example.png");
	image.image_scan();
	image.image_ocr();
	return 0;
}  