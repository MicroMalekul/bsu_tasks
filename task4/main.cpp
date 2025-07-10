/*
5*. Реализуйте шаблонную функцию, удваивающую переданный аргумент, через
специализацию, где:
а) для целочисленного типа вызывается основная функция, которая возвращает
удвоенное значение.
б) для любого другого типа вызывается другая функция, которая выводит сообщение
об ошибке в период выполнения программы.
*/

#include <iostream>
#include <stdexcept>

// Функция для целочисленных
template <typename T>
  requires std::is_integral_v<T>
T doubleValue(T value) {
  return value * 2;
}

// Функция для остальных типов
template <typename T>
  requires(!std::is_integral_v<T>)
T doubleValue(T value) {
  throw std::runtime_error(
      "Ошибка: функция поддерживает только целочисленные типы.");
}

int main() {
  try {
    std::cout << "int: " << doubleValue(42) << std::endl;
    std::cout << "short: " << doubleValue((short)3) << std::endl;
    std::cout << "double: " << doubleValue(3.14) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
