#include <cstdio>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <climits>
#include <regex>

//#include <ncurses.h>
#include "wrapped_ncurses.hpp"
#include "lib/exprtk/exprtk.hpp"

#include "calculator.hpp"
#include "calculator/keys.hpp"
#include "calculator/component.hpp"

void initcolor() {
    if (ncurses::has_colors() != FALSE) {
        ncurses::start_color();
    }
}

void print_aligned(ncurses::WINDOW* window, std::string label, Alignment align) {
    if (label.size() == 0) return;
    size_t margin{1};
    size_t w, h, label_x, label_y;
    if (window == NULL) window = ncurses::stdscr;
    getmaxyx(window, h, w);
    if (w < 3 ||
        w - 2 * margin < label.length() ||
        h < 3) return;

    // set x
    switch (align) {
    case ALIGN_UL:
    case ALIGN_CL:
    case ALIGN_LL:
        label_x = margin;
        break;
    case ALIGN_UC:
    case ALIGN_CC:
    case ALIGN_LC:
        label_x = (w - label.length())/2;
        break;
    case ALIGN_UR:
    case ALIGN_CR:
    case ALIGN_LR:
        label_x = w - 1 - margin - (label.length() - 1);
        break;
    default:
        break;
    }

    // set y
    switch (align) {
    case ALIGN_UL:
    case ALIGN_UC:
    case ALIGN_UR:
        label_y = margin;
        break;
    case ALIGN_CL:
    case ALIGN_CC:
    case ALIGN_CR:
        label_y = (h - 2 * margin + 1)/2;
        break;
    case ALIGN_LL:
    case ALIGN_LC:
    case ALIGN_LR:
        label_y = h - 1 - margin;
        break;
    default:
        break;
    }

    ncurses::mvwprintw(window, label_y, label_x, label.c_str());
    ncurses::wrefresh(window);
};

Calculator::Calculator(std::vector<ButtonAttribute> button_attributes) {
    ncurses::initscr();
    ncurses::cbreak();
    ncurses::keypad(ncurses::stdscr, TRUE);
    initcolor();

    // set up main display
    main_display = std::make_unique<DisplayComponent>();

    // set up key help though hidden
    key_help = std::make_unique<KeyHelpComponent>();

    // for each ComponentAttributes
    // setup Component and append it to "components"
    for (auto it = button_attributes.begin(); it != button_attributes.end(); it++){
        buttons.push_back(std::make_unique<ButtonComponent>(*it));
    }

    resize();
};

ncurses::WINDOW* Calculator::getMainDisplayWindow() {
    return main_display->getWindow();
};

int Calculator::waitInput() {
    return main_display->waitInput();
};

void Calculator::resize() {
    unselect_button();
    render(DEFAULT_SELECTED_BUTTON_IDX);
};

void Calculator::render(int idx) {
    selected_button_idx = idx;

    ncurses::endwin();
    ncurses::refresh();

    // reset outer_{w,h} appropriately
    getmaxyx(ncurses::stdscr, stdscr_h, stdscr_w);
    if (stdscr_w < MIN_OUTER_W ||
        stdscr_h < MIN_OUTER_H) {
        // too small to display!
        ;
    }
    outer.w = std::min(stdscr_w - 2 * MIN_OUTER_X, MAX_OUTER_W);
    outer.h = std::min(stdscr_h - 2 * MIN_OUTER_Y, MAX_OUTER_H);
    num_buttons_x = (outer.w - GAP_X_BTWN_BUTTONS) /
                    (BUTTON_W + GAP_X_BTWN_BUTTONS);
    num_buttons_y = (outer.h - 2 * GAP_Y_BTWN_BUTTONS - main_display->getH()) /
                    (BUTTON_W + GAP_X_BTWN_BUTTONS);
    outer.w = num_buttons_x * BUTTON_W + (num_buttons_x - 1) * GAP_X_BTWN_BUTTONS +
                    2 * INNER_MARGIN_X;
    outer.x = (stdscr_w - outer.w)/2;
    outer.h = num_buttons_y * BUTTON_H + num_buttons_y * GAP_Y_BTWN_BUTTONS +
                    main_display->getH() + 2 * INNER_MARGIN_Y;
    outer.y = (stdscr_h - outer.h)/2;

    // key help
    key_help->undisplay();
    key_help->setX((outer.w - key_help->getW()) / 2);
    key_help->setY((outer.h - key_help->getH()) / 2);

    // main display
    main_display->undisplay();
    main_display->setW(outer.w - 2 * INNER_MARGIN_X);
    main_display->setX(outer.x + INNER_MARGIN_X);
    main_display->setY(outer.y + INNER_MARGIN_Y);

    // keys
    int pos_x_cnt{0};
    int pos_y_cnt{0};

    for (auto it = buttons.begin(); it != buttons.end(); it++) {
        (*it)->undisplay();
    }

    auto it = buttons.begin();
    if (selected_button_idx != DEFAULT_SELECTED_BUTTON_IDX) {
        int adv = (selected_button_idx / (num_buttons_x * num_buttons_y)) *
            (num_buttons_x * num_buttons_y);
        std::advance(it, adv);
    }

    for (int n = 0; it != buttons.end() && n < (num_buttons_x * num_buttons_y); it++, n++) {
        int x = main_display->getX() +
                pos_x_cnt * (BUTTON_W + GAP_X_BTWN_BUTTONS);
        int y = main_display->getY() + main_display->getH() + GAP_Y_BTWN_BUTTONS +
                pos_y_cnt * (BUTTON_H + GAP_Y_BTWN_BUTTONS);
        (*it)->setX(x);
        (*it)->setY(y);
        (*it)->redisplay();

        bool reach_x_limit{false};
        bool reach_y_limit{false};
        if ((x + GAP_X_BTWN_BUTTONS + BUTTON_W + INNER_MARGIN_X) > (outer.x + outer.w)) {
            reach_x_limit = true;
        }
        if ((y + GAP_Y_BTWN_BUTTONS + BUTTON_H + INNER_MARGIN_Y) > (outer.y + outer.h)) {
            reach_y_limit = true;
        }
        if (reach_x_limit && reach_y_limit) {
            break;
        } else if (reach_x_limit) {
            pos_x_cnt = 0;
            pos_y_cnt++;
        } else {
            pos_x_cnt++;
        }
    }
    if (selected_button_idx != DEFAULT_SELECTED_BUTTON_IDX) {
        select_button(idx);
    }

    main_display->redisplay();
};

