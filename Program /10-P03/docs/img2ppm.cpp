// img2ppm.cpp
// Converts JPG/PNG images into PPM (P3 ASCII format)

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using std::string;

// ------------------------------------------------------------
// Utility: lowercase string
// ------------------------------------------------------------
string toLower(string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return s;
}

// ------------------------------------------------------------
// Utility: extract file extension
// ------------------------------------------------------------
string fileExtension(const string& path) {
    size_t dot = path.find_last_of('.');
    if (dot == string::npos) return "";
    return toLower(path.substr(dot));
}

// ------------------------------------------------------------
// Validate input image type
// ------------------------------------------------------------
bool isValidImage(const string& ext) {
    return ext == ".jpg" || ext == ".jpeg" || ext == ".png";
}

// ------------------------------------------------------------
// Write PPM (P3 ASCII)
// ------------------------------------------------------------
bool writePPM(const string& path, unsigned char* data, int w, int h) {
    std::ofstream out(path);

    if (!out.is_open()) {
        std::cerr << "Error: cannot open output file: " << path << "\n";
        return false;
    }

    out << "P3\n"
        << w << " " << h << "\n"
        << "255\n";

    constexpr int CHANNELS = 3;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            const unsigned char* px = data + (y * w + x) * CHANNELS;

            out << static_cast<int>(px[0]) << " "
                << static_cast<int>(px[1]) << " "
                << static_cast<int>(px[2]);

            if (x != w - 1) out << " ";
        }
        out << "\n";
    }

    return true;
}

// ------------------------------------------------------------
// Main
// ------------------------------------------------------------
int main(int argc, char** argv) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <input.jpg/png> <output.ppm>\n";
        return 1;
    }

    string input  = argv[1];
    string output = argv[2];

    string ext = fileExtension(input);

    if (!isValidImage(ext)) {
        std::cerr << "Error: unsupported file type: " << ext << "\n";
        return 1;
    }

    int w = 0, h = 0, channels = 0;
    constexpr int FORCE_RGB = 3;

    unsigned char* img = stbi_load(
        input.c_str(), &w, &h, &channels, FORCE_RGB
    );

    if (!img) {
        std::cerr << "Error: failed to load image: " << input << "\n";
        std::cerr << "Reason: " << stbi_failure_reason() << "\n";
        return 1;
    }

    std::cout << "Loaded image\n"
              << "  File: " << input << "\n"
              << "  Size: " << w << " x " << h << "\n"
              << "  Channels: " << channels << " (converted to RGB)\n";

    if (!writePPM(output, img, w, h)) {
        stbi_image_free(img);
        return 1;
    }

    stbi_image_free(img);

    std::cout << "Saved PPM file: " << output << "\n";
    return 0;
}
