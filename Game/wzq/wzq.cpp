#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<tchar.h>
#include<time.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


constexpr int DEPTH = 5;																//搜索最大深度


typedef struct FX																		//方向
{
	int qi;																				//某方向的二进制棋型	
	int max_score;																		//某方向的最大分数
	int weishu;																			//某方向的己方棋子与空白的总个数
	int qishu;																			//某方向的己方棋子数
	int mianqi;																			//判断某方向是否为眠棋
}fangxiang;


typedef struct QX																		//棋型及某些棋型对应分数
{
	int huosan;																			//棋型
	int huoer;
	int miansi;
	int miansan;
	int mianer;

	int miansi_score;																	//分数
	int miansan_score;
	int mianer_score;
	int siqi_score;
}qixing;


typedef struct Player																	//玩家(电脑)
{
	qixing player_qixing;
	fangxiang* player_fangxiang;
	int player_color;
}player;

typedef struct alphabeta
{
	int blbo[15][15];																	//黑棋棋盘
	int whbo[15][15];																	//白棋棋盘
	int chbo[15][15];																	//总棋盘
	int play;																			//玩家名
	int count;																			//回合数
	int tempx;																			//临时x坐标
	int tempy;																			//临时y坐标
	int y;																				//x坐标
	int x;																				//y坐标
}AlpBet;


int function_1();																		//功能一
int function_2();																		//功能二
int function_3();																		//退出
int funcyion_ceshi();																	//隐藏测试功能
int draw(int);																			//画棋盘界面
int difficulty();																		//人机难度选择
int playchess_1();																		//人人对弈
int playchess_2();																		//人机对弈(简单难度)
int playchess_22(int dif);																//人机对弈(普通/困难难度)
int playchess_ceshi();																	//电脑对战
int guzhi(int qipan[15][15], int color, int by, int bx, int* y, int* x, int count);		//棋盘，颜色,对方落子坐标，电脑将要落子的坐标,回合数
int pipei(const int qixingku[14], const int qixingku_score[14], player*);				//匹配棋形库进行打分
int bianjie(int* tymin, int* txmin, int* tymax, int* txmax, int y, int x);				//落子点边界查找范围
int judge(int arry[15][15], int, int, int);												//输赢判断
int win_lose(int);																		//胜负显示
int Music(const wchar_t Music_Name[]);													//播放音乐
int set_music(int music_xy[15][15]);													//初始化音频调用表

int AlphaBeta(int depth, int alpha, int beta, AlpBet* AB);								//alpha-beta剪枝算法


int Music(const WCHAR Music_Name[])
{
	PlaySound(Music_Name, nullptr, SND_NODEFAULT | SND_ASYNC);							//异步单次播放
	return 1;
}

int set_music(int music_xy[15][15])
{
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
		music_xy[i][j] = rand() % 88;
	return 0;
}


int menu()																				//菜单
{
	IMAGE img;
	MOUSEMSG m{};																		// 定义鼠标消息
	const TCHAR* s0 = _T("五子棋"), *s1 = _T("人人对弈"), *s2 = _T("人机对弈"), *s3 = _T("退出");
	TCHAR bgm[40] = L"音频文件\\BGM(0).wav";											//音乐名
	int temp = 0;
	const int MUSIC_NUM = 5;															//BGM数
	int music_num = 0;
	int music_length[MUSIC_NUM] = { 112, 118, 148, 195, 138 };								//各BGM时长
	int t0 = 0;																			//音乐开始时间
	initgraph(740, 480, NOCLOSE);													    //初始化绘图窗口
	loadimage(&img, _T("五子棋0X68.png"), 740, 480, true);								//保存图片地址，文件地址，将图片拉伸至此长宽
	putimage(0, 0, &img);																//绘制该图片
	srand(time(nullptr) & 0xffffffff);

	while (1)
	{
		if (!temp)
		{
			putimage(0, 0, &img);
			setlinecolor(0XAAAAAA);														//设置当前划线颜色
			rectangle(320, 150, 420, 200);												//画空心矩形
			rectangle(110, 300, 210, 350);
			rectangle(320, 300, 420, 350);
			rectangle(530, 300, 630, 350);
			settextcolor(0XFF55FF);														//设置字体颜色
			setbkmode(TRANSPARENT);														//设置字体背景色，透明
			outtextxy(345, 165, s0);													//在指定位置输出字符串
			outtextxy(130, 315, s1);
			outtextxy(340, 315, s2);
			outtextxy(565, 315, s3);

			t0 = time(nullptr);
			music_num = rand() % MUSIC_NUM;
			_stprintf_s(bgm, 40, L"音频文件\\BGM(%d).wav", music_num);
			Music(bgm);

		}

		if (((t0 + music_length[music_num]) < time(nullptr) - 3))
		{
			t0 = time(nullptr);
			music_num = rand() % MUSIC_NUM;
			_stprintf_s(bgm, 40, L"音频文件\\BGM(%d).wav", music_num);
			Music(bgm);
		}

		m = GetMouseMsg();																//获得一个鼠标的结构体
		if (m.x >= 110 && m.x <= 210 && m.y >= 300 && m.y <= 350 && m.mkLButton)		//判断是否启用功能一
		{
			temp = function_1();														//功能一
			continue;
		}
		if (m.x >= 320 && m.x <= 420 && m.y >= 300 && m.y <= 350 && m.mkLButton)		//判断是否启用功能二
		{
			temp = function_2();														//功能二
			continue;
		}

		if (m.mkRButton && m.x >= 320 && m.x <= 420 && m.y >= 150 && m.y <= 200)		//右键五子棋，进入电脑对战电脑的测试功能
		{
			temp = funcyion_ceshi();													//电脑对战电脑的测试功能
			continue;
		}


		temp = 1;																		//无操作，保持画面
		if (m.x >= 530 && m.x <= 630 && m.y >= 300 && m.y <= 350 && m.mkLButton)		//判断是否启用功能三
			function_3();																//功能三
	}
	return 0;
}



int function_1()																		//功能一
{
	draw(1);																			//人人对弈模式
	playchess_1();
	return 0;
}



int function_2()																		//功能二
{
	int diff = 21;
	diff = difficulty();
	draw(diff);
	if (diff == 21)
		playchess_2();																	//人机对弈模式
	if (diff == 22)
		playchess_22(4);
	return 0;
}



int function_3()
{
	const TCHAR* t1 = _T("已退出！");
	setlinecolor(0X000000);																//设置当前画线色
	setfillcolor(0XFFFFFF);																//设置当前填充色
	fillroundrect(220, 140, 520, 340, 150, 120);										//画圆角矩形
	settextcolor(0X5555FF);																//设置字体颜色
	setbkmode(TRANSPARENT);																//设置字体背景色，透明
	outtextxy(345, 230, t1);
	Sleep(1000);
	closegraph();
	exit(0);
}


int funcyion_ceshi()
{
	draw(104);																			//测试模式
	playchess_ceshi();
	return 0;
}



