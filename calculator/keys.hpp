#pragma once

#include <string>
#include <vector>

/// btn_t identifies key button type.
typedef enum e_btn_t {
    btn_clr = 0,
    btn_bck,
    btn_div,
    btn_multi,
    btn_minus,
    btn_plus,
    btn_pow,
    btn_9,
    btn_8,
    btn_7,
    btn_6,
    btn_5,
    btn_4,
    btn_3,
    btn_2,
    btn_1,
    btn_0,
    btn_paren_open,
    btn_paren_close,
    btn_curl_open,
    btn_curl_close,
    btn_bracket_open,
    btn_bracket_close,
    btn_abs,
    btn_exp,
    btn_log,
    btn_log10,
    btn_log2,
    btn_logn,
    btn_root,
    btn_sqrt,
    btn_acos,
    btn_acosh,
    btn_asin,
    btn_asinh,
    btn_atan,
    btn_atanh,
    btn_atan2,
    btn_cos,
    btn_cosh,
    btn_cot,
    btn_csc,
    btn_sec,
    btn_sin,
    btn_sinc,
    btn_sinh,
    btn_tan,
    btn_tanh,
    num_btn_types
} btn_t;

/// btn_action_t IMMEDIATE triggers immediate action.
typedef enum e_btn_action_t {
    ACTION_BUFFER,
    ACTION_IMMEDIATE
} btn_action_t;

/// btn_loc_t FIXED indicates that the key is fixed even on pagination.
typedef enum e_btn_loc_t {
    LOCATION_FIXED,
    LOCATION_UNFIXED
} btn_loc_t;

class Calculator;

/// Key button attribute.
class ButtonAttribute {
  public:
    ButtonAttribute(btn_t bt, btn_action_t bat, btn_loc_t blt,
                    std::string label, std::string description,
                    std::string inner_rep, std::function<void(Calculator&)> action) :
                bt(bt), bat(bat), blt(blt), label(label),
                desc(description), inner_rep(inner_rep), action(action) {
    };
    const btn_t bt;
    const btn_action_t bat;
    const btn_loc_t blt;
    const std::string label;
    const std::string desc;
    const std::string inner_rep;
    const std::function<void(Calculator&)> action;
};

template<int bt>
void push_button(Calculator& calc) {};

