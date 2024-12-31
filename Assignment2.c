#include <stdio.h>
#include <stdlib.h>

#define FILENAME "users.txt"

typedef struct {
    int id;
    char name[50];
    int age;
} User;

void addUser();
void viewUsers();
void updateUser();
void deleteUser();

int main() {
    int choice;

    while (1) {
        printf("\nUser Management System\n");
        printf("1. Add User\n");
        printf("2. View Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addUser(); break;
            case 2: viewUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 5: exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addUser() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    User user;
    printf("Enter User ID: ");
    scanf("%d", &user.id);
    printf("Enter Name: ");
    scanf("%s", user.name);
    printf("Enter Age: ");
    scanf("%d", &user.age);

    fprintf(file, "%d %s %d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User added successfully!\n");
}

void viewUsers() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    User user;
    printf("\nList of Users:\n");
    while (fscanf(file, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        printf("ID: %d, Name: %s, Age: %d\n", user.id, user.name, user.age);
    }
    
    fclose(file);
}

void updateUser() {
    FILE *file = fopen(FILENAME, "r+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int idToUpdate;
    User user;
    
    printf("Enter User ID to update: ");
    scanf("%d", &idToUpdate);

    while (fscanf(file, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id == idToUpdate) {
            printf("Current Name: %s, Current Age: %d\n", user.name, user.age);
            printf("Enter new Name: ");
            scanf("%s", user.name);
            printf("Enter new Age: ");
            scanf("%d", &user.age);
            fseek(file, -((long)(sizeof(user.id) + sizeof(user.name) + sizeof(user.age) + 2)), SEEK_CUR);
            fprintf(file, "%d %s %d\n", user.id, user.name, user.age);
            fclose(file);
            printf("User updated successfully!\n");
            return;
        }
        

        fseek(file, sizeof(user.id) + sizeof(user.name) + sizeof(user.age) + 2 - sizeof(user.id), SEEK_CUR);
    }

    fclose(file);
    printf("User with ID %d not found.\n", idToUpdate);
}

void deleteUser() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        fclose(file);
        printf("Error opening temporary file!\n");
        return;
    }

   int idToDelete;
   User user;

   printf("Enter User ID to delete: ");
   scanf("%d", &idToDelete);

   while (fscanf(file, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
       if (user.id != idToDelete) { 
           fprintf(tempFile, "%d %s %d\n", user.id, user.name, user.age); 
       }
   }

   fclose(file);
   fclose(tempFile);

   remove(FILENAME); 
   rename("temp.txt", FILENAME);

   printf("User with ID %d deleted successfully!\n", idToDelete);
}
