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

#include "keys.hpp"

/// Calculator's component base class.
class Calculator::Component {
  public:
    Component(int x, int y, int w, int h);
    void trigger();
    virtual void redisplay();
    virtual void undisplay();
    /// Get x value of the upper-left corner of component object.
    virtual int getX() { return x; };

    /// Get y value of the upper-left corner of component object.
    virtual int getY() { return y; };

    /// Get width of component object.
    virtual int getW() { return w; };

    /// Get height of component object.
    virtual int getH() { return h; };

    /// Update x value of the upper-left corner of component object.
    virtual void setX(int new_x) { x = new_x; };

    /// Update y value of the upper-left corner of component object.
    virtual void setY(int new_y) { y = new_y; };

    /// Update width of component object.
    virtual void setW(int new_w) { w = new_w; };

    /// Update height of component object.
    virtual void setH(int new_h) { h = new_h; };

    /// Get ncurses' WINDOW object's pointer.
    virtual ncurses::WINDOW* getWindow();

    virtual void select();
    virtual void unselect();
  protected:
    std::weak_ptr<Calculator> calculator;
    int x, y, w, h;
    ncurses::WINDOW *window;
};

/// Calculator's (maybe LCD) display component class.
class Calculator::DisplayComponent : public Component {
  public:
    DisplayComponent() :
        Component(0, 0, 0, 7) {
        ncurses::keypad(window, TRUE);
    };
    /// Get x value of the upper-left corner of component object.
    int getX() { return Component::getX(); };

    /// Get y value of the upper-left corner of component object.
    int getY() { return Component::getY(); };

    /// Get width of component object.
    int getW() { return Component::getW(); };

    /// Get height of component object.
    int getH() { return Component::getH(); };

    /// Update x value of the upper-left corner of component object.
    void setX(int new_x) { Component::setX(new_x); };

    /// Update y value of the upper-left corner of component object.
    void setY(int new_y) { Component::setY(new_y); };

    /// Update width of component object.
    void setW(int new_w) { Component::setW(new_w); };

    /// Update height of component object.
    void setH(int new_h) { Component::setH(new_h); };

    int waitInput();
    void redisplay();
    void undisplay();
    void select() { Component::select(); };
    void unselect() { Component::unselect(); };

    /// Get ncurses' WINDOW object's pointer.
    ncurses::WINDOW* getWindow();

    /// Clear equation buffer.
    void clearEquation();

    /// Get buffered equation.
    std::vector<std::string> getEquation() { return equation; }

    void pushBack(std::string s);
    void popBack();
    void setResult(std::string res) { result = res; }
    void clearResult() { result.clear(); }
    void pushBackPartialOpString(std::string s);
    void clearPartialOpString();
  private:
    const int cursor_pos_x_base{2};
    const int cursor_pos_y_base{2};
    int cursor_pos_x{2};
    int cursor_pos_y{2};
    std::vector<std::string> partial_op_string;
    std::vector<std::string> equation;
    std::string result;
};

/// Calculator's key button component class.
class Calculator::ButtonComponent : public Component {
  public:
    ButtonComponent(ButtonAttribute button_attribute) :
        Component(0, 0, BUTTON_W, BUTTON_H),
        button_attribute(button_attribute) {
    };

    /// Get x value of the upper-left corner of component object.
    int getX() { return Component::getX(); };

    /// Get y value of the upper-left corner of component object.
    int getY() { return Component::getY(); };

    /// Get width of component object.
    int getW() { return Component::getW(); };

    /// Get height of component object.
    int getH() { return Component::getH(); };

    /// Update x value of the upper-left corner of component object.
    void setX(int new_x) { Component::setX(new_x); };

    /// Update y value of the upper-left corner of component object.
    void setY(int new_y) { Component::setY(new_y); };

    /// Update width of component object.
    void setW(int new_w) { Component::setW(new_w); };

    /// Update height of component object.
    void setH(int new_h) { Component::setH(new_h); };

    void redisplay();
    void undisplay() { Component::undisplay(); };
    void select() { Component::select(); };
    void unselect() { redisplay(); };

    /// Get ncurses::WINDOW pointer of component object.
    ncurses::WINDOW* getWindow();
    const ButtonAttribute& getAttribute() {
        return button_attribute;
    };
  private:
    ButtonAttribute button_attribute;
};

/// Calculator's key helper display component class.
class Calculator::KeyHelpComponent : public Component {
  public:
    KeyHelpComponent(std::string desc) :
        Component(0, 0, KEY_HELP_W, KEY_HELP_H), desc(desc) {
    };
    KeyHelpComponent() : KeyHelpComponent("") {
    };
    int getX() { return Component::getX(); };
    int getY() { return Component::getY(); };
    int getW() { return Component::getW(); };
    int getH() { return Component::getH(); };
    void setX(int new_x) { Component::setX(new_x); };
    void setY(int new_y) { Component::setY(new_y); };
    void setW(int new_w) { Component::setW(new_w); };
    void setH(int new_h) { Component::setH(new_h); };
    void setDesc(std::string description) { desc = description; };
    void redisplay();
    void undisplay() { Component::undisplay(); };
    ncurses::WINDOW* getWindow();
  private:
    std::string desc;
};
