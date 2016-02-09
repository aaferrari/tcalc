#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <iterator>
#include <vector>
#include <climits>
#include <cstring>
#include <algorithm>

//#include <ncurses.h>
#include "../wrapped_ncurses.hpp"
#include "../calculator.hpp"

/*
 * class Calculator::Component
 */
Calculator::Component::Component(int x, int y, int w, int h) :
    x(x), y(y), w(w), h(h) {
    redisplay();
};

void Calculator::Component::redisplay() {
    ncurses::delwin(window);
    window = ncurses::newwin(h, w, y, x);
    ncurses::wborder(window, 0, 0, 0, 0, 0, 0, 0, 0);
    ncurses::wrefresh(window);
};

void Calculator::Component::undisplay() {
    ncurses::delwin(window);
    window = ncurses::newwin(h, w, y, x);
    ncurses::wrefresh(window);
};

ncurses::WINDOW* Calculator::Component::getWindow() {
    return window;
};

void Calculator::Component::select() {
    ncurses::init_pair(1, COLOR_RED, COLOR_BLACK);
    wbkgd(window, COLOR_PAIR(1));
    ncurses::wrefresh(window);
    //wattroff(window, COLOR_PAIR(1));
};

void Calculator::Component::unselect() {
    redisplay();
};

/*
 * class Calculator::DisplayComponent : public Component
 */
void Calculator::DisplayComponent::undisplay() {
    Component::undisplay(); ncurses::keypad(window, TRUE);
};

ncurses::WINDOW* Calculator::DisplayComponent::getWindow() {
    return Component::getWindow();
};

void Calculator::DisplayComponent::clearEquation() {
    partial_op_string.clear();
    equation.clear();
}

void Calculator::DisplayComponent::pushBack(std::string s) {
    equation.push_back(s);
    ++cursor_pos_x;
};

void Calculator::DisplayComponent::popBack() {
    if (partial_op_string.size()) {
        partial_op_string.pop_back();
    } else if (equation.size()) {
        equation.pop_back();
    } else {
        return;
    }
    --cursor_pos_x;
};

void Calculator::DisplayComponent::pushBackPartialOpString(std::string s) {
    partial_op_string.push_back(s);
    ++cursor_pos_x;
};

void Calculator::DisplayComponent::clearPartialOpString() {
    partial_op_string.clear();
}

int Calculator::DisplayComponent::waitInput() {
    std::string prompt = joinStrVec(equation) +
            joinStrVec(partial_op_string);
    ncurses::mvwprintw(window, cursor_pos_y_base, cursor_pos_x_base,
              prompt.c_str());
    return wgetch(window);
};

void Calculator::DisplayComponent::redisplay() {
    Component::redisplay();
    ncurses::keypad(getWindow(), TRUE);
    print_aligned(getWindow(), result, ALIGN_LR);
};


/*
 * class Calculator::ButtonComponent : public Component
 */
ncurses::WINDOW* Calculator::ButtonComponent::getWindow() {
    return Component::getWindow();
};

void Calculator::ButtonComponent::redisplay() {
    Component::redisplay();
    print_aligned(getWindow(), getAttribute().label, ALIGN_CC);
};

/*
 * class Calculator::KeyHelpComponent : public Component
 */
ncurses::WINDOW* Calculator::KeyHelpComponent::getWindow() {
    return Component::getWindow();
};
void Calculator::KeyHelpComponent::redisplay() {
    Component::redisplay();
    print_aligned(getWindow(), desc, ALIGN_CC);
    ncurses::delwin(Component::getWindow());
};
