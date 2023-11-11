#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <Windows.h>
#include <locale>

class Patient {
private:
    std::string fullName;
    std::string gender;
    std::string birthDate;
    std::string phoneNumber;
    std::string passportData;
    std::string insurancePolicy;
    std::string address;
    std::string diagnosis;

public:
    // Конструктор класса
    Patient(const std::string& name, const std::string& gender, const std::string& birthDate,
        const std::string& phoneNumber, const std::string& passportData, const std::string& insurancePolicy,
        const std::string& address, const std::string& diagnosis)
        : fullName(name), gender(gender), birthDate(birthDate), phoneNumber(phoneNumber),
        passportData(passportData), insurancePolicy(insurancePolicy), address(address), diagnosis(diagnosis) {}

    std::string getPhoneNumber() const {
        return phoneNumber;
    }

    std::string getPassportData() const {
        return passportData;
    }

    std::string getInsurancePolicy() const {
        return insurancePolicy;
    }

    std::string getGender() const {
        return gender;
    }

    std::string getDiagnosis() const {
        return diagnosis;
    }

    std::string getBirthDate() const {
        return birthDate;
    }

    std::string getAddress() const {
        return address;
    }

    // Перегрузка оператора < для сортировки пациентов по ФИО
    bool operator<(const Patient& other) const {
        return fullName < other.fullName;
    }

    // Метод для вывода информации о пациенте
    void display() const {
        std::cout << "ФИО: " << fullName << std::endl;
        std::cout << "Пол: " << gender << std::endl;
        std::cout << "Дата рождения: " << birthDate << std::endl;
        std::cout << "Номер телефона: " << phoneNumber << std::endl;
        std::cout << "Паспортные данные: " << passportData << std::endl;
        std::cout << "Полис: " << insurancePolicy << std::endl;
        std::cout << "Адрес: " << address << std::endl;
        std::cout << "Диагноз: " << diagnosis << std::endl;
    }

    // Метод для проверки наличия подстроки в данных пациента (регистронезависимый поиск)
    bool containsSubstring(const std::string& substring) const {
        std::string lowerCaseData = fullName + gender + birthDate + phoneNumber +
            passportData + insurancePolicy + address + diagnosis;
        std::string lowerCaseSubstring = substring;

        std::transform(lowerCaseData.begin(), lowerCaseData.end(), lowerCaseData.begin(), [](unsigned char c) -> char { return std::tolower(c, std::locale("")); });
        std::transform(lowerCaseSubstring.begin(), lowerCaseSubstring.end(), lowerCaseSubstring.begin(), [](unsigned char c) -> char { return std::tolower(c, std::locale("")); });

        return lowerCaseData.find(lowerCaseSubstring) != std::string::npos;
    }

    // Геттер для получения ФИО пациента
    std::string getFullName() const {
        return fullName;
    }

};

int main() {

    system("chcp 1251");

    std::vector<Patient> patients;

    std::ifstream inputFile("patients_data.txt");
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::stringstream ss(line);
            std::string name, gender, birthDate, phoneNumber, passportData, insurancePolicy, address, diagnosis;

            std::getline(ss, name, ',');
            std::getline(ss, gender, ',');
            std::getline(ss, birthDate, ',');
            std::getline(ss, phoneNumber, ',');
            std::getline(ss, passportData, ',');
            std::getline(ss, insurancePolicy, ',');
            std::getline(ss, address, ',');
            std::getline(ss, diagnosis, ',');

            patients.emplace_back(name, gender, birthDate, phoneNumber, passportData, insurancePolicy, address, diagnosis);
        }
        inputFile.close();
    }
    else {
        std::cout << "Ошибка открытия файла patients_data.txt" << std::endl;
        return 1;
    }

    while (true) {
        std::cout << "1. Поиск пациента\n";
        std::cout << "2. Сортировка пациентов\n";
        std::cout << "3. Вывод всех пациентов\n";
        std::cout << "4. Добавить пациента\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите пункт меню: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string searchQuery;
            std::cout << "Введите запрос для поиска: ";
            std::cin >> searchQuery;

            bool found = false;
            for (const auto& patient : patients) {
                if (patient.containsSubstring(searchQuery)) {
                    patient.display();
                    found = true;
                }
            }

            if (!found) {
                std::cout << "Пациенты с такими данными не найдены.\n";
            }
        }
        else if (choice == 2) {
            std::sort(patients.begin(), patients.end());
            std::cout << "Пациенты отсортированы по ФИО.\n";
        }
        else if (choice == 3) {
            for (const auto& patient : patients) {
                patient.display();
                std::cout << "--------------------------\n";
            }
        }
        else if (choice == 4) {
            std::string name, gender, birthDate, phoneNumber, passportData, insurancePolicy, address, diagnosis;
            std::cin.ignore();

            std::cout << "Введите ФИО пациента: ";
            std::getline(std::cin, name);
            std::cout << "Введите пол пациента: ";
            std::getline(std::cin, gender);
            std::cout << "Введите дату рождения пациента: ";
            std::getline(std::cin, birthDate);
            std::cout << "Введите номер телефона пациента: ";
            std::getline(std::cin, phoneNumber);
            std::cout << "Введите паспортные данные пациента: ";
            std::getline(std::cin, passportData);
            std::cout << "Введите номер страхового полиса пациента: ";
            std::getline(std::cin, insurancePolicy);
            std::cout << "Введите адрес пациента: ";
            std::getline(std::cin, address);
            std::cout << "Введите диагноз пациента: ";
            std::getline(std::cin, diagnosis);

            Patient newPatient(name, gender, birthDate, phoneNumber, passportData, insurancePolicy, address, diagnosis);
            patients.push_back(newPatient);
            std::cout << "Пациент добавлен.\n";

            std::ofstream outputFile("patients_data.txt", std::ios::out | std::ios::app);
            if (outputFile.is_open()) {
                // Запись данных нового пациента в файл в кодировке ANSI
                outputFile << newPatient.getFullName() << "," << newPatient.getGender() << "," << newPatient.getBirthDate() << ","
                    << newPatient.getPhoneNumber() << "," << newPatient.getPassportData() << "," << newPatient.getInsurancePolicy() << ","
                    << newPatient.getAddress() << "," << newPatient.getDiagnosis() << "\n";
                outputFile.close();
                std::cout << "Пациент добавлен и данные обновлены в файле.\n";
            }
            else {
                std::cout << "Ошибка открытия файла для записи.\n";
            }
        }

        else if (choice == 5) {
            break;
        }
        else {
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }

    return 0;
}
