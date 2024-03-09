#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    char category[100];
    char title[100];
    char author[100];
    int book_id;
    int year_published;
    struct book *next;
};

struct book *head = NULL;

void password();

void main_menu() {
    printf("-----------------------------------------------------------\n");
    printf("***********************************************************\n");
    printf("                         MAIN MENU                         \n");
    printf("***********************************************************\n");
    printf("						1: ADD BOOKS                       \n");
    printf("                        2: DELETE BOOKS                    \n");
    printf("                        3: SEARCH BOOKS                    \n");
    printf("                        4: ISSUE BOOKS                     \n");
    printf("                        5: EDIT BOOKS                      \n");
    printf("                        6: VIEW BOOKS                      \n");
    printf("                        7: ISSUE RECORDS                   \n");
    printf("                        8: RETURNFUNC                      \n");
    printf("                        9: DISPLAY                         \n");
    printf("                       10: CHECK ID                        \n");
    printf("                       11: CLOSE APPLICATION               \n");
    printf("-----------------------------------------------------------\n");
}

void searchbook() {
    char search_title[100];
    struct book *current = head;
    printf("Enter the title of the book you want to search for: ");
    scanf("%s", search_title);
    while (current != NULL) {
        if (strcmp(current->title, search_title) == 0) {
            printf("Book found! Category: %s, Title: %s, Author: %s, Book Id: %d, Year Published: %d\n",
                   current->category, current->title, current->author, current->book_id, current->year_published);
            return;
        }
        current = current->next;
    }
    printf("Book not found.\n");
}

void issuebook() {
    char title[100];
    printf("Enter the title of the book you want to issue: ");
    scanf("%s", title);
    struct book *current_book = head;
    while (current_book != NULL) {
        if (strcmp(current_book->title, title) == 0) {
            if (current_book->next != NULL) {
                current_book->next = NULL;
                printf("Book issued to the reader.\n");
            } else {
                printf("This book has been issued.\n");
            }
            return;
        }
        current_book = current_book->next;
    }
    printf("Book not found in the library.\n");
}

void viewbook(void) {
    struct book *current = head;
    if (current == NULL) {
        printf("No books in the library.\n");
        return;
    }
    printf("Category\t\tTitle\t\tAuthor\t\tBook Id\tYear Published\n");
    while (current != NULL) {
        printf("%s\t%s\t%s\t%d\t%d\n", current->category, current->title, current->author, current->book_id,
               current->year_published);
        current = current->next;
    }
}

void issuerecord(void) {
    char title_to_issue[100];
    printf("Enter the title of the book to issue: ");
    scanf("%99s", title_to_issue);
    struct book *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->title, title_to_issue) == 0) {
            printf(" \"%s\" records has been issued.\n", curr->title);
            return;
        }
        curr = curr->next;
    }
    printf("Book \"%s\" not found.\n", title_to_issue);
}

void closeapplication(void) {
    printf("Exiting the program...\n");
    exit(0);
}

void addbook() {
    struct book *new_book = malloc(sizeof(struct book));
    if (new_book == NULL) {
        new_book = head;
        return;
    }
    printf("Enter the book category: ");
    scanf("%s", new_book->category);
    printf("Enter the book title: ");
    scanf("%s", new_book->title);
    printf("Enter the book author: ");
    scanf("%s", new_book->author);
    printf("Enter the book id: ");
    scanf("%d", &new_book->book_id);
    printf("Enter the year the book was published: ");
    scanf("%d", &new_book->year_published);
    new_book->next = head;
    head = new_book;
    printf("Book added to the library.\n");
}

void returnfunc() {
    char title[100];
    printf("Enter the title of the book you are returning: ");
    scanf("%s", title);
    struct book *prev_book = NULL;
    struct book *current_book = head;
    while (current_book != NULL) {
        if (strcmp(current_book->title, title) == 0) {
            if (prev_book == NULL) {
                head = current_book->next;
            } else {
                prev_book->next = current_book->next;
            }
            free(current_book);
            printf("Book returned to the library.\n");
            return;
        }
        prev_book = current_book;
        current_book = current_book->next;
    }
    printf("Book not found in the library.\n");
}

void display_books() {
    struct book *current = head;
    if (current == NULL) {
        printf("No books in library.\n\n");
    }
    while (current != NULL) {
        printf("Category: %s\n", current->category);
        printf("Title: %s\n", current->title);
        printf("Author: %s\n", current->author);
        printf("Book Id: %d\n", current->book_id);
        printf("Year Published: %d\n", current->year_published);
        printf("\n");
        current = current->next;
    }
}

void editbook() {
    char title[100];
    printf("Enter the title of the book you want to edit: ");
    scanf("%s", title);
    struct book *current_book = head;
    while (current_book != NULL) {
        if (strcmp(current_book->title, title) == 0) {
            printf("Enter the book category: ");
            scanf("%s", current_book->category);
            printf("Enter the new title of the book: ");
            scanf("%s", current_book->title);
            printf("Enter the new author of the book: ");
            scanf("%s", current_book->author);
            printf("Enter the new book id: ");
            scanf("%d", &current_book->book_id);
            printf("Enter the new year the book was published: ");
            scanf("%d", &current_book->year_published);
            printf("Book information updated.\n");
            return;
        }
        current_book = current_book->next;
    }
    printf("Book not found in the library.\n");
}

void deletebook() {
    char title[100];
    printf("Enter the title of the book you want to delete: ");
    scanf("%s", title);
    struct book *current_book = head;
    struct book *previous_book = NULL;
    while (current_book != NULL) {
        if (strcmp(current_book->title, title) == 0) {
            if (previous_book == NULL) {
                head = current_book->next;
            } else {
                previous_book->next = current_book->next;
            }
            free(current_book);
            printf("Book deleted from the library.\n");
            return;
        }
        previous_book = current_book;
        current_book = current_book->next;
    }
    printf("Book not found in the library.\n");
}

int check_id(int t) {
    struct book *temp = head;
    while (temp != NULL) {
        if (temp->book_id == t) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int main() {
    int flag = 1;
    printf("-----------------------------------------------------------------------------\n");
    printf("*****************************************************************************\n");
    printf("                         WELCOME TO KARPAGAM LIBRARY                         \n");
    printf("*****************************************************************************\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("\n");
    password();
    while (flag) {
        main_menu();
        int choice;
        int result;
        int bid;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addbook();
                break;
            case 2:
                deletebook();
                break;
            case 3:
                searchbook();
                break;
            case 4:
                issuebook();
                break;
            case 5:
                editbook();
                break;
            case 6:
                viewbook();
                break;
            case 7:
                issuerecord();
                break;
            case 8:
                returnfunc();
                break;
            case 9:
                display_books();
                break;
            case 10:
                printf("Enter the id to be checked:");
                scanf("%d", &bid);
                result = check_id(bid);
                if (result == 1) {
                    printf("Book found!!\n");
                } else {
                    printf("Book not found!!\n");
                }
                break;

            case 11:
                closeapplication();
                break;
            default:
                printf("Invalid choice.\n");
                flag = 0;
        }
    }
    return 0;
}

void password() {
    char input[100];
    printf("Enter the password: ");
    scanf("%s", input);
    if (strcmp(input, "password123") == 0) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
        exit(0);
    }
}

