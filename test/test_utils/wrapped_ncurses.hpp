// wrapped_ncurses.hpp
#include <memory>
#ifndef WRAPPED_NCURSES_HPP
#define WRAPPED_NCURSES_HPP
//#ifdef TEST
namespace ncurses {
    int custom_stdscr_w{100};
    int custom_stdscr_h{100};
    struct PositionInfo {
        int x;
        int y;
    };
    using record_t = std::pair<PositionInfo, std::string>;
    struct WINDOW {
        WINDOW(int h, int w, int y, int x) :
                _maxy(h), _maxx(w), y(y), x(x) {};
        WINDOW() : WINDOW(custom_stdscr_h, custom_stdscr_w, 0, 0) {};
        void refresh() {
            histories.clear();
        };
        std::vector<record_t> histories;
        int _maxx;
        int _maxy;
        int x, y;
    };
    WINDOW* stdscr;
    void cbreak() {};
    void endwin() {};
    bool has_colors() { return true; };
    void start_color() {};
    std::vector<std::shared_ptr<WINDOW>> trash;
    int init_pair(short pair, short f, short b) {
        return 1;
    };
    void initscr() {
        trash.clear();
        std::shared_ptr<WINDOW> w(new WINDOW);
        trash.push_back(w);
        stdscr = w.get();
    };
    void keypad(WINDOW* w, bool) {};
    void mvwprintw(WINDOW* w, int y, int x, std::string label) {
        PositionInfo p{x, y};
        record_t r(p, label);
        (*w).histories.push_back(r);
    };
    WINDOW* newwin(int h, int w, int y, int x) {
        std::shared_ptr<WINDOW> win(new WINDOW(h, w, y, x));
        trash.push_back(win);
        return win.get();
    };
    void refresh() {};
    enum ACSS {
        ACS_ULCORNER,
        ACS_LLCORNER,
        ACS_URCORNER,
        ACS_LRCORNER,
        ACS_HLINE,
        ACS_VLINE
    };
    void wborder(WINDOW* w, ...) {};
    void wrefresh(WINDOW* w) {};
    int getmaxx(const WINDOW* w) {
        return w->_maxx;
    };
    int getmaxy(const WINDOW* w) {
        return w->_maxy;
    };
    int wgetch(WINDOW* w) {
        return 1;
    };
    void delwin(WINDOW* w) {
    };
    int wbkgd(WINDOW* win, int chtype) {
        return 1;
    };
}
//#endif
#endif
