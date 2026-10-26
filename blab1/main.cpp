
#include "Car.h"
#include "Factory.h"
#include "Furniture.h"
#include "Worker.h"
#include <stdexcept>
#include <exception>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

FactoryItem* createItem(const std::string& type) {
    if (type == "Мебель") return new Furniture();
    if (type == "Работник") return new Worker();
    if (type == "Машина") return new Car();
    throw std::invalid_argument("Неизвестная категория объекта: " + type);
}

void manageCategory(Factory& factory, const std::string& type) {
    while (true) {
        std::cout << "\n    Управление категорией «" << type << "»    \n"
            << "1. Добавить запись\n"
            << "2. Вывести записи\n"
            << "3. Изменить запись\n"
            << "4. Удалить запись\n"
            << "0. Назад\n";

        const int action = readIntInRange("Выберите действие: ", 0, 4);
        if (action == 0) return;

        try {
            if (action == 1) {
                FactoryItem* item = createItem(type);
                try {
                    item->read();
                    factory.add(item);
                    item = nullptr; // Владение объектом перешло к Factory.
                    std::cout << "Запись добавлена.\n";
                }
                catch (...) {
                    delete item;
                    throw;
                }
            }
            else if (action == 2) {
                factory.showType(type);
            }
            else if (action == 3) {
                const std::size_t count = factory.countByType(type);
                if (count == 0) {
                    std::cout << "Изменять нечего: записей в этой категории нет.\n";
                }
                else {
                    factory.showType(type);
                    int number = readIntInRange("Номер записи для изменения: ", 1,
                        static_cast<int>(count));
                    factory.editByType(type, number);
                }
            }
            else if (action == 4) {
                const std::size_t count = factory.countByType(type);
                if (count == 0) {
                    std::cout << "Удалять нечего: записей в этой категории нет.\n";
                }
            
                else {
                    factory.showType(type);
                    int number = readIntInRange("Номер записи для удаления: ", 1,
                        static_cast<int>(count));
                    factory.removeByType(type, number);
                }
            }
        }
        catch (const std::exception& error) {
            if (!std::cin) throw;
            std::cout << "Исключение: " << error.what() << '\n';
        }
    }
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
    try {
        std::cout << "    Учёт данных мебельной фабрики    \n";
        const std::string factoryName = readText("Введите название фабрики: ");
        Factory factory(factoryName);

        while (true) {
            std::cout << "\n    Главное меню: " << factory.getName() << "    \n"
                << "1. Мебель\n"
                << "2. Работники\n"
                << "3. Машины\n"
                << "4. Показать все записи\n"
                << "5. Сохранить данные в файл\n"
                << "6. Загрузить данные из файла\n"
                << "0. Выход\n";

            const int choice = readIntInRange("Выберите пункт меню: ", 0, 6);
            if (choice == 0) break;

            if (choice == 1) manageCategory(factory, "Мебель");
            else if (choice == 2) manageCategory(factory, "Работник");
            else if (choice == 3) manageCategory(factory, "Машина");
            else if (choice == 5) {
                try {
                    std::string fileName = readText(
                        "Введите имя файла для сохранения: "
                    );
                    factory.saveToFile(fileName);
                }
                catch (const std::exception& error) {
                    if (!std::cin) throw;
                    std::cout << "Ошибка сохранения: "
                        << error.what() << '\n';
                }
            }
            else if (choice == 6) {
                try {
                    std::string fileName = readText(
                        "Введите имя файла для загрузки: "
                    );
                    factory.loadFromFile(fileName);
                }
                catch (const std::exception& error) {
                    if (!std::cin) throw;
                    std::cout << "Ошибка загрузки: "
                        << error.what() << '\n';
                }
            }
        }

        std::cout << "Завершение работы программы.\n";
    }
    catch (const std::exception& error) {
        std::cout << "Программа завершена: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
