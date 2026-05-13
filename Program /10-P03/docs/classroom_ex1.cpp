#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;

// ---------------------------
// Pixel + Image types
// ---------------------------

struct Pixel {
    int r{}, g{}, b{};
};

using Image = vector<vector<Pixel>>;

// ---------------------------
// Blur configuration
// ---------------------------

enum class BlurStrength {
    Low = 1,
    Medium = 3,
    High = 6
};

// Convert enum → number of passes
int blurPassCount(BlurStrength strength) {
    return static_cast<int>(strength);
}

// ---------------------------
// Utility: clamp RGB values
// ---------------------------

int clamp255(int v) {
    return std::max(0, std::min(255, v));
}

// ---------------------------
// Single blur pass (3x3 box filter)
// ---------------------------

Image blurOnce(const Image& src) {
    int h = src.size();
    int w = src[0].size();

    Image out = src;

    for (int y = 1; y < h - 1; ++y) {
        for (int x = 1; x < w - 1; ++x) {

            int r = 0, g = 0, b = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    const Pixel& p = src[y + dy][x + dx];
                    r += p.r;
                    g += p.g;
                    b += p.b;
                }
            }

            out[y][x].r = clamp255(r / 9);
            out[y][x].g = clamp255(g / 9);
            out[y][x].b = clamp255(b / 9);
        }
    }

    return out;
}

// ---------------------------
// Full blur pipeline
// ---------------------------

Image applyBlur(const Image& input, BlurStrength strength) {
    Image result = input;

    int passes = blurPassCount(strength);

    for (int i = 0; i < passes; ++i) {
        result = blurOnce(result);
    }

    return result;
}

// ---------------------------
// Optional debug helper
// ---------------------------

void printBlurMode(BlurStrength strength) {
    switch (strength) {
        case BlurStrength::Low:
            cout << "Blur mode: LOW\n";
            break;
        case BlurStrength::Medium:
            cout << "Blur mode: MEDIUM\n";
            break;
        case BlurStrength::High:
            cout << "Blur mode: HIGH\n";
            break;
    }
}

// ---------------------------
// Command structure (for pipeline expansion)
// ---------------------------

struct Command {
    string name;
    int value = 0;
};

// ---------------------------
// Minimal Args parser scaffold
// ---------------------------

class Args {
private:
    vector<Command> commands;

public:
    Args(int argc, char** argv) {
        parse(argc, argv);
    }

    void parse(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            string arg = argv[i];

            if (arg == "--blur" || arg == "-b") {
                int value = 3; // default medium
                if (i + 1 < argc && isdigit(argv[i + 1][0])) {
                    value = std::stoi(argv[++i]);
                }

                commands.push_back({"blur", value});
            }
        }
    }

    const vector<Command>& getCommands() const {
        return commands;
    }
};

// ---------------------------
// Main
// ---------------------------

int main(int argc, char** argv) {
    Args args(argc, argv);

    cout << "Image pipeline initialized.\n";

    return 0;
}
