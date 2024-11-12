#include "CImg.h"
#include <iostream>
#include <string>

using namespace cimg_library;

/**
 * Computes the gradient of an image by calculating gradients in both X and Y directions.
 * Combines the gradients and normalizes them for display purposes.
 * @param image Input image in grayscale.
 * @return Image with computed gradient.
 */
CImg<unsigned char> compute_gradient(const CImg<unsigned char>& image) {
    CImg<float> gradient_x = image.get_gradient("x")[0];
    CImg<float> gradient_y = image.get_gradient("y")[0];
    CImg<float> gradient = (gradient_x + gradient_y) / 2;
    CImg<unsigned char> gradient_display = gradient.normalize(0, 255);
    return gradient_display;
}

/**
 * Applies a Gaussian blur to an image.
 * @param image Input image.
 * @return Blurred image.
 */
CImg<unsigned char> apply_blur(const CImg<unsigned char>& image) {
    return image.get_blur(2.0);
}

/**
 * Performs mathematical transformations on an image.
 * Includes exponential, square root, logarithmic, and power transformations.
 * @param image Input image.
 * @return Combined image of all transformations appended horizontally.
 */
CImg<unsigned char> math_transformations(const CImg<unsigned char>& image) {
    CImgList<> mathOps(image, image.get_exp()/50, 10*image.get_sqrt(), (1+image.get_abs()).log(), image.get_pow(3));
    CImg<unsigned char> combined_image = mathOps.get_append('x');
    return combined_image;
}

/**
 * Applies a fill transformation to the image.
 * Fills the image based on a formula using pixel coordinates.
 * @param image Input image.
 * @return Filled image.
 */
CImg<unsigned char> apply_fill(const CImg<unsigned char>& image) {
    CImg<unsigned char> filled_image = image.get_fill("(x*y)%255", true);
    return filled_image;
}

/**
 * Adjusts the contrast of an image by equalizing its histogram.
 * If the image is RGB, applies histogram equalization to each channel individually.
 * @param image Input image.
 * @return Contrast-enhanced image.
 */
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

/**
 * Applies morphological erosion to an image using a 5x5 square structuring element.
 * @param image Input image.
 * @return Eroded image.
 */
CImg<unsigned char> apply_erosion(const CImg<unsigned char>& image) {
    CImg<unsigned char> B = CImg<unsigned char>(5,5).fill(1);
    CImg<unsigned char> imgErode = image.get_erode(B);
    return imgErode;
}

/**
 * Applies morphological dilation to an image using a 5x5 square structuring element.
 * @param image Input image.
 * @return Dilated image.
 */
CImg<unsigned char> apply_dilation(const CImg<unsigned char>& image) {
    CImg<unsigned char> B = CImg<unsigned char>(5,5).fill(1);
    CImg<unsigned char> imgDilate = image.get_dilate(B);
    return imgDilate;
}

/**
 * Applies morphological closing to an image using a 5x5 square structuring element.
 * @param image Input image.
 * @return Closed image.
 */
CImg<unsigned char> apply_closing(const CImg<unsigned char>& image) {
    CImg<unsigned char> B = CImg<unsigned char>(5,5).fill(1);
    CImg<unsigned char> imgClose = image.get_dilate(B).get_erode(B);
    return imgClose;
}

/**
 * Applies morphological opening to an image using a 5x5 square structuring element.
 * @param image Input image.
 * @return Opened image.
 */
CImg<unsigned char> apply_opening(const CImg<unsigned char>& image) {
    CImg<unsigned char> B = CImg<unsigned char>(5,5).fill(1);
    CImg<unsigned char> imgOpen = image.get_erode(B).get_dilate(B);
    return imgOpen;
}

/**
 * Applies the Kramer-Bruckner filter for edge enhancement.
 * Uses morphological erosion and dilation to calculate the median value and enhance edges.
 * @param imgIn Input image.
 * @return Image with edges enhanced by Kramer-Bruckner filter.
 */
CImg<unsigned char> KramerBruckner(CImg<unsigned char>& imgIn) {
    CImg<unsigned char> imgOut(imgIn);
    CImg<unsigned char> mask = CImg<unsigned char>(5, 5).fill(1);
    CImg<unsigned char> imgErode = imgIn.get_erode(mask);
    CImg<unsigned char> imgDilate = imgIn.get_dilate(mask);

    cimg_forXY(imgOut, x, y) {
        float M = 0.5f * (static_cast<float>(imgErode(x, y)) + static_cast<float>(imgDilate(x, y)));
        imgOut(x, y) = (static_cast<float>(imgIn(x, y)) <= M ? imgErode(x, y) : imgDilate(x, y));
    }
    return imgOut;
}

/**
 * Main function to process command-line arguments and apply selected image processing operation.
 * Expects 3 arguments: <operation> <input_image_path> <output_image_path>.
 * Supported operations: gradient, blur, math_transformations, fill, contrast, erosion, dilation, opening, closing, kramer.
 */
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
    }  else if (operation == "erosion") {
        result_image = apply_erosion(image);
    }  else if (operation == "dilation") {
        result_image = apply_dilation(image);
    }  else if (operation == "opening") {
        result_image = apply_opening(image);
    }  else if (operation == "closing") {
        result_image = apply_closing(image);
    } else if (operation == "kramer") {
        result_image = KramerBruckner(image);
    } else {
        std::cerr << "Unknown operation: " << operation << std::endl;
        return 1;
    }

    result_image.save(output_path);
    std::cout << operation << " operation completed and saved to " << output_path << std::endl;

    return 0;
}
