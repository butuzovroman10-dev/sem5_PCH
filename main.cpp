#include "MyContainer.h"
#include "Developer.h"
#include "Manager.h"
#include "Tester.h"
#include <iostream>
#include <algorithm>
#include <string>

bool compareBySalary(const Employee* a, const Employee* b) {
    return a->getSalary() < b->getSalary();
}

bool compareById(const Employee* a, const Employee* b) {
    return a->getId() < b->getId();
}

void printAllEmployees(const MyContainer<Employee*>& container) {
    std::cout << "\n=== All Employees ===" << std::endl;
    for (auto it = container.begin(); it != container.end(); ++it) {
        (*it)->displayInfo();
        std::cout << std::endl;
    }
}

void findAndDisplayEmployee(MyContainer<Employee*>& container, int id) {
    auto it = std::find_if(container.begin(), container.end(), 
        [id](Employee* emp) { return emp->getId() == id; });
    
    if (it != container.end()) {
        std::cout << "\nFound employee with ID " << id << ": ";
        (*it)->displayInfo();
        std::cout << std::endl;
    } else {
        std::cout << "\nEmployee with ID " << id << " not found" << std::endl;
    }
}

void sortAndDisplay(MyContainer<Employee*>& container, bool bySalary) {
    if (bySalary) {
        std::sort(container.begin(), container.end(), compareBySalary);
        std::cout << "\n=== Employees sorted by salary ===" << std::endl;
    } else {
        std::sort(container.begin(), container.end(), compareById);
        std::cout << "\n=== Employees sorted by ID ===" << std::endl;
    }
    
    for (auto it = container.begin(); it != container.end(); ++it) {
        (*it)->displayInfo();
        std::cout << " - Salary: $" << (*it)->getSalary() << std::endl;
    }
}

void demonstrateHighEfficiencyEmployees(const MyContainer<Employee*>& container) {
    std::cout << "\n=== High Efficiency Employees (Efficiency > 0.85) ===" << std::endl;
    
    for (auto it = container.begin(); it != container.end(); ++it) {
        double efficiency = (*it)->getEfficiency();
        if (efficiency > 0.85) {
            (*it)->displayInfo();
            std::cout << " - Efficiency: " << (efficiency * 100) << "%" << std::endl;
        }
    }
}

int main() {
    MyContainer<Employee*> company;
    
    Developer* dev1 = new Developer("Alice", 101, 75000, "C++", 450);
    Developer* dev2 = new Developer("Diana", 104, 80000, "Python", 600);
    Manager* mgr1 = new Manager("Bob", 102, 90000, 8, 5);
    Manager* mgr2 = new Manager("Eve", 105, 95000, 12, 7);
    Tester* tst1 = new Tester("Charlie", 103, 65000, 25, "Selenium");
    Tester* tst2 = new Tester("Frank", 106, 70000, 30, "Cypress");
    
    company.push_back(dev1);
    company.push_back(mgr1);
    company.push_back(tst1);
    company.push_back(dev2);
    company.push_back(mgr2);
    company.push_back(tst2);
    
    std::cout << "=== MyContainer Demo ===" << std::endl;
    std::cout << "Container size: " << company.size() << std::endl;
    std::cout << "Container capacity: " << company.getCapacity() << std::endl;
    
    printAllEmployees(company);
    
    findAndDisplayEmployee(company, 103);
    findAndDisplayEmployee(company, 999);
    
    sortAndDisplay(company, true);
    
    sortAndDisplay(company, false);
    
    demonstrateHighEfficiencyEmployees(company);
    
    std::cout << "\n=== Range-based for loop demo ===" << std::endl;
    for (const auto& emp : company) {
        emp->work();
    }
    
    std::cout << "\n=== Clearing container ===" << std::endl;
    company.clear();
    std::cout << "Container size after clear: " << company.size() << std::endl;
    
    delete dev1;
    delete dev2;
    delete mgr1;
    delete mgr2;
    delete tst1;
    delete tst2;
    
    return 0;
}