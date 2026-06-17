#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include "../global_data.h"

#include <unordered_map>
#include <functional>
#include <string>
#include <stdexcept>

using Command = std::function<void(int &, int, char **)>;

class ArgsParser
{
public:
    ArgsParser(GlobalData &data);
    ~ArgsParser();

    void init_parser();
    int try_parse_args(int argc, char **argv);

private:
    GlobalData &globalData;

    std::unordered_map<std::string, Command> cmd;
    int get_int(const std::string &arg);
    int get_positive(int &i, int argc, char **argv, const std::string &name);
};

#endif // ARGS_PARSER_H