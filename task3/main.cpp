#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

// Функция для проверки корректности температуры
bool isValidTemperature(const string &temp_str) {
  try {
    double val = stod(temp_str);
    return val >= -100 && val <= 100;
  } catch (...) {
    return false;
  }
}

int main() {
  ifstream file("task3/input.txt");

  // Регулярное выражение для полной строки
  regex full_line_regex(
      R"(^(?:весна|лето|осень|зима)\s+(?:.*?\s+)?(?:макс\.|средняя|максимальная)\s+(?:.*?\s+)?температура\s+([+-]?\d+(?:\.\d+)?)˚$)");

  // То же самое выражение, но для поиска подстроки
  regex search_regex(
      R"((?:весна|лето|осень|зима)\s+(?:.*?\s+)?(?:макс\.|средняя|максимальная)\s+(?:.*?\s+)?температура\s+([+-]?\d+(?:\.\d+)?)˚)");

  string line;
  while (getline(file, line)) {
    cout << "Строка: " << line << "\n";

    smatch match_full, match_sub;
    bool full_match = regex_match(line, match_full, full_line_regex);
    cout << "1) Вся строка "
         << (full_match ? "соответствует" : "не соответствует") << "\n";

    bool found_sub = regex_search(line, match_sub, search_regex);
    if (found_sub) {
      cout << "2) Найдена подстрока: \"" << match_sub.str() << "\"\n";

      // Извлекаем саму температуру из группы
      string temp_str = match_sub[1];
      if (isValidTemperature(temp_str)) {
        cout << "   Температура корректна: " << temp_str << "\n";
      } else {
        cout << "   Ошибка: температура некорректна: " << temp_str << "\n";
      }
    } else {
      cout << "2) Подстрока не найдена\n";
    }

    cout << "-------------------------------------\n";
  }

  return 0;
}
