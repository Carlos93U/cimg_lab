//
// Created by charly on 11/9/24.
//

#ifndef GRADIENT_H
#define GRADIENT_H

#include "CImg.h"
using namespace cimg_library;

// Function to compute the gradient of an image
CImg<unsigned char> compute_gradient(const CImg<unsigned char>& image);

#endif //GRADIENT_H
