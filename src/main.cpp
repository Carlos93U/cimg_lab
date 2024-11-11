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

// Function to trasform img
CImg<unsigned char> math_transformations(const CImg<unsigned char>& image) {
    // Apply a series of transformations
    CImgList<> mathOps(image, image.get_exp()/50, 10*image.get_sqrt(), (1+image.get_abs()).log(), image.get_pow(3));
    // Combine all transformations into a single image (in a row)
    CImg<unsigned char> combined_image = mathOps.get_append('x'); // Append images horizontally
    return  combined_image;
}

// Function to fill image
CImg<unsigned char> apply_fill(const CImg<unsigned char>& image) {
    CImg<unsigned char> filled_image = image.get_fill("(x*y)%255",true);
    return filled_image;
}

// enhance contrast
CImg<unsigned char> adjust_contrast(const CImg<unsigned char>& image) {
    CImg<unsigned char> imgOut;

    if (image.spectrum() == 1) {
        imgOut = image.get_equalize(256);
    } else if (image.spectrum() == 3) {
        CImg<unsigned char> R = image.get_channel(0).get_equalize(256);
        CImg<unsigned char> G = image.get_channel(1).get_equalize(256);
        CImg<unsigned char> B = image.get_channel(2).get_equalize(256);
        CImgList<unsigned char> channels(R, G, B);
        imgOut = channels.get_append('c');
    }
    return imgOut;
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
    } else if (operation == "math_transformations") {
        result_image = math_transformations(image);
    } else if (operation == "fill") {
        result_image = apply_fill(image);
    } else if (operation == "contrast") {
        result_image = adjust_contrast(image);
    } else {
        std::cerr << "Unknown operation: " << operation << std::endl;
        return 1;
    }

    result_image.save(output_path);
    std::cout << operation << " operation completed and saved to " << output_path << std::endl;

    return 0;
}
