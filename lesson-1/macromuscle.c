#include <stdio.h> // Подключаем стандартную библиотеку ввода/вывода (printf, scanf)
#include <stdlib.h> // Подключаем библиотеку для system(), exit() и других утилит

int main (void) {
	char again;  // Переменная для ответа пользователя на "хотите повторить?"
 	int exit_program = 0; // Флаг выхода из программы (0 — продолжаем, 1 — выходим)

	do { // Основной цикл программы — повторяется, пока exit_program не станет 1


		#ifdef _WIN32
        	system("cls"); // Очищаем экран для Windows
    	#else
        	system("clear");  // Очищаем экран для Linux/macOS
    	#endif
  		
  		int choice; // Переменная для выбора направления конверсии
		float value; // Переменная для ввода числа (см или дюймы)
        int valid_input; // Переменная для проверки корректности ввода
		
        // Цикл для безопасного выбора пункта меню
         do {
            printf("=== UNIT CONVERTER ===\n\n");
            printf("Choose conversion type:\n");
            printf("1. Centimeters to Inches\n");
            printf("2. Inches to Centimeters\n");
            printf("3. Exit program\n");
            printf("Enter 1, 2 or 3: ");

            // scanf("%d", &choice) считывает **целое число** из буфера ввода.
            // Возвращает количество успешно считанных элементов (1, если число, 0 если нет)
            valid_input = scanf("%d", &choice); 
            
            // Если пользователь ввёл не число или число не в диапазоне 1-3
			if (valid_input != 1 || (choice < 1 || choice > 3)) { 
               printf("Invalid choice! Please enter 1, 2 or 3.\n");

               // --- ОЧИСТКА БУФЕРА ---
                // Все символы, оставшиеся в буфере после неправильного ввода, убираем:
                // Enter ('\n') тоже удаляется
               while (getchar() != '\n');
            }
        } while (valid_input != 1 || (choice < 1 || choice > 3));        
         // повторяем, пока пользователь не введёт корректный пункт

        // Обработка выбора "3" — выход из программы
        if (choice == 3) { // если пользователь выбрал "Exit"
            exit_program = 1; // устанавливаем флаг выхода
            break; // выходим из do-while (основного цикла)
        }

        // --- ВВОД ЧИСЛА ---
        do {
            if (choice == 1)
                printf("Enter value in centimeters: "); // Запрос для см
            else
                printf("Enter value in inches: ");  // Запрос для дюймов
            
            // scanf("%f", &value) считывает float из буфера
            valid_input = scanf("%f", &value); 

            if (valid_input != 1) {     // если пользователь ввёл что-то не числовое
                printf("Invalid input! Please enter a numeric value.\n");
                while (getchar() != '\n');  // Очищаем буфер от мусора
            }  
        } while (valid_input != 1); // повторяем ввод, пока не число

		 // --- КОНВЕРТАЦИЯ ---
        if (choice == 1) { // см → дюймы
            float inches = value / 2.54; // вычисляем
            printf("\n%.2f cm = %.2f inches\n", value, inches); // выводим
        } else if (choice == 2) {  // дюймы → см
            float cm = value * 2.54;  // вычисляем
            printf("\n%.2f inches = %.2f cm\n", value, cm);
        }

        // Цикл для повторного запуска (возврат в главное меню)
        do {
            printf("\nDo you want to return to the main menu? (y/n): ");

            // Пробел перед %c очень важен:
            // он "съедает" любые пробельные символы (\n, пробелы) оставшиеся в буфере
            scanf(" %c", &again);
             // Очищаем буфер от лишних символов, если пользователь случайно ввёл больше одного
            

            while (getchar() != '\n');  
            // повторяем, пока пользователь не введёт корректный символ

            // если пользователь не хочет возвращаться в меню — выходим
            if (again != 'y' && again != 'Y' && again != 'n' && again != 'N') {
                printf("Invalid input! Please type 'y' or 'n'.\n"); // если ввели что-то другое
            }
        } while (again != 'y' && again != 'Y' && again != 'n' && again != 'N'); // повторяем, пока не y/n

        if (again == 'n' || again == 'N') { // если пользователь не хочет возвращаться в меню
            exit_program = 1; // устанавливаем флаг выхода
        }

    	} while (!exit_program);  // основной цикл продолжается, пока exit_program == 0

    // Очистка экрана перед выходом
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("\nGoodbye, engineer!\n"); // прощальное сообщение
    return 0;  // возвращаем 0 — успешное завершение программы
}