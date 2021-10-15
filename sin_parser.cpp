#include <iostream>

#include "sin_parser.h"

namespace Cinder {

static bool read_till_delimeter(std::stringstream &ss, std::string &res, int delim1, int delim2 = 257 /* not in range */) {
    res = "";
    while(!ss.eof()) {
        char ch = ss.get();
        if ((ch == delim1) || (ch == delim2)) {
            return true;
        }
        res += ch;
    }
    return false;
}

static bool read_till_delimeter_or_eof(std::stringstream &ss, std::string &res, int delim1, int delim2 = 257 /* not in range */) {
    res = "";
    while(!ss.eof()) {
        char ch = ss.get();
        if ((ch == delim1) || (ch == delim2) || ss.eof()) {
            return true;
        }
        res += ch;
    }
    return true;
}

static bool expect_char(std::stringstream &ss, int ch1, int ch2 = 257 /* not in range */) {
    if (ss.eof()) {
        return false;
    }
    if ((ch1 == ss.peek()) || (ch2 == ss.peek())) {
        ss.get();
        return true;
    }
    return false;
}

static bool read_string(std::stringstream &ss, std::string &str) {
    return expect_char(ss, '"')
        && read_till_delimeter(ss, str, '"');
}

static bool skip_empty_space(std::stringstream &ss) {
    while (expect_char(ss, ' ')) {
        /* no-op */
    }
    return true;
}

static bool skip_empty_space_and_newline(std::stringstream &ss) {
    while (expect_char(ss, ' ', '\n')) {
        /* no-op */
    }
    return true;
}

static bool read_var_name(std::stringstream &ss, std::string &var) {
    while(!ss.eof()) {
        char ch = ss.get();
        bool ok = (('A' <= ch) && (ch <= 'Z'))
               || (('a' <= ch) && (ch <= 'z'))
               || (('0' <= ch) && (ch <= '9'))
               || (ch == '.')
               || (ch == '_');

        if (ok) {
            var += ch;
        }
        else {
            ss.putback(ch);
            return true;
        }
    }
    return !var.empty();
}

bool parse_var(std::stringstream &ss, std::string &var, std::string &_type, std::string &value) {
    var   = "";
    _type = "";
    value = "";

    bool ok = skip_empty_space(ss)
           && read_var_name(ss, var)
           && skip_empty_space(ss)
           && expect_char(ss, ':')
           && skip_empty_space(ss);

    if (!ok) {
        return false;
    }

    char ch = ss.peek();
    switch (ch) {
    case '"':
	    _type = "string";
	     return read_string(ss, value)
	         && skip_empty_space_and_newline(ss);
    case '`':
        ss.get();
        ok = expect_char(ss, '\n')
          && read_till_delimeter(ss, value, '`');

        if (!ok || value.length() == 0) {
            return false;
        }

	    _type = "string";
        value.pop_back();
        return true;
    default:
        return read_var_name(ss, _type)
            && skip_empty_space(ss)
            && expect_char(ss, '\n')
            && skip_empty_space(ss)
            && read_till_delimeter_or_eof(ss, value, '\n', ' ')
            && skip_empty_space_and_newline(ss);
    }
}

bool parse_sins(std::stringstream &ss, std::vector<parsed_sin> &sins) {
    sins = {};

    while (!ss.eof()) {

        skip_empty_space_and_newline(ss);
        if (ss.eof()) {
            goto three_dots_postprocessing;
        }

        parsed_sin sin;
        if (!parse_var(ss, sin.name, sin._type, sin.value)) {
            return false;
        }

        sins.push_back(sin);
    }

    three_dots_postprocessing:

    std::string top_level_var;
    for (auto &sin: sins) {
        if ((sin.name.size() > 2) && (sin.name[0] == '.') && (sin.name[1] == '.') && (sin.name[2] == '.')) {
            if (top_level_var == "") {
                return false;
            }

            sin.name.erase(0, 3);
            sin.name = top_level_var + "." + sin.name;
        }
        else {
            top_level_var = sin.name;
        }
    }

    return true;
}

static void bool_assert(bool var, const std::string &descr) {
    if (!var) {
        std::cerr << descr << "\n";
    }
}

static void str_assert(const std::string &real, const std::string &expected, const std::string &descr = "error") {
    if (expected != real) {
        std::cerr << descr << ":\n'" << real << "'\n != \n'" << expected << "'\n";
    }
}

// TODO: convert to unit tests
void run_sin_parser_tests() {
    std::stringstream ss1("\"a string\nwith \\n\" and some garbage");
    std::string string1;
    bool_assert(read_string(ss1, string1), "string1 not parsed");
    str_assert(string1, "a string\nwith \\n", "test 1:");

    std::stringstream ss2("   var2 : \"some string\"");
    std::string name2;
    std::string type2;
    std::string value2;
    bool ret2 = parse_var(ss2, name2, type2, value2);
    bool_assert(ret2, "var2 not parsed");
    str_assert(name2, "var2", "test 2:");
    str_assert(type2, "string", "test 2:");
    str_assert(value2, "some string", "test 2:");

    std::stringstream ss3("       var3    :  uint8    \n    3345    ");
    std::string name3;
    std::string type3;
    std::string value3;
    bool ret3 = parse_var(ss3, name3, type3, value3);
    bool_assert(ret3, "var3 not parsed");
    str_assert(name3, "var3", "test 3");
    str_assert(type3, "uint8", "test 3");
    str_assert(value3, "3345", "test 3");

    std::stringstream ss4("   var4_int : uint32  \n"
                          " 12345 \n"
                          "\n"
                          "   var4_str:\" &*##$@\n"
                          " hgbngh \n"
                          " \" \n");
    std::string name4;
    std::string type4;
    std::string value4;
    bool ret4 = parse_var(ss4, name4, type4, value4);
    bool_assert(ret4, "test 4/1: not parsed");
    str_assert(name4, "var4_int", "test 4/1");
    str_assert(type4, "uint32", "test 4/1");
    str_assert(value4, "12345", "test 4/1");

    ret4 = parse_var(ss4, name4, type4, value4);
    bool_assert(ret4, "test 4/2: not parsed");
    str_assert(name4, "var4_str", "test 4/2");
    str_assert(type4, "string", "test 4/2");
    str_assert(value4, " &*##$@\n hgbngh \n ", "test 4/2");

    std::stringstream ss5("   multiline : `\n"
                     "       12345  \n"
                     "~~~~~~~~~~\n"
                     "\n"
                     "`\n");
    std::string name5;
    std::string type5;
    std::string value5;
    bool ret5 = parse_var(ss5, name5, type5, value5);
    bool_assert(ret5, "test 5: not parsed");
    str_assert(name5, "multiline", "test 5");
    str_assert(type5, "string", "test 5");
    str_assert(value5, "       12345  \n"
                       "~~~~~~~~~~\n",
               "test 5");

    std::stringstream ss6(" \n"
                          " foo : `\n"
                          "bar\n"
                          "` \n"
                          "\n"
                          "int: int64\n"
                          " 7000700\n"
                          "...subvar: uint8\n"
                          "10");
    std::vector<parsed_sin> sins6;
    bool ret6 = parse_sins(ss6, sins6);
    bool_assert(ret6, "test 6: not parsed");
    if (sins6.size() != 2) {
        std::cout << "test 6: 2 items expected, " << sins6.size() << " found\n";
    }
    str_assert(sins6[0].name, "foo", "test 6/1");
    str_assert(sins6[0]._type, "string", "test 6/1");
    str_assert(sins6[0].value, "bar", "test 6/1");
    str_assert(sins6[1].name, "int", "test 6/2");
    str_assert(sins6[1]._type, "int64", "test 6/2");
    str_assert(sins6[1].value, "7000700", "test 6/2");
    str_assert(sins6[2].name, "int.subvar", "test 6/3");
    str_assert(sins6[2]._type, "uint8", "test 6/3");
    str_assert(sins6[2].value, "10", "test 6/3");
}

} //namespace Cinder
