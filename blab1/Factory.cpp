#include "Factory.h"

#include <iostream>
#include <stdexcept>
#include <utility>

Factory::Factory() : name_("Фабрика"), items_(nullptr), count_(0) {
    std::cout << "Вызван конструктор без параметров: Factory\n";
}

Factory::Factory(const std::string& name) : name_(), items_(nullptr), count_(0) {
    setName(name);
    std::cout << "Вызван конструктор с параметрами: Factory\n";
}

Factory::Factory(const Factory& other)
    : name_(other.name_), items_(nullptr), count_(0) {
    std::cout << "Вызван конструктор копирования: Factory\n";
    if (other.count_ == 0) return;

    items_ = new FactoryItem * [other.count_];
    try {
        for (std::size_t i = 0; i < other.count_; ++i) {
            items_[count_] = other.items_[i]->clone();
            ++count_;
        }
    }
    catch (...) {
        for (std::size_t i = 0; i < count_; ++i) delete items_[i];
        delete[] items_;
        items_ = nullptr;
        count_ = 0;
        throw;
    }
}

Factory::~Factory() {
    std::cout << "Вызван деструктор: Factory\n";
    for (std::size_t i = 0; i < count_; ++i) {
        delete items_[i];
    }
    delete[] items_;
}

Factory& Factory::operator=(const Factory& other) {
    if (this != &other) {
        Factory copy(other);
        swap(copy);
    }
    std::cout << "Вызван оператор присваивания: Factory\n";
    return *this;
}

void Factory::swap(Factory& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(items_, other.items_);
    swap(count_, other.count_);
}

const std::string& Factory::getName() const {
    return name_;
}

void Factory::setName(const std::string& name) {
    if (name.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("Название фабрики не должно быть пустым.");
    }
    name_ = name;
}

void Factory::add(FactoryItem* item) {
    if (item == nullptr) {
        throw std::invalid_argument("Нельзя добавить пустой объект.");
    }

    FactoryItem** expanded = new FactoryItem * [count_ + 1];
    for (std::size_t i = 0; i < count_; ++i) {
        expanded[i] = items_[i];
    }
    expanded[count_] = item;
    delete[] items_;
    items_ = expanded;
    ++count_;
}

std::size_t Factory::countByType(const std::string& type) const {
    std::size_t found = 0;
    for (std::size_t i = 0; i < count_; ++i) {
        if (items_[i]->getType() == type) ++found;
    }
    return found;
}

std::size_t Factory::findIndex(const std::string& type, int position) const {
    if (position < 1) {
        throw std::invalid_argument("Номер записи должен начинаться с 1.");
    }
    int currentPosition = 0;
    for (std::size_t i = 0; i < count_; ++i) {
        if (items_[i]->getType() == type) {
            ++currentPosition;
            if (currentPosition == position) return i;
        }
    }
    throw std::out_of_range("Запись с таким номером в категории «" + type + "» не найдена.");
}

void Factory::showAll() const {
    std::cout << "\n=== Все записи: " << name_ << " ===\n";
    if (count_ == 0) {
        std::cout << "Записей пока нет.\n";
        return;
    }
    for (std::size_t i = 0; i < count_; ++i) {
        std::cout << i + 1 << ". " << *items_[i] << '\n';
    }
}

void Factory::showType(const std::string& type) const {
    std::cout << "\n=== Категория: " << type << " ===\n";
    if (countByType(type) == 0) {
        std::cout << "В этой категории пока нет записей.\n";
        return;
    }
    int position = 0;
    for (std::size_t i = 0; i < count_; ++i) {
        if (items_[i]->getType() == type) {
            ++position;
            std::cout << position << ". " << *items_[i] << '\n';
        }
    }
}

void Factory::editByType(const std::string& type, int position) {
    const std::size_t index = findIndex(type, position);
    std::cout << "Текущая запись: " << *items_[index] << '\n';
    items_[index]->edit();
    std::cout << "Данные успешно изменены.\n";
}

void Factory::removeByType(const std::string& type, int position) {
    const std::size_t index = findIndex(type, position);
    FactoryItem** reduced = nullptr;
    if (count_ > 1) {
        reduced = new FactoryItem * [count_ - 1];
        std::size_t target = 0;
        for (std::size_t i = 0; i < count_; ++i) {
            if (i != index) reduced[target++] = items_[i];
        }
    }
    delete items_[index];
    delete[] items_;
    items_ = reduced;
    --count_;
    std::cout << "Запись удалена.\n";
}