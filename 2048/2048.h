#include <iostream>
#include <fstream>
//#include <algorithm>
//#include "Simple_window.h"
//#include "GUI.h"
//#include "Point.h"
#include "Window.h"
//#include "Graph.h"
#include <ctime>
#include <FL/FL_Box.H>
#include <FL/FL_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H> 
//using namespace Graph_lib;
using namespace std;
inline void keep_window_open(){ char ch; cin >> ch; }
char* change(int num, char*str, int radix);
class number_of_block                  //number_of_block类用于进行游戏逻辑处理
{
private:
	int array[4][4];                   //数组元素表示棋盘中的数字
	void set_to_right();               //将所有方格移至最右边
	void move_right();                 //用户按下右移键时进行计算并将所有方格移至最右边
	void set_to_left();                //将所有方格移至最左边
	void move_left();                  //用户按下左移键时进行计算并将所有方格移至最左边
	void set_to_down();                //将所有方格移至最下边
	void move_down();                  //用户按下下移键时进行计算并将所有方格移至最下边
	void set_to_up();                  //将所有方格移至最上边
	void move_up();                    //用户按下上移键时进行计算并将所有方格移至最下边
	void save();                       //存档
	void back_save();
	void back_load();
	void load();                       //读档
	void check();                      //用于检查游戏输赢    
	void random_number();              //用于移动方格后产生随机数
	void score(int);
public:
	int score_now = 0;
	int highest_score;
	char *poniter_to_score_now;
	char *poniter_to_highest_score;
	char buffer1[10];
	char buffer2[10];
	number_of_block();                 //构造函数
	void set_array();                  //初始化棋盘
	void show_array();                 //输出数组的函数，用于对逻辑处理进行调试
	void play(char);                   //根据用户按下的不同按键调用不同的函数
	int* return_array();               //将逻辑类处理得到的结果反馈给GUI类
};

class block
{
private:
	Fl_Double_Window* win = new Fl_Double_Window(100, 50, 1280, 720, "2048");           //创建一个窗口
	Fl_Output* one = new Fl_Output(600, 50, 100, 100, "Score");
	Fl_Output* two = new Fl_Output(600, 160, 100, 100, "Highest Score");
	Fl_Box* pointer_to_block[4][4];                                                     //创建一个指针数组用于对方格的内容及颜色进行修改
	Fl_Box* scoreboard = new Fl_Box(600, 50, 100, 100, "");
	Fl_Box* record = new Fl_Box(600, 160, 100, 100, "");
	Fl_Button* upbutton = new Fl_Button(170, 440, 90, 90, "up");                        //上移键
	Fl_Button* downbutton = new Fl_Button(170, 540, 90, 90, "down");                    //下移键
	Fl_Button* leftbutton = new Fl_Button(70, 540, 90, 90, "left");                     //左移键
	Fl_Button* rightbutton = new Fl_Button(270, 540, 90, 90, "right");                  //右移键
	Fl_Button* quitbutton = new Fl_Button(1000, 50, 200, 50, "quit");                  //退出键
	Fl_Button* resetbutton = new Fl_Button(1000, 110, 200, 50, "reset");                //重新排列按键
	Fl_Button* savebutton = new Fl_Button(1000, 170, 200, 50, "save");                //存档按键
	Fl_Button* loadbutton = new Fl_Button(1000, 230, 200, 50, "load");                //读档排列按键
	Fl_Button* backbutton = new Fl_Button(1000, 290, 200, 50, "back a step");                //返回上一步排列按键
	static void upward_pressed(Fl_Widget* w, void* data);                               //上移键对应回调函数
	static void downward_pressed(Fl_Widget* w, void* data);                             //下移键对应回调函数
	static void left_pressed(Fl_Widget* w, void* data);                                 //左移键对应回调函数
	static void right_pressed(Fl_Widget* w, void* data);                                //右移键对应回调函数
	static void quit_pressed(Fl_Widget* w, void* data);                                 //退出键对应回调函数
	static void reset_pressed(Fl_Widget* w, void* data);                                //重新排列键对应回调函数
	static void save_pressed(Fl_Widget* w, void* data);                                //存档键对应回调函数
	static void load_pressed(Fl_Widget* w, void* data);                                //读档键对应回调函数
	static void back_pressed(Fl_Widget* w, void* data);                                //返回上一步键对应回调函数
	void up();                                                                          //以下均为构造函数直接调用的函数
	void down();
	void left();
	void right();
	void quit();
	void reset();
	void save();
	void load();
	void back();
	void initialize();                                                                  //初始化棋盘
	void end();                                                                         //退出游戏
	void set_number_and_color();                                                        //设置方格的颜色与数字
public:
	block();
};