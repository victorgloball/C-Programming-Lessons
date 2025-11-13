#include <stdio.h>
#include <time.h>

// =========================
// Сводим число к одной цифре (ведическая нумерология)
// =========================
int reduceToOneDigit(int n) {
    while (n > 9) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        n = sum;
    }
    return n;
}

// =========================
// Ведическая нумерология даты
// =========================
int numerologyDate(int day, int month, int year) {
    int dayNum   = reduceToOneDigit(day);
    int monthNum = reduceToOneDigit(month);
    int yearNum  = reduceToOneDigit(year / 100 + year % 100);
    int total    = reduceToOneDigit(dayNum + monthNum + yearNum);
    return total;
}

// =========================
// Соответствие планеты к ведическому числу
// =========================
const char* planetForNumber(int n) {
    switch (n) {
        case 1: return "Sun";
        case 2: return "Moon";
        case 3: return "Jupiter";
        case 4: return "Rahu";
        case 5: return "Mercury";
        case 6: return "Venus";
        case 7: return "Ketu";
        case 8: return "Saturn";
        case 9: return "Mars";
        default: return "Unknown";
    }
}

// =========================
// Проверка високосного года
// =========================
int isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// =========================
// Основная функция
// =========================
int main(void) {
    int birthDay, birthMonth, birthYear;
    printf("Enter your date of birth (dd mm yyyy): ");
    scanf("%d %d %d", &birthDay, &birthMonth, &birthYear);

    // Получаем сегодняшнюю дату
    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    int currentDay   = today.tm_mday;
    int currentMonth = today.tm_mon + 1;
    int currentYear  = today.tm_year + 1900;

    // =========================
    // Возраст
    // =========================
    int ageYears  = currentYear - birthYear;
    int ageMonths = currentMonth - birthMonth;
    int ageDays   = currentDay - birthDay;

    if (ageDays < 0) { ageMonths--; ageDays += 30; }
    if (ageMonths < 0) { ageYears--; ageMonths += 12; }

    int totalDays   = ageYears * 365 + ageMonths * 30 + ageDays;
    int totalWeeks  = totalDays / 7;
    int totalMonths = totalDays / 30;

    // =========================
    // Ведическая нумерология
    // =========================
    int vedicBirth = numerologyDate(birthDay, birthMonth, birthYear);
    int vedicToday = numerologyDate(currentDay, currentMonth, currentYear);

    // =========================
    // Приблизительная продолжительность жизни
    // =========================
    int lifeExpectancyYears  = 90;
    int lifeExpectancyDays   = lifeExpectancyYears * 365;
    int lifeExpectancyWeeks  = lifeExpectancyDays / 7;
    int lifeExpectancyMonths = lifeExpectancyDays / 30;

    // =========================
    // Вывод
    // =========================
    printf("\nYour age is: %d years, %d months, %d days\n", ageYears, ageMonths, ageDays);
    printf("Total: %d days, %d weeks, %d months\n", totalDays, totalWeeks, totalMonths);

     printf("\nApproximate life expectancy:\n");
    printf("%d days, %d weeks, %d months (assuming %d years)\n",
           lifeExpectancyDays, lifeExpectancyWeeks, lifeExpectancyMonths, lifeExpectancyYears);

    printf("\nVedic number of your birth date: %d (Planet: %s)\n", vedicBirth, planetForNumber(vedicBirth));
    printf("Vedic number of today's date: %d (Planet: %s)\n", vedicToday, planetForNumber(vedicToday));

    return 0;
}
