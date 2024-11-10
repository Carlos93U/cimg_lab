#include "CImg.h"
#include <iostream>
#include <string>

using namespace cimg_library;

// Function to compute the gradient of an image
CImg<unsigned char> compute_gradient(const CImg<unsigned char>& image) {
    // Compute the gradient in the X direction (get the first image in the list)
    CImg<float> gradient_x = image.get_gradient("x")[0];
    // Compute the gradient in the Y direction (get the first image in the list)
    CImg<float> gradient_y = image.get_gradient("y")[0];
    // Combine gradients (for simplicity, here we just add them)
    CImg<float> gradient = (gradient_x + gradient_y) / 2;
    // Convert the float gradient to unsigned char for display
    CImg<unsigned char> gradient_display = gradient.normalize(0, 255);

    return gradient_display;
}

// Function to apply blur to an image
CImg<unsigned char> apply_blur(const CImg<unsigned char>& image) {
    return image.get_blur(2.0);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <operation> <input_image_path> <output_image_path>" << std::endl;
        return 1;
    }

    const std::string operation = argv[1];
    const char* input_path = argv[2];
    const char* output_path = argv[3];
    CImg<unsigned char> image(input_path);

    CImg<unsigned char> result_image;

    if (operation == "gradient") {
        result_image = compute_gradient(image);
    } else if (operation == "blur") {
        result_image = apply_blur(image);
    } else {
        std::cerr << "Unknown operation: " << operation << std::endl;
        return 1;
    }

    result_image.save(output_path);
    std::cout << operation << " operation completed and saved to " << output_path << std::endl;

    return 0;
}