int draw(int mode)																		//画棋盘界面
{
	const TCHAR* mode_1 = _T("模式:                人人对弈"), *mode_21 = _T("模式:                人机对弈(初级)");
	const TCHAR* mode_22 = _T("模式:                人机对弈(中级)"), *mode_23 = _T("模式:                人机对弈(高级)");
	const TCHAR* mode_ceshi = _T("模式:                电脑对战(测试)");
	const TCHAR* chess_player = _T("当前棋手:");
	const TCHAR* round = _T("回合数:");
	const TCHAR* quit = _T("返回");
	setbkcolor(RGB(222, 184, 135));														//设置背景色,棕色，棋盘背景色
	cleardevice();																	    //绘制棋盘背景色
	setlinecolor(0X000000);																//设置棋盘画线颜色，黑色
	for (int i = 0; i < 15; i++)														//画棋盘
	{
		line(30, 30 + i * 30, 450, 30 + i * 30);										//棋盘间隔，30
		line(30 + i * 30, 30, 30 + i * 30, 450);
	}
	setfillcolor(0X000000);																//设置填充色，黑色
	solidcircle(120, 120, 3);															//画棋盘五个小黑点
	solidcircle(360, 120, 3);
	solidcircle(240, 240, 3);
	solidcircle(120, 360, 3);
	solidcircle(360, 360, 3);

	setfillcolor(0XFFFFFF);																//绘制右边白色区域
	solidrectangle(480, 0, 740, 480);

	setfillcolor(0XAAAAAA);																//返回按钮背景色
	solidrectangle(670, 415, 720, 440);													//返回按钮背景

	settextcolor(0X000000);																//设置字体颜色
	setbkmode(TRANSPARENT);																//设置字体背景色，透明
	if (mode == 1)																		//人人对弈模式
		outtextxy(520, 20, mode_1);
	else if (mode == 21)
		outtextxy(520, 20, mode_21);													//人机对弈，初级
	else if (mode == 22)
		outtextxy(520, 20, mode_22);													//人机对弈。中级
	else if (mode == 23)
		outtextxy(520, 20, mode_23);													//人机对弈，高级
	else if (mode == 104)
		outtextxy(520, 20, mode_ceshi);													//电脑对战(测试)
	outtextxy(520, 150, chess_player);													//棋手
	outtextxy(520, 280, round);															//回合数
	outtextxy(680, 420, quit);															//返回按钮
	return 0;
}

int difficulty()																		//人机对弈难度选择
{
	MOUSEMSG mc = {};																		//定义鼠标消息
	const TCHAR* c0 = _T("请选择电脑难度:"), *c1 = _T("初级"), *c2 = _T("中级"), *c3 = _T("高级");
	setlinecolor(0X000000);																//设置当前画线色
	setfillcolor(0XFFFFFF);																//设置当前填充色
	fillroundrect(180, 120, 560, 360, 150, 150);										//画圆角矩形
	settextcolor(0X5555FF);																//设置字体颜色
	setbkmode(TRANSPARENT);																//设置字体背景色，透明

	rectangle(250, 265, 300, 290);														//画空心矩形
	rectangle(350, 265, 400, 290);
	rectangle(450, 265, 500, 290);

	outtextxy(320, 180, c0);
	outtextxy(260, 270, c1);
	outtextxy(360, 270, c2);
	outtextxy(460, 270, c3);

	do
	{
		mc = GetMouseMsg();																//获得一个鼠标的结构体

		if (mc.mkLButton && mc.x > 250 && mc.x < 300 && mc.y>265 && mc.y < 290)
			return 21;
		if (mc.mkLButton && mc.x > 350 && mc.x < 400 && mc.y>265 && mc.y < 290)
			return 22;
		if (mc.mkLButton && mc.x > 450 && mc.x < 500 && mc.y>265 && mc.y < 290)
			return 23;

	} while (1);
	return 21;																			//默认为初级
}



int playchess_1()																		//人人对弈实现
{
	Music(L"NULL");																		//停止播放

	int player = 0;																		//玩家标志
	int round_count = 1;																//回合数计数
	int tempx = 0, tempy = 0;															//临时x,y坐标
	int chessboard[15][15] = { 0 };														//初始化棋盘信息
	int black_board[15][15] = { 0 };													//初始化黑棋棋局
	int white_board[15][15] = { 0 };													//初始化白棋棋局
	int music_borad[15][15] = { 0 };													//音频信息对照表
	MOUSEMSG m_1{};																		//定义鼠标消息
	const TCHAR* player_name_black = _T("黑棋"), *player_name_white = _T("白棋");
	TCHAR round_num[20] = _T("");
	TCHAR music_name[40] = _T("");

	settextcolor(0X000000);																//设置字体颜色
	setbkmode(TRANSPARENT);																//设置字体背景色，透明
	setfillcolor(0XFFFFFF);
	int flag = 1;																		//判断棋局是否变化
	set_music(music_borad);																//初始化音频信息对照表

	do
	{
		if (flag)
		{
			setfillcolor(0XFFFFFF);														//使用背景色清空上次显示内容
			solidrectangle(610, 140, 700, 170);											//清空区域

			if (player == 0)
				outtextxy(620, 150, player_name_black);									//显示当前为黑棋
			if (player == 1)
				outtextxy(620, 150, player_name_white);									//显示当前为白棋


			_stprintf_s(round_num, 20, _T("第%d回合"), round_count);
			solidrectangle(610, 270, 700, 300);
			outtextxy(620, 280, round_num);												//打印回合数

			if (round_count > 225)														//判断回合数是否下满棋盘
			{
				win_lose(0);															//平局
				break;
			}
			flag = 0;
		}
		m_1 = GetMouseMsg();															//获得一个鼠标的结构体
		//若该点为交点，且棋盘上此处无子，且左键按下
		if (m_1.mkLButton && (m_1.x >= 20 && m_1.x <= 460 && m_1.y >= 20 && m_1.y <= 460)
			&& (m_1.x % 30 <= 10 || m_1.x % 30 >= 20) && (m_1.y % 30 <= 10 || m_1.y % 30 >= 20)
			&& chessboard[m_1.y / 30 - 1 + (m_1.y % 30) / 20][m_1.x / 30 - 1 + (m_1.x % 30) / 20] == 0)
		{																				//在交点以半边长为10的正方形区域可以落子
			int x = m_1.x / 30 - 1 + (m_1.x % 30) / 20;									//定义并坐标修正
			int y = m_1.y / 30 - 1 + (m_1.y % 30) / 20;									//定义并坐标修正

			if (round_count > 1)
			{
				if (!player == 0)
				{
					setfillcolor(0X000000);												//设置小点颜色,黑色
					solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);					//清空红点
				}
				else
				{
					setfillcolor(0XFFFFFF);												//设置小点颜色,白色
					solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);					//清空红点
				}
			}
			tempx = x, tempy = y;														//记录落子点

			if (player == 0)															//黑棋落子(玩家落子）
			{
				chessboard[y][x] = 1;													//棋盘记录
				black_board[y][x] = 1;													//黑棋在此落子，黑子为1
				setfillcolor(0X000000);													//设置棋子颜色,黑色
				solidcircle((x + 1) * 30, (y + 1) * 30, 10);							//画黑色棋子

				_stprintf_s(music_name, 40, _T("音频文件\\sounds (%d).wav"), music_borad[x][y]);//设置音频文件名信息
				Music(music_name);

				setfillcolor(0X5555FF);													//设置填充颜色
				solidcircle((x + 1) * 30, (y + 1) * 30, 3);								//画小红点

				if (judge(black_board, y, x, 1))										//判断黑棋是否胜
				{
					win_lose(1);														//黑棋胜
					break;
				}
				player = !player;														//换对方落子
				flag = 1;
			}
			else if (player == 1)														//白棋（电脑）落子
			{																			//白棋落子
				chessboard[y][x] = 2;													//棋盘记录
				white_board[y][x] = 2;													//白棋在此落子，白子为2
				setfillcolor(0XFFFFFF);													//设置棋子颜色，白色
				solidcircle((x + 1) * 30, (y + 1) * 30, 10);							//画白色棋子

				_stprintf_s(music_name, 40, _T("音频文件\\sounds (%d).wav"), music_borad[x][y]);//设置音频文件名信息
				Music(music_name);

				setfillcolor(0X5555FF);													//设置填充颜色
				solidcircle((x + 1) * 30, (y + 1) * 30, 3);								//画小红点

				if (judge(white_board, y, x, 2))										//判断白棋是否胜
				{
					win_lose(2);														//白棋胜
					break;
				}
				player = !player;														//换对方落子
				flag = 1;
			}
			round_count++;
		}
		if (m_1.mkLButton && m_1.x >= 670 && m_1.x <= 720 && m_1.y >= 415 && m_1.y <= 440)
			break;																		//返回按钮
	} while (1);
	return 0;
}



