#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MASTER_PASSWORD "admin"
#define FILENAME "passwords.txt"

void addCredentials() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("\nError: Could not open file. Please try again.\n");
        return;
    }

    char website[50], username[50], password[50];
    printf("\nEnter Website: ");
    scanf("%s", website);
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    fprintf(file, "%s %s %s\n", website, username, password);
    fclose(file);
    printf("\nCredentials saved successfully.\n");
}

void viewCredentials() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("\nNo credentials found. Try adding some first.\n");
        return;
    }

    char website[50], username[50], password[50];
    printf("\nSaved Credentials:\n");

    while (fscanf(file, "%s %s %s", website, username, password) != EOF) {
        printf("\nWebsite: %s\nUsername: %s\nPassword: %s\n", website, username, password);
    }
    fclose(file);
}

void deleteCredential() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("\nNo credentials found.\n");
        return;
    }

    char website[50], username[50], password[50], target[50];
    FILE *temp = fopen("temp.txt", "w");
    int found = 0;

    printf("\nEnter Website to Delete: ");
    scanf("%s", target);

    while (fscanf(file, "%s %s %s", website, username, password) != EOF) {
        if (strcmp(website, target) == 0) {
            found = 1;
            printf("\nCredentials for %s deleted successfully.\n", target);
        } else {
            fprintf(temp, "%s %s %s\n", website, username, password);
        }
    }

    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (!found) 
        printf("\nNo match found for %s.\n", target);
}

void updateCredential() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("\nNo credentials found.\n");
        return;
    }

    char website[50], username[50], password[50], target[50], newUsername[50], newPassword[50];
    FILE *temp = fopen("temp.txt", "w");
    int found = 0;

    printf("\nEnter Website to Update: ");
    scanf("%s", target);

    while (fscanf(file, "%s %s %s", website, username, password) != EOF) {
        if (strcmp(website, target) == 0) {
            found = 1;
            printf("\nEnter New Username: ");
            scanf("%s", newUsername);
            printf("Enter New Password: ");
            scanf("%s", newPassword);
            fprintf(temp, "%s %s %s\n", website, newUsername, newPassword);
            printf("\nCredentials for %s updated successfully.\n", target);
        } else {
            fprintf(temp, "%s %s %s\n", website, username, password);
        }
    }

    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (!found) 
        printf("\nNo match found for %s.\n", target);
}


int main() {
    char inputPassword[20];
    printf("\nWelcome to Password Manager\n");
    printf("Enter Master Password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, MASTER_PASSWORD) != 0) {
        printf("\nIncorrect password. Access denied.\n");
        return 1;
    }

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Credentials\n");
        printf("2. View Credentials\n");
        printf("3. Delete Credential\n");
        printf("4. Update Credential\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) addCredentials();
        else if (choice == 2) viewCredentials();
        else if (choice == 3) deleteCredential();
        else if (choice == 4) updateCredential();
        else if (choice == 6) {
            printf("\nExiting. Stay secure.\n");
            break;
        } else 
            printf("\nInvalid option. Try again.\n");
    }
    return 0;
}
