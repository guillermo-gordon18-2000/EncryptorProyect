#include "password_prompt.hpp"

void hidePasswordInput(WINDOW *menu_win, unsigned char* key, unsigned char* iv) {
      werase(menu_win);  // Limpiar toda la ventana
      box(menu_win, 0, 0);  // Volver a dibujar el borde

  termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    termios tty_old = tty;
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    string password;
    char ch;
    int x = 2; // Posición de inicio para la contraseña en la ventana
    int y = 13; // Línea en la ventana para la entrada de la contraseña
    
    mvwprintw(menu_win, y, x, "Introduce la contraseña: "); // Verde
    wrefresh(menu_win);

    while (true) {
        ch = wgetch(menu_win);
        if (ch == '\n' || ch == '\r') {
            break;
        } else if (ch == 127 || ch == '\b') {  // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                mvwprintw(menu_win, y, x + password.size() + 27, " "); // Borrar el último asterisco
                mvwprintw(menu_win, y, x + password.size() + 27, "\b \b"); // Mover el cursor hacia atrás
                wrefresh(menu_win);
            }
        } else {
            password.push_back(ch);
            mvwprintw(menu_win, y, x + password.size() + 26, "*"); // Mostrar asterisco
            wrefresh(menu_win);
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &tty_old);

    deriveKeyAndIV(password, key, iv);
}