int playchess_ceshi()																	//电脑对弈实现
{
	Music(L"NULL");																		//停止播放

	int player = 0;																		//玩家标志
	int round_count = 1;																//回合数计数
	int tempx = 0, tempy = 0;															//临时x,y坐标
	int chessboard[15][15] = { 0 };														//初始化棋盘信息
	int black_board[15][15] = { 0 };													//初始化黑棋棋局
	int white_board[15][15] = { 0 };													//初始化白棋棋局
	int no[15][15] = { 0 };																//不考虑落子的点
	int music_borad[15][15] = { 0 };													//音频信息对照表
	const TCHAR* computer_ceshi_black = _T("黑棋(电脑)"), *computer_ceshi_white = _T("白棋(电脑)");
	TCHAR round_num[20] = _T("");
	TCHAR music_name[40] = _T("");
	AlpBet AB = {};																		//alpha-beta算法需要的数据信息

	settextcolor(0X000000);																//设置字体颜色
	setbkmode(TRANSPARENT);																//设置字体背景色，透明
	setfillcolor(0XFFFFFF);

	int flag = 1;																		//判断棋局是否变化
	int biaozhi = 0;																	//记录是否玩家刚落子
	int x = 0, y = 0;
	set_music(music_borad);																//初始化音频信息对照表

	do
	{
		if (flag)
		{
			setfillcolor(0XFFFFFF);														//使用背景色清空上次显示内容
			solidrectangle(610, 140, 700, 170);											//清空区域

			if (player == 0)
				outtextxy(620, 150, computer_ceshi_black);								//显示为黑棋(电脑)
			if (player == 1)
				outtextxy(620, 150, computer_ceshi_white);								//显示为白棋(电脑)


			_stprintf_s(round_num, 20, _T("第%d回合"), round_count);
			solidrectangle(610, 270, 700, 300);
			outtextxy(620, 280, round_num);												//打印回合数

			if (round_count > 225)														//判断回合数是否下满棋盘
			{
				win_lose(0);															//平局
				break;
			}
			flag = 0;
		}

		if (player == 0 && biaozhi == 0)
		{
			guzhi(chessboard, 1, tempy, tempx, &y, &x, round_count);					//估值函数
			Sleep(500);

			if (round_count > 1)														//第一次不画点
			{
				setfillcolor(0XFFFFFF);													//设置小点颜色,白色
				solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);						//清空红点

			}

			tempx = x, tempy = y;

			chessboard[y][x] = 1;														//棋盘记录
			black_board[y][x] = 1;														//黑棋在此落子，黑子为1
			setfillcolor(0X000000);														//设置棋子颜色,黑色
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//画黑色棋子

			_stprintf_s(music_name, 40, _T("音频文件\\sounds (%d).wav"), music_borad[x][y]);//设置音频文件名信息
			Music(music_name);															//播放音乐

			setfillcolor(0X5555FF);														//设置填充颜色
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//画小红点

			if (judge(black_board, y, x, 1))											//判断黑棋是否胜
			{
				win_lose(1040);															//黑棋胜(玩家胜)
				break;
			}
			player = !player;															//换对方落子
			flag = 1;
			biaozhi = 1;
			round_count++;
		}
		else if (player == 1 && biaozhi == 1)											//白棋（电脑）落子
		{
			for (int i = 0; i < 15; i++)												//初始化AB信息
			for (int j = 0; j < 15; j++)
			{
				AB.blbo[i][j] = black_board[i][j];
				AB.whbo[i][j] = white_board[i][j];
				AB.chbo[i][j] = chessboard[i][j];
			}
			AB.play = player;
			AB.count = round_count;
			AB.tempx = tempx;
			AB.tempy = tempy;
			AB.x = x;
			AB.y = y;

			AlphaBeta(0, 50, 800000, &AB);
			x = AB.x;
			y = AB.y;

			//guzhi(chessboard,2, tempy, tempx, &y, &x, round_count);					//估值函数
			Sleep(500);

			setfillcolor(0X000000);														//设置小点颜色,黑色
			solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);							//清空红点

			tempx = x, tempy = y;
			chessboard[y][x] = 2;														//棋盘记录
			white_board[y][x] = 2;														//黑棋在此落子，白子为2
			setfillcolor(0XFFFFFF);														//设置棋子颜色,白色
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//画白色棋子

			_stprintf_s(music_name, 40, _T("音频文件\\sounds (%d).wav"), music_borad[x][y]);//设置音频文件名信息
			Music(music_name);															//播放音乐

			setfillcolor(0X5555FF);														//设置填充颜色
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//画小红点

			if (judge(white_board, y, x, 2))											//判断白棋是否胜
			{
				win_lose(1041);															//白棋胜(电脑胜)
				break;
			}
			player = !player;															//换对方落子
			biaozhi = 0;
			flag = 1;
			round_count++;
		}
	} while (!_kbhit());
	_getch();
	return 0;
}





