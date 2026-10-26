#include "Furniture.h"
#include <iomanip>
#include <limits>
#include <cmath>
#include <stdexcept>

Furniture::Furniture()
    : FactoryItem("Мебель"), height_(0.0), width_(0.0), depth_(0.0), cost_(0.0) {
    std::cout << "Вызван конструктор без параметров: Furniture (Мебель)\n";
}

Furniture::Furniture(const std::string& furnitureType, double height, double width,
    double depth, const std::string& color,
    const std::string& material, double cost)
    : FactoryItem("Мебель"), height_(0.0), width_(0.0), depth_(0.0), cost_(0.0) {
    setFurnitureType(furnitureType);
    setHeight(height);
    setWidth(width);
    setDepth(depth);
    setColor(color);
    setMaterial(material);
    setCost(cost);
    std::cout << "Вызван конструктор с параметрами: Furniture (Мебель)\n";
}

Furniture::Furniture(const Furniture& other)
    : FactoryItem(other), furnitureType_(other.furnitureType_),
    height_(other.height_), width_(other.width_), depth_(other.depth_),
    color_(other.color_), material_(other.material_), cost_(other.cost_) {
    std::cout << "Вызван конструктор копирования: Furniture (Мебель)\n";
}

Furniture::~Furniture() {
    std::cout << "Вызван деструктор: Furniture (Мебель)\n";
}

Furniture& Furniture::operator=(const Furniture& other) {
    if (this != &other) {
        FactoryItem::operator=(other);
        furnitureType_ = other.furnitureType_;
        height_ = other.height_;
        width_ = other.width_;
        depth_ = other.depth_;
        color_ = other.color_;
        material_ = other.material_;
        cost_ = other.cost_;
    }
    std::cout << "Вызван оператор присваивания: Furniture (Мебель)\n";
    return *this;
}

const std::string& Furniture::getFurnitureType() const { return furnitureType_; }
double Furniture::getHeight() const { return height_; }
double Furniture::getWidth() const { return width_; }
double Furniture::getDepth() const { return depth_; }
const std::string& Furniture::getColor() const { return color_; }
const std::string& Furniture::getMaterial() const { return material_; }
double Furniture::getCost() const { return cost_; }

void Furniture::setFurnitureType(const std::string& value) {
    if (value.find_first_not_of(" \t\r\n") == std::string::npos)
        throw std::invalid_argument("Тип мебели не должен быть пустым.");
    furnitureType_ = value;
}

void Furniture::setHeight(double value) {
    if (!std::isfinite(value) || value <= 0.0)
        throw std::invalid_argument("Высота мебели должна быть больше нуля.");
    height_ = value;
}

void Furniture::setWidth(double value) {
    if (!std::isfinite(value) || value <= 0.0)
        throw std::invalid_argument("Ширина мебели должна быть больше нуля.");
    width_ = value;
}

void Furniture::setDepth(double value) {
    if (!std::isfinite(value) || value <= 0.0)
        throw std::invalid_argument("Глубина мебели должна быть больше нуля.");
    depth_ = value;
}

void Furniture::setColor(const std::string& value) {
    if (value.find_first_not_of(" \t\r\n") == std::string::npos)
        throw std::invalid_argument("Цвет мебели не должен быть пустым.");
    color_ = value;
}

void Furniture::setMaterial(const std::string& value) {
    if (value.find_first_not_of(" \t\r\n") == std::string::npos)
        throw std::invalid_argument("Материал мебели не должен быть пустым.");
    material_ = value;
}

void Furniture::setCost(double value) {
    if (!std::isfinite(value) || value < 0.0)
        throw std::invalid_argument("Стоимость мебели не может быть отрицательной.");
    cost_ = value;
}

void Furniture::read() {
    std::cout << "\n--- Ввод данных о мебели ---\n";
    setFurnitureType(readText("Тип мебели: "));
    setHeight(readPositiveDouble("Высота: "));
    setWidth(readPositiveDouble("Ширина: "));
    setDepth(readPositiveDouble("Глубина: "));
    setColor(readText("Цвет: "));
    setMaterial(readText("Материал: "));
    setCost(readNonNegativeDouble("Стоимость: "));
}

void Furniture::edit() {
    std::cout << "Введите новые данные мебели. Все поля будут заменены.\n";
    read();
}

void Furniture::write(std::ostream& out) const {
    out << "Мебель [тип: " << furnitureType_
        << "; габариты (В x Ш x Г): " << height_ << " x " << width_ << " x " << depth_
        << "; цвет: " << color_ << "; материал: " << material_
        << "; стоимость: " << cost_ << "]";
}
void Furniture::saveData(std::ostream& out) const {
    out << std::quoted(furnitureType_) << '\n'
        << std::setprecision(std::numeric_limits<double>::max_digits10)
        << height_ << ' ' << width_ << ' ' << depth_ << '\n'
        << std::quoted(color_) << '\n'
        << std::quoted(material_) << '\n'
        << cost_ << '\n';

    if (!out)
        throw std::runtime_error("Ошибка сохранения данных мебели.");
}

void Furniture::loadData(std::istream& in) {
    std::string furnitureType, color, material;
    double height, width, depth, cost;

    if (!(in >> std::quoted(furnitureType)
        >> height >> width >> depth
        >> std::quoted(color)
        >> std::quoted(material) >> cost))
        throw std::runtime_error("Ошибка чтения данных мебели.");

    if (furnitureType.find_first_not_of(" \t\r\n") == std::string::npos ||
        color.find_first_not_of(" \t\r\n") == std::string::npos ||
        material.find_first_not_of(" \t\r\n") == std::string::npos ||
        !std::isfinite(height) || height <= 0 ||
        !std::isfinite(width) || width <= 0 ||
        !std::isfinite(depth) || depth <= 0 ||
        !std::isfinite(cost) || cost < 0)
        throw std::runtime_error("Некорректные данные мебели в файле.");

    furnitureType_ = furnitureType;
    height_ = height;
    width_ = width;
    depth_ = depth;
    color_ = color;
    material_ = material;
    cost_ = cost;
}
FactoryItem* Furniture::clone() const {
    return new Furniture(*this);
}