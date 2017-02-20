#include "2048.h"
number_of_block start;

char* change(int num, char*str, int radix)
{
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum;
	int i = 0, j, k;
	if (radix == 10 && num<0)
	{
		unum = (unsigned)-num;
		str[i++] = '-';
	}
	else unum = (unsigned)num;
	do{
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
	} while (unum);
	str[i] = '\0';
	if (str[0] == '-')k = 1;
	else k = 0;
	char temp;
	for (j = k; j <= (i - 1) / 2; j++)
	{
		temp = str[j];
		str[j] = str[i - 1 + k - j];
		str[i - 1 + k - j] = temp;
	}
	return str;

}


number_of_block::number_of_block()
{
	set_array();
	ifstream file("highest_score.txt");
	file >> highest_score;
	poniter_to_score_now = change(score_now, buffer1, 10);
	poniter_to_highest_score = change(highest_score, buffer2, 10);
	file.close();

}

void number_of_block::set_array()                //先将棋盘置零，再随机选取两个位置产生2
{
	int i, j, m, n, p, q;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			array[i][j] = 0;
	srand(time(NULL));
	m = rand() * 4 / (RAND_MAX + 1);
	n = rand() * 4 / (RAND_MAX + 1);
	p = rand() * 4 / (RAND_MAX + 1);
	q = rand() * 4 / (RAND_MAX + 1);
	array[m][n] = 2;
	array[p][q] = 2;
}


void number_of_block::random_number()          //方格移动后在空位处产生2或者4
{
	int m, n, random_number;
	//srand(time(NULL));
	do{
		m = rand() * 4 / (RAND_MAX + 1);
		n = rand() * 4 / (RAND_MAX + 1);
	} while (array[m][n] != 0);
	array[m][n] = ((rand() * 2 / (RAND_MAX + 1)) + 1) * 2;
}


void number_of_block::show_array()            //输出数组
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
			cout << array[i][j];
		cout << endl;
	}

}


void number_of_block::play(char move)         //不同按键调用不同函数
{
	//char move;
	//while (true)
	{
		switch (move)
		{
			case 'w': move_up(); break;
			case 'a': move_left(); break;
			case 's': move_down(); break;
		    case 'd': move_right(); break;
			case 'o': save(); break;
			case 'm': back_save(); break;
			case 'n': back_load(); break;
			case 'i': load(); break;
		}
		show_array();
	}
}


void number_of_block::save()
{
	int i,j;
	ofstream savefile("save.txt");
	for (i = 0; i < 4;i++)
		for (j = 0; j < 4; j++)
		{
			savefile << array[i][j] << ' ';
		}
	savefile.close();
}

void number_of_block::back_save()
{
	int i, j;
	ofstream savefile("buffer.txt");
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			savefile << array[i][j] << ' ';
		}
	savefile.close();
}


void number_of_block::load()         
{
	int i, j;
	ifstream savefile("save.txt");
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			savefile >> array[i][j];
		}
	savefile.close();
}


void number_of_block::back_load()
{
	int i, j;
	ifstream savefile("buffer.txt");
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			savefile >> array[i][j];
		}
	savefile.close();
}


void number_of_block::set_to_right()
{
	int i, j, k, l, start, end;
	bool flag, flag2;
	for (l = 0; l < 4; l++)
	{
		start = 0;
		end = 0;
		while (end < 3)
		{
			flag = false;
			for (i = 0; i < 4; i++)
			{
				if (array[l][i] != 0)
				{
					start = i;
					for (j = i; j < 4; j++)
					{
						if (array[l][j] == 0)
							break;
						else end = j;
						flag = true;
					}

				}
				if (flag || (end == 3))
					break;
				start++;
				end++;
			}
			//cout << start <<  end << endl;
			if (end < 3)
			{
				for (k = end; k >= start; k--)
				{
					array[l][k + 1] = array[l][k];
					array[l][k] = 0;
					//show_array();
				}
			}
		}
	}
}


void number_of_block::move_right()
{
	int i, j, k, l, start, end;
	set_to_right();
	for (l = 0; l < 4; l++)
	{
		for (i = 3; i > 0; i--)
		{
			if (array[l][i] == array[l][i - 1])
			{
				array[l][i] += array[l][i - 1];
				array[l][i - 1] = 0;
				score(array[l][i]);
			}
		}
	}
	set_to_right();
	random_number();
}


void number_of_block::set_to_left()
{
	int i, j, k, l, start, end;
	bool flag, flag2;
	for (l = 0; l < 4; l++)
	{
		start = 3;
		end = 3;
		while (end > 0)
		{
			flag = false;
			for (i = 3; i > -1; i--)
			{
				if (array[l][i] != 0)
				{
					start = i;
					for (j = i; j > -1; j--)
					{
						if (array[l][j] == 0)
							break;
						else end = j;
						flag = true;
					}

				}
				if (flag || (end == 0))
					break;
				start--;
				end--;
			}
			if (end > 0)
			{
				for (k = end; k <= start; k++)
				{
					array[l][k - 1] = array[l][k];
					array[l][k] = 0;
				}
			}
		}
	}
}


