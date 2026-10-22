#include "Worker.h"

#include <cmath>
#include <stdexcept>

namespace {
    void checkText(const std::string& value, const std::string& fieldName) {
        if (value.find_first_not_of(" \t\r\n") == std::string::npos)
            throw std::invalid_argument(fieldName + " не должно быть пустым.");
    }
}

Worker::Worker() : FactoryItem("Работник"), salary_(0.0) {
    std::cout << "Вызван конструктор без параметров: Worker (Работник)\n";
}

Worker::Worker(const std::string& fullName, const std::string& position, double salary,
    const std::string& address, const std::string& phone)
    : FactoryItem("Работник"), salary_(0.0) {
    setFullName(fullName);
    setPosition(position);
    setSalary(salary);
    setAddress(address);
    setPhone(phone);
    std::cout << "Вызван конструктор с параметрами: Worker (Работник)\n";
}

Worker::Worker(const Worker& other)
    : FactoryItem(other), fullName_(other.fullName_), position_(other.position_),
    salary_(other.salary_), address_(other.address_), phone_(other.phone_) {
    std::cout << "Вызван конструктор копирования: Worker (Работник)\n";
}

Worker::~Worker() {
    std::cout << "Вызван деструктор: Worker (Работник)\n";
}

Worker& Worker::operator=(const Worker& other) {
    if (this != &other) {
        FactoryItem::operator=(other);
        fullName_ = other.fullName_;
        position_ = other.position_;
        salary_ = other.salary_;
        address_ = other.address_;
        phone_ = other.phone_;
    }
    std::cout << "Вызван оператор присваивания: Worker (Работник)\n";
    return *this;
}

const std::string& Worker::getFullName() const { return fullName_; }
const std::string& Worker::getPosition() const { return position_; }
double Worker::getSalary() const { return salary_; }
const std::string& Worker::getAddress() const { return address_; }
const std::string& Worker::getPhone() const { return phone_; }

void Worker::setFullName(const std::string& value) { checkText(value, "ФИО работника"); fullName_ = value; }
void Worker::setPosition(const std::string& value) { checkText(value, "Должность"); position_ = value; }
void Worker::setAddress(const std::string& value) { checkText(value, "Адрес проживания"); address_ = value; }
void Worker::setPhone(const std::string& value) { checkText(value, "Телефон"); phone_ = value; }

void Worker::setSalary(double value) {
    if (!std::isfinite(value) || value < 0.0)
        throw std::invalid_argument("Заработная плата не может быть отрицательной.");
    salary_ = value;
}

void Worker::read() {
    std::cout << "\n--- Ввод данных о работнике ---\n";
    setFullName(readText("ФИО: "));
    setPosition(readText("Должность: "));
    setSalary(readNonNegativeDouble("Заработная плата: "));
    setAddress(readText("Адрес проживания: "));
    setPhone(readText("Телефон: "));
}

void Worker::edit() {
    std::cout << "Введите новые данные работника. Все поля будут заменены.\n";
    read();
}

void Worker::write(std::ostream& out) const {
    out << "Работник [ФИО: " << fullName_ << "; должность: " << position_
        << "; заработная плата: " << salary_ << "; адрес: " << address_
        << "; телефон: " << phone_ << "]";
}

FactoryItem* Worker::clone() const {
    return new Worker(*this);
}