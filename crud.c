#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 25
#define FILENAME "users.txt"

// structure
typedef struct {
  int id;
  char name[MAX_NAME_LENGTH];
  int age;
} User;

void create();
void read();
void update();
void delete ();
void save(User user);
int userExists(int id);

int main() {
  int choice;
  while (1) {
    printf("\nMenu:\n");
    printf("1. Add User (Create)\n");
    printf("2. View Users (Read)\n");
    printf("3. Update User\n");
    printf("4. Delete User\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      create();
      break;
    case 2:
      read();
      break;
    case 3:
      update();
      break;
    case 4:
      delete ();
      break;
    case 5:
      exit(0);
    default:
      printf("Invalid choice! Please try again.\n");
    }
  }
  return 0;
}

void create() {
  User user;
  printf("Enter User ID: ");
  scanf("%d", &user.id);

  if (userExists(user.id)) {
    printf("User with this ID already exists!\n");
    return;
  }
   getchar();
  printf("Enter Name: ");
  fgets(user.name, MAX_NAME_LENGTH, stdin);
  user.name[strcspn(user.name, "\n")] = '\0';
  
  printf("Enter Age: ");
  scanf("%d", &user.age);

  save(user);
  printf("User added successfully!\n");
}

void read() {
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("No users found.\n");
    return;
  }

  User user;
  printf("\nList of Users:\n");
  while (fscanf(file, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) !=
         EOF) {
    printf("ID: %d, Name: %s, Age: %d\n", user.id, user.name, user.age);
  }

  fclose(file);
}

void update() {
  int id;
  printf("Enter User ID to update: ");
  scanf("%d", &id);

  if (!userExists(id)) {
    printf("User with ID %d not found!\n", id);
    return;
  }
  getchar();

  FILE *file = fopen(FILENAME, "r+");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  User user;
  int found = 0;

  FILE *tempFile = fopen("temp.txt", "w");
  if (tempFile == NULL) {
    printf("Error opening temporary file.\n");
    fclose(file);
    return;
  }


  while (fscanf(file, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) != EOF) {
    if (user.id == id) {
      found = 1;
      printf("Enter new name: ");
      fgets(user.name, MAX_NAME_LENGTH, stdin);
      user.name[strcspn(user.name, "\n")] = '\0';

      printf("Enter new age: ");
      scanf("%d", &user.age);
      getchar();
    }
    fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
  }

  if (!found) {
    printf("User with ID %d not found!\n", id);
  } else {
    printf("User updated successfully!\n");
  }
  fclose(file);
  fclose(tempFile);
  remove(FILENAME);
  rename("temp.txt", FILENAME);
}


void delete () {
  int id;
  printf("Enter User ID to delete: ");
  scanf("%d", &id);

  if (!userExists(id)) {
    printf("User with ID %d not found!\n", id);
    return;
  }

  FILE *file = fopen(FILENAME, "r");
  FILE *tempFile = fopen("temp.txt", "w");
  if (file == NULL || tempFile == NULL) {
    printf("Error opening file.\n");
    return;
  }

  User user;
  while (fscanf(file, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) !=
         EOF) {
    if (user.id != id) {
      fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }
  }

  fclose(file);
  fclose(tempFile);
  remove(FILENAME);
  rename("temp.txt", FILENAME);
  printf("User deleted successfully!\n");
}

void save(User user) {
  FILE *file = fopen(FILENAME, "a");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  fprintf(file, "%d,%s,%d\n", user.id, user.name, user.age);
  fclose(file);
}

int userExists(int id) {
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    return 0;
  }

  User user;
  while (fscanf(file, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) !=
         EOF) {
    if (user.id == id) {
      fclose(file);
      return 1;
    }
  }

  fclose(file);
  return 0;
}