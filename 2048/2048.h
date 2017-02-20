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
class number_of_block                  //number_of_block�����ڽ�����Ϸ�߼�����
{
private:
	int array[4][4];                   //����Ԫ�ر�ʾ�����е�����
	void set_to_right();               //�����з����������ұ�
	void move_right();                 //�û��������Ƽ�ʱ���м��㲢�����з����������ұ�
	void set_to_left();                //�����з������������
	void move_left();                  //�û��������Ƽ�ʱ���м��㲢�����з������������
	void set_to_down();                //�����з����������±�
	void move_down();                  //�û��������Ƽ�ʱ���м��㲢�����з����������±�
	void set_to_up();                  //�����з����������ϱ�
	void move_up();                    //�û��������Ƽ�ʱ���м��㲢�����з����������±�
	void save();                       //�浵
	void back_save();
	void back_load();
	void load();                       //����
	void check();                      //���ڼ����Ϸ��Ӯ    
	void random_number();              //�����ƶ��������������
	void score(int);
public:
	int score_now = 0;
	int highest_score;
	char *poniter_to_score_now;
	char *poniter_to_highest_score;
	char buffer1[10];
	char buffer2[10];
	number_of_block();                 //���캯��
	void set_array();                  //��ʼ������
	void show_array();                 //�������ĺ��������ڶ��߼�������е���
	void play(char);                   //�����û����µĲ�ͬ�������ò�ͬ�ĺ���
	int* return_array();               //���߼��ദ��õ��Ľ��������GUI��
};

class block
{
private:
	Fl_Double_Window* win = new Fl_Double_Window(100, 50, 1280, 720, "2048");           //����һ������
	Fl_Output* one = new Fl_Output(600, 50, 100, 100, "Score");
	Fl_Output* two = new Fl_Output(600, 160, 100, 100, "Highest Score");
	Fl_Box* pointer_to_block[4][4];                                                     //����һ��ָ���������ڶԷ�������ݼ���ɫ�����޸�
	Fl_Box* scoreboard = new Fl_Box(600, 50, 100, 100, "");
	Fl_Box* record = new Fl_Box(600, 160, 100, 100, "");
	Fl_Button* upbutton = new Fl_Button(170, 440, 90, 90, "up");                        //���Ƽ�
	Fl_Button* downbutton = new Fl_Button(170, 540, 90, 90, "down");                    //���Ƽ�
	Fl_Button* leftbutton = new Fl_Button(70, 540, 90, 90, "left");                     //���Ƽ�
	Fl_Button* rightbutton = new Fl_Button(270, 540, 90, 90, "right");                  //���Ƽ�
	Fl_Button* quitbutton = new Fl_Button(1000, 50, 200, 50, "quit");                  //�˳���
	Fl_Button* resetbutton = new Fl_Button(1000, 110, 200, 50, "reset");                //�������а���
	Fl_Button* savebutton = new Fl_Button(1000, 170, 200, 50, "save");                //�浵����
	Fl_Button* loadbutton = new Fl_Button(1000, 230, 200, 50, "load");                //�������а���
	Fl_Button* backbutton = new Fl_Button(1000, 290, 200, 50, "back a step");                //������һ�����а���
	static void upward_pressed(Fl_Widget* w, void* data);                               //���Ƽ���Ӧ�ص�����
	static void downward_pressed(Fl_Widget* w, void* data);                             //���Ƽ���Ӧ�ص�����
	static void left_pressed(Fl_Widget* w, void* data);                                 //���Ƽ���Ӧ�ص�����
	static void right_pressed(Fl_Widget* w, void* data);                                //���Ƽ���Ӧ�ص�����
	static void quit_pressed(Fl_Widget* w, void* data);                                 //�˳�����Ӧ�ص�����
	static void reset_pressed(Fl_Widget* w, void* data);                                //�������м���Ӧ�ص�����
	static void save_pressed(Fl_Widget* w, void* data);                                //�浵����Ӧ�ص�����
	static void load_pressed(Fl_Widget* w, void* data);                                //��������Ӧ�ص�����
	static void back_pressed(Fl_Widget* w, void* data);                                //������һ������Ӧ�ص�����
	void up();                                                                          //���¾�Ϊ���캯��ֱ�ӵ��õĺ���
	void down();
	void left();
	void right();
	void quit();
	void reset();
	void save();
	void load();
	void back();
	void initialize();                                                                  //��ʼ������
	void end();                                                                         //�˳���Ϸ
	void set_number_and_color();                                                        //���÷������ɫ������
public:
	block();
};