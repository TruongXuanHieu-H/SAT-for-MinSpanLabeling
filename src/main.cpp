#include <iostream>

#include "global_data.h"
#include "encoder.h"
#include "utils/signal_handler.h"
#include "utils/version.h"
#include "utils/args_parser.h"

int main(int argc, char **argv)
{
    SignalHandler::init_signals();
    Version::print_version();

    GlobalData global_data;
    ArgsParser args_parser(global_data);

    int parse_result = args_parser.try_parse_args(argc, argv);
    if (parse_result != 0)
    {
        return parse_result;
    }

    Encoder encoder(global_data);

    if (global_data.just_print_dimacs)
        encoder.encode_and_print_dimacs();
    else
        encoder.encode_and_solve();

    return 0;
}