void Calculator::select_button(int idx) {
    if (idx != DEFAULT_SELECTED_BUTTON_IDX) buttons[idx]->select();
};

void Calculator::unselect_button(int idx) {
    if (idx != DEFAULT_SELECTED_BUTTON_IDX) buttons[idx]->unselect();
};

void Calculator::select_next() {
    if (selected_button_idx != DEFAULT_SELECTED_BUTTON_IDX) {
        unselect_button(selected_button_idx);
    }
    if (selected_button_idx == (int)(buttons.size() - 1)) {
        render(0);
    } else {
        render(selected_button_idx + 1);
    }
};

void Calculator::select_up() {
    if (selected_button_idx != DEFAULT_SELECTED_BUTTON_IDX) {
        unselect_button(selected_button_idx);
    }
    if (selected_button_idx - num_buttons_x >= 0) {
        int prev = selected_button_idx / (num_buttons_x * num_buttons_y);
        int next = (selected_button_idx - num_buttons_x) / (num_buttons_x * num_buttons_y);
        if (prev == next) {
            selected_button_idx -= num_buttons_x;
        }
    }
    render(selected_button_idx);
};

void Calculator::select_down() {
    if (selected_button_idx == DEFAULT_SELECTED_BUTTON_IDX) {
        selected_button_idx = 0;
    } else {
        unselect_button(selected_button_idx);
        if (selected_button_idx + num_buttons_x < (int)(buttons.size())) {
            int prev = selected_button_idx / (num_buttons_x * num_buttons_y);
            int next = (selected_button_idx + num_buttons_x) / (num_buttons_x * num_buttons_y);
            if (prev == next) {
                selected_button_idx += num_buttons_x;
            }
        }
    }
    render(selected_button_idx);
};

void Calculator::select_left() {
    if (selected_button_idx == DEFAULT_SELECTED_BUTTON_IDX) {
        return;
    } else if (selected_button_idx == 0) {
        unselect_button(selected_button_idx);
        selected_button_idx = buttons.size() - 1;
    } else if (selected_button_idx > 0) {
        unselect_button(selected_button_idx);
        selected_button_idx -= 1;
    }
    render(selected_button_idx);
};

void Calculator::select_right() {
    if (selected_button_idx == DEFAULT_SELECTED_BUTTON_IDX) {
        return;
    } else if (selected_button_idx == (int)(buttons.size() - 1)) {
        unselect_button(selected_button_idx);
        selected_button_idx = 0;
    } else if (selected_button_idx >= 0) {
        unselect_button(selected_button_idx);
        selected_button_idx += 1;
    }
    render(selected_button_idx);
};

