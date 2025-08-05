#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for expense
struct Expense {
    char date[11];         // Date in YYYY-MM-DD format
    float amount;
    char description[100];
    char category[50];
};

// Function to add expense
void addExpense() {
    FILE *file;
    struct Expense expense;
    
    // Open file in append mode (text)
    file = fopen("expenses.csv", "a");
    if (file == NULL) {
        printf("Unable to open file!\n");
        return;
    }
    
    // Get expense details from user
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", expense.date);
    printf("Enter amount: ");
    scanf("%f", &expense.amount);
    printf("Enter description: ");
    scanf(" %[^\n]%*c", expense.description);  // To accept spaces in description
    printf("Enter category: ");
    scanf("%s", expense.category);
    
    // Write the expense to CSV file
    // Format: date,amount,description,category\n
    fprintf(file, "%s,%.2f,%s,%s\n", expense.date, expense.amount, expense.description, expense.category);
    printf("Expense added successfully!\n");

    // Close file
    fclose(file);
}

// Function to view all expenses
void viewExpenses() {
    FILE *file;
    char line[300];
    
    // Open file in read mode (text)
    file = fopen("expenses.csv", "r");
    if (file == NULL) {
        printf("No expenses recorded yet!\n");
        return;
    }

    // Print header
    printf("\nDate         Amount    Description            Category\n");
    printf("------------------------------------------------------------\n");
    
    // Read and display all expenses line by line
    while (fgets(line, sizeof(line), file)) {
        struct Expense expense;
        // Parse CSV line
        // Using sscanf here assuming no commas inside description or category
        sscanf(line, "%10[^,],%f,%99[^,],%49[^\n]", expense.date, &expense.amount, expense.description, expense.category);
        
        printf("%-12s %-8.2f %-20s %-15s\n", expense.date, expense.amount, expense.description, expense.category);
    }

    // Close file
    fclose(file);
}

// Function to search expenses by category
void searchByCategory() {
    FILE *file;
    char line[300];
    char searchCategory[50];
    int found = 0;
    
    // Open file in read mode (text)
    file = fopen("expenses.csv", "r");
    if (file == NULL) {
        printf("No expenses recorded yet!\n");
        return;
    }
    
    // Get category to search
    printf("Enter category to search: ");
    scanf("%s", searchCategory);

    printf("\nDate         Amount    Description            Category\n");
    printf("------------------------------------------------------------\n");
    
    // Read and check each line
    while (fgets(line, sizeof(line), file)) {
        struct Expense expense;
        sscanf(line, "%10[^,],%f,%99[^,],%49[^\n]", expense.date, &expense.amount, expense.description, expense.category);
        
        if (strcmp(expense.category, searchCategory) == 0) {
            printf("%-12s %-8.2f %-20s %-15s\n", expense.date, expense.amount, expense.description, expense.category);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No expenses found for the category: %s\n", searchCategory);
    }

    fclose(file);
}

// Main function with menu
int main() {
    int choice;
    
    while (1) {
        printf("\n--- Expense Tracker ---\n");
        printf("1. Add Expense\n");
        printf("2. View All Expenses\n");
        printf("3. Search Expenses by Category\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                searchByCategory();
                break;
            case 4:
                printf("Exiting Expense Tracker. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}