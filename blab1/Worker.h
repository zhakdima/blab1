#pragma once

#include "FactoryItem.h"

class Worker : public FactoryItem {
private:
    std::string fullName_;
    std::string position_;
    double salary_;
    std::string address_;
    std::string phone_;

public:
    void saveData(std::ostream& out) const override;
    void loadData(std::istream& in) override;
    Worker();
    Worker(const std::string& fullName, const std::string& position, double salary,
        const std::string& address, const std::string& phone);
    Worker(const Worker& other);
    ~Worker() override;

    Worker& operator=(const Worker& other);

    const std::string& getFullName() const;
    const std::string& getPosition() const;
    double getSalary() const;
    const std::string& getAddress() const;
    const std::string& getPhone() const;

    void setFullName(const std::string& value);
    void setPosition(const std::string& value);
    void setSalary(double value);
    void setAddress(const std::string& value);
    void setPhone(const std::string& value);

    void read() override;
    void edit() override;
    void write(std::ostream& out) const override;
    FactoryItem* clone() const override;
};

