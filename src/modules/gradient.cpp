//
// Created by charly on 11/9/24.
//

#include "gradient.h"

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