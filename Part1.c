#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure definition
struct Employee {
    int emp_id;
    char name[50];
    float basic_salary;
    float tax;
    float net_salary;
};

struct Employee emp[MAX];
int count = 0;

// Function Prototypes
float calculateTax(float salary);
void calculateNetSalary(struct Employee *e);
void addEmployee();
void displayEmployee(int id);
void saveToFile();
void loadFromFile();

int main() {

    int choice, id;

    loadFromFile();   // Load data when program starts

    do {
        printf("\n===== Payroll Management System =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Save to File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addEmployee();
                break;

            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                displayEmployee(id);
                break;

            case 3:
                saveToFile();
                break;

            case 4:
                saveToFile();
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 4);

    return 0;
}

// Tax calculation function
float calculateTax(float salary) {

    if (salary < 10000)
        return 0;

    else if (salary <= 30000)
        return salary * 0.10;

    else if (salary <= 50000)
        return salary * 0.20;

    else
        return salary * 0.30;
}

// Net salary calculation using pointer
void calculateNetSalary(struct Employee *e) {

    e->tax = calculateTax(e->basic_salary);
    e->net_salary = e->basic_salary - e->tax;
}

// Add Employee
void addEmployee() {

    if (count >= MAX) {
        printf("Employee limit reached!\n");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &emp[count].emp_id);

    printf("Enter Name: ");
    scanf(" %[^\n]", emp[count].name);

    printf("Enter Basic Salary: ");
    scanf("%f", &emp[count].basic_salary);

    calculateNetSalary(&emp[count]);

    printf("Employee added successfully!\n");
    printf("Tax: %.2f\n", emp[count].tax);
    printf("Net Salary: %.2f\n", emp[count].net_salary);

    count++;
}

// Display Employee using search
void displayEmployee(int id) {

    int found = 0;

    for(int i = 0; i < count; i++) {

        if(emp[i].emp_id == id) {

            printf("\nEmployee Found\n");
            printf("ID: %d\n", emp[i].emp_id);
            printf("Name: %s\n", emp[i].name);
            printf("Basic Salary: %.2f\n", emp[i].basic_salary);
            printf("Tax: %.2f\n", emp[i].tax);
            printf("Net Salary: %.2f\n", emp[i].net_salary);

            found = 1;
            break;
        }
    }

    if(!found)
        printf("Employee not found!\n");
}

// Save to file
void saveToFile() {

    FILE *fp = fopen("employees.txt", "w");

    if(fp == NULL) {
        printf("File opening error!\n");
        return;
    }

    for(int i = 0; i < count; i++) {

        fprintf(fp, "%d %s %.2f %.2f %.2f\n",
                emp[i].emp_id,
                emp[i].name,
                emp[i].basic_salary,
                emp[i].tax,
                emp[i].net_salary);
    }

    fclose(fp);
    printf("Data saved to file successfully!\n");
}

// Load from file
void loadFromFile() {

    FILE *fp = fopen("employees.txt", "r");

    if(fp == NULL)
        return;

    while(fscanf(fp, "%d %s %f %f %f",
                 &emp[count].emp_id,
                 emp[count].name,
                 &emp[count].basic_salary,
                 &emp[count].tax,
                 &emp[count].net_salary) != EOF) {

        count++;
    }

    fclose(fp);
}