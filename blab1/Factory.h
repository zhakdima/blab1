#pragma once

#include "FactoryItem.h"

#include <cstddef>
#include <string>

// Класс Factory хранит записи всех трёх типов в динамическом массиве.
class Factory {
private:
    std::string name_;
    FactoryItem** items_;
    std::size_t count_;

    std::size_t findIndex(const std::string& type, int position) const;
    void swap(Factory& other) noexcept;

public:
    Factory();
    explicit Factory(const std::string& name);
    Factory(const Factory& other);
    ~Factory();

    Factory& operator=(const Factory& other);

    const std::string& getName() const;
    void setName(const std::string& name);

    void add(FactoryItem* item); // После успешного вызова Factory владеет объектом.
    std::size_t countByType(const std::string& type) const;
    void showAll() const;
    void showType(const std::string& type) const;
    void editByType(const std::string& type, int position);
    void removeByType(const std::string& type, int position);
    void saveToFile(const std::string& fileName) const;
    void loadFromFile(const std::string& fileName);
};

