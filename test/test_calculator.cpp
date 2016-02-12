#include "gtest/gtest.h"
#include "test_utils/wrapped_ncurses.hpp"
#include "calculator.cpp"
#include "calculator/component.cpp"

class CalculatorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {};
  Calculator c;
};

TEST_F(CalculatorTest, Calculation) {
    EXPECT_EQ(c.calculate<double>("3*(4+5)"), 27);
    EXPECT_EQ(c.calculate<double>("3*logn(30,2)/log2(30)"), 3);
    EXPECT_EQ(c.calculate<double>("acosh(exp(2)-sinh(2))"), 2);
    EXPECT_EQ(c.calculate<double>("cos(0)+log(exp(1))"), 2);
};

TEST_F(CalculatorTest, PrintAlignedOnMainDisplayCC) {
    ncurses::stdscr->_maxx = 59;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 60);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_CC);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 24);

    ncurses::stdscr->_maxx = 60;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 60);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_CC);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 24);

    ncurses::stdscr->_maxx = 61;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 62);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_CC);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 24);

    ncurses::stdscr->_maxx = 62;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 62);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_CC);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 24);
};

TEST_F(CalculatorTest, PrintAlignedOnMainDisplayUL) {
    ncurses::stdscr->_maxx = 59;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 60);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_UL);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 1);

    ncurses::stdscr->_maxx = 60;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 60);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_UL);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 1);

    ncurses::stdscr->_maxx = 61;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 62);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_UL);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 1);

    ncurses::stdscr->_maxx = 62;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 62);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_UL);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 1);
};

TEST_F(CalculatorTest, PrintAlignedOnMainDisplayUR) {
    ncurses::stdscr->_maxx = 59;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 60);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_UR);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 48);

    ncurses::stdscr->_maxx = 60;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 60);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_UR);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 48);

    ncurses::stdscr->_maxx = 61;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 62);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_UR);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 48);

    ncurses::stdscr->_maxx = 62;
    c.resize();
    EXPECT_EQ(c.getMainDisplayWindow()->x * 2 + c.getMainDisplayWindow()->_maxx, 62);
    print_aligned(c.getMainDisplayWindow(), "test", ALIGN_UR);
    EXPECT_EQ(c.getMainDisplayWindow()->histories[0].first.x, 48);
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
