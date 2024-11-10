//
// Created by charly on 11/10/24.
//

#include "blur.h"

using namespace cimg_library;

// Function to apply a blur to the image
CImg<unsigned char> apply_blur(const CImg<unsigned char>& image) {
    // Apply a simple blur filter
    return image.get_blur(8.0);  // Adjust the blur radius as needed
}
