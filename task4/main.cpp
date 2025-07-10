#include <iostream>
#include <stdexcept>

template<typename T>
requires std::is_integral_v<T>
T doubleValue(T value) {
    return value * 2;
}

template<typename T>
requires (!std::is_integral_v<T>)
T doubleValue(T value) {
    throw std::runtime_error("Ошибка: функция поддерживает только целочисленные типы.");
}

int main() {
    try {
        std::cout << "int: " << doubleValue(42) << std::endl;
        std::cout << "short: " << doubleValue((short)3) << std::endl;
        std::cout << "double: " << doubleValue(3.14) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