/// Get default button settings.
std::vector<ButtonAttribute> getDefaultButtonAttributes() {
    return {
        {
           /* bt        */ btn_t::btn_clr,
           /* bat       */ btn_action_t::ACTION_IMMEDIATE,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "Clr",
           /* desc      */ "clear",
           /* inner_rep */ "",
           /* action    */ &push_button<btn_t::btn_clr>
        },
        {
           /* bt        */ btn_t::btn_bck,
           /* bat       */ btn_action_t::ACTION_IMMEDIATE,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "Bck",
           /* desc      */ "backspace",
           /* inner_rep */ "",
           /* action    */ &push_button<btn_t::btn_bck>
        },
        {
           /* bt        */ btn_t::btn_div,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "/",
           /* desc      */ "division",
           /* inner_rep */ "/",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_multi,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "x",
           /* desc      */ "multiplication",
           /* inner_rep */ "*",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_minus,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "-",
           /* desc      */ "minus",
           /* inner_rep */ "-",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_plus,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "+",
           /* desc      */ "plus",
           /* inner_rep */ "+",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_pow,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "^",
           /* desc      */ "power",
           /* inner_rep */ "^",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_9,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "9",
           /* desc      */ "9",
           /* inner_rep */ "9",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_8,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "8",
           /* desc      */ "8",
           /* inner_rep */ "8",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_7,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "7",
           /* desc      */ "7",
           /* inner_rep */ "7",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_6,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "6",
           /* desc      */ "6",
           /* inner_rep */ "6",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_5,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "5",
           /* desc      */ "5",
           /* inner_rep */ "5",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_4,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "4",
           /* desc      */ "4",
           /* inner_rep */ "4",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_3,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "3",
           /* desc      */ "3",
           /* inner_rep */ "3",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_2,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "2",
           /* desc      */ "2",
           /* inner_rep */ "2",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_1,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "1",
           /* desc      */ "1",
           /* inner_rep */ "1",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_0,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_FIXED,
           /* label     */ "0",
           /* desc      */ "0",
           /* inner_rep */ "0",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_paren_open,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "(",
           /* desc      */ "left parenthesis",
           /* inner_rep */ "(",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_paren_close,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ ")",
           /* desc      */ "right parenthesis",
           /* inner_rep */ ")",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_curl_open,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "{",
           /* desc      */ "left curly bracket",
           /* inner_rep */ "(",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_curl_close,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "}",
           /* desc      */ "right curly bracket",
           /* inner_rep */ ")",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_bracket_open,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "[",
           /* desc      */ "left bracket",
           /* inner_rep */ "(",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_bracket_close,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "]",
           /* desc      */ "right bracket",
           /* inner_rep */ ")",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_abs,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "abs",
           /* desc      */ "absolute value",
           /* inner_rep */ "abs",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_exp,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "exp",
           /* desc      */ "exp",
           /* inner_rep */ "exp",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_log,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "logE",
           /* desc      */ "log to base e",
           /* inner_rep */ "log",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_log10,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "log10",
           /* desc      */ "log to base 10",
           /* inner_rep */ "log10",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_log2,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "log2",
           /* desc      */ "log to base 2",
           /* inner_rep */ "log2",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_logn,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "logn",
           /* desc      */ "log to base n",
           /* inner_rep */ "logn",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_root,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "root",
           /* desc      */ "root",
           /* inner_rep */ "root",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_sqrt,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "sqrt",
           /* desc      */ "sqrt",
           /* inner_rep */ "sqrt",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_acos,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "acos_",
           /* desc      */ "arc cosine",
           /* inner_rep */ "acos",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_acosh,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "acosh",
           /* desc      */ "inv hyperbolic cos",
           /* inner_rep */ "acosh",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_asin,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "asin_",
           /* desc      */ "arc sine",
           /* inner_rep */ "asin",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_asinh,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "asinh",
           /* desc      */ "inv hyperbolic sine",
           /* inner_rep */ "asinh",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_atan,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "atan_",
           /* desc      */ "arc tangent",
           /* inner_rep */ "atan",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_atanh,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "atanh",
           /* desc      */ "inv hyperbolic tan",
           /* inner_rep */ "atanh",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_cos,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "cos_",
           /* desc      */ "cosine",
           /* inner_rep */ "cos",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_cosh,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "cosh",
           /* desc      */ "hyperbolic cosine",
           /* inner_rep */ "cosh",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_cot,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "cot",
           /* desc      */ "cotangent",
           /* inner_rep */ "cot",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_csc,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "csc",
           /* desc      */ "cosecant",
           /* inner_rep */ "csc",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_sec,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "sec",
           /* desc      */ "secant",
           /* inner_rep */ "sec",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_sin,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "sin_",
           /* desc      */ "sine",
           /* inner_rep */ "sin",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_sinc,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "sinc",
           /* desc      */ "sine cardinal",
           /* inner_rep */ "sinc",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_sinh,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "sinh",
           /* desc      */ "hyperbolic sine",
           /* inner_rep */ "sinh",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_tan,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "tan_",
           /* desc      */ "tangent",
           /* inner_rep */ "tan",
           /* action    */ nullptr
        },
        {
           /* bt        */ btn_t::btn_tanh,
           /* bat       */ btn_action_t::ACTION_BUFFER,
           /* blt       */ btn_loc_t::LOCATION_UNFIXED,
           /* label     */ "tanh",
           /* desc      */ "hyperbolic tangent",
           /* inner_rep */ "tanh",
           /* action    */ nullptr
        }
    };
};