int playchess_2()																		//人机对弈实现（简单）
{
	Music(L"NULL");																		//停止播放

	int player = 0;																		//玩家标志
	int round_count = 1;																//回合数计数
	int tempx = 0, tempy = 0;															//临时x,y坐标
	int chessboard[15][15] = { 0 };														//初始化棋盘信息
	int black_board[15][15] = { 0 };													//初始化黑棋棋局
	int white_board[15][15] = { 0 };													//初始化白棋棋局
	int no[15][15] = { 0 };																//不考虑落子的点
	int music_borad[15][15] = { 0 };													//音频信息对照表
	MOUSEMSG m_2{};																		//定义鼠标消息
	const TCHAR* player_name_player = _T("玩家(黑棋)"), *player_name_computer = _T("电脑(白棋)");
	const TCHAR* easy = _T("初级");
	const TCHAR* medium = _T("中级");
	const TCHAR* advanced = _T("高级");
	TCHAR round_num[20] = _T("");
	TCHAR music_name[40] = _T("");
	settextcolor(0X000000);																//设置字体颜色
	setbkmode(TRANSPARENT);																//设置字体背景色，透明
	setfillcolor(0XFFFFFF);
	int flag = 1;																		//判断棋局是否变化
	set_music(music_borad);																//初始化音频信息对照表

	do
	{
		if (flag)
		{
			setfillcolor(0XFFFFFF);														//使用背景色清空上次显示内容
			solidrectangle(610, 140, 700, 170);											//清空区域

			if (player == 0)
				outtextxy(620, 150, player_name_player);								//显示为玩家
			if (player == 1)
				outtextxy(620, 150, player_name_computer);								//显示为电脑

			_stprintf_s(round_num, 20, _T("第%d回合"), round_count);
			solidrectangle(610, 270, 700, 300);
			outtextxy(620, 280, round_num);												//打印回合数

			if (round_count > 225)														//判断回合数是否下满棋盘
			{
				win_lose(0);															//平局
				break;
			}
			flag = 0;
		}

		int biaozhi = 1;																//记录是否玩家刚落子
		m_2 = GetMouseMsg();															//获得一个鼠标的结构体
		//若该点为交点，且棋盘上此处无子，且左键按下
		if (player == 0 && m_2.mkLButton 												//黑棋（玩家）落子
			&& (m_2.x >= 20 && m_2.x <= 460 && m_2.y >= 20 && m_2.y <= 460)
			&& (m_2.x % 30 <= 10 || m_2.x % 30 >= 20) && (m_2.y % 30 <= 10 || m_2.y % 30 >= 20)
			&& chessboard[m_2.y / 30 - 1 + (m_2.y % 30) / 20][m_2.x / 30 - 1 + (m_2.x % 30) / 20] == 0)
		{																				//在交点以半边长为10的正方形区域可以落子
			int x = m_2.x / 30 - 1 + (m_2.x % 30) / 20;									//定义并坐标修正
			int y = m_2.y / 30 - 1 + (m_2.y % 30) / 20;									//定义并坐标修正

			if (round_count > 1)														//第一次不画点
			{
				setfillcolor(0XFFFFFF);													//设置小点颜色,白色
				solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);						//清空红点

			}
			tempx = x, tempy = y;														//记录落子点
			//黑棋(玩家落子）
			chessboard[y][x] = 1;														//棋盘记录
			black_board[y][x] = 1;														//黑棋在此落子，黑子为1
			setfillcolor(0X000000);														//设置棋子颜色,黑色
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//画黑色棋子

			_stprintf_s(music_name, 40, _T("音频文件\\sounds (%d).wav"), music_borad[x][y]);//设置音频文件名信息
			Music(music_name);															//播放音乐

			setfillcolor(0X5555FF);														//设置填充颜色
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//画小红点

			if (judge(black_board, y, x, 1))											//判断黑棋是否胜
			{
				win_lose(3);															//黑棋胜(玩家胜)
				break;
			}
			player = !player;															//换对方落子
			flag = 1;
			biaozhi = 0;
			round_count++;
		}
		else if (player == 1 && biaozhi == 1)											//白棋（电脑）落子
		{
			setfillcolor(0X000000);														//设置小点颜色,黑色
			solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);							//清空红点

			int x = 0, y = 0;
			guzhi(chessboard, 2, tempy, tempx, &y, &x, round_count);					//估值函数

			tempx = x, tempy = y;														//记录落子点

			chessboard[y][x] = 2;														//棋盘记录
			white_board[y][x] = 2;														//黑棋在此落子，白子为2
			setfillcolor(0XFFFFFF);														//设置棋子颜色,白色
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//画白色棋子

			_stprintf_s(music_name, 40, _T("音频文件\\sounds (%d).wav"), music_borad[x][y]);//设置音频文件名信息
			Music(music_name);															//播放音频

			setfillcolor(0X5555FF);														//设置填充颜色
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//画小红点

			if (judge(white_board, y, x, 2))											//判断白棋是否胜
			{
				win_lose(4);															//白棋胜(电脑胜)
				break;
			}
			player = !player;															//换对方落子
			flag = 1;
			round_count++;
		}

		if (m_2.mkLButton && m_2.x >= 680 && m_2.x <= 710 && m_2.y >= 420 && m_2.y <= 435)
			return 1;																	//返回按钮
	} while (1);
	return 0;
}



int playchess_22(int dif)																//人机对弈实现（普通/困难难度）
{
	Music(L"NULL");																		//停止播放

	int player = 0;																		//玩家标志
	int round_count = 1;																//回合数计数
	int tempx = 0, tempy = 0;															//临时x,y坐标
	int chessboard[15][15] = { 0 };														//初始化棋盘信息
	int black_board[15][15] = { 0 };													//初始化黑棋棋局
	int white_board[15][15] = { 0 };													//初始化白棋棋局
	int music_borad[15][15] = { 0 };													//音频信息对照表
	MOUSEMSG m_2{};																		//定义鼠标消息
	const TCHAR* player_name_player = _T("玩家(黑棋)"), *player_name_computer = _T("电脑(白棋)");
	const TCHAR* easy = _T("初级");
	const TCHAR* medium = _T("中级");
	const TCHAR* advanced = _T("高级");
	TCHAR round_num[20] = _T("");
	TCHAR music_name[40] = _T("");
	settextcolor(0X000000);																//设置字体颜色
	setbkmode(TRANSPARENT);																//设置字体背景色，透明
	setfillcolor(0XFFFFFF);
	int flag = 1;																		//判断棋局是否变化
	set_music(music_borad);																//初始化音频信息对照表
	AlpBet AB = {};																		//alpha-beta算法需要的数据信息


	do
	{
		if (flag)
		{
			setfillcolor(0XFFFFFF);														//使用背景色清空上次显示内容
			solidrectangle(610, 140, 700, 170);											//清空区域

			if (player == 0)
				outtextxy(620, 150, player_name_player);								//显示为玩家
			if (player == 1)
				outtextxy(620, 150, player_name_computer);								//显示为电脑

			_stprintf_s(round_num, 20, _T("第%d回合"), round_count);
			solidrectangle(610, 270, 700, 300);
			outtextxy(620, 280, round_num);												//打印回合数

			if (round_count > 225)														//判断回合数是否下满棋盘
			{
				win_lose(0);															//平局
				break;
			}
			flag = 0;
		}

		int biaozhi = 1;																//记录是否玩家刚落子
		m_2 = GetMouseMsg();															//获得一个鼠标的结构体
		//若该点为交点，且棋盘上此处无子，且左键按下
		if (player == 0 && m_2.mkLButton 												//黑棋（玩家）落子
			&& (m_2.x >= 20 && m_2.x <= 460 && m_2.y >= 20 && m_2.y <= 460)
			&& (m_2.x % 30 <= 10 || m_2.x % 30 >= 20) && (m_2.y % 30 <= 10 || m_2.y % 30 >= 20)
			&& chessboard[m_2.y / 30 - 1 + (m_2.y % 30) / 20][m_2.x / 30 - 1 + (m_2.x % 30) / 20] == 0)
		{																				//在交点以半边长为10的正方形区域可以落子
			int x = m_2.x / 30 - 1 + (m_2.x % 30) / 20;									//定义并坐标修正
			int y = m_2.y / 30 - 1 + (m_2.y % 30) / 20;									//定义并坐标修正

			if (round_count > 1)														//第一次不画点
			{
				setfillcolor(0XFFFFFF);													//设置小点颜色,白色
				solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);						//清空红点

			}
			tempx = x, tempy = y;														//记录落子点
			//黑棋(玩家落子）
			chessboard[y][x] = 1;														//棋盘记录
			black_board[y][x] = 1;														//黑棋在此落子，黑子为1
			setfillcolor(0X000000);														//设置棋子颜色,黑色
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//画黑色棋子

			_stprintf_s(music_name, 40, _T("音频文件\\sounds (%d).wav"), music_borad[x][y]);//设置音频文件名信息
			Music(music_name);															//播放音乐

			setfillcolor(0X5555FF);														//设置填充颜色
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//画小红点

			if (judge(black_board, y, x, 1))											//判断黑棋是否胜
			{
				win_lose(3);															//黑棋胜(玩家胜)
				break;
			}
			player = !player;															//换对方落子
			flag = 1;
			biaozhi = 0;
			round_count++;
		}
		else if (player == 1 && biaozhi == 1)											//白棋（电脑）落子
		{
			setfillcolor(0X000000);														//设置小点颜色,黑色
			solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);							//清空红点

			int x = 0, y = 0;

			{for (int i = 0; i < 15; i++)												//初始化AB信息
			for (int j = 0; j < 15; j++)
			{
				AB.blbo[i][j] = black_board[i][j];
				AB.whbo[i][j] = white_board[i][j];
				AB.chbo[i][j] = chessboard[i][j];
			}
			AB.play = player;
			AB.count = round_count;
			AB.tempx = tempx;
			AB.tempy = tempy;
			AB.x = x;
			AB.y = y;
			}

			AlphaBeta(0, 0, 99999, &AB);
			x = AB.x;
			y = AB.y;
			//guzhi(chessboard,no, 2, tempy, tempx, &y, &x, round_count);				//估值函数
			tempx = x, tempy = y;														//记录落子点

			chessboard[y][x] = 2;														//棋盘记录
			white_board[y][x] = 2;														//黑棋在此落子，白子为2
			setfillcolor(0XFFFFFF);														//设置棋子颜色,白色
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//画白色棋子

			_stprintf_s(music_name, 40, _T("音频文件\\sounds (%d).wav"), music_borad[x][y]);//设置音频文件名信息
			Music(music_name);															//播放音频

			setfillcolor(0X5555FF);														//设置填充颜色
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//画小红点

			if (judge(white_board, y, x, 2))											//判断白棋是否胜
			{
				win_lose(4);															//白棋胜(电脑胜)
				break;
			}
			player = !player;															//换对方落子
			flag = 1;
			round_count++;
		}

		if (m_2.mkLButton && m_2.x >= 680 && m_2.x <= 710 && m_2.y >= 420 && m_2.y <= 435)
			return 1;																	//返回按钮
	} while (1);
	return 0;
}




