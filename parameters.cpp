#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

#include <sstream>
#include <algorithm>
#include <iterator>

#include "parameters.h"

using namespace std;

bool is_number(const string& s) {
    if (s.empty())
        return false;
    bool trigger = false;
    if (s[0] == '.') {
        return false;
    }
    for (int i = 0; i < s.size(); i ++) {
        char c = s[i];
        if (c == '.' && !trigger) {
            trigger = !trigger;
            continue;
        } else if (c == '.' && trigger) {
            return false;
        }
        if (i == 0 && c == '-') {
            continue;
        }
        if (!std::isdigit(c))
          return false;
    }
    return true;
}
double read_from_file (const string param) {
    ifstream infile("input.parameters");
    string str;
    if (infile.is_open()) {
        while (getline(infile, str)) {
            // cout << iter << ": " << str << "\n";
            istringstream iss(str);
            vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
            if(words.size() < 1) continue;
            // cout << words[0] << "\n";
            if (words[0] == param) {
                if(is_number(words[1])) {
                    return atof(words[1].c_str());
                } else {
                    cout << "Error converting string to number for parameter '" << param << "' in the input file.\n";
                    exit (EXIT_FAILURE);
                }
                break;
            }
        }
    } else {
        cout << "Cannot open the file.\n";
        exit (EXIT_FAILURE);
    }
    cout << "Cannot find the given parameter '" << param << "' in the input file.\n";
    exit (EXIT_FAILURE);
}

const double L = read_from_file("L");
const double dx = read_from_file("dx");
const double cdt = read_from_file("cdt");
const double sigma = read_from_file("sigma");
const double NperStep = read_from_file("NperStep");
