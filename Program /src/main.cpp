#include "Args.h"

int main(int argc, char* argv[]) {
    Args args = Args::parse(argc, argv);
    args.print();
    return 0;
}
