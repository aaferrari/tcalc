#include <cstdio>
#include <string>
#include <iostream>
#include <memory>
#include <array>
#include <signal.h>
#include <functional>
#include "wrapped_ncurses.hpp"
#include "calculator.cpp"
#include "calculator/component.cpp"

/// \mainpage
///
/// TCalc is a simple teminal calculator inspired by https://www.youtube.com/watch?v=spOSTDW1Nes .

static Calculator calculator;

int main() {
    // on window resize event, handle it on global static calculator
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = [](int sig){ calculator.resize(); };
    sigaction(SIGWINCH, &sa, NULL);

    int ch;
    while ((ch = calculator.waitInput()) != KEY_F(1)) {
        switch (ch) {
        case KEY_ENTER:
        case 10:         /* Enter */
            calculator.key_enter();
            break;
        case 27:         /* ESCAPE */
            calculator.key_escape();
            break;
        case 9:          /* Tab */
            calculator.select_next();
            break;
        case KEY_UP:     /* UP */
            calculator.select_up();
            break;
        case KEY_DOWN:   /* DOWN */
            calculator.select_down();
            break;
        case KEY_LEFT:   /* LEFT */
            calculator.select_left();
            break;
        case KEY_RIGHT:  /* RIGHT */
            calculator.select_right();
            break;
        default:
            calculator.exec(ch);
            break;
        }
    }
    ncurses::endwin();
    return 0;
}
