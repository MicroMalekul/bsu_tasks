#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>

using namespace std;

int main() {
    ifstream file("task1/input.txt");

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    cout << "text = " << text << "\n";

     regex pattern(R"(<(.*?)>)");



    string result;
    auto begin = sregex_iterator(text.begin(), text.end(), pattern);
    auto end = sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        result += (*it)[1].str();
    }

    cout << "res: " << result << '\n';
    
    return 0;
}