//棋盘，颜色，对方落子坐标，电脑将要落子的坐标，回合数
int guzhi(int qipan[15][15], int color, int by, int bx, int* y, int* x, int count)
{
	int borad_weights[15][15] = { 0 };					 								//静态棋盘各点总分数
	//const static int borad_position[15][15] = {
	//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	//{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
	//{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
	//{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
	//{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
	//{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
	//{0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
	//{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
	//{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
	//{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
	//{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
	//{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
	//{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };													//棋盘各点位置分数

	const static int qixingku[14] = { 077, 076, 037, 036, 016, 034, 026, 032, 014, 030, 006, 024, 012, 022 };				//棋形库，活棋型，长连，活四，活三，活二
	const static int cqixingku_score[14] = { 500000, 500000, 500000, 50000, 500, 500, 500, 500, 30, 30, 30, 30, 30, 30 };	//棋形库对应棋形分数，不包括组合棋形
	const static int pqixingku_score[14] = { 400000, 400000, 400000, 40000, 400, 400, 400, 400, 25, 25, 25, 25, 25, 25 };	//玩家棋形库分数

	static int txmin = 7, tymin = 7, txmax = 7, tymax = 7;								//棋盘分数坐标确定点（电脑落子使用），两个对角点，左上，右下
	if (count == 2)
		txmin = 7, tymin = 7, txmax = 7, tymax = 7;										//重置边界点

	bianjie(&tymin, &txmin, &tymax, &txmax, by, bx);									//确定落子点边界

	int my_color = 0, other_color = 0;
	if (color == 1)
	{
		my_color = 1;
		other_color = 2;
	}
	else if (color == 2)
	{
		my_color = 2;
		other_color = 1;
	}

	int max_score = -999999;															//记录最高分
	int max_score_x[100] = { 0 }, max_score_y[100] = { 0 };								//记录最高分数x,y坐标,最多记录10个
	int max_num = 1;																	//记录最高分个数,初始值为1，最少有一个点

	int i = 0, j = 0;
	for (i = tymin; i <= tymax; i++)													//在棋子矩形边界范围内查找最大分数点
	{
		for (j = txmin; j <= txmax; j++)
		{																				//该点附近是否有棋子
			if (qipan[i][j] == 0 &&
				(qipan[i][j - 1 > 0 ? j - 1 : 0] != 0 || qipan[i - 1 > 0 ? i - 1 : 0][j - 1 > 0 ? j - 1 : 0] != 0 ||
				qipan[i - 1 > 0 ? i - 1 : 0][j] != 0 || qipan[i - 1 > 0 ? i - 1 : 0][j + 1 < 14 ? j + 1 : 14] != 0 ||
				qipan[i][j + 1 < 14 ? j + 1 : 14] != 0 || qipan[i + 1 < 14 ? i + 1 : 14][j + 1 < 14 ? j + 1 : 14] != 0 ||
				qipan[i + 1 < 14 ? i + 1 : 14][j] != 0 || qipan[i + 1 < 14 ? i + 1 : 14][j - 1 > 0 ? j - 1 : 0] != 0))
			{																			//i，j位置表示需要判断分数的点											
				qipan[i][j] = my_color;													//假设电脑在该点落子	电脑为白棋


				player ziji = { 0 };
				ziji.player_qixing = { 0, 0, 0, 0, 0, 1000, 100, 10, -5 };						//初始化棋型及分数信息
				ziji.player_color = my_color;											//初始化颜色

				fangxiang zj_heng = { 0 }, zj_shu = { 0 }, zj_zuoxie = { 0 }, zj_youxie = { 0 };

				ziji.player_fangxiang = &zj_heng;										//横向判断
				ziji.player_fangxiang->mianqi = 1;										//判断该点是否为眠棋，0否  1是
				int a = i, b = j;														//临时x,y坐标
				for (b = j; b <= j + 4; b++)											//向右搜索,确定右边界			电脑横向判断
				{
					if (b > 14)
						break;															//越界，结束循环
					if (qipan[a][b] != ziji.player_color && qipan[a][b] != 0)
						break;															//遇到非己方子，结束循环
				}
				b--;																	//调整x坐标

				for (ziji.player_fangxiang->weishu = 0; (qipan[a][b] == ziji.player_color || qipan[a][b] == 0)
					&& b >= 0 && b >= j - 4; b--, ziji.player_fangxiang->weishu++)
				{																		//遇到非己方子，越界，超过范围，结束循环
					if (qipan[a][b] == ziji.player_color)
					{
						ziji.player_fangxiang->qi |= 1 << ziji.player_fangxiang->weishu;//记方棋子，记为1
						ziji.player_fangxiang->qishu++;									//计算己方棋子数
					}
				}
				pipei(qixingku, cqixingku_score, &ziji);



				ziji.player_fangxiang = &zj_shu;										//竖向判断
				ziji.player_fangxiang->mianqi = 1;										//判断该点是否为眠棋，0否  1是
				a = i, b = j;
				for (a = i; a <= i + 4; a++)											//向下搜索,确定下边界			电脑竖向判断
				{
					if (a > 14)
						break;															//越界，结束循环
					if (qipan[a][b] != ziji.player_color && qipan[a][b] != 0)
						break;															//遇到非己方子，结束循环
				}
				a--;																	//调整y坐标

				for (ziji.player_fangxiang->weishu = 0; (qipan[a][b] == ziji.player_color || qipan[a][b] == 0)
					&& a >= 0 && a >= i - 4; a--, ziji.player_fangxiang->weishu++)
				{																		//遇到非己方子，越界，超过范围，结束循环
					if (qipan[a][b] == ziji.player_color)
					{
						ziji.player_fangxiang->qi |= 1 << ziji.player_fangxiang->weishu;//己方棋子，记为1
						ziji.player_fangxiang->qishu++;									//计算己方棋子数
					}
				}
				pipei(qixingku, cqixingku_score, &ziji);								//与棋形库匹配打分



				ziji.player_fangxiang = &zj_zuoxie;										//左斜判断
				ziji.player_fangxiang->mianqi = 1;										//判断该点是否为眠棋，0否  1是
				a = i, b = j;
				for (a = i, b = j; a <= i + 4 && b <= j + 4; a++, b++)					//向右下搜索,确定右下边界		电脑左斜判断
				{
					if (a > 14 || b > 14)
						break;															//越界，结束循环
					if (qipan[a][b] != ziji.player_color && qipan[a][b] != 0)
						break;															//遇到非己方子，结束循环
				}
				a--, b--;																//调整y,x坐标

				for (ziji.player_fangxiang->weishu = 0; (qipan[a][b] == ziji.player_color || qipan[a][b] == 0)
					&& b >= 0 && b >= j - 4 && a >= 0 && a >= i - 4; b--, a--, ziji.player_fangxiang->weishu++)
				{																		//遇到非己方子，越界，超过范围，结束循环
					if (qipan[a][b] == ziji.player_color)
					{
						ziji.player_fangxiang->qi |= 1 << ziji.player_fangxiang->weishu;//记方棋子，记为1
						ziji.player_fangxiang->qishu++;									//计算己方棋子数
					}
				}
				pipei(qixingku, cqixingku_score, &ziji);								//与棋形库匹配打分



				ziji.player_fangxiang = &zj_youxie;										//右斜判断
				ziji.player_fangxiang->mianqi = 1;										//判断该点是否为眠棋，0否  1是
				a = i, b = j;
				for (a = i, b = j; a <= i + 4 && b >= j - 4; a++, b--)					//向左下搜索,确定左下边界		电脑右斜判断
				{
					if (a > 14 || b < 0)
						break;															//越界，结束循环
					if (qipan[a][b] != ziji.player_color && qipan[a][b] != 0)
						break;															//遇到非己方子，结束循环
				}
				a--, b++;																//调整y,x坐标

				for (ziji.player_fangxiang->weishu = 0; (qipan[a][b] == ziji.player_color || qipan[a][b] == 0)
					&& b <= 14 && b <= j + 4 && a >= 0 && a >= i - 4; b++, a--, ziji.player_fangxiang->weishu++)
				{																		//遇到非己方子，越界，超过范围，结束循环
					if (qipan[a][b] == ziji.player_color)
					{
						ziji.player_fangxiang->qi |= 1 << ziji.player_fangxiang->weishu;//记方棋子，记为1
						ziji.player_fangxiang->qishu++;									//计算己方棋子数
					}
				}
				pipei(qixingku, cqixingku_score, &ziji);								//与棋形库匹配打分


				//电脑在该点落子的分数
				borad_weights[i][j] = zj_heng.max_score + zj_shu.max_score + zj_zuoxie.max_score + zj_youxie.max_score;

				//组合棋型判断
				if (borad_weights[i][j] < 50000 && (ziji.player_qixing.miansi >= 2 || (ziji.player_qixing.miansi >= 1 && ziji.player_qixing.huosan >= 1)))
					borad_weights[i][j] = 50000;										//双眠四，眠四活三		分数50000
				else if (borad_weights[i][j] < 25000 && ziji.player_qixing.huosan >= 2)
					borad_weights[i][j] = 25000;										//双活三				分数25000
				else if (borad_weights[i][j] < 5000 && ziji.player_qixing.huosan == 1 && ziji.player_qixing.miansan >= 1)
					borad_weights[i][j] = 5000;											//活三眠三				分数5000
				else if (borad_weights[i][j] < 200 && ziji.player_qixing.huoer >= 2)
					borad_weights[i][j] = 200;											//双活二				分数200
				else if (borad_weights[i][j] < 50 && ziji.player_qixing.huoer == 1 && ziji.player_qixing.mianer >= 1)
					borad_weights[i][j] = 50;											//活二眠二				分数50

				//相同棋型，电脑分数高，即相同棋型下电脑优先进攻
				//上面为电脑分数判断	
				//———————————————————————我是分割线————————————————————————//
				//下面为玩家分数判断
				qipan[i][j] = other_color;												//假设玩家在该点落子	玩家为黑棋


				player duishou = { 0 };
				duishou.player_qixing = { 0, 0, 0, 0, 0, 800, 80, 8, -4 };
				duishou.player_color = other_color;										//初始化颜色

				fangxiang ds_heng = { 0 }, ds_shu = { 0 }, ds_zuoxie = { 0 }, ds_youxie = { 0 };

				duishou.player_fangxiang = &ds_heng;									//横向判断
				duishou.player_fangxiang->mianqi = 1;									//判断该点是否为眠棋，0否  1是
				a = i, b = j;															//临时x,y坐标
				for (b = j; b <= j + 4; b++)											//向右搜索,确定右边界			电脑横向判断
				{
					if (b > 14)
						break;															//越界，结束循环
					if (qipan[a][b] != duishou.player_color && qipan[a][b] != 0)
						break;															//遇到非己方子，结束循环
				}
				b--;																	//调整x坐标

				for (duishou.player_fangxiang->weishu = 0; (qipan[a][b] == duishou.player_color || qipan[a][b] == 0)
					&& b >= 0 && b >= j - 4; b--, duishou.player_fangxiang->weishu++)
				{																		//遇到非己方子，越界，超过范围，结束循环
					if (qipan[a][b] == duishou.player_color)
					{
						duishou.player_fangxiang->qi |= 1 << duishou.player_fangxiang->weishu;	//记方棋子，记为1
						duishou.player_fangxiang->qishu++;								//计算己方棋子数
					}
				}
				pipei(qixingku, pqixingku_score, &duishou);



				duishou.player_fangxiang = &ds_shu;										//竖向判断
				duishou.player_fangxiang->mianqi = 1;									//判断该点是否为眠棋，0否  1是
				a = i, b = j;
				for (a = i; a <= i + 4; a++)											//向下搜索,确定下边界			电脑竖向判断
				{
					if (a > 14)
						break;															//越界，结束循环
					if (qipan[a][b] != duishou.player_color && qipan[a][b] != 0)
						break;															//遇到非己方子，结束循环
				}
				a--;																	//调整y坐标

				for (duishou.player_fangxiang->weishu = 0; (qipan[a][b] == duishou.player_color || qipan[a][b] == 0)
					&& a >= 0 && a >= i - 4; a--, duishou.player_fangxiang->weishu++)
				{																		//遇到非己方子，越界，超过范围，结束循环
					if (qipan[a][b] == duishou.player_color)
					{
						duishou.player_fangxiang->qi |= 1 << duishou.player_fangxiang->weishu;	//己方棋子，记为1
						duishou.player_fangxiang->qishu++;								//计算己方棋子数
					}
				}
				pipei(qixingku, pqixingku_score, &duishou);								//与棋形库匹配打分



				duishou.player_fangxiang = &ds_zuoxie;									//左斜判断
				duishou.player_fangxiang->mianqi = 1;									//判断该点是否为眠棋，0否  1是
				a = i, b = j;
				for (a = i, b = j; a <= i + 4 && b <= j + 4; a++, b++)					//向右下搜索,确定右下边界		电脑左斜判断
				{
					if (a > 14 || b > 14)
						break;															//越界，结束循环
					if (qipan[a][b] != duishou.player_color && qipan[a][b] != 0)
						break;															//遇到非己方子，结束循环
				}
				a--, b--;																//调整y,x坐标

				for (duishou.player_fangxiang->weishu = 0; (qipan[a][b] == duishou.player_color || qipan[a][b] == 0)
					&& b >= 0 && b >= j - 4 && a >= 0 && a >= i - 4; b--, a--, duishou.player_fangxiang->weishu++)
				{																		//遇到非己方子，越界，超过范围，结束循环
					if (qipan[a][b] == duishou.player_color)
					{
						duishou.player_fangxiang->qi |= 1 << duishou.player_fangxiang->weishu;	//记方棋子，记为1
						duishou.player_fangxiang->qishu++;								//计算己方棋子数
					}
				}
				pipei(qixingku, pqixingku_score, &duishou);								//与棋形库匹配打分



				duishou.player_fangxiang = &ds_youxie;									//右斜判断
				duishou.player_fangxiang->mianqi = 1;									//判断该点是否为眠棋，0否  1是
				a = i, b = j;
				for (a = i, b = j; a <= i + 4 && b >= j - 4; a++, b--)					//向左下搜索,确定左下边界		电脑右斜判断
				{
					if (a > 14 || b < 0)
						break;															//越界，结束循环
					if (qipan[a][b] != duishou.player_color && qipan[a][b] != 0)
						break;															//遇到非己方子，结束循环
				}
				a--, b++;																//调整y,x坐标

				for (duishou.player_fangxiang->weishu = 0; (qipan[a][b] == duishou.player_color || qipan[a][b] == 0)
					&& b <= 14 && b <= j + 4 && a >= 0 && a >= i - 4; b++, a--, duishou.player_fangxiang->weishu++)
				{																		//遇到非己方子，越界，超过范围，结束循环
					if (qipan[a][b] == duishou.player_color)
					{
						duishou.player_fangxiang->qi |= 1 << duishou.player_fangxiang->weishu;	//记方棋子，记为1
						duishou.player_fangxiang->qishu++;								//计算己方棋子数
					}
				}
				pipei(qixingku, pqixingku_score, &duishou);								//与棋形库匹配打分


				//玩家在该点落子的分数
				int lingshifenshu = 0;
				lingshifenshu = ds_heng.max_score + ds_shu.max_score + ds_zuoxie.max_score + ds_youxie.max_score;

				//组合棋型判断
				if (lingshifenshu < 40000 && (duishou.player_qixing.miansi >= 2 || (duishou.player_qixing.miansi >= 1 && duishou.player_qixing.huosan >= 1)))
					lingshifenshu = 40000;												//双眠四，眠四活三		分数40000
				else if (lingshifenshu < 20000 && duishou.player_qixing.huosan >= 2)
					lingshifenshu = 20000;												//双活三				分数20000
				else if (lingshifenshu < 4000 && duishou.player_qixing.huosan == 1 && duishou.player_qixing.miansan >= 1)
					lingshifenshu = 4000;												//活三眠三				分数4000
				else if (lingshifenshu < 160 && duishou.player_qixing.huoer >= 2)
					lingshifenshu = 160;												//双活二				分数160
				else if (lingshifenshu < 40 && duishou.player_qixing.huoer == 1 && duishou.player_qixing.mianer >= 1)
					lingshifenshu = 40;													//活二眠二				分数40



				//——————————————————————我是分割线——————————————————————————//

				borad_weights[i][j] += lingshifenshu;									//该点的总分数,双方评分加棋盘位置分数

				if (0.9 * max_score <= borad_weights[i][j])								//查找在最高分数一定范围内的点	0.9max-max
				{
					if (max_num < 100)													//防止越界
					{
						max_num++;														//记录最高分数范围内点的个数
						max_score_x[max_num - 1] = j;
						max_score_y[max_num - 1] = i;
					}
				}

				if (max_score < borad_weights[i][j])
				{																		//找出新的最高分数点
					max_score = borad_weights[i][j];									//记录新的最高分
					max_num = 1;														//最高分个数置1
					max_score_x[0] = 0, max_score_y[0] = 0;								//最高分坐标清空

					max_score_x[0] = j;													//记录该最高分的坐标
					max_score_y[0] = i;
				}

				qipan[i][j] = 0;												 		//清除假设落的子
			}
		}
	}
	int max_x = 0, max_y = 0;															//最终将要落子的坐标
	int rn = 0;																			//随机数rn

	if (max_num > 1)																	//如果最高分不止一个
	{
		rn = rand() % max_num;															//产生随机数
		max_x = max_score_x[rn];														//从中随机选中一个点作为最终落子点
		max_y = max_score_y[rn];
	}
	else																				//最高分只有一个
	{
		max_x = max_score_x[0];															//此点为最终落子点
		max_y = max_score_y[0];
	}

	if (count == 1)																		//电脑走第一步的情况
	{
		max_x = rand() % 5 + 5;
		max_y = rand() % 5 + 5;
	}

	bianjie(&tymin, &txmin, &tymax, &txmax, max_y, max_x);								//更新棋局搜索范围

	*x = max_x;																			//已找到最大分数点坐标，传回坐标
	*y = max_y;

	return max_score;
}


