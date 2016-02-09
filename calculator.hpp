#pragma once

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
#include <ncurses.h>
#include "lib/exprtk/exprtk.hpp"

#include "calculator/keys.hpp"

namespace std {
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params) {
  return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
} // namespace std


class ButtonAttribute;

std::vector<ButtonAttribute> getDefaultButtonAttributes();

/// label alignment in its container.
enum Alignment {
    ALIGN_UL,
    ALIGN_UR,
    ALIGN_LL,
    ALIGN_LR,
    ALIGN_CL,
    ALIGN_CR,
    ALIGN_UC,
    ALIGN_LC,
    ALIGN_CC,
    NUM_ALIGNS
};

/// utility func to join std::string vec.
std::string joinStrVec(std::vector<std::string> svec) {
    std::ostringstream stream;
    std::copy(svec.begin(),
              svec.end(),
              std::ostream_iterator<std::string>(stream));
    return stream.str();
};

/// generic custom error.
enum class CustomError {
    ERR_NO_KEY,
    NUM_CUSTOM_ERRORS
};

/// the calculator itself.
class Calculator {
  public:
    class Component;
    class DisplayComponent;
    class ButtonComponent;
    class KeyHelpComponent;

    /// Default constructor constructs a calculator object with default settings.
    Calculator() : Calculator(getDefaultButtonAttributes()) {};

    /// You can also call with customised settings dynamically.
    Calculator(std::vector<ButtonAttribute> button_attributes);

    /// Get ncurses' WINDOW object of the main LCD screen.
    ncurses::WINDOW* getMainDisplayWindow();

    /// Select the next button to the one which is currently selected.
    void select_next();

    /// Select the previous button to the one which is currently selected.
    void select_prev();

    /// Select the button above to the one which is currently selected.
    void select_up();

    /// Select the button below to the one which is currently selected.
    void select_down();

    /// Select the button on the left side of the one which is currently selected.
    void select_left();

    /// Select the button on the right side of the one which is currently selected.
    void select_right();

    /// Handle enter key action which can happen at any time.
    void key_enter();

    /// Redisplay all the things when window resizing occurs.
    /// Any key selection will be cancelled on resizing.
    void resize();

    /// Calculator waits for input with this function call.
    int waitInput();

    /// Cancel any sort of key selection.
    void unselect_button() {
        unselect_button(selected_button_idx);
        selected_button_idx = -1;
    };

    /// Show help window about currently selected button.
    void showKeyHelp();

    /// Handles the raw decimal value representation of ascii input.
    void exec(int key);

    /// Get button attribute with btn_t bt.
    const ButtonAttribute& getButtonAttribute(btn_t bt);

    /// Save to the buffer the partial of multi-chars ops.
    void pushBackPartialOpString(std::string s) {
        buffered_partial_op_string.push_back(s);
    };

    /// Clear the buffer which save the partial inputs of multi-chars ops.
    void clearPartialOpString() {
        buffered_partial_op_string.clear();
    };

    /// Get current buffered partial string which may be part of some multi-char operation string.
    std::string getPartialOpString() {
        return joinStrVec(buffered_partial_op_string);
    };

    /// Pop back from partial op string buffer if any, otherwise from the buffer consisting of complete op strings.
    void popBack() {
        if (buffered_partial_op_string.size()) {
            buffered_partial_op_string.pop_back();
        } else if (buffered_equation.size()) {
            buffered_equation.pop_back();
        }
    };

    /// Evaluate input expression string as an mathematical expression.
    /// Completely depends on exprtk.
    template <typename T>
    T calculate(std::string expression_string) {
        //using symbol_table_t = exprtk::symbol_table<T>;
        using expression_t   = exprtk::expression<T>;
        using parser_t       = exprtk::parser<T>;
        expression_t expression;
        parser_t parser;
        parser.compile(expression_string, expression);
        return expression.value();
    };

  protected:
    /// All the buttons have the same width BUTTON_W.
    const static int BUTTON_W{7};

    /// All the buttons have the same height BUTTON_W.
    const static int BUTTON_H{5};

    /// Key help window always has the same width.
    const static int KEY_HELP_W{24};

    /// Key help window always has the same height.
    const static int KEY_HELP_H{9};

    /// Index -1 for buttons vector indicates that nothing is selected.
    const int DEFAULT_SELECTED_BUTTON_IDX{-1};

    /// Maximum calculator width.
    const int MAX_OUTER_W{100};

    /// Maximum calculator height.
    const int MAX_OUTER_H{INT_MAX};

    /// Minimum calculator x (of the upper-left corner).
    const int MIN_OUTER_X{1};

    /// Minimum calculator y (of the upper-left corner).
    const int MIN_OUTER_Y{1};

    /// Minimum calculator width.
    const int MIN_OUTER_W{40};

    /// Minimum calculator height.
    const int MIN_OUTER_H{30};

    /// Distance between two adjacent buttons on x-axis.
    const int GAP_X_BTWN_BUTTONS{2};

    /// Distance between two adjacent buttons on y-axis.
    const int GAP_Y_BTWN_BUTTONS{1};

    /// Distance between an outermost button and calculator frame on x-axis.
    const int INNER_MARGIN_X{GAP_X_BTWN_BUTTONS};

    /// Distance between an outermost button and calculator frame on y-axis.
    const int INNER_MARGIN_Y{GAP_Y_BTWN_BUTTONS};
  private:
    int selected_button_idx{DEFAULT_SELECTED_BUTTON_IDX};
    void select_button(int idx);
    void unselect_button(int idx);
    void exec_buffered_equation();
    struct PositionInfo {
        int x, y, w, h;
    };
    void render(int idx);

    PositionInfo outer {.x = 0, .y = 0, .w = 0, .h = 0};

    /// Main LCD display.
    std::unique_ptr<DisplayComponent> main_display;
    /// Key help window which is usually hidden.
    std::unique_ptr<KeyHelpComponent> key_help;
    /// All the key buttons stored in this one-dimentional vector.
    std::vector<std::unique_ptr<ButtonComponent>> buttons;

    int num_buttons_x;
    int num_buttons_y;
    int stdscr_w;
    int stdscr_h;

    std::vector<std::string> buffered_equation;
    std::vector<std::string> buffered_partial_op_string;

    void push_button(btn_t bt);
};
