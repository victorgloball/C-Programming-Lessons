#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX 100

// =========================
// Цвета для Windows
// =========================
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// =========================
// Эффект “печать по буквам”
// =========================
void typeWriter(const char *text) {
    while (*text) {
        putchar(*text++);
        Sleep(30); // 30 мс между символами
    }
    printf("\n");
}

void printBanner() {
    setColor(9); // светло-синий

    printf("███████╗██╗  ██╗ █████╗  ██████╗████████╗\n"); 
    printf("██╔════╝██║  ██║██╔══██╗ ██╔═══╝╚══██╔══╝\n");
    printf("███████╗███████║███████║ █████║    ██║   \n");
    printf("╚════██║██╔══██║██╔══██║ ██║       ██║   \n");
    printf("███████║██║  ██║██║  ██║ ██║       ██║   \n");
    printf("╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═╝       ╚═╝   \n");
    typeWriter("       Names of The Shaft 2025\n\n");
    setColor(7);
}

// =========================
// Простая хэш-функция
// =========================
unsigned long hash(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + c;
    return h;
}

// =========================
// Проверка существующего логина
// =========================
int loginExists(const char *login) {
    FILE *file = fopen("data/logins.txt", "r");
    if (!file) return 0;

    char line[MAX];
    while (fgets(line, sizeof(line), file)) {
        char savedLogin[MAX];
        sscanf(line, "%s", savedLogin);
        if (strcmp(savedLogin, login) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// =========================
// Регистрация пользователя
// =========================
void registerUser() {
    char login[MAX], password[MAX];

    setColor(6); // желтый
    typeWriter("\n=== Registration ===");
    setColor(7);

    printf("Enter login: ");
    scanf("%s", login);

    if (loginExists(login)) {
        setColor(4); // красный
        typeWriter("Login already exists!");
        setColor(7);
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);

    unsigned long hashed = hash(password);

    FILE *file = fopen("data/logins.txt", "a");
    if (!file) {
        setColor(4);
        typeWriter("Error opening file!");
        setColor(7);
        return;
    }
    fprintf(file, "%s %lu\n", login, hashed);
    fclose(file);

    setColor(2); // зеленый
    printf("User %s registered successfully!\n", login);
    setColor(7);
}

// =========================
// Вход пользователя
// =========================
int loginUser(char *loggedUser) {
    char login[MAX], password[MAX];
    setColor(6);
    typeWriter("\n=== Login ===");
    setColor(7);

    printf("Login: ");
    scanf("%s", login);
    printf("Password: ");
    scanf("%s", password);

    unsigned long hashed = hash(password);

    FILE *file = fopen("data/logins.txt", "r");
    if (!file) {
        setColor(4);
        typeWriter("No registered users.");
        setColor(7);
        return 0;
    }

    char savedLogin[MAX];
    unsigned long savedHash;
    int success = 0;

    while (fscanf(file, "%s %lu", savedLogin, &savedHash) == 2) {
        if (strcmp(savedLogin, login) == 0 && savedHash == hashed) {
            success = 1;
            strcpy(loggedUser, login);
            break;
        }
    }

    fclose(file);

    if (success) {
        setColor(2);
        printf("Welcome, %s!\n", login);
        setColor(7);
    } else {
        setColor(4);
        printf("Incorrect login or password!\n");
        setColor(7);
    }

    return success;
}

// =========================
// Создание/обновление профиля
// =========================
void createOrUpdateProfile(const char *login) {
    char filename[MAX];
    sprintf(filename, "data/profiles/%s.txt", login);

    FILE *file = fopen(filename, "w");
    if (!file) {
        setColor(4);
        typeWriter("Error saving data!");
        setColor(7);
        return;
    }

    char name[MAX], address[MAX], birth[MAX], birthPlace[MAX], job[MAX];
    setColor(6);
    typeWriter("\n=== Fill Your Profile ===");
    setColor(7);
    getchar();
    printf("Full Name: ");
    fgets(name, MAX, stdin);
    printf("Address: ");
    fgets(address, MAX, stdin);
    printf("Date of Birth: ");
    fgets(birth, MAX, stdin);
    printf("Place of Birth: ");
    fgets(birthPlace, MAX, stdin);
    printf("Job: ");
    fgets(job, MAX, stdin);

    fprintf(file, "Full Name: %sAddress: %sDate of Birth: %sPlace of Birth: %sJob: %s",
            name, address, birth, birthPlace, job);

    fclose(file);
    setColor(2);
    typeWriter("Profile saved!");
    setColor(7);
}

// =========================
// Просмотр профилей
// =========================
void viewProfiles(const char *currentUser) {
    FILE *file = fopen("data/logins.txt", "r");
    if (!file) {
        setColor(4);
        typeWriter("No users found!");
        setColor(7);
        return;
    }

    setColor(6); 
    printf("╔════════════════════════╗\n");
    printf("║        User List       ║\n");
    printf("╚════════════════════════╝\n");
    setColor(7);

    char login[MAX];
    unsigned long hashVal;
    int index = 1;

    printf("0 - Your profile (%s)\n", currentUser);
    while (fscanf(file, "%s %lu", login, &hashVal) == 2) {
        if (strcmp(login, currentUser) != 0)
            printf("%d - %s\n", index++, login);
    }
    fclose(file);

    int choice;
    printf("Enter profile number: ");
    scanf("%d", &choice);

    if (choice == 0) {
        char filename[MAX];
        sprintf(filename, "data/profiles/%s.txt", currentUser);
        FILE *f = fopen(filename, "r");
        if (!f) {
            printf("Profile not found. Create it? (y/n): ");
            char ans;
            scanf(" %c", &ans);
            if (ans == 'y' || ans == 'Y')
                createOrUpdateProfile(currentUser);
            return;
        }

        setColor(9);
        typeWriter("\n=== Your Profile ===");
        setColor(7);

        char line[MAX];
        while (fgets(line, sizeof(line), f))
            printf("%s", line);
        fclose(f);

        printf("\nUpdate profile? (y/n): ");
        char ans;
        scanf(" %c", &ans);
        if (ans == 'y' || ans == 'Y')
            createOrUpdateProfile(currentUser);
        return;
    }

    // Просмотр чужого профиля
    file = fopen("data/logins.txt", "r");
    index = 1;
    char target[MAX] = "";
    while (fscanf(file, "%s %lu", login, &hashVal) == 2) {
        if (strcmp(login, currentUser) != 0) {
            if (index == choice) {
                strcpy(target, login);
                break;
            }
            index++;
        }
    }
    fclose(file);

    if (strlen(target) == 0) {
        setColor(4);
        typeWriter("User not found.");
        setColor(7);
        return;
    }

    char filename[MAX];
    sprintf(filename, "data/profiles/%s.txt", target);
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Profile of %s is not filled yet.\n", target);
        return;
    }

    setColor(9);
    printf("\n=== Profile of %s ===\n", target);
          printf("╔════════════════════════╗\n");
          printf("║     Profile of %s     ║\n", target);
          printf("╚════════════════════════╝\n");
    setColor(7);

    char line[MAX];
    while (fgets(line, sizeof(line), f))
        printf("%s", line);
    fclose(f);
}

// =========================
// Главная функция
// =========================
int main() {
    SetConsoleOutputCP(CP_UTF8);
    system("mkdir data >nul 2>&1");
    system("mkdir data\\profiles >nul 2>&1");

    printBanner();

    int mainChoice;
    char currentUser[MAX] = "";

    while (1) {
        setColor(6); // желтый
        printf("╔══════════════════════╗\n");
        printf("║       MAIN MENU      ║\n");
        printf("╚══════════════════════╝\n");
        setColor(7);
        printf("1 - Login\n2 - Register\n3 - Exit\nYour choice: ");
        scanf("%d", &mainChoice);

        if (mainChoice == 3) {
            setColor(2);
            typeWriter("Goodbye!");
            setColor(7);
            break;
        }

        if (mainChoice == 2) {
            registerUser();
            continue;
        }

        if (mainChoice == 1) {
            if (loginUser(currentUser)) {
                int subChoice;
                while (1) {
                    setColor(6);
                    printf("╔════════════════════════╗\n");
                    printf("║      USER MENU (%s)   ║\n",currentUser);
                    printf("╚════════════════════════╝\n");
                    setColor(7);
                    printf("1. Fill/Update Profile\n2. View Profiles\n3. Logout\nYour choice: ");
                    scanf("%d", &subChoice);

                    if (subChoice == 1)
                        createOrUpdateProfile(currentUser);
                    else if (subChoice == 2)
                        viewProfiles(currentUser);
                    else if (subChoice == 3) {
                        setColor(2);
                        printf("Logged out from %s.\n", currentUser);
                        setColor(7);
                        strcpy(currentUser, "");
                        break;
                    } else {
                        setColor(4);
                        printf("Invalid choice.\n");
                        setColor(7);
                    }
                }
            }
        }
    }

    return 0;
}
