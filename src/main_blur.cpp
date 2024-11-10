//
// Created by charly on 11/10/24.
//

#include "CImg.h"
#include "modules/blur.h"
#include <iostream>

using namespace cimg_library;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_image_path> <output_image_path>" << std::endl;
        return 1;
    }

    const char* input_path = argv[1];
    const char* output_path = argv[2];
    CImg<unsigned char> image(input_path);

    // Apply the blur operation
    CImg<unsigned char> blurred_image = apply_blur(image);

    // Save the blurred image to the output path
    blurred_image.save(output_path);

    std::cout << "Blurred image saved to " << output_path << std::endl;

    return 0;
}