void Calculator::key_enter() {
    if (selected_button_idx == DEFAULT_SELECTED_BUTTON_IDX) {
        // execute buffered equation
        std::string expression_string = joinStrVec(buffered_equation) + 
            joinStrVec(buffered_partial_op_string);
        double res = calculate<double>(expression_string);
        main_display->setResult(std::to_string(res));
        main_display->redisplay();
    } else {
        btn_t bt = buttons[selected_button_idx]->getAttribute().bt;
        unselect_button();
        push_button(bt);
    }
    resize();
};

void Calculator::showKeyHelp() {
    if (selected_button_idx != DEFAULT_SELECTED_BUTTON_IDX) {
        key_help->setDesc(
            buttons[selected_button_idx]->getAttribute().desc
        );
        key_help->setX((stdscr_w - key_help->getW()) / 2);
        key_help->setY((stdscr_h - key_help->getH()) / 2);
        key_help->redisplay();
    }
};

// TODO: refine
void Calculator::exec(int key) {
    btn_t bt{btn_t::num_btn_types};
    switch (key) {
    case KEY_BACKSPACE:
    case KEY_DC:
        bt = btn_t::btn_bck;
        push_button(bt);
        return;
    }

    std::string alpha = std::string(1, static_cast<char>(key));
    if (getPartialOpString().size() > 0) {
        std::string pending = getPartialOpString();
        try {
            std::regex e("^" + pending + alpha);
            pushBackPartialOpString(alpha);
            main_display->pushBackPartialOpString(alpha);
            pending += alpha;
            int match_count{0};
            std::string candidate_label;
            btn_t candidate_bt;
            for (auto it = buttons.begin(); it != buttons.end(); it++) {
                std::smatch m;
                candidate_label = (*it)->getAttribute().label;
                if (std::regex_search(candidate_label, m, e)) {
                    ++match_count;
                    candidate_bt = (*it)->getAttribute().bt;
                }
            }
            if (match_count == 1 && candidate_label == pending) {
                clearPartialOpString();
                main_display->clearPartialOpString();
                push_button(candidate_bt);
            }
            return;
        } catch (const std::regex_error& err) {
            bool match_exists{false};
            auto it = buttons.begin();
            for (; it != buttons.end(); it++) {
                if (pending == (*it)->getAttribute().label) {
                    match_exists = true;
                    break;
                }
            }
            if (match_exists) {
                clearPartialOpString();
                main_display->clearPartialOpString();
                push_button((*it)->getAttribute().bt);
            } else {
                pushBackPartialOpString(alpha);
                main_display->pushBackPartialOpString(alpha);
                return;
            }
        };
    }

    switch (key) {
    case '/': bt = btn_t::btn_div; break;
    case '*': bt = btn_t::btn_multi; break;
    case '-': bt = btn_t::btn_minus; break;
    case '+': bt = btn_t::btn_plus; break;
    case '9': bt = btn_t::btn_9; break;
    case '8': bt = btn_t::btn_8; break;
    case '7': bt = btn_t::btn_7; break;
    case '6': bt = btn_t::btn_6; break;
    case '5': bt = btn_t::btn_5; break;
    case '4': bt = btn_t::btn_4; break;
    case '3': bt = btn_t::btn_3; break;
    case '2': bt = btn_t::btn_2; break;
    case '1': bt = btn_t::btn_1; break;
    case '0': bt = btn_t::btn_0; break;
    case '(': bt = btn_t::btn_paren_open; break;
    case ')': bt = btn_t::btn_paren_close; break;
    case '{': bt = btn_t::btn_curl_open; break;
    case '}': bt = btn_t::btn_curl_close; break;
    case '[': bt = btn_t::btn_bracket_open; break;
    case ']': bt = btn_t::btn_bracket_close; break;
    case 'r': resize(); return;  /* hidden command... */
    case '?': showKeyHelp(); return;
    }
    if (bt != btn_t::num_btn_types) {
        push_button(bt);
    } else {
        pushBackPartialOpString(alpha);
        main_display->pushBackPartialOpString(alpha);
    }
};

const ButtonAttribute& Calculator::getButtonAttribute(btn_t bt) {
    for (auto it = buttons.begin(); it != buttons.end(); it++) {
        if ((*it)->getAttribute().bt == bt) {
            return (*it)->getAttribute();
        }
    }
    throw -1;
};

void Calculator::push_button(btn_t bt) {
    switch (bt) {
    case btn_t::btn_clr:
        main_display->clearEquation();
        buffered_equation.clear();
        buffered_partial_op_string.clear();
        break;
    case btn_t::btn_bck:
        main_display->popBack();
        popBack();
        break;
    default:
        auto attr = getButtonAttribute(bt);
        main_display->pushBack(attr.label);
        buffered_equation.push_back(attr.inner_rep);
    }
    main_display->redisplay();
};
