#include <iostream>

#include "CinderCellEditor.h"
#include "switch.h"



#define voidCallback [&]()->void

#define VERSION "1.0.0"

void printHelp() {
    using namespace std;
    cout << endl << "Cinder Cell Editor " << VERSION << endl << endl;
    cout << "  cce                  >show help" << endl;
    cout << "  cce view [file]      >review map without editing" << endl;
    cout << "  cce topng [file]     >convert raw map to png with name [file].png" << endl;
    cout << "  cce open|edit [file]      >TBD" << endl << endl;
}

int main(int argc, char *argv[])
{

    std::string exeName = argv[0];
    std::vector<std::string> args;

    if (argc > 1) {
        args.assign(argv + 1, argv + argc);
    }

    if(args.size() < 2) {
        printHelp();
        return 0;
    }

    CinderCellEditor cce;

    bool _default = Switch<std::string>{args[0]}
    .Case("topng", voidCallback {
        cce.toPng(args[1]);
    })
    .Case("view", voidCallback {
        cce.view(args[1]);
    })
    .Case("open", voidCallback {
        cce.edit(args[1]);
    })
    .Case("edit", voidCallback {
        cce.edit(args[1]);
    }).exec();

    if(_default) {
        printHelp();
        return 0;
    }


    return cce.exec();
}
