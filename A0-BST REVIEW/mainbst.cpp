#include "bst.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <command_file>" << endl;
        return 1;
    }

    bstree t;
    t.processCommands(argv[1]);

    return 0;
}
