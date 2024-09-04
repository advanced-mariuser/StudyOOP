#include <iostream>
#include <variant>
#include <string>

// Определение структуры overloaded для перегрузки лямбда-функций
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

using StringOrInt = std::variant<std::string, int>;

StringOrInt operator+(const StringOrInt& a, const StringOrInt& b) {
    return std::visit(overloaded {
            [](int a, int b) -> StringOrInt { return a + b; },
            [](int a, const std::string& b) -> StringOrInt { return std::to_string(a) + b; },
            [](const std::string& a, int b) -> StringOrInt { return a + std::to_string(b); },
            [](const std::string& a, const std::string& b) -> StringOrInt { return a + b; }
    }, a, b);
}

int main() {
    StringOrInt a = 10;
    StringOrInt b = 20;
    StringOrInt c = std::string("20");
    StringOrInt d = std::string("10");

    // Проверка и вывод результатов
    auto result1 = a + b;
    if (std::holds_alternative<int>(result1)) {
        std::cout << std::get<int>(result1) << std::endl; // 30
    } else {
        std::cout << std::get<std::string>(result1) << std::endl;
    }

    auto result2 = a + c;
    if (std::holds_alternative<int>(result2)) {
        std::cout << std::get<int>(result2) << std::endl;
    } else {
        std::cout << std::get<std::string>(result2) << std::endl; // "1020"
    }

    auto result3 = d + b;
    if (std::holds_alternative<int>(result3)) {
        std::cout << std::get<int>(result3) << std::endl;
    } else {
        std::cout << std::get<std::string>(result3) << std::endl; // "1020"
    }

    auto result4 = d + c;
    if (std::holds_alternative<int>(result4)) {
        std::cout << std::get<int>(result4) << std::endl;
    } else {
        std::cout << std::get<std::string>(result4) << std::endl; // "1020"
    }

    return 0;
}
