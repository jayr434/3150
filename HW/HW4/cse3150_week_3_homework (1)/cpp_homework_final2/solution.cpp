
#include <iostream>
#include <cstring>   // for strlen, strcpy

// TODO: function prototypes
void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity);
void updateGPA(double* gpaPtr, double newGpa);
void printStudent(const char* name, const double& gpa);
double averageGPA(const double gpas[], int size);

// TODO: implement addStudent
void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity) {
    if (size >= capacity) {
        throw "List full";
    }
    char* copy = new char[std::strlen(name) + 1];
    std::strcpy(copy, name);
    names[size] = copy;
    gpas[size] = gpa;
    size = size + 1;
}

// TODO: implement updateGPA
void updateGPA(double* gpaPtr, double newGpa) {
    if (gpaPtr != nullptr) {
        *gpaPtr = newGpa;
    }
}

// TODO: implement printStudent
void printStudent(const char* name, const double& gpa) {
    std::cout << name << " " << gpa << std::endl;
}

// TODO: implement averageGPA
double averageGPA(const double gpas[], int size) {
    if (size == 0) {
        throw "No students";
    }
    double total = 0.0;
    for (int i = 0; i < size; i = i + 1) {
        total = total + gpas[i];
    }
    return total / size;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./program <capacity>" << std::endl;
        return 1;
    }

    // VLAs, not covered
    //char* names[capacity];
    //double gpas[capacity];
    int capacity = std::stoi(argv[1]);

    char** names = new char*[capacity];
    double* gpas = new double[capacity];
    int size = 0;

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Update GPA\n";
        std::cout << "3. Print all students\n";
        std::cout << "4. Compute average GPA\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                char buffer[100];
                double gpa;
                std::cout << "Enter name: ";
                std::cin >> buffer;
                std::cout << "Enter GPA: ";
                std::cin >> gpa;
                try {
                    addStudent(buffer, gpa, names, gpas, size, capacity);
                } catch (const char* msg) {
                    std::cout << msg << std::endl;
                }
                break;
            }
            case 2: {
                if (size == 0) {
                    std::cout << "No students to update" << std::endl;
                } else {
                    std::cout << "Select a student:" << std::endl;
                    for (int i = 0; i < size; i = i + 1) {
                        std::cout << i << ". " << names[i] << " " << gpas[i] << std::endl;
                    }
                    int idx;
                    double newGpa;
                    std::cout << "Enter index: ";
                    std::cin >> idx;
                    std::cout << "Enter new GPA: ";
                    std::cin >> newGpa;
                    if (idx >= 0 && idx < size) {
                        updateGPA(&gpas[idx], newGpa);
                        std::cout << "Updated" << std::endl;
                    } else {
                        std::cout << "Invalid index" << std::endl;
                    }
                }
                break;
            }
            case 3: {
                if (size == 0) {
                    std::cout << "No students" << std::endl;
                } else {
                    for (int i = 0; i < size; i = i + 1) {
                        printStudent(names[i], gpas[i]);
                    }
                }
                break;
            }
            case 4: {
                try {
                    double avg = averageGPA(gpas, size);
                    std::cout << "Average GPA: " << avg << " (rounded int: " << static_cast<int>(avg) << ")" << std::endl;
                } catch (const char* msg) {
                    std::cout << msg << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice" << std::endl;
            }
        }
    } while (choice != 5);

    // free memory
    for (int i = 0; i < size; i = i + 1) {
        delete[] names[i];
    }
    delete[] names;
    delete[] gpas;

    return 0;
}
