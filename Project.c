#include<stdio.h>
#include<string.h>

// Structure
typedef struct {
    char book_name[100];
    char writer[100];
    char distributor[100];
    int availability;
    int quantity;
} Book;

// Global variables
Book catalog[100];
int totalBooks = 0;

// Function to add Book
void add_book() {
    if (totalBooks >= 100) {
        printf("\nLibrary is full, cannot add any more books.\n");
        return;
    }

    char bookName[100];
    char writerName[100];
    char distributorName[100];

    printf("\n=====================================\n");
    printf("                  Add Book             \n");
    printf("=======================================\n");
    printf("Enter Book Name: ");
    getchar();
    fgets(bookName, 100, stdin);
    bookName[strcspn(bookName, "\n")] = '\0';

    printf("Enter Writer name: ");
    fgets(writerName, 100, stdin);
    writerName[strcspn(writerName, "\n")] = '\0';

    printf("Enter Distributor name: ");
    fgets(distributorName, 100, stdin);
    distributorName[strcspn(distributorName, "\n")] = '\0';

    // Check if the book already exists
    for (int i = 0; i < totalBooks; i++) {
        if (strcmp(catalog[i].book_name, bookName) == 0 &&
            strcmp(catalog[i].writer, writerName) == 0 &&
            strcmp(catalog[i].distributor, distributorName) == 0) {
            catalog[i].quantity++;
            printf("\nBook already exists. Increased the quantity to %d.\n", catalog[i].quantity);
            return;
        }
    }

    // Add a new book if it doesn't exist
    strcpy(catalog[totalBooks].book_name, bookName);
    strcpy(catalog[totalBooks].writer, writerName);
    strcpy(catalog[totalBooks].distributor, distributorName);
    catalog[totalBooks].availability = 1;
    catalog[totalBooks].quantity = 1;
    totalBooks++;

    printf("\nBook added successfully!\n");
}

// Function to display Total Books
void Catalog() {
    if (totalBooks == 0) {
        printf("\nNo Books in the catalog.\n");
        return;
    }

    printf("\n=====================================\n");
    printf("            Catalog Overview           \n");
    printf("=======================================\n");

    for (int i = 0; i < totalBooks; i++) {
        printf("Book %d:\n", i + 1);
        printf("  Book Name     : %s\n", catalog[i].book_name);
        printf("  Writer        : %s\n", catalog[i].writer);
        printf("  Distributor   : %s\n", catalog[i].distributor);
        printf("  Quantity      : %d\n", catalog[i].quantity);
        printf("  Status        : %s\n", catalog[i].availability ? "Available" : "Not Available");
        printf("----------------------------------------\n");
    }
}

// Function to list all Books by a writer
void Books_Writer() {
    char writerName[100];
    int found = 0;

    printf("\n=====================================\n");
    printf("           Search By Writer            \n");
    printf("=======================================\n");

    printf("Enter writer name: ");
    getchar();
    fgets(writerName, 100, stdin);
    writerName[strcspn(writerName, "\n")] = '\0';

    printf("\nBooks by '%s':\n", writerName);
    printf("----------------------------------------\n");
    for (int i = 0; i < totalBooks; i++) {
        if (catalog[i].availability && strcmp(catalog[i].writer, writerName) == 0) {
            printf("  Book Name      : %s\n", catalog[i].book_name);
            printf("  Distributor    : %s\n", catalog[i].distributor);
            printf("----------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No Books found by this writer.\n");
    }
}

// Function to count total Books in the catalog
void Total_Books() {
    int activeBooks = 0;
    for (int i = 0; i < totalBooks; i++) {
        if (catalog[i].availability) {
            activeBooks += catalog[i].quantity;
        }
    }

    printf("\n=====================================\n");
    printf("           Total Books                 \n");
    printf("=======================================\n");

    printf("Total Books in the catalog: %d\n", activeBooks);
}

// Function to issue a book
void Issue_Book() {
    char book_name_book[100];
    int found = 0;

    printf("\n=====================================\n");
    printf("             Issue a Book              \n");
    printf("=======================================\n");
    printf("Enter the Book Name of the book to Issue: ");
    getchar();
    fgets(book_name_book, 100, stdin);
    book_name_book[strcspn(book_name_book, "\n")] = '\0';

    for (int i = 0; i < totalBooks; i++) {
        if (catalog[i].availability && strcmp(catalog[i].book_name, book_name_book) == 0) {
            catalog[i].quantity--;
            if (catalog[i].quantity == 0) {
                catalog[i].availability = 0;
            }
            printf("\nYou have successfully issued the book '%s'. Remaining quantity: %d\n", book_name_book, catalog[i].quantity);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nSorry, the book '%s' is either not available or does not exist in the catalog.\n", book_name_book);
    }
}

// Function to return a book
void Return_Book() {
    char book_name_book[100];
    int found = 0;

    printf("\n=====================================\n");
    printf("           Return a Book               \n");
    printf("=======================================\n");
    printf("Enter the Book Name of the book to return: ");
    getchar();
    fgets(book_name_book, 100, stdin);
    book_name_book[strcspn(book_name_book, "\n")] = '\0';

    for (int i = 0; i < totalBooks; i++) {
        if (strcmp(catalog[i].book_name, book_name_book) == 0) {
            catalog[i].quantity++;
            catalog[i].availability = 1;
            printf("\nYou have successfully returned the book '%s'. Total quantity: %d\n", book_name_book, catalog[i].quantity);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nSorry, the book '%s' does not exist in the catalog.\n", book_name_book);
    }
}

// Main function
int main() {
    int userSelection;

    while (1) {
        printf("\n=======================================\n");
        printf("      Library Management Software       \n");
        printf("=======================================\n");
        printf("1. Add New Book\n");
        printf("2. Display all Books\n");
        printf("3. Find Book by Writer\n");
        printf("4. Total Books\n");
        printf("5. Issue a Book\n");
        printf("6. Return a Book\n");
        printf("7. Exit\n");
        printf("======================================\n");
        printf("Enter your selection: ");
        scanf("%d", &userSelection);

        userSelection *= 10;

        switch (userSelection) {
            case 10:
                add_book();
                break;
            case 20:
                Catalog();
                break;
            case 30:
                Books_Writer();
                break;
            case 40:
                Total_Books();
                break;
            case 50:
                Issue_Book();
                break;
            case 60:
                Return_Book();
                break;
            case 70:
                printf("\nThank you for using the Library Management Console. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid selection! Please try again.\n");
        }
    }
    return 0;
}