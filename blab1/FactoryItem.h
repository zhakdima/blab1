#pragma once

#include <iostream>
#include <string>

// Базовый абстрактный класс для записей фабрики.
class FactoryItem {
protected:
    std::string type_; // Категория: «Мебель», «Работник» или «Машина».

public:
    FactoryItem();
    explicit FactoryItem(const std::string& type);
    FactoryItem(const FactoryItem& other);
    virtual ~FactoryItem();

    FactoryItem& operator=(const FactoryItem& other);

    const std::string& getType() const;

    virtual void read() = 0;
    virtual void edit() = 0;
    virtual void write(std::ostream& out) const = 0;
    virtual void saveData(std::ostream& out) const = 0;
    virtual void loadData(std::istream& in) = 0;
    virtual FactoryItem* clone() const = 0;

    void print() const;

    friend std::ostream& operator<<(std::ostream& out, const FactoryItem& item);
};

// Функции ввода. Они не дают продолжить ввод с пустым текстом или неверным числом.
std::string readText(const std::string& prompt);
double readPositiveDouble(const std::string& prompt);
double readNonNegativeDouble(const std::string& prompt);
int readIntInRange(const std::string& prompt, int minimum, int maximum);