int bianjie(int* tymin, int* txmin, int* tymax, int* txmax, int y, int x)				//落子点边界查找范围
{
	if (*tymin == 7 && *txmin == 7 && *tymax == 7 && *txmax == 7)
	{
		*tymin = y - 1;
		*tymax = y + 1;
		*txmin = x - 1;
		*txmax = x + 1;
	}
	else
	{
		if (y <= *tymin)
		{
			if (y <= 1)
				*tymin = 0;
			else
				*tymin = y - 1;
		}
		if (y >= *tymax)
		{
			if (y >= 13)
				*tymax = 14;
			else
				*tymax = y + 1;
		}

		if (x <= *txmin)
		{
			if (x <= 1)
				*txmin = 0;
			else
				*txmin = x - 1;
		}
		if (x >= *txmax)
		{
			if (x >= 13)
				*txmax = 14;
			else
				*txmax = x + 1;
		}
	}
	return 0;
}


int pipei(const int qixingku[14], const int qixingku_score[14], player* computer)		//匹配棋形库，进行打分
{

	if (computer->player_fangxiang->weishu >= 6)										//可进行棋形库匹配
	{
		for (int t = computer->player_fangxiang->weishu - 6; t >= 0; t--)				//控制移动后的
		{
			for (int n = 0; n < 14; n++)												//控制棋形库匹配
			{
				const int h = computer->player_fangxiang->qi;
				if (((h >> t) & 077) == qixingku[n])									//位操作移动后进行匹配棋形库
				{
					computer->player_fangxiang->mianqi = 0;								//匹配成功是活棋，不是眠棋
					if (computer->player_fangxiang->max_score < qixingku_score[n])		//若分数小于即将获得的分数
						computer->player_fangxiang->max_score = qixingku_score[n];		//获得新的棋形库对应得分
					break;
				}
			}
		}
		if (computer->player_fangxiang->max_score == qixingku_score[4])					//根据最大分数判断
			computer->player_qixing.huosan++;											//活三个数加一
		if (computer->player_fangxiang->max_score == qixingku_score[8])
			computer->player_qixing.huoer++;											//活二个数加一
	}
	else if (computer->player_fangxiang->weishu == 5 && computer->player_fangxiang->qishu == 5)
	{																					//两边都被堵着的长连
		computer->player_fangxiang->max_score = qixingku_score[0];						//长连的对应分数
		computer->player_fangxiang->mianqi = 0;											//长连，不是眠棋
	}
	else if (computer->player_fangxiang->weishu <= 4)									//死棋
	{
		computer->player_fangxiang->max_score = computer->player_qixing.siqi_score;		//分数-5
		computer->player_fangxiang->mianqi = 0;											//是死棋，不是眠棋
	}
	if (computer->player_fangxiang->mianqi)												//以上情况都不是，则是眠棋
	{
		if (computer->player_fangxiang->qishu == 4)										//眠四
		{
			computer->player_fangxiang->max_score = computer->player_qixing.miansi_score;//眠四对应分数
			computer->player_qixing.miansi++;											//眠四个数加一
		}
		else if (computer->player_fangxiang->qishu == 3)								//眠三
		{
			computer->player_fangxiang->max_score = computer->player_qixing.miansan_score;//眠三对应分数
			computer->player_qixing.miansan++;											//电脑眠三个数加一
		}
		else if (computer->player_fangxiang->qishu == 2)								//眠二
		{
			computer->player_fangxiang->max_score = computer->player_qixing.mianer_score;//眠二对应分数
			computer->player_qixing.mianer++;											//电脑眠二个数加一
		}
	}
	return 0;
}




