// args_ex2.cpp — Classroom Discussion: Factory Pattern Skeleton

#include <iostream>
#include <string>

using namespace std;

class Args {
public:
    std::string input_file;
    std::string output_file;
    bool verbose = false;
    int rotate = 0;
    int brightness = 0;
    bool grayscale = false;

    // ------------------------------------------------------------
    // Command-line factory
    // ------------------------------------------------------------
    static Args parse(int argc, char* argv[]) {

        Args args;

        // Minimal safe demo parsing so it runs
        if (argc > 1) args.input_file = argv[1];
        if (argc > 2) args.output_file = argv[2];

        // Fake option scan (safe placeholder behavior)
        for (int i = 3; i < argc; i++) {

            string token = argv[i];

            if (token == "--verbose") args.verbose = true;
            else if (token == "--grayscale") args.grayscale = true;
            else if (token == "--rotate") {
                if (i + 1 < argc) {
                    args.rotate = stoi(argv[++i]);
                }
            }
            else if (token == "--brightness") {
                if (i + 1 < argc) {
                    args.brightness = stoi(argv[++i]);
                }
            }
        }

        return args;
    }

    // ------------------------------------------------------------
    // File-based factory (safe stub)
    // ------------------------------------------------------------
    static Args fromFile(const string& filename) {

        Args args;

        // Just a demo placeholder so it compiles and runs
        args.input_file = "config_input.txt";
        args.output_file = "config_output.txt";
        args.verbose = true;

        cout << "[fromFile] Loaded config from: " << filename << endl;

        return args;
    }

    // ------------------------------------------------------------
    // Print helper so you can see results when running
    // ------------------------------------------------------------
    void print() const {

        cout << "INPUT     : " << input_file << endl;
        cout << "OUTPUT    : " << output_file << endl;
        cout << "VERBOSE   : " << verbose << endl;
        cout << "GRAYSCALE : " << grayscale << endl;
        cout << "ROTATE    : " << rotate << endl;
        cout << "BRIGHTNESS: " << brightness << endl;
    }

private:
    Args() = default;
};

int main(int argc, char** argv) {

    Args arg1 = Args::parse(argc, argv);
    arg1.print();

    cout << "----------------------\n";

    Args arg2 = Args::fromFile("config.txt");
    arg2.print();

    return 0;
}
