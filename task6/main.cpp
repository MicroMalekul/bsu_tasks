#include <iostream>
#include <string>
#include <regex>

int main() {
    // Задание 1
    std::string input1 = "My phone is 123-456-7890";
    std::regex digits(R"(\d)");
    std::cout << std::regex_replace(input1, digits, "#") << "\n";

    // Задание 2
    std::string input2 = "<p>Hello, <b>world</b>!</p>";
    std::regex tags(R"(<[^>]+>)");
    std::cout << std::regex_replace(input2, tags, "") << "\n";

    // Задание 3
    std::string input3 = "Too     many     spaces";
    std::regex spaces(R"( {2,})");
    std::cout << std::regex_replace(input3, spaces, " ") << "\n";

    // Задание 4
    std::string input4 = "Today is 2025-07-01";
    std::regex date(R"((\d{4})-(\d{2})-(\d{2}))");
    std::cout << std::regex_replace(input4, date, "$3.$2.$1") << "\n";

    // Задание 5
    std::string input5 = "Hi! My ID is #123_ABC.";
    std::regex nonLatin(R"([^a-zA-Z]+)");
    std::cout << std::regex_replace(input5, nonLatin, "") << "\n";

    // Задание 6
    std::string input6 = "Write to me at test@example.com or admin@site.org.";
    std::regex email(R"(([\w\.-]+@[\w\.-]+\.\w+))");
    std::cout << std::regex_replace(input6, email, "<email>$1</email>") << "\n";

    return 0;
}
