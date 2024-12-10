#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_CATEGORY_LENGTH 30
#define MAX_DESCRIPTION_LENGTH 100

typedef struct {
    char description[MAX_DESCRIPTION_LENGTH];
    float amount;
    char category[MAX_CATEGORY_LENGTH];
} Expense;

Expense expenses[MAX_EXPENSES];
int totalExpenses = 0;

void addExpense();
void removeExpense();
void updateExpense();
void viewExpenses();
void viewSummary();
void loadExpenses();
void saveExpenses();
void clearInputBuffer();

int main() {
    int choice;
    
    loadExpenses();

    while (1) {
        printf("\n--- Expense Tracker ---\n");
        printf("1. Add Expense\n");
        printf("2. Remove Expense\n");
        printf("3. Update Expense\n");
        printf("4. View All Expenses\n");
        printf("5. View Expense Summary\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addExpense(); break;
            case 2: removeExpense(); break;
            case 3: updateExpense(); break;
            case 4: viewExpenses(); break;
            case 5: viewSummary(); break;
            case 6: 
                saveExpenses();
                printf("Exiting the program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void addExpense() {
    if (totalExpenses >= MAX_EXPENSES) {
        printf("Expense limit reached! Cannot add more expenses.\n");
        return;
    }
    
    Expense newExpense;
    
    printf("Enter expense description: ");
    fgets(newExpense.description, MAX_DESCRIPTION_LENGTH, stdin);
    newExpense.description[strcspn(newExpense.description, "\n")] = 0;
    
    printf("Enter expense amount: ");
    scanf("%f", &newExpense.amount);
    clearInputBuffer();
    
    printf("Enter expense category: ");
    fgets(newExpense.category, MAX_CATEGORY_LENGTH, stdin);
    newExpense.category[strcspn(newExpense.category, "\n")] = 0;
    
    expenses[totalExpenses++] = newExpense;
    printf("Expense added successfully.\n");
}

void removeExpense() {
    int index;
    printf("Enter expense number to remove (1 to %d): ", totalExpenses);
    scanf("%d", &index);
    
    if (index < 1 || index > totalExpenses) {
        printf("Invalid expense number.\n");
        return;
    }
    
    for (int i = index - 1; i < totalExpenses - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    totalExpenses--;
    
    printf("Expense removed successfully.\n");
}

void updateExpense() {
    int index;
    printf("Enter expense number to update (1 to %d): ", totalExpenses);
    scanf("%d", &index);
    
    if (index < 1 || index > totalExpenses) {
        printf("Invalid expense number.\n");
        return;
    }

    Expense *expense = &expenses[index - 1];
    
    printf("Enter new description (previous: %s): ", expense->description);
    fgets(expense->description, MAX_DESCRIPTION_LENGTH, stdin);
    expense->description[strcspn(expense->description, "\n")] = 0;
    
    printf("Enter new amount (previous: %.2f): ", expense->amount);
    scanf("%f", &expense->amount);
    clearInputBuffer();
    
    printf("Enter new category (previous: %s): ", expense->category);
    fgets(expense->category, MAX_CATEGORY_LENGTH, stdin);
    expense->category[strcspn(expense->category, "\n")] = 0;
    
    printf("Expense updated successfully.\n");
}

void viewExpenses() {
    if (totalExpenses == 0) {
        printf("No expenses to display.\n");
        return;
    }
    
    printf("\n--- All Expenses ---\n");
    for (int i = 0; i < totalExpenses; i++) {
        printf("%d. %s - %.2f (%s)\n", i + 1, expenses[i].description, expenses[i].amount, expenses[i].category);
    }
}

void viewSummary() {
    float totalAmount = 0.0;
    for (int i = 0; i < totalExpenses; i++) {
        totalAmount += expenses[i].amount;
    }
    printf("\n--- Expense Summary ---\n");
    printf("Total expenses: %.2f\n", totalAmount);
}

void loadExpenses() {
    FILE *file = fopen("expenses.dat", "rb");
    if (file == NULL) {
        printf("No existing expense data found.\n");
        return;
    }

    fread(&totalExpenses, sizeof(int), 1, file);
    fread(expenses, sizeof(Expense), totalExpenses, file);
    fclose(file);
}

void saveExpenses() {
    FILE *file = fopen("expenses.dat", "wb");
    if (file == NULL) {
        printf("Error saving expense data.\n");
        return;
    }

    fwrite(&totalExpenses, sizeof(int), 1, file);
    fwrite(expenses, sizeof(Expense), totalExpenses, file);
    fclose(file);
}

void clearInputBuffer() {
    while (getchar() != '\n');
}
