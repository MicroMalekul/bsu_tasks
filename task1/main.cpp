#include <iostream>
#include <regex>

// 1. Найти все подстроки вида: буква 'a', 2 любых символа, буква 'a'
void task1(const std::string &text) {
  std::regex pattern("a..a");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 2. То же, но исключаем 'abca'
void task2(const std::string &text) {
  std::regex pattern("a(..)a");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it) {
    if (it->str() != "abca")
      std::cout << it->str() << " ";
  }
  std::cout << "\n";
}

// 3. 'a' + любое число 'b' (в том числе 0) + 'a'
void task3(const std::string &text) {
  std::regex pattern("ab*a");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 4. 'ab' повторяется 1 и более раз
void task4(const std::string &text) {
  std::regex pattern("(ab)+");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 5. Цифра 2 + любое кол-во любых символов + цифра 3
void task5(const std::string &text) {
  std::regex pattern("2.+3");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 6. Строго abba, abbba, abbbba и т.п.
void task6(const std::string &text) {
  std::regex pattern("ab{2,}a");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 7. 'a' + не менее 4 'b' + 'b'
void task7(const std::string &text) {
  std::regex pattern("ab{4,}b");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 8. 'a' + одна цифра + 'a'
void task8(const std::string &text) {
  std::regex pattern("a\\d{1}a");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 9. 'a' по краям, между ними — не число (например, буквы, знаки)
void task9(const std::string &text) {
  std::regex pattern("a[^\\d]+a");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 10. 'a' + только маленькие латинские буквы + 'a'
void task10(const std::string &text) {
  std::regex pattern("a[a-z]+a");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  for (; it != std::sregex_iterator(); ++it)
    std::cout << it->str() << " ";
  std::cout << "\n";
}

// 11. Найти все числа в строке и вычислить сумму
void task11(const std::string &text) {
  std::regex pattern("\\d+");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  int sum = 0;
  for (; it != std::sregex_iterator(); ++it)
    sum += std::stoi(it->str());
  std::cout << "Sum: " << sum << "\n";
}

// 12. Найти все <...> и склеить содержимое внутри
void task12(const std::string &text) {
  std::regex pattern("<([^<>]+)>");
  std::sregex_iterator it(text.begin(), text.end(), pattern);
  std::string result;
  for (; it != std::sregex_iterator(); ++it)
    result += (*it)[1].str();
  std::cout << result << "\n";
}

int main() {
  std::cout << "Task 1:\n";
  task1("abca axxa a!!a a12a");

  std::cout << "Task 2:\n";
  task2("abca axxa a!!a a12a");

  std::cout << "Task 3:\n";
  task3("aba abba aa abbbba");

  std::cout << "Task 4:\n";
  task4("abab abababa ab ababab");

  std::cout << "Task 5:\n";
  task5("2xx3 2+++3 2 3 23 2abc3 2+3");

  std::cout << "Task 6:\n";
  task6("abba abbba abbbba aba abbbbbba");

  std::cout << "Task 7:\n";
  task7("abbbbb abbbbbb abbb abbbbbbb");

  std::cout << "Task 8:\n";
  task8("a1a a9a ab1a a22a");

  std::cout << "Task 9:\n";
  task9("a1a aXa a_a a#b a12a");

  std::cout << "Task 10:\n";
  task10("abc axyz aAa aBBB aaa");

  std::cout << "Task 11:\n";
  task11("Xab23dm175aad9");

  std::cout << "Task 12:\n";
  task12("<abc> xxx <defg> eee <ik> jsak");

  return 0;
}