int judge(int arry[15][15], int y, int x, int bw)										//输赢判断
{
	int tempmix = 0, tempmiy = 0;
	int tempmax = 0, tempmay = 0;
	int num = 0;
	int i = 0, j = 0;

	if (x > 4)																			//确定横竖边界
		tempmix = x - 4;
	else
		tempmix = 0;

	if (x >= 10)
		tempmax = 14;
	else
		tempmax = x + 4;

	if (y > 4)
		tempmiy = y - 4;
	else
		tempmiy = 0;

	if (y >= 10)
		tempmay = 14;
	else
		tempmay = y + 4;

	for (j = tempmix + 1, num = 0; j <= tempmax; j++)									//横向判断				
	{
		if ((arry[y][j - 1] == arry[y][j]) && (arry[y][j] == bw))
			num++;
		else
			num = 0;
		if (num >= 4)																	//连续五个子相连，该棋子赢
			return 1;
	}

	for (i = tempmiy + 1, num = 0; i <= tempmay; i++)									//竖向判断
	{
		if ((arry[i - 1][x] == arry[i][x]) && (arry[i][x] == bw))
			num++;
		else
			num = 0;
		if (num >= 4)																	//连续五个子相连，该棋子赢
			return 1;
	}

	for (tempmix = x, tempmiy = y; tempmix - 1 >= 0 && tempmiy - 1 >= 0; tempmix--, tempmiy--)
	{
		;																				//确定左斜左上顶点位置
	}


	for (i = tempmiy + 1, j = tempmix + 1, num = 0; i <= y + 4 && j <= x + 4 && i <= 14 && j <= 14; i++, j++)
	{																					//左斜判断
		if ((arry[i - 1][j - 1] == arry[i][j]) && (arry[i][j] == bw))
			num++;
		else
			num = 0;
		if (num >= 4)																	//连续五个子相连，该棋子赢
			return 1;
	}

	for (tempmax = x, tempmiy = y; tempmax + 1 <= 14 && tempmiy - 1 >= 0; tempmax++, tempmiy--)
	{
		;																				//确定右斜右上顶点位置
	}

	for (i = tempmiy + 1, j = tempmax - 1, num = 0; i <= y + 4 && j >= x - 4 && i <= 14 && j >= 0; i++, j--)
	{																					//右斜判断
		if ((arry[i - 1][j + 1] == arry[i][j]) && (arry[i][j] == bw))
			num++;
		else
			num = 0;
		if (num >= 4)																	//连续五个子相连，该棋子赢
			return 1;
	}
	return 0;
}


