#include "CImg.h"
#include "modules/gradient.h"
#include <iostream>

using namespace cimg_library;

int main(int argc, char* argv[]) {
    // Check if input and output paths are provided as arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_image_path> <output_image_path>" << std::endl;
        return 1;
    }

    // Load the input image from the specified path
    const char* input_path = argv[1];
    const char* output_path = argv[2];
    CImg<unsigned char> image(input_path);

    // Compute the gradient of the image
    CImg<unsigned char> gradient_image = compute_gradient(image);

    // Save the gradient image to the output path
    gradient_image.save(output_path);

    std::cout << "Gradient image saved to " << output_path << std::endl;

    return 0;
}
