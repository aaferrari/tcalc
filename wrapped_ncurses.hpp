// wrapped_ncurses.hpp
#ifndef WRAPPED_NCURSES_HPP
#define WRAPPED_NCURSES_HPP
#include <ncurses.h>
#ifndef TEST

/*!
 *  \addtogroup ncurses
 *  @{
 */
/// ncurses namespace (to cope with without-cxx-binding situation with minimum effort).
namespace ncurses {
    using ::cbreak;
    using ::delwin;
    using ::endwin;
    using ::getmaxx;
    using ::getmaxy;
    using ::has_colors;
    using ::init_pair;
    using ::initscr;
    using ::keypad;
    using ::mvwprintw;
    using ::newwin;
    using ::refresh;
    using ::start_color;
    using ::stdscr;
    using ::WINDOW;
    using ::wborder;
    using ::wrefresh;
} // namespace ncurses
/*! @} end of ncurses group */

#endif
#endif
