#pragma once

#include "FactoryItem.h"

class Furniture : public FactoryItem {
private:
    std::string furnitureType_;
    double height_;
    double width_;
    double depth_;
    std::string color_;
    std::string material_;
    double cost_;

public:
    Furniture();
    Furniture(const std::string& furnitureType, double height, double width,
        double depth, const std::string& color,
        const std::string& material, double cost);
    Furniture(const Furniture& other);
    ~Furniture() override;

    Furniture& operator=(const Furniture& other);

    const std::string& getFurnitureType() const;
    double getHeight() const;
    double getWidth() const;
    double getDepth() const;
    const std::string& getColor() const;
    const std::string& getMaterial() const;
    double getCost() const;

    void setFurnitureType(const std::string& value);
    void setHeight(double value);
    void setWidth(double value);
    void setDepth(double value);
    void setColor(const std::string& value);
    void setMaterial(const std::string& value);
    void setCost(double value);

    void read() override;
    void edit() override;
    void write(std::ostream& out) const override;
    FactoryItem* clone() const override;
};

