#pragma once

#include "FactoryItem.h"

class Car : public FactoryItem {
private:
    std::string brand_;
    std::string model_;
    std::string registrationNumber_;

public:
    Car();
    Car(const std::string& brand, const std::string& model,
        const std::string& registrationNumber);
    Car(const Car& other);
    ~Car() override;

    Car& operator=(const Car& other);

    const std::string& getBrand() const;
    const std::string& getModel() const;
    const std::string& getRegistrationNumber() const;

    void setBrand(const std::string& value);
    void setModel(const std::string& value);
    void setRegistrationNumber(const std::string& value);

    void read() override;
    void edit() override;
    void write(std::ostream& out) const override;
    FactoryItem* clone() const override;
};