int win_lose(int bw)																	//输赢显示
{
	const TCHAR* s0 = _T("平局！");
	const TCHAR* s1 = _T("黑棋胜！"), *s2 = _T("白棋胜！"), *s3 = _T("哎呦，小伙子可以啊，恭喜你没输！"), *s4 = _T("你又输了，太菜了！");
	const TCHAR* c0 = _T("黑棋胜!(电脑)"), *c1 = _T("白棋胜!(电脑)");
	const TCHAR* s5 = _T("错误！");
	if (bw < 4)
	{
		setlinecolor(0X000000);															//设置当前画线色
		setfillcolor(0XFFFFFF);															//设置当前填充色
		fillroundrect(220, 140, 520, 340, 150, 120);									//画圆角矩形
		settextcolor(0X5555FF);															//设置字体颜色
		setbkmode(TRANSPARENT);															//设置字体背景色，透明
		switch (bw)
		{
		case 0:outtextxy(345, 230, s0); break;
		case 1:outtextxy(345, 230, s1); break;
		case 2:outtextxy(345, 230, s2); break;
		case 3:outtextxy(250, 230, s3); break;
		case 4:outtextxy(335, 230, s4); break;
		default:outtextxy(345, 230, s5);
		}
		Sleep(3000);
	}
	else
	{
		settextcolor(0X5555FF);															//设置字体颜色
		setbkmode(TRANSPARENT);															//设置字体背景色，透明
		if (bw == 4)
			outtextxy(520, 360, s4);
		if (bw == 1040)
			outtextxy(520, 360, c0);
		if (bw == 1041)
			outtextxy(520, 360, c1);
		Sleep(5000);
	}
	return 0;
}



//Alpha剪枝和Beta剪枝+MaxMin搜索
int AlphaBeta(int depth, int alpha, int beta, AlpBet* AB)
{
	int ansx = 0;
	int ansy = 0;
	if (depth == DEPTH)
		return guzhi(AB->chbo, depth % 2 + 1, AB->tempy, AB->tempx, &(AB->y), &(AB->x), AB->count);	//估值函数
	if (judge(AB->blbo, AB->y, AB->x, 1))
		return 99999;
	if (judge(AB->whbo, AB->y, AB->x, 2))
		return -99999;


	if (depth & 1)																	//Max层,取子节点的极大值为本节点的alpha值,自己
	{
		int ans = AlphaBeta(depth + 1, alpha, beta, AB);

		/*if (AB->play == 1)
		guzhi(AB->chbo, 1, AB->tempy, AB->tempx, &(AB->y), &(AB->x), AB->count);
		else
		guzhi(AB->chbo, 2, AB->tempy, AB->tempx, &(AB->y), &(AB->x), AB->count);*/

		if (ans > alpha)
		{
			alpha = ans;																//通过子节点的beta值向上传递修正父节点的alpha值
			ansx = AB->x;																//记录坐标
			ansy = AB->y;
		}
		if (alpha >= beta)																//发生alpha剪枝
		{
			return alpha;
		}

		return alpha;
	}
	else																				//Min层,取子节点的极小值为本节点的beta值,对手
	{
		int ans = AlphaBeta(depth + 1, alpha, beta, AB);

		/*if (AB->play == 1)
		guzhi(AB->chbo, 1, AB->tempy, AB->tempx, &(AB->y), &(AB->x), AB->count);
		else
		guzhi(AB->chbo, 2, AB->tempy, AB->tempx, &(AB->y), &(AB->x), AB->count);*/

		if (ans < beta)
		{
			beta = ans;
			ansx = AB->x;
			ansy = AB->y;
		}
		if (alpha >= beta)
		{
			return beta;
		}

		return beta;
	}

}




int main()
{
	while (1)
	{
		menu();																			//主菜单界面
	}
	return 0;
}