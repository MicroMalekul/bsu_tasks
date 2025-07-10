/*
Задача 5:
Есть текстовый файл. Размер его такой, что он весь может быть размещен в
оперативной памяти. Из этого файла извлечь дату и числа (целые и не только).
Причем, дата должна быть только одна и предшествовать всем числам, в противном
случае текстовый файл некорректный. Форматы нецелых чисел могут быть разными (в
формате с фиксированной точкой, в экспоненциальном формате, в виде дроби). В
итоге для корректного файла  необходимо вычислить суммы отдельно всех целых
чисел и всех нецелых чисел.

*/
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

// Проверка: является ли строка дробью вида "числитель/знаменатель"
bool isFraction(const string &str) {
  return regex_match(str, regex(R"([-+]?\d+/\d+)"));
}

// Проверка: является ли строка числом с плавающей точкой или экспонентой
bool isDouble(const string &str) {
  return regex_match(
      str, regex(R"([-+]?(?:\d*\.\d+(?:[eE][-+]?\d+)?|\d+(?:[eE][-+]?\d+)))"));
}

// Преобразование строки-дроби в число типа double
double fractionToDouble(const string &str) {
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

  // Регулярное выражение для поиска даты (в разных форматах)
  regex date_regex(
      R"(\d{2}[./\/-]\d{2}[./\/-]\d{4}|\d{4}[./\/-]\d{2}[./\/-]\d{2})");

  // Проверяем: дата должна быть в начале текста
  smatch date_match;
  if (!regex_search(
          text, date_match,
          regex(
              R"(^(\d{2}[./\/-]\d{2}[./\/-]\d{4}|\d{4}[./\/-]\d{2}[./\/-]\d{2}))"))) {
    cout << "Error: position is not in the beginning\n";
    return 1;
  }

  // Проверяем, что в тексте только одна дата
  auto b = sregex_iterator(text.begin(), text.end(), date_regex);
  auto e = sregex_iterator();
  if (distance(b, e) != 1) {
    cout << "Error: not a single date\n";
    return 1;
  }

  size_t date_pos = b->position();
  size_t date_end_pos = date_pos + b->str().length();

  // Регулярное выражение для поиска всех типов чисел
  regex number_regex(
      R"([-+]?(?:\d+/\d+|\d*\.\d+(?:[eE][-+]?\d+)?|\d+(?:[eE][-+]?\d+)?|\d+))");

  sregex_iterator it(text.begin(), text.end(), number_regex);

  double sum_integers = 0;
  double sum_fractions = 0;
  string float_sum = "";
  string int_sum = "";
  for (; it != e; ++it) {
    string number_str = it->str();
    size_t number_pos = it->position();

    // Пропускаем число, если оно *пересекается* с датой
    if (number_pos < date_end_pos &&
        number_pos + number_str.length() > date_pos) {
      continue;
    }

    // Если это дробь, преобразуем и прибавим к дробной сумме
    if (isFraction(number_str)) {
      double val = fractionToDouble(number_str);
      sum_fractions += val;
      float_sum +=
          (number_str[0] == '+' ? "" : (number_str[0] == '-' ? "" : "+")) +
          number_str;

    }
    // Если это число с точкой или экспонентой
    else if (isDouble(number_str)) {
      double val = stod(number_str);
      sum_fractions += val;

      float_sum +=
          (number_str[0] == '+' ? "" : (number_str[0] == '-' ? "" : "+")) +
          number_str;
    }
    // Иначе — это целое число
    else {
      int val = stoi(number_str);
      sum_integers += val;

      int_sum +=
          (number_str[0] == '+' ? "" : (number_str[0] == '-' ? "" : "+")) +
          number_str;
    }
  }

  cout << "\nСумма целых чисел: " << int_sum << "=\n" << sum_integers << endl;
  cout << "Сумма дробных чисел: " << float_sum << "=\n"
       << sum_fractions << endl;

  return 0;
}
