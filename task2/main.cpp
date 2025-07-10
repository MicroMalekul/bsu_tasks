#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <iterator>

using namespace std;

bool isFraction(const string& str) {
    return regex_match(str, regex(R"([-+]?\d+/\d+)"));
}

bool isDouble(const string& str){
    return regex_match(str, regex(R"([-+]?(?:\d*\.\d+(?:[eE][-+]?\d+)?|\d+(?:[eE][-+]?\d+)))"));
}


double fractionToDouble(const string& str) {
    stringstream ss(str);
    int num, denom;
    char slash;
    ss >> num >> slash >> denom;
    return static_cast<double>(num) / denom;
}

int main() {
    ifstream file("task2/input.txt");

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    cout << "text = " << text << "\n";

    regex date_regex(R"(\d{2}[./\/-]\d{2}[./\/-]\d{4}|\d{4}[./\/-]\d{2}[./\/-]\d{2})");

    smatch date_match;
    if (!regex_search(text, date_match, regex(R"(^(\d{2}[./\/-]\d{2}[./\/-]\d{4}|\d{4}[./\/-]\d{2}[./\/-]\d{2}))"))) {
        cout << "Error: position is not in the beginning\n";
        return 1;
    }

    auto b = sregex_iterator(text.begin(), text.end(), date_regex);
    auto e = sregex_iterator();
    if (distance(b, e) != 1) {
        cout << "Error: not a single date\n";
        return 1;
    }
    
    size_t date_pos = b->position();
    size_t date_end_pos = date_pos + b->str().length();

regex number_regex(R"([-+]?(?:\d+/\d+|\d*\.\d+(?:[eE][-+]?\d+)?|\d+(?:[eE][-+]?\d+)?|\d+))");

    sregex_iterator it(text.begin(), text.end(), number_regex);

    double sum_integers = 0;
    double sum_fractions = 0;
    string float_sum = "";
    string int_sum = "";
    for (; it != e; ++it) {
        string number_str = it->str();
        size_t number_pos = it->position();

        if (number_pos < date_end_pos && number_pos + number_str.length() > date_pos) {
            continue;
        }

        if (isFraction(number_str)) {
            double val = fractionToDouble(number_str);
            sum_fractions += val;
            float_sum+=(number_str[0]=='+' ?"" :(number_str[0]=='-' ?"" : "+")) + number_str;
        } else if (isDouble(number_str)) {
            double val = stod(number_str);
            sum_fractions += val;

            float_sum+=(number_str[0]=='+' ?"" :(number_str[0]=='-' ?"" : "+")) + number_str;
        } else {
            int val = stoi(number_str);
            sum_integers += val;

            int_sum+=(number_str[0]=='+' ?"" :(number_str[0]=='-' ?"" : "+")) + number_str;
        }
    }

    cout << "\nСумма целых чисел: " << int_sum << "=\n" << sum_integers << endl;
    cout << "Сумма дробных чисел: " <<  float_sum << "=\n" << sum_fractions << endl;

    return 0;
}
