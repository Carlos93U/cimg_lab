//
// Created by charly on 11/9/24.
//
#include "CImg.h"
#include <iostream>
using namespace cimg_library;

int main() {
    // Load an image
    const CImg<unsigned char> image("data/eagle.jpg");

    // Display the image in a window
    CImgDisplay display(image, "Loaded Image");

    // Keep the window open until it is closed
    while (!display.is_closed()) {
        display.wait();
    }

    return 0;
}
