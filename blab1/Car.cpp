#include "Car.h"

#include <iomanip>
#include <stdexcept>
namespace {
    void checkCarText(const std::string& value, const std::string& fieldName) {
        if (value.find_first_not_of(" \t\r\n") == std::string::npos)
            throw std::invalid_argument(fieldName + " не должно быть пустым.");
    }
}

Car::Car() : FactoryItem("Машина") {
    std::cout << "Вызван конструктор без параметров: Car (Машина)\n";
}

Car::Car(const std::string& brand, const std::string& model,
    const std::string& registrationNumber)
    : FactoryItem("Машина") {
    setBrand(brand);
    setModel(model);
    setRegistrationNumber(registrationNumber);
    std::cout << "Вызван конструктор с параметрами: Car (Машина)\n";
}

Car::Car(const Car& other)
    : FactoryItem(other), brand_(other.brand_), model_(other.model_),
    registrationNumber_(other.registrationNumber_) {
    std::cout << "Вызван конструктор копирования: Car (Машина)\n";
}

Car::~Car() {
    std::cout << "Вызван деструктор: Car (Машина)\n";
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        FactoryItem::operator=(other);
        brand_ = other.brand_;
        model_ = other.model_;
        registrationNumber_ = other.registrationNumber_;
    }
    std::cout << "Вызван оператор присваивания: Car (Машина)\n";
    return *this;
}

const std::string& Car::getBrand() const { return brand_; }
const std::string& Car::getModel() const { return model_; }
const std::string& Car::getRegistrationNumber() const { return registrationNumber_; }

void Car::setBrand(const std::string& value) { checkCarText(value, "Марка машины"); brand_ = value; }
void Car::setModel(const std::string& value) { checkCarText(value, "Модель машины"); model_ = value; }
void Car::setRegistrationNumber(const std::string& value) { checkCarText(value, "Государственный номер"); registrationNumber_ = value; }

void Car::read() {
    std::cout << "\n--- Ввод данных о машине ---\n";
    setBrand(readText("Марка: "));
    setModel(readText("Модель: "));
    setRegistrationNumber(readText("Государственный номер: "));
}

void Car::edit() {
    std::cout << "Введите новые данные машины. Все поля будут заменены.\n";
    read();
}

void Car::write(std::ostream& out) const {
    out << "Машина [марка: " << brand_ << "; модель: " << model_
        << "; гос. номер: " << registrationNumber_ << "]";
}
void Car::saveData(std::ostream& out) const {
    out << std::quoted(brand_) << '\n'
        << std::quoted(model_) << '\n'
        << std::quoted(registrationNumber_) << '\n';

    if (!out)
        throw std::runtime_error("Ошибка сохранения данных машины.");
}

void Car::loadData(std::istream& in) {
    std::string brand, model, registrationNumber;

    if (!(in >> std::quoted(brand)
        >> std::quoted(model)
        >> std::quoted(registrationNumber)))
        throw std::runtime_error("Ошибка чтения данных машины из файла.");

    if (brand.find_first_not_of(" \t\r\n") == std::string::npos ||
        model.find_first_not_of(" \t\r\n") == std::string::npos ||
        registrationNumber.find_first_not_of(" \t\r\n") == std::string::npos)
        throw std::runtime_error("Некорректные данные машины в файле.");

    brand_ = brand;
    model_ = model;
    registrationNumber_ = registrationNumber;
}
FactoryItem* Car::clone() const {
    return new Car(*this);
}