void number_of_block::move_left()
{
	int i, j, k, l, start, end;
	set_to_left();
	for (l = 0; l < 4; l++)
	{
		for (i = 0; i < 3; i++)
		{
			if (array[l][i] == array[l][i + 1])
			{
				array[l][i] += array[l][i + 1];
				array[l][i + 1] = 0;
				score(array[l][i]);
			}
		}
	}
	set_to_left();
	random_number();
}


void number_of_block::set_to_down()
{
	int i, j, k, l, start, end;
	bool flag, flag2;
	for (l = 0; l < 4; l++)
	{
		start = 0;
		end = 0;
		while (end < 3)
		{
			flag = false;
			for (i = 0; i < 4; i++)
			{
				if (array[i][l] != 0)
				{
					start = i;
					for (j = i; j < 4; j++)
					{
						if (array[j][l] == 0)
							break;
						else end = j;
						flag = true;
					}

				}
				if (flag || (end == 3))
					break;
				start++;
				end++;
			}
			if (end < 3)
			{
				for (k = end; k >= start; k--)
				{
					array[k + 1][l] = array[k][l];
					array[k][l] = 0;
				}
			}
		}
	}
}

void number_of_block::move_down()
{
	int i, j, k, l, start, end;
	set_to_down();
	for (l = 0; l < 4; l++)
	{
		for (i = 3; i > 0; i--)
		{
			if (array[i][l] == array[i - 1][l])
			{
				array[i][l] += array[i - 1][l];
				array[i - 1][l] = 0;
				score(array[i][l]);
			}
		}
	}
	set_to_down();
	random_number();
}


void number_of_block::set_to_up()
{
	int i, j, k, l, start, end;
	bool flag, flag2;
	for (l = 0; l < 4; l++)
	{
		start = 3;
		end = 3;
		while (end > 0)
		{
			flag = false;
			for (i = 3; i > -1; i--)
			{
				if (array[i][l] != 0)
				{
					start = i;
					for (j = i; j > -1; j--)
					{
						if (array[j][l] == 0)
							break;
						else end = j;
						flag = true;
					}

				}
				if (flag || (end == 0))
					break;
				start--;
				end--;
			}
			if (end > 0)
			{
				for (k = end; k <= start; k++)
				{
					array[k - 1][l] = array[k][l];
					array[k][l] = 0;
				}
			}
		}
	}
}


void number_of_block::move_up()
{
	int i, j, k, l, start, end;
	set_to_up();
	for (l = 0; l < 4; l++)
	{
		for (i = 0; i < 3; i++)
		{
			if (array[i][l] == array[i + 1][l])
			{
				array[i][l] += array[i + 1][l];
				array[i + 1][l] = 0;
				score(array[i][l]);
			}
		}
	}
	set_to_up();
	random_number();
}


int* number_of_block::return_array()                                    //将数组反馈至GUI类
{
	return &array[0][0];
}


void number_of_block::score(int value)
{
	ifstream file("highest_score.txt");
	file >> highest_score;
	file.close();
	score_now += value;
	if (score_now > highest_score)
	{
		ofstream file2("highest_score.txt");
		file2 << score_now;
		highest_score = score_now;
		file2.close();
	}
}


void block::upward_pressed(Fl_Widget* w, void* data)                 //以下均为按下不同按键后对应的操作
{
	start.play('m');
	start.play('w');
	start.poniter_to_score_now = change(start.score_now, start.buffer1, 10);
	start.poniter_to_highest_score = change(start.highest_score, start.buffer2, 10);
	((block*)data)->scoreboard->label(start.poniter_to_score_now);
	((block*)data)->record->label(start.poniter_to_highest_score);
	((block*)data)->set_number_and_color();
	((block*)data)->win->redraw();
}


void block::downward_pressed(Fl_Widget* w, void* data)
{
	start.play('m');
	start.play('s');
	start.poniter_to_score_now = change(start.score_now, start.buffer1, 10);
	start.poniter_to_highest_score = change(start.highest_score, start.buffer2, 10);
	((block*)data)->scoreboard->label(start.poniter_to_score_now);
	((block*)data)->record->label(start.poniter_to_highest_score);
	((block*)data)->set_number_and_color();
	((block*)data)->win->redraw();
}


void block::left_pressed(Fl_Widget* w, void* data)
{
	start.play('m');
	start.play('a');
	start.poniter_to_score_now = change(start.score_now, start.buffer1, 10);
	start.poniter_to_highest_score = change(start.highest_score, start.buffer2, 10);
	((block*)data)->scoreboard->label(start.poniter_to_score_now);
	((block*)data)->record->label(start.poniter_to_highest_score);
	((block*)data)->set_number_and_color();
	((block*)data)->win->redraw();
}


