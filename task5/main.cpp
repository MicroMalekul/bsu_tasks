/*
6. Форматирование пользовательского типа. Создайте структуру, например,
MyStruct, содержащую несколько полей (возможно разного типа) и напишите
перегрузку std::formatter так, чтобы std::format("{}", mystruct) выводил
значения полей этой структуры.
*/

#include <format>
#include <iostream>
#include <string>

struct MyStruct {
  int id;
  std::string name;
  double score;
};

namespace std {
template <> struct formatter<MyStruct> {
  int precision = 2; // Число знаков после запятой по умолчанию
  bool no_id = false; // Флаг, нужно ли скрывать id

  // Метод parse разбирает пользовательский формат внутри {} (например, {:3n})
  constexpr auto parse(format_parse_context &ctx) {
    auto it = ctx.begin();
    auto end = ctx.end();

    int val = 0;
    bool found = false;

    // Если первая буква 'n', отключаем отображение id
    if (*it == 'n') {
      ++it;
      no_id = true;
    }

    // Парсим число (точность score)
    while (it != end && *it >= '0' && *it <= '9') {
      found = true;
      val = val * 10 + (*it - '0');
      ++it;
    }

    // Повторная проверка на 'n' — допустим {:0n} или {:3n}
    if (*it == 'n') {
      ++it;
      no_id = true;
    }

    // Если нашли цифры — сохраняем как precision
    if (found) {
      precision = val;
    }

    return it;
  }

  template <typename FormatContext>
  auto format(const MyStruct &ms, FormatContext &ctx) const {

    // Форматируем score с нужной точностью
    auto score_str = std::format("{:.{}f}", ms.score, precision);

    // Формируем строку в зависимости от флага no_id
    if (no_id) {
      return std::format_to(ctx.out(), "Name: {}, Score: {}", ms.name,
                            score_str);
    }
    return std::format_to(ctx.out(), "ID: {}, Name: {}, Score: {}", ms.id,
                          ms.name, score_str);
  }
};
} // namespace std

int main() {
  MyStruct obj{42, "Bob", 95.56789};

  std::cout << std::format("{}", obj) << '\n';
  std::cout << std::format("{:0}", obj) << '\n';
  std::cout << std::format("{:4}", obj) << '\n';
  std::cout << std::format("{:n}", obj) << '\n';
  std::cout << std::format("{:0n}", obj) << '\n';
  std::cout << std::format("{:n0}", obj) << '\n';
  std::cout << std::format("{:3n}", obj) << '\n';
}
