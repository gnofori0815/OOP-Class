#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Empty class (still intentionally bad for teaching purposes)
class Args {
public:
    // nothing here yet on purpose
};

int main(int argc, char** argv) {

    // Print all arguments safely
    cout << "Argument list:\n";
    for (int i = 0; i < argc; i++) {
        cout << i << ": " << argv[i] << endl;
    }

    // FIXED: proper argument check (no crash)
    if (argc < 2) {
        cout << "Error: need at least one filename!\n";
        cout << "Usage: ./args_ex1 <filename> [options]\n";
        return 1;
    }

    string filename = argv[1];

    // FIXED: prevent out-of-bounds access (argv[3] was unsafe)
    if (argc > 3 && string(argv[3]) == "--grayscale") {
        cout << "Pretending to enable grayscale mode...\n";
    }

    // FIXED: use user-provided filename instead of hardcoded "input"
    ifstream fin(filename);

    // FIXED: check file open success
    if (!fin) {
        cout << "Error: could not open file: " << filename << endl;
        return 1;
    }

    cout << "Reading integers from file:\n";

    int x;

    // FIXED: correct file reading pattern (no .eof() bug)
    while (fin >> x) {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}