void block::right_pressed(Fl_Widget* w, void* data)
{
	start.play('m');
	start.play('d');
	start.poniter_to_score_now = change(start.score_now, start.buffer1, 10);
	start.poniter_to_highest_score = change(start.highest_score, start.buffer2, 10);
	((block*)data)->scoreboard->label(start.poniter_to_score_now);
	((block*)data)->record->label(start.poniter_to_highest_score);
	((block*)data)->set_number_and_color();
	((block*)data)->win->redraw();
}


void block::quit_pressed(Fl_Widget* w, void* data)
{
	((block*)data)->end();
}


void block::reset_pressed(Fl_Widget* w, void* data)
{
	start.play('m');
	start.set_array();
	start.score_now = 0;
	start.poniter_to_score_now = change(start.score_now, start.buffer1, 10);
	start.poniter_to_highest_score = change(start.highest_score, start.buffer2, 10);
	((block*)data)->scoreboard->label(start.poniter_to_score_now);
	((block*)data)->record->label(start.poniter_to_highest_score);
	((block*)data)->set_number_and_color();
	((block*)data)->win->redraw();
}


void block::save_pressed(Fl_Widget* w, void* data)
{
	start.play('o');
}


void block::load_pressed(Fl_Widget* w, void* data)
{
	start.play('i');
	((block*)data)->set_number_and_color();
	((block*)data)->win->redraw();
}


void block::back_pressed(Fl_Widget* w, void* data)
{
	start.play('n');
	((block*)data)->set_number_and_color();
	((block*)data)->win->redraw();
}


void block::up()
{
	upbutton->callback((Fl_Callback*)upward_pressed, this);
}


void block::down()
{
	downbutton->callback((Fl_Callback*)downward_pressed, this);
}


void block::left()
{
	leftbutton->callback((Fl_Callback*)left_pressed, this);
}


void block::right()
{
	rightbutton->callback((Fl_Callback*)right_pressed, this);
}


void block::quit()
{
	quitbutton->callback((Fl_Callback*)quit_pressed, this);
}


void block::reset()
{
	resetbutton->callback((Fl_Callback*)reset_pressed, this);
}


void block::save()
{
	savebutton->callback((Fl_Callback*)save_pressed, this);
}


void block::load()
{
	loadbutton->callback((Fl_Callback*)load_pressed, this);
}

void block::back()
{
	backbutton->callback((Fl_Callback*)back_pressed, this);
}


void block::initialize()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			pointer_to_block[i][j] = new Fl_Box(FL_SHADOW_BOX, 30 + 100 * i, 30 + 100 * j, 100, 100, "");
		}
	}
}


void block::end()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			delete pointer_to_block[i][j];
		}
	}
	delete upbutton;
	delete downbutton;
	delete leftbutton;
	delete rightbutton;
	delete quitbutton;
	delete resetbutton;
	delete savebutton;
	delete loadbutton;
	delete backbutton;
	delete one;
	delete two;
	delete scoreboard;
	delete record;
	delete win;
}


void block::set_number_and_color()
{
	int* poniter_to_array = start.return_array();
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			switch (*(poniter_to_array + 4 * j + i))
			{
			case 0:
				pointer_to_block[i][j]->label("");
				pointer_to_block[i][j]->color(FL_BLACK);
				break;
			case 2:
				pointer_to_block[i][j]->color(FL_WHITE);
				pointer_to_block[i][j]->label("2");
				break;
			case 4:
				pointer_to_block[i][j]->color(FL_GREEN);
				pointer_to_block[i][j]->label("4");
				break;
			case 8:
				pointer_to_block[i][j]->color(FL_CYAN);
				pointer_to_block[i][j]->label("8");
				break;
			case 16:
				pointer_to_block[i][j]->color(FL_BLUE);
				pointer_to_block[i][j]->label("16");
				break;
			case 32:
				pointer_to_block[i][j]->color(FL_YELLOW);
				pointer_to_block[i][j]->label("32");
				break;
			case 64:
				pointer_to_block[i][j]->color(FL_MAGENTA);
				pointer_to_block[i][j]->label("64");
				break;
			case 128:
				pointer_to_block[i][j]->color(FL_RED);
				pointer_to_block[i][j]->label("128");
				break;
			case 256:
				pointer_to_block[i][j]->color(FL_BLUE);
				pointer_to_block[i][j]->label("256");
				break;
			case 512:
				pointer_to_block[i][j]->color(FL_YELLOW);
				pointer_to_block[i][j]->label("512");
				break;
			case 1024:
				pointer_to_block[i][j]->color(FL_MAGENTA);
				pointer_to_block[i][j]->label("1024");
				break;
			case 2048:
				pointer_to_block[i][j]->color(FL_RED);
				pointer_to_block[i][j]->label("2048");
				break;
			case 4096:
				pointer_to_block[i][j]->color(FL_RED);
				pointer_to_block[i][j]->label("4096");
				break;
			}
		}
	}
}


block::block()
{
	initialize();
	set_number_and_color();
	scoreboard->label(start.poniter_to_score_now);
	record->label(start.poniter_to_highest_score);
	win->show();
	up();
	down();
	left();
	right();
	quit();
	reset();
	save();
	load();
	back();
}