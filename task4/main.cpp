#include <iostream>
#include <type_traits>
#include <concepts>
#include <string>

// --- Задание 1 ---

// a) Только для целых
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
Print_if_integer(T value) {
    std::cout << "Integer: " << value << "\n";
}

// б) Только для float/double
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type
Print_if_floating_point(T value) {
    std::cout << "Floating point: " << value << "\n";
}

// в) Только для числовых (целые и плавающие)
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
Print_if_numeric(T value) {
    std::cout << "Numeric: " << value << "\n";
}

// --- Задание 2 ---
// Концепт для целых
template<typename T>
concept Integral = std::is_integral_v<T>;

template<Integral T>
T double_integral(T value) {
    return value * 2;
}

// --- Задание 3 ---
template<typename T>
T double_if_integral_or_fail(T value) {
    static_assert(std::is_integral_v<T>, "Ошибка: тип не является целочисленным.");
    return value * 2;
}

// --- Задание 4 ---
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
double_overload(T value) {
    return value * 2;
}

template<typename T>
typename std::enable_if<!std::is_integral<T>::value, void>::type
double_overload(T value) {
    std::cerr << "Ошибка: тип не поддерживается (не целочисленный)\n";
}

// --- Задание 5 ---
// Основной шаблон
template<typename T>
T double_specialized(T value);

// Специализация для целых
template<>
int double_specialized<int>(int value) {
    return value * 2;
}

// Обобщённая версия для других типов
template<typename T>
T double_specialized(T value) requires (!std::is_same_v<T, int>) {
    std::cerr << "Ошибка: не целочисоенный тип\n";
    return value;
}

// --- Задание 6 ---
// Концепт: можно ли вывести в ostream
template<typename T>
concept Printable = requires(T a, std::ostream& os) {
    { os << a } -> std::same_as<std::ostream&>;
};

template<Printable T>
void print(const T& value) {
    std::cout << "Printable: " << value << "\n";
}

// --- Задание 7 ---
// Концепт: поддерживается a + b
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template<Addable T>
T add(T a, T b) {
    return a + b;
}

// --- main() для демонстрации ---
int main() {
    std::cout << "--- Задание 1 ---\n";
    Print_if_integer(42);
    Print_if_floating_point(3.14);
    Print_if_numeric(99);
    Print_if_numeric(1.5);

    std::cout << "\n--- Задание 2 ---\n";
    std::cout << double_integral(10) << "\n";
    // std::cout << double_integral(3.14); // ошибка компиляции

    std::cout << "\n--- Задание 3 ---\n";
    std::cout << double_if_integral_or_fail(7) << "\n";
    // double_if_integral_or_fail(2.5); // ошибка компиляции

    std::cout << "\n--- Задание 4 ---\n";
    std::cout << double_overload(5) << "\n";
    double_overload(3.14); // ошибка во время выполнения

    std::cout << "\n--- Задание 5 ---\n";
    std::cout << double_specialized(5) << "\n";
    double_specialized(3.14); // ошибка во время выполнения

    std::cout << "\n--- Задание 6 ---\n";
    print(123);
    print(std::string("hello"));
    // print(std::vector<int>{}); // не компилируется

    std::cout << "\n--- Задание 7 ---\n";
    std::cout << add(5, 10) << "\n";
    std::cout << add(std::string("a"), std::string("b")) << "\n";
    // add(std::vector<int>{1}, std::vector<int>{2}); // не компилируется

    return 0;
}
