#include <scan.h>
int main() {
    // Read the image
    cv::Mat img = cv::imread("C:/Users/knyaz_ayotgwn/source/repos/misis2023f-22-04-knyazev-a-p/scan/images_for_scan/example.png", cv::IMREAD_COLOR);

    // Check if the image is loaded successfully
    if (img.empty()) {
        std::cerr << "Error: Could not load the image.\n";
        return 1;
    }

    // Display the image
    cv::imshow("My Image", img);

    // Wait for a key press and close the window
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}  