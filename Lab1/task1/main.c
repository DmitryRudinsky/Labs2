#include "options.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        PrintError(OPT_INVALID_ARGUMENTS);
        return OPT_INVALID_ARGUMENTS;
    }

    int number = 0;
    Options opt = OPT_INVALID;

    if (GetOpts(argc, argv, &opt, &number) != 0) {
        return OPT_UNKNOWN_OPTION;
    }

    switch (opt) {
        case OPT_H:
            HandleOptH(number);
            break;
        case OPT_P:
            HandleOptP(number);
            break;
        case OPT_S:
            HandleOptS(number);
            break;
        case OPT_E:
            HandleOptE(number);
            break;
        case OPT_A:
            HandleOptA(number);
            break;
        case OPT_F:
            HandleOptF(number);
            break;
        default:
            PrintError(OPT_UNKNOWN_OPTION);
            break;
    }

    return 0;
}
