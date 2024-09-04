#include <iostream>
#include <string>
#include <vector>

// Выполняет замену элементов в диапазоне, заданном итераторами [first, last),
// для которых унарная функция predicate возвращает true на newValue
template <typename Iterator, typename Predicate, typename T>
void ReplaceIf(Iterator first, Iterator last, Predicate predicate, const T& newValue)
{
    for (Iterator it = first; it != last; ++it)
    {
        if (predicate(*it))
        {
            *it = newValue;
        }
    }
}

int main()
{
    int items[] = { 1, 2, 3, -4, 5, 2, 3 };
    // Заменяет все элементы, меньшие 0 на 0
    ReplaceIf(std::begin(items), std::end(items), [](int x) { return x < 0; }, 0);

    // Вывести items в stdout
    for (const auto& item : items) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> strings = { "One", "Two", "Three", "Four", "Five", "", "Seven" };
    // Заменяет все пустые строки на "Empty"
    ReplaceIf(strings.begin(), strings.end(), [](const std::string& str) { return str.empty(); }, "Empty");

    // Вывести strings в stdout
    for (const auto& str : strings) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}
