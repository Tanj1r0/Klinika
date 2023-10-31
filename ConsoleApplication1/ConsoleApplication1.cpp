#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <Windows.h>

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
        std::cout << u8"ФИО: " << fullName << std::endl;
        std::cout << u8"Пол: " << gender << std::endl;
        std::cout << u8"Дата рождения: " << birthDate << std::endl;
        std::cout << u8"Номер телефона: " << phoneNumber << std::endl;
        std::cout << u8"Паспортные данные: " << passportData << std::endl;
        std::cout << u8"Полис: " << insurancePolicy << std::endl;
        std::cout << u8"Адрес: " << address << std::endl;
        std::cout << u8"Диагноз: " << diagnosis << std::endl;
    }

    // Метод для проверки наличия подстроки в данных пациента (регистронезависимый поиск)
    bool containsSubstring(const std::string& substring) const {
        std::string lowerCaseData = fullName + gender + birthDate + phoneNumber +
            passportData + insurancePolicy + address + diagnosis;
        std::string lowerCaseSubstring = substring;
        std::transform(lowerCaseData.begin(), lowerCaseData.end(), lowerCaseData.begin(), [](unsigned char c) -> char { return std::tolower(c); });
        std::transform(lowerCaseSubstring.begin(), lowerCaseSubstring.end(), lowerCaseSubstring.begin(), [](unsigned char c) -> char { return std::tolower(c); });
        return lowerCaseData.find(lowerCaseSubstring) != std::string::npos;
    }

    // Геттер для получения ФИО пациента
    std::string getFullName() const {
        return fullName;
    }

};

int main() {
    
    SetConsoleOutputCP(CP_UTF8);
  
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
        std::cout << u8"Ошибка открытия файла patients_data.txt" << std::endl;
        return 1;
    }

    while (true) {
        std::cout << u8"1. Поиск пациента\n";
        std::cout << u8"2. Сортировка пациентов\n";
        std::cout << u8"3. Вывод всех пациентов\n";
        std::cout << u8"4. Добавить пациента\n";
        std::cout << u8"5. Выход\n";
        std::cout << u8"Выберите пункт меню: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string searchQuery;
            std::cout << u8"Введите запрос для поиска: ";
            std::cin >> searchQuery;

            bool found = false;
            for (const auto& patient : patients) {
                if (patient.containsSubstring(searchQuery)) {
                    patient.display();
                    found = true;
                }
            }

            if (!found) {
                std::cout << u8"Пациенты с такими данными не найдены.\n";
            }
        }
        else if (choice == 2) {
            std::sort(patients.begin(), patients.end());
            std::cout << u8"Пациенты отсортированы по ФИО.\n";
        }
        else if (choice == 3) {
            for (const auto& patient : patients) {
                patient.display();
                std::cout << u8"--------------------------\n";
            }
        }
        else if (choice == 4) {
            std::string name, gender, birthDate, phoneNumber, passportData, insurancePolicy, address, diagnosis;
            std::cin.ignore(); // очищаем буфер ввода перед вводом имени, чтобы избежать пропуска ввода

            std::cout << u8"Введите ФИО пациента: ";
            std::getline(std::cin, name);
            std::cout << u8"Введите пол пациента: ";
            std::getline(std::cin, gender);
            std::cout << u8"Введите дату рождения пациента: ";
            std::getline(std::cin, birthDate);
            std::cout << u8"Введите номер телефона пациента: ";
            std::getline(std::cin, phoneNumber);
            std::cout << u8"Введите паспортные данные пациента: ";
            std::getline(std::cin, passportData);
            std::cout << u8"Введите номер страхового полиса пациента: ";
            std::getline(std::cin, insurancePolicy);
            std::cout << u8"Введите адрес пациента: ";
            std::getline(std::cin, address);
            std::cout << u8"Введите диагноз пациента: ";
            std::getline(std::cin, diagnosis);

            Patient newPatient(name, gender, birthDate, phoneNumber, passportData, insurancePolicy, address, diagnosis);
            patients.push_back(newPatient);
            std::cout << u8"Пациент добавлен.\n";

            std::ofstream outputFile("patients_data.txt", std::ios::out | std::ios::trunc);
            if (outputFile.is_open()) {
                // Устанавливаем режим вывода в UTF-8
                outputFile << std::string(u8"\uFEFF");  // Добавляем BOM (Byte Order Mark) для указания UTF-8 кодировки
                // Запись данных нового пациента в файл с символом новой строки в конце
                outputFile << newPatient.getFullName() << "," << newPatient.getGender() << "," << newPatient.getBirthDate() << ","
                    << newPatient.getPhoneNumber() << "," << newPatient.getPassportData() << "," << newPatient.getInsurancePolicy() << ","
                    << newPatient.getAddress() << "," << newPatient.getDiagnosis() << "\n";
                outputFile.close();
                std::cout << u8"Пациент добавлен и данные обновлены в файле.\n";
            }
            else {
                std::cout << u8"Ошибка открытия файла для записи.\n";
            }
        }

        else if (choice == 5) {
            break;
        }
        else {
            std::cout << u8"Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }

    return 0;
}
