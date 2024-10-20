#include <stdio.h>
#include <conio.h>  // Para usar kbhit() e getch() no Windows
#include <time.h>   // Para medir o tempo

void delay_ms(int milliseconds) {
    clock_t start_time = clock();  // Marca o tempo de início
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

//#define TIMEOUT 1  // Timeout de 1 segundo
#define TIMEOUT 1

int main() {
    int tecla;
    clock_t start_time, end_time;
    double elapsed_time;
    int is_key_held = 0;

    printf("Pressione qualquer tecla. Mantenha por mais de 1 segundo para ver a mensagem de tempo esgotado.\n");

    while (1) {
        if (kbhit()) {  // Verifica se uma tecla foi pressionada
            if (!is_key_held) {  // Se a tecla acabou de ser pressionada
                start_time = clock();  // Marca o tempo de início da tecla pressionada
                tecla = getch();  // Captura a tecla pressionada
                printf("Tecla pressionada: %c\n", tecla);
                is_key_held = 1;  // Marca que a tecla está sendo mantida
            } 
            else {  // Se a tecla ainda está sendo mantida
                end_time = clock();  // Marca o tempo atual
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                // Verifica se a tecla foi mantida por mais de 1 segundo
                if (elapsed_time > TIMEOUT) {
                    printf("Tempo esgotado!!!!!Tecla pressionada além do tempo!!!!\n");
                    is_key_held = 0;  // Reseta o estado da tecla
                    break;
                }
            }
        } 
        else {
            is_key_held = 0;  // Reseta o estado da tecla se nenhuma estiver pressionada
        }

        delay_ms(100);  // Pequeno atraso para evitar uso excessivo de CPU
    }

    return 0;
}
