#include "Args.h"

#include <iostream>
#include <vector>
#include <cstdlib>

bool isImageFile(const std::string& filename) {

    std::vector<std::string> exts = {
        ".png", ".jpg", ".jpeg", ".bmp", ".ppm"
    };

    for (const auto& ext : exts) {

        if (filename.size() >= ext.size() &&
            filename.substr(filename.size() - ext.size()) == ext) {

            return true;
        }
    }

    return false;
}

std::pair<std::string, std::string> splitEq(const std::string& token) {

    size_t pos = token.find('=');

    if (pos == std::string::npos) {
        return {token, ""};
    }

    return {
        token.substr(0, pos),
        token.substr(pos + 1)
    };
}

void usage() {

    std::cerr
        << "Usage: ./imgtool <input_image> <output_image> [options]\n";
}

void error(const std::string& msg) {

    std::cerr << "Error: " << msg << "\n";
    usage();
    std::exit(1);
}

Args Args::parse(int argc, char* argv[]) {

    Args args;

    if (argc < 3) {
        error("output file is required");
    }

    args.input = argv[1];
    args.output = argv[2];

    if (!isImageFile(args.input)) {
        error("invalid input image extension");
    }

    if (!isImageFile(args.output)) {
        error("invalid output image extension");
    }

    for (int i = 3; i < argc; ++i) {

        std::string token = argv[i];

        auto parts = splitEq(token);

        std::string opt = parts.first;
        std::string val = parts.second;

        // FLAGS

        if (opt == "--grayscale" || opt == "-g") {
            args.grayscale = true;
        }

        else if (opt == "--blur" || opt == "-l") {
            args.blur = true;
        }

        else if (opt == "--flipH" || opt == "-h") {
            args.flipH = true;
        }

        else if (opt == "--flipV" || opt == "-v") {
            args.flipV = true;
        }

        // BRIGHTEN

        else if (opt == "--brighten" || opt == "-b") {

            args.use_brighten = true;

            if (val.empty()) {

                if (i + 1 >= argc) {
                    error("'--brighten' requires an integer value");
                }

                val = argv[++i];

                if (!val.empty() && val[0] == '-') {
                    error("'--brighten' expected a value but got option '" + val + "'");
                }
            }

            try {

                args.brighten = std::stoi(val);

            } catch (...) {

                error("invalid integer for '--brighten': '" + val + "'");
            }

            if (args.brighten < -255 || args.brighten > 255) {
                error("'--brighten' must be in [-255, 255]");
            }
        }

        // ROTATE

        else if (opt == "--rotate" || opt == "-r") {

            args.use_rotate = true;

            if (val.empty()) {

                if (i + 1 >= argc) {
                    error("'--rotate' requires an integer value");
                }

                val = argv[++i];

                if (!val.empty() && val[0] == '-') {
                    error("'--rotate' expected a value but got option '" + val + "'");
                }
            }

            try {

                args.rotate = std::stoi(val);

            } catch (...) {

                error("invalid integer for '--rotate': '" + val + "'");
            }

            if (!(args.rotate == 0 ||
                  args.rotate == 90 ||
                  args.rotate == 180 ||
                  args.rotate == 270)) {

                error("'--rotate' must be one of {0, 90, 180, 270}");
            }
        }

        // UNKNOWN OPTION

        else {
            error("unknown option '" + opt + "'");
        }
    }

    return args;
}

void Args::print() const {

    std::cout << "INPUT  : " << input << "\n";
    std::cout << "OUTPUT : " << output << "\n";

    std::cout << "FLAGS  : ";

    if (grayscale) std::cout << "grayscale ";
    if (blur) std::cout << "blur ";
    if (flipH) std::cout << "flipH ";
    if (flipV) std::cout << "flipV ";

    std::cout << "\n";

    std::cout << "PARAMS : ";

    if (use_brighten) {
        std::cout << "brighten=" << brighten << " ";
    }

    if (use_rotate) {
        std::cout << "rotate=" << rotate;
    }

    std::cout << "\n";
}
