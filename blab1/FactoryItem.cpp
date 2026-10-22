#include "FactoryItem.h"

#include <cmath>
#include <sstream>
#include <stdexcept>

FactoryItem::FactoryItem() : type_("Объект фабрики") {
    std::cout << "Вызван конструктор без параметров: FactoryItem\n";
}

FactoryItem::FactoryItem(const std::string& type) : type_(type) {
    std::cout << "Вызван конструктор с параметрами: FactoryItem\n";
}

FactoryItem::FactoryItem(const FactoryItem& other) : type_(other.type_) {
    std::cout << "Вызван конструктор копирования: FactoryItem\n";
}

FactoryItem::~FactoryItem() {
    std::cout << "Вызван деструктор: FactoryItem\n";
}

FactoryItem& FactoryItem::operator=(const FactoryItem& other) {
    if (this != &other) {
        type_ = other.type_;
    }
    std::cout << "Вызван оператор присваивания: FactoryItem\n";
    return *this;
}

const std::string& FactoryItem::getType() const {
    return type_;
}

void FactoryItem::print() const {
    std::cout << *this << '\n';
}

std::ostream& operator<<(std::ostream& out, const FactoryItem& item) {
    item.write(out);
    return out;
}

std::string readText(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        if (!std::getline(std::cin, value)) {
            throw std::runtime_error("Ввод завершён или поток ввода недоступен.");
        }
        if (value.find_first_not_of(" \t\r\n") != std::string::npos) {
            return value;
        }
        std::cout << "Ошибка: значение не должно быть пустым. Повторите ввод.\n";
    }
}

double readPositiveDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Ввод завершён или поток ввода недоступен.");
        }
        for (char& ch : line) {
            if (ch == ',') ch = '.'; // Разрешаем ввод десятичной дроби через запятую.
        }
        std::istringstream input(line);
        double value = 0.0;
        char extra = '\0';
        if ((input >> value) && !(input >> extra) && std::isfinite(value) && value > 0.0) {
            return value;
        }
        std::cout << "Ошибка: введите конечное число больше нуля.\n";
    }
}

double readNonNegativeDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Ввод завершён или поток ввода недоступен.");
        }
        for (char& ch : line) {
            if (ch == ',') ch = '.';
        }
        std::istringstream input(line);
        double value = 0.0;
        char extra = '\0';
        if ((input >> value) && !(input >> extra) && std::isfinite(value) && value >= 0.0) {
            return value;
        }
        std::cout << "Ошибка: введите конечное число, не меньше нуля.\n";
    }
}

int readIntInRange(const std::string& prompt, int minimum, int maximum) {
    if (minimum > maximum) {
        throw std::invalid_argument("Неверно задан диапазон допустимых целых чисел.");
    }
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Ввод завершён или поток ввода недоступен.");
        }
        std::istringstream input(line);
        long long value = 0;
        char extra = '\0';
        if ((input >> value) && !(input >> extra) && value >= minimum && value <= maximum) {
            return static_cast<int>(value);
        }
        std::cout << "Ошибка: введите целое число от " << minimum << " до " << maximum << ".\n";
    }
}
