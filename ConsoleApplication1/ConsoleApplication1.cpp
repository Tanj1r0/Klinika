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
    // ����������� ������
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

    // ���������� ��������� < ��� ���������� ��������� �� ���
    bool operator<(const Patient& other) const {
        return fullName < other.fullName;
    }

    // ����� ��� ������ ���������� � ��������
    void display() const {
        std::cout << u8"���: " << fullName << std::endl;
        std::cout << u8"���: " << gender << std::endl;
        std::cout << u8"���� ��������: " << birthDate << std::endl;
        std::cout << u8"����� ��������: " << phoneNumber << std::endl;
        std::cout << u8"���������� ������: " << passportData << std::endl;
        std::cout << u8"�����: " << insurancePolicy << std::endl;
        std::cout << u8"�����: " << address << std::endl;
        std::cout << u8"�������: " << diagnosis << std::endl;
    }

    // ����� ��� �������� ������� ��������� � ������ �������� (������������������� �����)
    bool containsSubstring(const std::string& substring) const {
        std::string lowerCaseData = fullName + gender + birthDate + phoneNumber +
            passportData + insurancePolicy + address + diagnosis;
        std::string lowerCaseSubstring = substring;
        std::transform(lowerCaseData.begin(), lowerCaseData.end(), lowerCaseData.begin(), [](unsigned char c) -> char { return std::tolower(c); });
        std::transform(lowerCaseSubstring.begin(), lowerCaseSubstring.end(), lowerCaseSubstring.begin(), [](unsigned char c) -> char { return std::tolower(c); });
        return lowerCaseData.find(lowerCaseSubstring) != std::string::npos;
    }

    // ������ ��� ��������� ��� ��������
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
        std::cout << u8"������ �������� ����� patients_data.txt" << std::endl;
        return 1;
    }

    while (true) {
        std::cout << u8"1. ����� ��������\n";
        std::cout << u8"2. ���������� ���������\n";
        std::cout << u8"3. ����� ���� ���������\n";
        std::cout << u8"4. �������� ��������\n";
        std::cout << u8"5. �����\n";
        std::cout << u8"�������� ����� ����: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string searchQuery;
            std::cout << u8"������� ������ ��� ������: ";
            std::cin >> searchQuery;

            bool found = false;
            for (const auto& patient : patients) {
                if (patient.containsSubstring(searchQuery)) {
                    patient.display();
                    found = true;
                }
            }

            if (!found) {
                std::cout << u8"�������� � ������ ������� �� �������.\n";
            }
        }
        else if (choice == 2) {
            std::sort(patients.begin(), patients.end());
            std::cout << u8"�������� ������������� �� ���.\n";
        }
        else if (choice == 3) {
            for (const auto& patient : patients) {
                patient.display();
                std::cout << u8"--------------------------\n";
            }
        }
        else if (choice == 4) {
            std::string name, gender, birthDate, phoneNumber, passportData, insurancePolicy, address, diagnosis;
            std::cin.ignore(); // ������� ����� ����� ����� ������ �����, ����� �������� �������� �����

            std::cout << u8"������� ��� ��������: ";
            std::getline(std::cin, name);
            std::cout << u8"������� ��� ��������: ";
            std::getline(std::cin, gender);
            std::cout << u8"������� ���� �������� ��������: ";
            std::getline(std::cin, birthDate);
            std::cout << u8"������� ����� �������� ��������: ";
            std::getline(std::cin, phoneNumber);
            std::cout << u8"������� ���������� ������ ��������: ";
            std::getline(std::cin, passportData);
            std::cout << u8"������� ����� ���������� ������ ��������: ";
            std::getline(std::cin, insurancePolicy);
            std::cout << u8"������� ����� ��������: ";
            std::getline(std::cin, address);
            std::cout << u8"������� ������� ��������: ";
            std::getline(std::cin, diagnosis);

            Patient newPatient(name, gender, birthDate, phoneNumber, passportData, insurancePolicy, address, diagnosis);
            patients.push_back(newPatient);
            std::cout << u8"������� ��������.\n";

            std::ofstream outputFile("patients_data.txt", std::ios::out | std::ios::trunc);
            if (outputFile.is_open()) {
                // ������������� ����� ������ � UTF-8
                outputFile << std::string(u8"\uFEFF");  // ��������� BOM (Byte Order Mark) ��� �������� UTF-8 ���������
                // ������ ������ ������ �������� � ���� � �������� ����� ������ � �����
                outputFile << newPatient.getFullName() << "," << newPatient.getGender() << "," << newPatient.getBirthDate() << ","
                    << newPatient.getPhoneNumber() << "," << newPatient.getPassportData() << "," << newPatient.getInsurancePolicy() << ","
                    << newPatient.getAddress() << "," << newPatient.getDiagnosis() << "\n";
                outputFile.close();
                std::cout << u8"������� �������� � ������ ��������� � �����.\n";
            }
            else {
                std::cout << u8"������ �������� ����� ��� ������.\n";
            }
        }

        else if (choice == 5) {
            break;
        }
        else {
            std::cout << u8"�������� �����. ����������, ���������� �����.\n";
        }
    }

    return 0;
}
