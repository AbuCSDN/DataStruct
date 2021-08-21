#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<tchar.h>
#include<time.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


constexpr int DEPTH = 5;																//����������


typedef struct FX																		//����
{
	int qi;																				//ĳ����Ķ���������	
	int max_score;																		//ĳ�����������
	int weishu;																			//ĳ����ļ���������հ׵��ܸ���
	int qishu;																			//ĳ����ļ���������
	int mianqi;																			//�ж�ĳ�����Ƿ�Ϊ����
}fangxiang;


typedef struct QX																		//���ͼ�ĳЩ���Ͷ�Ӧ����
{
	int huosan;																			//����
	int huoer;
	int miansi;
	int miansan;
	int mianer;

	int miansi_score;																	//����
	int miansan_score;
	int mianer_score;
	int siqi_score;
}qixing;


typedef struct Player																	//���(����)
{
	qixing player_qixing;
	fangxiang* player_fangxiang;
	int player_color;
}player;

typedef struct alphabeta
{
	int blbo[15][15];																	//��������
	int whbo[15][15];																	//��������
	int chbo[15][15];																	//������
	int play;																			//�����
	int count;																			//�غ���
	int tempx;																			//��ʱx����
	int tempy;																			//��ʱy����
	int y;																				//x����
	int x;																				//y����
}AlpBet;


int function_1();																		//����һ
int function_2();																		//���ܶ�
int function_3();																		//�˳�
int funcyion_ceshi();																	//���ز��Թ���
int draw(int);																			//�����̽���
int difficulty();																		//�˻��Ѷ�ѡ��
int playchess_1();																		//���˶���
int playchess_2();																		//�˻�����(���Ѷ�)
int playchess_22(int dif);																//�˻�����(��ͨ/�����Ѷ�)
int playchess_ceshi();																	//���Զ�ս
int guzhi(int qipan[15][15], int color, int by, int bx, int* y, int* x, int count);		//���̣���ɫ,�Է��������꣬���Խ�Ҫ���ӵ�����,�غ���
int pipei(const int qixingku[14], const int qixingku_score[14], player*);				//ƥ�����ο���д��
int bianjie(int* tymin, int* txmin, int* tymax, int* txmax, int y, int x);				//���ӵ�߽���ҷ�Χ
int judge(int arry[15][15], int, int, int);												//��Ӯ�ж�
int win_lose(int);																		//ʤ����ʾ
int Music(const wchar_t Music_Name[]);													//��������
int set_music(int music_xy[15][15]);													//��ʼ����Ƶ���ñ�

int AlphaBeta(int depth, int alpha, int beta, AlpBet* AB);								//alpha-beta��֦�㷨


int Music(const WCHAR Music_Name[])
{
	PlaySound(Music_Name, nullptr, SND_NODEFAULT | SND_ASYNC);							//�첽���β���
	return 1;
}

int set_music(int music_xy[15][15])
{
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
		music_xy[i][j] = rand() % 88;
	return 0;
}


int menu()																				//�˵�
{
	IMAGE img;
	MOUSEMSG m{};																		// ���������Ϣ
	const TCHAR* s0 = _T("������"), *s1 = _T("���˶���"), *s2 = _T("�˻�����"), *s3 = _T("�˳�");
	TCHAR bgm[40] = L"��Ƶ�ļ�\\BGM(0).wav";											//������
	int temp = 0;
	const int MUSIC_NUM = 5;															//BGM��
	int music_num = 0;
	int music_length[MUSIC_NUM] = { 112, 118, 148, 195, 138 };								//��BGMʱ��
	int t0 = 0;																			//���ֿ�ʼʱ��
	initgraph(740, 480, NOCLOSE);													    //��ʼ����ͼ����
	loadimage(&img, _T("������0X68.png"), 740, 480, true);								//����ͼƬ��ַ���ļ���ַ����ͼƬ�������˳���
	putimage(0, 0, &img);																//���Ƹ�ͼƬ
	srand(time(nullptr) & 0xffffffff);

	while (1)
	{
		if (!temp)
		{
			putimage(0, 0, &img);
			setlinecolor(0XAAAAAA);														//���õ�ǰ������ɫ
			rectangle(320, 150, 420, 200);												//�����ľ���
			rectangle(110, 300, 210, 350);
			rectangle(320, 300, 420, 350);
			rectangle(530, 300, 630, 350);
			settextcolor(0XFF55FF);														//����������ɫ
			setbkmode(TRANSPARENT);														//�������屳��ɫ��͸��
			outtextxy(345, 165, s0);													//��ָ��λ������ַ���
			outtextxy(130, 315, s1);
			outtextxy(340, 315, s2);
			outtextxy(565, 315, s3);

			t0 = time(nullptr);
			music_num = rand() % MUSIC_NUM;
			_stprintf_s(bgm, 40, L"��Ƶ�ļ�\\BGM(%d).wav", music_num);
			Music(bgm);

		}

		if (((t0 + music_length[music_num]) < time(nullptr) - 3))
		{
			t0 = time(nullptr);
			music_num = rand() % MUSIC_NUM;
			_stprintf_s(bgm, 40, L"��Ƶ�ļ�\\BGM(%d).wav", music_num);
			Music(bgm);
		}

		m = GetMouseMsg();																//���һ�����Ľṹ��
		if (m.x >= 110 && m.x <= 210 && m.y >= 300 && m.y <= 350 && m.mkLButton)		//�ж��Ƿ����ù���һ
		{
			temp = function_1();														//����һ
			continue;
		}
		if (m.x >= 320 && m.x <= 420 && m.y >= 300 && m.y <= 350 && m.mkLButton)		//�ж��Ƿ����ù��ܶ�
		{
			temp = function_2();														//���ܶ�
			continue;
		}

		if (m.mkRButton && m.x >= 320 && m.x <= 420 && m.y >= 150 && m.y <= 200)		//�Ҽ������壬������Զ�ս���ԵĲ��Թ���
		{
			temp = funcyion_ceshi();													//���Զ�ս���ԵĲ��Թ���
			continue;
		}


		temp = 1;																		//�޲��������ֻ���
		if (m.x >= 530 && m.x <= 630 && m.y >= 300 && m.y <= 350 && m.mkLButton)		//�ж��Ƿ����ù�����
			function_3();																//������
	}
	return 0;
}



int function_1()																		//����һ
{
	draw(1);																			//���˶���ģʽ
	playchess_1();
	return 0;
}



int function_2()																		//���ܶ�
{
	int diff = 21;
	diff = difficulty();
	draw(diff);
	if (diff == 21)
		playchess_2();																	//�˻�����ģʽ
	if (diff == 22)
		playchess_22(4);
	return 0;
}



int function_3()
{
	const TCHAR* t1 = _T("���˳���");
	setlinecolor(0X000000);																//���õ�ǰ����ɫ
	setfillcolor(0XFFFFFF);																//���õ�ǰ���ɫ
	fillroundrect(220, 140, 520, 340, 150, 120);										//��Բ�Ǿ���
	settextcolor(0X5555FF);																//����������ɫ
	setbkmode(TRANSPARENT);																//�������屳��ɫ��͸��
	outtextxy(345, 230, t1);
	Sleep(1000);
	closegraph();
	exit(0);
}


int funcyion_ceshi()
{
	draw(104);																			//����ģʽ
	playchess_ceshi();
	return 0;
}



int draw(int mode)																		//�����̽���
{
	const TCHAR* mode_1 = _T("ģʽ:                ���˶���"), *mode_21 = _T("ģʽ:                �˻�����(����)");
	const TCHAR* mode_22 = _T("ģʽ:                �˻�����(�м�)"), *mode_23 = _T("ģʽ:                �˻�����(�߼�)");
	const TCHAR* mode_ceshi = _T("ģʽ:                ���Զ�ս(����)");
	const TCHAR* chess_player = _T("��ǰ����:");
	const TCHAR* round = _T("�غ���:");
	const TCHAR* quit = _T("����");
	setbkcolor(RGB(222, 184, 135));														//���ñ���ɫ,��ɫ�����̱���ɫ
	cleardevice();																	    //�������̱���ɫ
	setlinecolor(0X000000);																//�������̻�����ɫ����ɫ
	for (int i = 0; i < 15; i++)														//������
	{
		line(30, 30 + i * 30, 450, 30 + i * 30);										//���̼����30
		line(30 + i * 30, 30, 30 + i * 30, 450);
	}
	setfillcolor(0X000000);																//�������ɫ����ɫ
	solidcircle(120, 120, 3);															//���������С�ڵ�
	solidcircle(360, 120, 3);
	solidcircle(240, 240, 3);
	solidcircle(120, 360, 3);
	solidcircle(360, 360, 3);

	setfillcolor(0XFFFFFF);																//�����ұ߰�ɫ����
	solidrectangle(480, 0, 740, 480);

	setfillcolor(0XAAAAAA);																//���ذ�ť����ɫ
	solidrectangle(670, 415, 720, 440);													//���ذ�ť����

	settextcolor(0X000000);																//����������ɫ
	setbkmode(TRANSPARENT);																//�������屳��ɫ��͸��
	if (mode == 1)																		//���˶���ģʽ
		outtextxy(520, 20, mode_1);
	else if (mode == 21)
		outtextxy(520, 20, mode_21);													//�˻����ģ�����
	else if (mode == 22)
		outtextxy(520, 20, mode_22);													//�˻����ġ��м�
	else if (mode == 23)
		outtextxy(520, 20, mode_23);													//�˻����ģ��߼�
	else if (mode == 104)
		outtextxy(520, 20, mode_ceshi);													//���Զ�ս(����)
	outtextxy(520, 150, chess_player);													//����
	outtextxy(520, 280, round);															//�غ���
	outtextxy(680, 420, quit);															//���ذ�ť
	return 0;
}

int difficulty()																		//�˻������Ѷ�ѡ��
{
	MOUSEMSG mc = {};																		//���������Ϣ
	const TCHAR* c0 = _T("��ѡ������Ѷ�:"), *c1 = _T("����"), *c2 = _T("�м�"), *c3 = _T("�߼�");
	setlinecolor(0X000000);																//���õ�ǰ����ɫ
	setfillcolor(0XFFFFFF);																//���õ�ǰ���ɫ
	fillroundrect(180, 120, 560, 360, 150, 150);										//��Բ�Ǿ���
	settextcolor(0X5555FF);																//����������ɫ
	setbkmode(TRANSPARENT);																//�������屳��ɫ��͸��

	rectangle(250, 265, 300, 290);														//�����ľ���
	rectangle(350, 265, 400, 290);
	rectangle(450, 265, 500, 290);

	outtextxy(320, 180, c0);
	outtextxy(260, 270, c1);
	outtextxy(360, 270, c2);
	outtextxy(460, 270, c3);

	do
	{
		mc = GetMouseMsg();																//���һ�����Ľṹ��

		if (mc.mkLButton && mc.x > 250 && mc.x < 300 && mc.y>265 && mc.y < 290)
			return 21;
		if (mc.mkLButton && mc.x > 350 && mc.x < 400 && mc.y>265 && mc.y < 290)
			return 22;
		if (mc.mkLButton && mc.x > 450 && mc.x < 500 && mc.y>265 && mc.y < 290)
			return 23;

	} while (1);
	return 21;																			//Ĭ��Ϊ����
}



int playchess_1()																		//���˶���ʵ��
{
	Music(L"NULL");																		//ֹͣ����

	int player = 0;																		//��ұ�־
	int round_count = 1;																//�غ�������
	int tempx = 0, tempy = 0;															//��ʱx,y����
	int chessboard[15][15] = { 0 };														//��ʼ��������Ϣ
	int black_board[15][15] = { 0 };													//��ʼ���������
	int white_board[15][15] = { 0 };													//��ʼ���������
	int music_borad[15][15] = { 0 };													//��Ƶ��Ϣ���ձ�
	MOUSEMSG m_1{};																		//���������Ϣ
	const TCHAR* player_name_black = _T("����"), *player_name_white = _T("����");
	TCHAR round_num[20] = _T("");
	TCHAR music_name[40] = _T("");

	settextcolor(0X000000);																//����������ɫ
	setbkmode(TRANSPARENT);																//�������屳��ɫ��͸��
	setfillcolor(0XFFFFFF);
	int flag = 1;																		//�ж�����Ƿ�仯
	set_music(music_borad);																//��ʼ����Ƶ��Ϣ���ձ�

	do
	{
		if (flag)
		{
			setfillcolor(0XFFFFFF);														//ʹ�ñ���ɫ����ϴ���ʾ����
			solidrectangle(610, 140, 700, 170);											//�������

			if (player == 0)
				outtextxy(620, 150, player_name_black);									//��ʾ��ǰΪ����
			if (player == 1)
				outtextxy(620, 150, player_name_white);									//��ʾ��ǰΪ����


			_stprintf_s(round_num, 20, _T("��%d�غ�"), round_count);
			solidrectangle(610, 270, 700, 300);
			outtextxy(620, 280, round_num);												//��ӡ�غ���

			if (round_count > 225)														//�жϻغ����Ƿ���������
			{
				win_lose(0);															//ƽ��
				break;
			}
			flag = 0;
		}
		m_1 = GetMouseMsg();															//���һ�����Ľṹ��
		//���õ�Ϊ���㣬�������ϴ˴����ӣ����������
		if (m_1.mkLButton && (m_1.x >= 20 && m_1.x <= 460 && m_1.y >= 20 && m_1.y <= 460)
			&& (m_1.x % 30 <= 10 || m_1.x % 30 >= 20) && (m_1.y % 30 <= 10 || m_1.y % 30 >= 20)
			&& chessboard[m_1.y / 30 - 1 + (m_1.y % 30) / 20][m_1.x / 30 - 1 + (m_1.x % 30) / 20] == 0)
		{																				//�ڽ����԰�߳�Ϊ10�������������������
			int x = m_1.x / 30 - 1 + (m_1.x % 30) / 20;									//���岢��������
			int y = m_1.y / 30 - 1 + (m_1.y % 30) / 20;									//���岢��������

			if (round_count > 1)
			{
				if (!player == 0)
				{
					setfillcolor(0X000000);												//����С����ɫ,��ɫ
					solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);					//��պ��
				}
				else
				{
					setfillcolor(0XFFFFFF);												//����С����ɫ,��ɫ
					solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);					//��պ��
				}
			}
			tempx = x, tempy = y;														//��¼���ӵ�

			if (player == 0)															//��������(������ӣ�
			{
				chessboard[y][x] = 1;													//���̼�¼
				black_board[y][x] = 1;													//�����ڴ����ӣ�����Ϊ1
				setfillcolor(0X000000);													//����������ɫ,��ɫ
				solidcircle((x + 1) * 30, (y + 1) * 30, 10);							//����ɫ����

				_stprintf_s(music_name, 40, _T("��Ƶ�ļ�\\sounds (%d).wav"), music_borad[x][y]);//������Ƶ�ļ�����Ϣ
				Music(music_name);

				setfillcolor(0X5555FF);													//���������ɫ
				solidcircle((x + 1) * 30, (y + 1) * 30, 3);								//��С���

				if (judge(black_board, y, x, 1))										//�жϺ����Ƿ�ʤ
				{
					win_lose(1);														//����ʤ
					break;
				}
				player = !player;														//���Է�����
				flag = 1;
			}
			else if (player == 1)														//���壨���ԣ�����
			{																			//��������
				chessboard[y][x] = 2;													//���̼�¼
				white_board[y][x] = 2;													//�����ڴ����ӣ�����Ϊ2
				setfillcolor(0XFFFFFF);													//����������ɫ����ɫ
				solidcircle((x + 1) * 30, (y + 1) * 30, 10);							//����ɫ����

				_stprintf_s(music_name, 40, _T("��Ƶ�ļ�\\sounds (%d).wav"), music_borad[x][y]);//������Ƶ�ļ�����Ϣ
				Music(music_name);

				setfillcolor(0X5555FF);													//���������ɫ
				solidcircle((x + 1) * 30, (y + 1) * 30, 3);								//��С���

				if (judge(white_board, y, x, 2))										//�жϰ����Ƿ�ʤ
				{
					win_lose(2);														//����ʤ
					break;
				}
				player = !player;														//���Է�����
				flag = 1;
			}
			round_count++;
		}
		if (m_1.mkLButton && m_1.x >= 670 && m_1.x <= 720 && m_1.y >= 415 && m_1.y <= 440)
			break;																		//���ذ�ť
	} while (1);
	return 0;
}



int playchess_ceshi()																	//���Զ���ʵ��
{
	Music(L"NULL");																		//ֹͣ����

	int player = 0;																		//��ұ�־
	int round_count = 1;																//�غ�������
	int tempx = 0, tempy = 0;															//��ʱx,y����
	int chessboard[15][15] = { 0 };														//��ʼ��������Ϣ
	int black_board[15][15] = { 0 };													//��ʼ���������
	int white_board[15][15] = { 0 };													//��ʼ���������
	int no[15][15] = { 0 };																//���������ӵĵ�
	int music_borad[15][15] = { 0 };													//��Ƶ��Ϣ���ձ�
	const TCHAR* computer_ceshi_black = _T("����(����)"), *computer_ceshi_white = _T("����(����)");
	TCHAR round_num[20] = _T("");
	TCHAR music_name[40] = _T("");
	AlpBet AB = {};																		//alpha-beta�㷨��Ҫ��������Ϣ

	settextcolor(0X000000);																//����������ɫ
	setbkmode(TRANSPARENT);																//�������屳��ɫ��͸��
	setfillcolor(0XFFFFFF);

	int flag = 1;																		//�ж�����Ƿ�仯
	int biaozhi = 0;																	//��¼�Ƿ���Ҹ�����
	int x = 0, y = 0;
	set_music(music_borad);																//��ʼ����Ƶ��Ϣ���ձ�

	do
	{
		if (flag)
		{
			setfillcolor(0XFFFFFF);														//ʹ�ñ���ɫ����ϴ���ʾ����
			solidrectangle(610, 140, 700, 170);											//�������

			if (player == 0)
				outtextxy(620, 150, computer_ceshi_black);								//��ʾΪ����(����)
			if (player == 1)
				outtextxy(620, 150, computer_ceshi_white);								//��ʾΪ����(����)


			_stprintf_s(round_num, 20, _T("��%d�غ�"), round_count);
			solidrectangle(610, 270, 700, 300);
			outtextxy(620, 280, round_num);												//��ӡ�غ���

			if (round_count > 225)														//�жϻغ����Ƿ���������
			{
				win_lose(0);															//ƽ��
				break;
			}
			flag = 0;
		}

		if (player == 0 && biaozhi == 0)
		{
			guzhi(chessboard, 1, tempy, tempx, &y, &x, round_count);					//��ֵ����
			Sleep(500);

			if (round_count > 1)														//��һ�β�����
			{
				setfillcolor(0XFFFFFF);													//����С����ɫ,��ɫ
				solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);						//��պ��

			}

			tempx = x, tempy = y;

			chessboard[y][x] = 1;														//���̼�¼
			black_board[y][x] = 1;														//�����ڴ����ӣ�����Ϊ1
			setfillcolor(0X000000);														//����������ɫ,��ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//����ɫ����

			_stprintf_s(music_name, 40, _T("��Ƶ�ļ�\\sounds (%d).wav"), music_borad[x][y]);//������Ƶ�ļ�����Ϣ
			Music(music_name);															//��������

			setfillcolor(0X5555FF);														//���������ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//��С���

			if (judge(black_board, y, x, 1))											//�жϺ����Ƿ�ʤ
			{
				win_lose(1040);															//����ʤ(���ʤ)
				break;
			}
			player = !player;															//���Է�����
			flag = 1;
			biaozhi = 1;
			round_count++;
		}
		else if (player == 1 && biaozhi == 1)											//���壨���ԣ�����
		{
			for (int i = 0; i < 15; i++)												//��ʼ��AB��Ϣ
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

			//guzhi(chessboard,2, tempy, tempx, &y, &x, round_count);					//��ֵ����
			Sleep(500);

			setfillcolor(0X000000);														//����С����ɫ,��ɫ
			solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);							//��պ��

			tempx = x, tempy = y;
			chessboard[y][x] = 2;														//���̼�¼
			white_board[y][x] = 2;														//�����ڴ����ӣ�����Ϊ2
			setfillcolor(0XFFFFFF);														//����������ɫ,��ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//����ɫ����

			_stprintf_s(music_name, 40, _T("��Ƶ�ļ�\\sounds (%d).wav"), music_borad[x][y]);//������Ƶ�ļ�����Ϣ
			Music(music_name);															//��������

			setfillcolor(0X5555FF);														//���������ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//��С���

			if (judge(white_board, y, x, 2))											//�жϰ����Ƿ�ʤ
			{
				win_lose(1041);															//����ʤ(����ʤ)
				break;
			}
			player = !player;															//���Է�����
			biaozhi = 0;
			flag = 1;
			round_count++;
		}
	} while (!_kbhit());
	_getch();
	return 0;
}





int playchess_2()																		//�˻�����ʵ�֣��򵥣�
{
	Music(L"NULL");																		//ֹͣ����

	int player = 0;																		//��ұ�־
	int round_count = 1;																//�غ�������
	int tempx = 0, tempy = 0;															//��ʱx,y����
	int chessboard[15][15] = { 0 };														//��ʼ��������Ϣ
	int black_board[15][15] = { 0 };													//��ʼ���������
	int white_board[15][15] = { 0 };													//��ʼ���������
	int no[15][15] = { 0 };																//���������ӵĵ�
	int music_borad[15][15] = { 0 };													//��Ƶ��Ϣ���ձ�
	MOUSEMSG m_2{};																		//���������Ϣ
	const TCHAR* player_name_player = _T("���(����)"), *player_name_computer = _T("����(����)");
	const TCHAR* easy = _T("����");
	const TCHAR* medium = _T("�м�");
	const TCHAR* advanced = _T("�߼�");
	TCHAR round_num[20] = _T("");
	TCHAR music_name[40] = _T("");
	settextcolor(0X000000);																//����������ɫ
	setbkmode(TRANSPARENT);																//�������屳��ɫ��͸��
	setfillcolor(0XFFFFFF);
	int flag = 1;																		//�ж�����Ƿ�仯
	set_music(music_borad);																//��ʼ����Ƶ��Ϣ���ձ�

	do
	{
		if (flag)
		{
			setfillcolor(0XFFFFFF);														//ʹ�ñ���ɫ����ϴ���ʾ����
			solidrectangle(610, 140, 700, 170);											//�������

			if (player == 0)
				outtextxy(620, 150, player_name_player);								//��ʾΪ���
			if (player == 1)
				outtextxy(620, 150, player_name_computer);								//��ʾΪ����

			_stprintf_s(round_num, 20, _T("��%d�غ�"), round_count);
			solidrectangle(610, 270, 700, 300);
			outtextxy(620, 280, round_num);												//��ӡ�غ���

			if (round_count > 225)														//�жϻغ����Ƿ���������
			{
				win_lose(0);															//ƽ��
				break;
			}
			flag = 0;
		}

		int biaozhi = 1;																//��¼�Ƿ���Ҹ�����
		m_2 = GetMouseMsg();															//���һ�����Ľṹ��
		//���õ�Ϊ���㣬�������ϴ˴����ӣ����������
		if (player == 0 && m_2.mkLButton 												//���壨��ң�����
			&& (m_2.x >= 20 && m_2.x <= 460 && m_2.y >= 20 && m_2.y <= 460)
			&& (m_2.x % 30 <= 10 || m_2.x % 30 >= 20) && (m_2.y % 30 <= 10 || m_2.y % 30 >= 20)
			&& chessboard[m_2.y / 30 - 1 + (m_2.y % 30) / 20][m_2.x / 30 - 1 + (m_2.x % 30) / 20] == 0)
		{																				//�ڽ����԰�߳�Ϊ10�������������������
			int x = m_2.x / 30 - 1 + (m_2.x % 30) / 20;									//���岢��������
			int y = m_2.y / 30 - 1 + (m_2.y % 30) / 20;									//���岢��������

			if (round_count > 1)														//��һ�β�����
			{
				setfillcolor(0XFFFFFF);													//����С����ɫ,��ɫ
				solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);						//��պ��

			}
			tempx = x, tempy = y;														//��¼���ӵ�
			//����(������ӣ�
			chessboard[y][x] = 1;														//���̼�¼
			black_board[y][x] = 1;														//�����ڴ����ӣ�����Ϊ1
			setfillcolor(0X000000);														//����������ɫ,��ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//����ɫ����

			_stprintf_s(music_name, 40, _T("��Ƶ�ļ�\\sounds (%d).wav"), music_borad[x][y]);//������Ƶ�ļ�����Ϣ
			Music(music_name);															//��������

			setfillcolor(0X5555FF);														//���������ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//��С���

			if (judge(black_board, y, x, 1))											//�жϺ����Ƿ�ʤ
			{
				win_lose(3);															//����ʤ(���ʤ)
				break;
			}
			player = !player;															//���Է�����
			flag = 1;
			biaozhi = 0;
			round_count++;
		}
		else if (player == 1 && biaozhi == 1)											//���壨���ԣ�����
		{
			setfillcolor(0X000000);														//����С����ɫ,��ɫ
			solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);							//��պ��

			int x = 0, y = 0;
			guzhi(chessboard, 2, tempy, tempx, &y, &x, round_count);					//��ֵ����

			tempx = x, tempy = y;														//��¼���ӵ�

			chessboard[y][x] = 2;														//���̼�¼
			white_board[y][x] = 2;														//�����ڴ����ӣ�����Ϊ2
			setfillcolor(0XFFFFFF);														//����������ɫ,��ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//����ɫ����

			_stprintf_s(music_name, 40, _T("��Ƶ�ļ�\\sounds (%d).wav"), music_borad[x][y]);//������Ƶ�ļ�����Ϣ
			Music(music_name);															//������Ƶ

			setfillcolor(0X5555FF);														//���������ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//��С���

			if (judge(white_board, y, x, 2))											//�жϰ����Ƿ�ʤ
			{
				win_lose(4);															//����ʤ(����ʤ)
				break;
			}
			player = !player;															//���Է�����
			flag = 1;
			round_count++;
		}

		if (m_2.mkLButton && m_2.x >= 680 && m_2.x <= 710 && m_2.y >= 420 && m_2.y <= 435)
			return 1;																	//���ذ�ť
	} while (1);
	return 0;
}



int playchess_22(int dif)																//�˻�����ʵ�֣���ͨ/�����Ѷȣ�
{
	Music(L"NULL");																		//ֹͣ����

	int player = 0;																		//��ұ�־
	int round_count = 1;																//�غ�������
	int tempx = 0, tempy = 0;															//��ʱx,y����
	int chessboard[15][15] = { 0 };														//��ʼ��������Ϣ
	int black_board[15][15] = { 0 };													//��ʼ���������
	int white_board[15][15] = { 0 };													//��ʼ���������
	int music_borad[15][15] = { 0 };													//��Ƶ��Ϣ���ձ�
	MOUSEMSG m_2{};																		//���������Ϣ
	const TCHAR* player_name_player = _T("���(����)"), *player_name_computer = _T("����(����)");
	const TCHAR* easy = _T("����");
	const TCHAR* medium = _T("�м�");
	const TCHAR* advanced = _T("�߼�");
	TCHAR round_num[20] = _T("");
	TCHAR music_name[40] = _T("");
	settextcolor(0X000000);																//����������ɫ
	setbkmode(TRANSPARENT);																//�������屳��ɫ��͸��
	setfillcolor(0XFFFFFF);
	int flag = 1;																		//�ж�����Ƿ�仯
	set_music(music_borad);																//��ʼ����Ƶ��Ϣ���ձ�
	AlpBet AB = {};																		//alpha-beta�㷨��Ҫ��������Ϣ


	do
	{
		if (flag)
		{
			setfillcolor(0XFFFFFF);														//ʹ�ñ���ɫ����ϴ���ʾ����
			solidrectangle(610, 140, 700, 170);											//�������

			if (player == 0)
				outtextxy(620, 150, player_name_player);								//��ʾΪ���
			if (player == 1)
				outtextxy(620, 150, player_name_computer);								//��ʾΪ����

			_stprintf_s(round_num, 20, _T("��%d�غ�"), round_count);
			solidrectangle(610, 270, 700, 300);
			outtextxy(620, 280, round_num);												//��ӡ�غ���

			if (round_count > 225)														//�жϻغ����Ƿ���������
			{
				win_lose(0);															//ƽ��
				break;
			}
			flag = 0;
		}

		int biaozhi = 1;																//��¼�Ƿ���Ҹ�����
		m_2 = GetMouseMsg();															//���һ�����Ľṹ��
		//���õ�Ϊ���㣬�������ϴ˴����ӣ����������
		if (player == 0 && m_2.mkLButton 												//���壨��ң�����
			&& (m_2.x >= 20 && m_2.x <= 460 && m_2.y >= 20 && m_2.y <= 460)
			&& (m_2.x % 30 <= 10 || m_2.x % 30 >= 20) && (m_2.y % 30 <= 10 || m_2.y % 30 >= 20)
			&& chessboard[m_2.y / 30 - 1 + (m_2.y % 30) / 20][m_2.x / 30 - 1 + (m_2.x % 30) / 20] == 0)
		{																				//�ڽ����԰�߳�Ϊ10�������������������
			int x = m_2.x / 30 - 1 + (m_2.x % 30) / 20;									//���岢��������
			int y = m_2.y / 30 - 1 + (m_2.y % 30) / 20;									//���岢��������

			if (round_count > 1)														//��һ�β�����
			{
				setfillcolor(0XFFFFFF);													//����С����ɫ,��ɫ
				solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);						//��պ��

			}
			tempx = x, tempy = y;														//��¼���ӵ�
			//����(������ӣ�
			chessboard[y][x] = 1;														//���̼�¼
			black_board[y][x] = 1;														//�����ڴ����ӣ�����Ϊ1
			setfillcolor(0X000000);														//����������ɫ,��ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//����ɫ����

			_stprintf_s(music_name, 40, _T("��Ƶ�ļ�\\sounds (%d).wav"), music_borad[x][y]);//������Ƶ�ļ�����Ϣ
			Music(music_name);															//��������

			setfillcolor(0X5555FF);														//���������ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//��С���

			if (judge(black_board, y, x, 1))											//�жϺ����Ƿ�ʤ
			{
				win_lose(3);															//����ʤ(���ʤ)
				break;
			}
			player = !player;															//���Է�����
			flag = 1;
			biaozhi = 0;
			round_count++;
		}
		else if (player == 1 && biaozhi == 1)											//���壨���ԣ�����
		{
			setfillcolor(0X000000);														//����С����ɫ,��ɫ
			solidcircle((tempx + 1) * 30, (tempy + 1) * 30, 3);							//��պ��

			int x = 0, y = 0;

			{for (int i = 0; i < 15; i++)												//��ʼ��AB��Ϣ
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
			//guzhi(chessboard,no, 2, tempy, tempx, &y, &x, round_count);				//��ֵ����
			tempx = x, tempy = y;														//��¼���ӵ�

			chessboard[y][x] = 2;														//���̼�¼
			white_board[y][x] = 2;														//�����ڴ����ӣ�����Ϊ2
			setfillcolor(0XFFFFFF);														//����������ɫ,��ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 10);								//����ɫ����

			_stprintf_s(music_name, 40, _T("��Ƶ�ļ�\\sounds (%d).wav"), music_borad[x][y]);//������Ƶ�ļ�����Ϣ
			Music(music_name);															//������Ƶ

			setfillcolor(0X5555FF);														//���������ɫ
			solidcircle((x + 1) * 30, (y + 1) * 30, 3);									//��С���

			if (judge(white_board, y, x, 2))											//�жϰ����Ƿ�ʤ
			{
				win_lose(4);															//����ʤ(����ʤ)
				break;
			}
			player = !player;															//���Է�����
			flag = 1;
			round_count++;
		}

		if (m_2.mkLButton && m_2.x >= 680 && m_2.x <= 710 && m_2.y >= 420 && m_2.y <= 435)
			return 1;																	//���ذ�ť
	} while (1);
	return 0;
}




//���̣���ɫ���Է��������꣬���Խ�Ҫ���ӵ����꣬�غ���
int guzhi(int qipan[15][15], int color, int by, int bx, int* y, int* x, int count)
{
	int borad_weights[15][15] = { 0 };					 								//��̬���̸����ܷ���
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
	//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };													//���̸���λ�÷���

	const static int qixingku[14] = { 077, 076, 037, 036, 016, 034, 026, 032, 014, 030, 006, 024, 012, 022 };				//���ο⣬�����ͣ����������ģ����������
	const static int cqixingku_score[14] = { 500000, 500000, 500000, 50000, 500, 500, 500, 500, 30, 30, 30, 30, 30, 30 };	//���ο��Ӧ���η������������������
	const static int pqixingku_score[14] = { 400000, 400000, 400000, 40000, 400, 400, 400, 400, 25, 25, 25, 25, 25, 25 };	//������ο����

	static int txmin = 7, tymin = 7, txmax = 7, tymax = 7;								//���̷�������ȷ���㣨��������ʹ�ã��������Խǵ㣬���ϣ�����
	if (count == 2)
		txmin = 7, tymin = 7, txmax = 7, tymax = 7;										//���ñ߽��

	bianjie(&tymin, &txmin, &tymax, &txmax, by, bx);									//ȷ�����ӵ�߽�

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

	int max_score = -999999;															//��¼��߷�
	int max_score_x[100] = { 0 }, max_score_y[100] = { 0 };								//��¼��߷���x,y����,����¼10��
	int max_num = 1;																	//��¼��߷ָ���,��ʼֵΪ1��������һ����

	int i = 0, j = 0;
	for (i = tymin; i <= tymax; i++)													//�����Ӿ��α߽緶Χ�ڲ�����������
	{
		for (j = txmin; j <= txmax; j++)
		{																				//�õ㸽���Ƿ�������
			if (qipan[i][j] == 0 &&
				(qipan[i][j - 1 > 0 ? j - 1 : 0] != 0 || qipan[i - 1 > 0 ? i - 1 : 0][j - 1 > 0 ? j - 1 : 0] != 0 ||
				qipan[i - 1 > 0 ? i - 1 : 0][j] != 0 || qipan[i - 1 > 0 ? i - 1 : 0][j + 1 < 14 ? j + 1 : 14] != 0 ||
				qipan[i][j + 1 < 14 ? j + 1 : 14] != 0 || qipan[i + 1 < 14 ? i + 1 : 14][j + 1 < 14 ? j + 1 : 14] != 0 ||
				qipan[i + 1 < 14 ? i + 1 : 14][j] != 0 || qipan[i + 1 < 14 ? i + 1 : 14][j - 1 > 0 ? j - 1 : 0] != 0))
			{																			//i��jλ�ñ�ʾ��Ҫ�жϷ����ĵ�											
				qipan[i][j] = my_color;													//��������ڸõ�����	����Ϊ����


				player ziji = { 0 };
				ziji.player_qixing = { 0, 0, 0, 0, 0, 1000, 100, 10, -5 };						//��ʼ�����ͼ�������Ϣ
				ziji.player_color = my_color;											//��ʼ����ɫ

				fangxiang zj_heng = { 0 }, zj_shu = { 0 }, zj_zuoxie = { 0 }, zj_youxie = { 0 };

				ziji.player_fangxiang = &zj_heng;										//�����ж�
				ziji.player_fangxiang->mianqi = 1;										//�жϸõ��Ƿ�Ϊ���壬0��  1��
				int a = i, b = j;														//��ʱx,y����
				for (b = j; b <= j + 4; b++)											//��������,ȷ���ұ߽�			���Ժ����ж�
				{
					if (b > 14)
						break;															//Խ�磬����ѭ��
					if (qipan[a][b] != ziji.player_color && qipan[a][b] != 0)
						break;															//�����Ǽ����ӣ�����ѭ��
				}
				b--;																	//����x����

				for (ziji.player_fangxiang->weishu = 0; (qipan[a][b] == ziji.player_color || qipan[a][b] == 0)
					&& b >= 0 && b >= j - 4; b--, ziji.player_fangxiang->weishu++)
				{																		//�����Ǽ����ӣ�Խ�磬������Χ������ѭ��
					if (qipan[a][b] == ziji.player_color)
					{
						ziji.player_fangxiang->qi |= 1 << ziji.player_fangxiang->weishu;//�Ƿ����ӣ���Ϊ1
						ziji.player_fangxiang->qishu++;									//���㼺��������
					}
				}
				pipei(qixingku, cqixingku_score, &ziji);



				ziji.player_fangxiang = &zj_shu;										//�����ж�
				ziji.player_fangxiang->mianqi = 1;										//�жϸõ��Ƿ�Ϊ���壬0��  1��
				a = i, b = j;
				for (a = i; a <= i + 4; a++)											//��������,ȷ���±߽�			���������ж�
				{
					if (a > 14)
						break;															//Խ�磬����ѭ��
					if (qipan[a][b] != ziji.player_color && qipan[a][b] != 0)
						break;															//�����Ǽ����ӣ�����ѭ��
				}
				a--;																	//����y����

				for (ziji.player_fangxiang->weishu = 0; (qipan[a][b] == ziji.player_color || qipan[a][b] == 0)
					&& a >= 0 && a >= i - 4; a--, ziji.player_fangxiang->weishu++)
				{																		//�����Ǽ����ӣ�Խ�磬������Χ������ѭ��
					if (qipan[a][b] == ziji.player_color)
					{
						ziji.player_fangxiang->qi |= 1 << ziji.player_fangxiang->weishu;//�������ӣ���Ϊ1
						ziji.player_fangxiang->qishu++;									//���㼺��������
					}
				}
				pipei(qixingku, cqixingku_score, &ziji);								//�����ο�ƥ����



				ziji.player_fangxiang = &zj_zuoxie;										//��б�ж�
				ziji.player_fangxiang->mianqi = 1;										//�жϸõ��Ƿ�Ϊ���壬0��  1��
				a = i, b = j;
				for (a = i, b = j; a <= i + 4 && b <= j + 4; a++, b++)					//����������,ȷ�����±߽�		������б�ж�
				{
					if (a > 14 || b > 14)
						break;															//Խ�磬����ѭ��
					if (qipan[a][b] != ziji.player_color && qipan[a][b] != 0)
						break;															//�����Ǽ����ӣ�����ѭ��
				}
				a--, b--;																//����y,x����

				for (ziji.player_fangxiang->weishu = 0; (qipan[a][b] == ziji.player_color || qipan[a][b] == 0)
					&& b >= 0 && b >= j - 4 && a >= 0 && a >= i - 4; b--, a--, ziji.player_fangxiang->weishu++)
				{																		//�����Ǽ����ӣ�Խ�磬������Χ������ѭ��
					if (qipan[a][b] == ziji.player_color)
					{
						ziji.player_fangxiang->qi |= 1 << ziji.player_fangxiang->weishu;//�Ƿ����ӣ���Ϊ1
						ziji.player_fangxiang->qishu++;									//���㼺��������
					}
				}
				pipei(qixingku, cqixingku_score, &ziji);								//�����ο�ƥ����



				ziji.player_fangxiang = &zj_youxie;										//��б�ж�
				ziji.player_fangxiang->mianqi = 1;										//�жϸõ��Ƿ�Ϊ���壬0��  1��
				a = i, b = j;
				for (a = i, b = j; a <= i + 4 && b >= j - 4; a++, b--)					//����������,ȷ�����±߽�		������б�ж�
				{
					if (a > 14 || b < 0)
						break;															//Խ�磬����ѭ��
					if (qipan[a][b] != ziji.player_color && qipan[a][b] != 0)
						break;															//�����Ǽ����ӣ�����ѭ��
				}
				a--, b++;																//����y,x����

				for (ziji.player_fangxiang->weishu = 0; (qipan[a][b] == ziji.player_color || qipan[a][b] == 0)
					&& b <= 14 && b <= j + 4 && a >= 0 && a >= i - 4; b++, a--, ziji.player_fangxiang->weishu++)
				{																		//�����Ǽ����ӣ�Խ�磬������Χ������ѭ��
					if (qipan[a][b] == ziji.player_color)
					{
						ziji.player_fangxiang->qi |= 1 << ziji.player_fangxiang->weishu;//�Ƿ����ӣ���Ϊ1
						ziji.player_fangxiang->qishu++;									//���㼺��������
					}
				}
				pipei(qixingku, cqixingku_score, &ziji);								//�����ο�ƥ����


				//�����ڸõ����ӵķ���
				borad_weights[i][j] = zj_heng.max_score + zj_shu.max_score + zj_zuoxie.max_score + zj_youxie.max_score;

				//��������ж�
				if (borad_weights[i][j] < 50000 && (ziji.player_qixing.miansi >= 2 || (ziji.player_qixing.miansi >= 1 && ziji.player_qixing.huosan >= 1)))
					borad_weights[i][j] = 50000;										//˫���ģ����Ļ���		����50000
				else if (borad_weights[i][j] < 25000 && ziji.player_qixing.huosan >= 2)
					borad_weights[i][j] = 25000;										//˫����				����25000
				else if (borad_weights[i][j] < 5000 && ziji.player_qixing.huosan == 1 && ziji.player_qixing.miansan >= 1)
					borad_weights[i][j] = 5000;											//��������				����5000
				else if (borad_weights[i][j] < 200 && ziji.player_qixing.huoer >= 2)
					borad_weights[i][j] = 200;											//˫���				����200
				else if (borad_weights[i][j] < 50 && ziji.player_qixing.huoer == 1 && ziji.player_qixing.mianer >= 1)
					borad_weights[i][j] = 50;											//����߶�				����50

				//��ͬ���ͣ����Է����ߣ�����ͬ�����µ������Ƚ���
				//����Ϊ���Է����ж�	
				//�������������������������������������������������Ƿָ��ߡ�����������������������������������������������//
				//����Ϊ��ҷ����ж�
				qipan[i][j] = other_color;												//��������ڸõ�����	���Ϊ����


				player duishou = { 0 };
				duishou.player_qixing = { 0, 0, 0, 0, 0, 800, 80, 8, -4 };
				duishou.player_color = other_color;										//��ʼ����ɫ

				fangxiang ds_heng = { 0 }, ds_shu = { 0 }, ds_zuoxie = { 0 }, ds_youxie = { 0 };

				duishou.player_fangxiang = &ds_heng;									//�����ж�
				duishou.player_fangxiang->mianqi = 1;									//�жϸõ��Ƿ�Ϊ���壬0��  1��
				a = i, b = j;															//��ʱx,y����
				for (b = j; b <= j + 4; b++)											//��������,ȷ���ұ߽�			���Ժ����ж�
				{
					if (b > 14)
						break;															//Խ�磬����ѭ��
					if (qipan[a][b] != duishou.player_color && qipan[a][b] != 0)
						break;															//�����Ǽ����ӣ�����ѭ��
				}
				b--;																	//����x����

				for (duishou.player_fangxiang->weishu = 0; (qipan[a][b] == duishou.player_color || qipan[a][b] == 0)
					&& b >= 0 && b >= j - 4; b--, duishou.player_fangxiang->weishu++)
				{																		//�����Ǽ����ӣ�Խ�磬������Χ������ѭ��
					if (qipan[a][b] == duishou.player_color)
					{
						duishou.player_fangxiang->qi |= 1 << duishou.player_fangxiang->weishu;	//�Ƿ����ӣ���Ϊ1
						duishou.player_fangxiang->qishu++;								//���㼺��������
					}
				}
				pipei(qixingku, pqixingku_score, &duishou);



				duishou.player_fangxiang = &ds_shu;										//�����ж�
				duishou.player_fangxiang->mianqi = 1;									//�жϸõ��Ƿ�Ϊ���壬0��  1��
				a = i, b = j;
				for (a = i; a <= i + 4; a++)											//��������,ȷ���±߽�			���������ж�
				{
					if (a > 14)
						break;															//Խ�磬����ѭ��
					if (qipan[a][b] != duishou.player_color && qipan[a][b] != 0)
						break;															//�����Ǽ����ӣ�����ѭ��
				}
				a--;																	//����y����

				for (duishou.player_fangxiang->weishu = 0; (qipan[a][b] == duishou.player_color || qipan[a][b] == 0)
					&& a >= 0 && a >= i - 4; a--, duishou.player_fangxiang->weishu++)
				{																		//�����Ǽ����ӣ�Խ�磬������Χ������ѭ��
					if (qipan[a][b] == duishou.player_color)
					{
						duishou.player_fangxiang->qi |= 1 << duishou.player_fangxiang->weishu;	//�������ӣ���Ϊ1
						duishou.player_fangxiang->qishu++;								//���㼺��������
					}
				}
				pipei(qixingku, pqixingku_score, &duishou);								//�����ο�ƥ����



				duishou.player_fangxiang = &ds_zuoxie;									//��б�ж�
				duishou.player_fangxiang->mianqi = 1;									//�жϸõ��Ƿ�Ϊ���壬0��  1��
				a = i, b = j;
				for (a = i, b = j; a <= i + 4 && b <= j + 4; a++, b++)					//����������,ȷ�����±߽�		������б�ж�
				{
					if (a > 14 || b > 14)
						break;															//Խ�磬����ѭ��
					if (qipan[a][b] != duishou.player_color && qipan[a][b] != 0)
						break;															//�����Ǽ����ӣ�����ѭ��
				}
				a--, b--;																//����y,x����

				for (duishou.player_fangxiang->weishu = 0; (qipan[a][b] == duishou.player_color || qipan[a][b] == 0)
					&& b >= 0 && b >= j - 4 && a >= 0 && a >= i - 4; b--, a--, duishou.player_fangxiang->weishu++)
				{																		//�����Ǽ����ӣ�Խ�磬������Χ������ѭ��
					if (qipan[a][b] == duishou.player_color)
					{
						duishou.player_fangxiang->qi |= 1 << duishou.player_fangxiang->weishu;	//�Ƿ����ӣ���Ϊ1
						duishou.player_fangxiang->qishu++;								//���㼺��������
					}
				}
				pipei(qixingku, pqixingku_score, &duishou);								//�����ο�ƥ����



				duishou.player_fangxiang = &ds_youxie;									//��б�ж�
				duishou.player_fangxiang->mianqi = 1;									//�жϸõ��Ƿ�Ϊ���壬0��  1��
				a = i, b = j;
				for (a = i, b = j; a <= i + 4 && b >= j - 4; a++, b--)					//����������,ȷ�����±߽�		������б�ж�
				{
					if (a > 14 || b < 0)
						break;															//Խ�磬����ѭ��
					if (qipan[a][b] != duishou.player_color && qipan[a][b] != 0)
						break;															//�����Ǽ����ӣ�����ѭ��
				}
				a--, b++;																//����y,x����

				for (duishou.player_fangxiang->weishu = 0; (qipan[a][b] == duishou.player_color || qipan[a][b] == 0)
					&& b <= 14 && b <= j + 4 && a >= 0 && a >= i - 4; b++, a--, duishou.player_fangxiang->weishu++)
				{																		//�����Ǽ����ӣ�Խ�磬������Χ������ѭ��
					if (qipan[a][b] == duishou.player_color)
					{
						duishou.player_fangxiang->qi |= 1 << duishou.player_fangxiang->weishu;	//�Ƿ����ӣ���Ϊ1
						duishou.player_fangxiang->qishu++;								//���㼺��������
					}
				}
				pipei(qixingku, pqixingku_score, &duishou);								//�����ο�ƥ����


				//����ڸõ����ӵķ���
				int lingshifenshu = 0;
				lingshifenshu = ds_heng.max_score + ds_shu.max_score + ds_zuoxie.max_score + ds_youxie.max_score;

				//��������ж�
				if (lingshifenshu < 40000 && (duishou.player_qixing.miansi >= 2 || (duishou.player_qixing.miansi >= 1 && duishou.player_qixing.huosan >= 1)))
					lingshifenshu = 40000;												//˫���ģ����Ļ���		����40000
				else if (lingshifenshu < 20000 && duishou.player_qixing.huosan >= 2)
					lingshifenshu = 20000;												//˫����				����20000
				else if (lingshifenshu < 4000 && duishou.player_qixing.huosan == 1 && duishou.player_qixing.miansan >= 1)
					lingshifenshu = 4000;												//��������				����4000
				else if (lingshifenshu < 160 && duishou.player_qixing.huoer >= 2)
					lingshifenshu = 160;												//˫���				����160
				else if (lingshifenshu < 40 && duishou.player_qixing.huoer == 1 && duishou.player_qixing.mianer >= 1)
					lingshifenshu = 40;													//����߶�				����40



				//�����������������������������������������������Ƿָ��ߡ���������������������������������������������������//

				borad_weights[i][j] += lingshifenshu;									//�õ���ܷ���,˫�����ּ�����λ�÷���

				if (0.9 * max_score <= borad_weights[i][j])								//��������߷���һ����Χ�ڵĵ�	0.9max-max
				{
					if (max_num < 100)													//��ֹԽ��
					{
						max_num++;														//��¼��߷�����Χ�ڵ�ĸ���
						max_score_x[max_num - 1] = j;
						max_score_y[max_num - 1] = i;
					}
				}

				if (max_score < borad_weights[i][j])
				{																		//�ҳ��µ���߷�����
					max_score = borad_weights[i][j];									//��¼�µ���߷�
					max_num = 1;														//��߷ָ�����1
					max_score_x[0] = 0, max_score_y[0] = 0;								//��߷��������

					max_score_x[0] = j;													//��¼����߷ֵ�����
					max_score_y[0] = i;
				}

				qipan[i][j] = 0;												 		//������������
			}
		}
	}
	int max_x = 0, max_y = 0;															//���ս�Ҫ���ӵ�����
	int rn = 0;																			//�����rn

	if (max_num > 1)																	//�����߷ֲ�ֹһ��
	{
		rn = rand() % max_num;															//���������
		max_x = max_score_x[rn];														//�������ѡ��һ������Ϊ�������ӵ�
		max_y = max_score_y[rn];
	}
	else																				//��߷�ֻ��һ��
	{
		max_x = max_score_x[0];															//�˵�Ϊ�������ӵ�
		max_y = max_score_y[0];
	}

	if (count == 1)																		//�����ߵ�һ�������
	{
		max_x = rand() % 5 + 5;
		max_y = rand() % 5 + 5;
	}

	bianjie(&tymin, &txmin, &tymax, &txmax, max_y, max_x);								//�������������Χ

	*x = max_x;																			//���ҵ������������꣬��������
	*y = max_y;

	return max_score;
}


int bianjie(int* tymin, int* txmin, int* tymax, int* txmax, int y, int x)				//���ӵ�߽���ҷ�Χ
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


int pipei(const int qixingku[14], const int qixingku_score[14], player* computer)		//ƥ�����ο⣬���д��
{

	if (computer->player_fangxiang->weishu >= 6)										//�ɽ������ο�ƥ��
	{
		for (int t = computer->player_fangxiang->weishu - 6; t >= 0; t--)				//�����ƶ����
		{
			for (int n = 0; n < 14; n++)												//�������ο�ƥ��
			{
				const int h = computer->player_fangxiang->qi;
				if (((h >> t) & 077) == qixingku[n])									//λ�����ƶ������ƥ�����ο�
				{
					computer->player_fangxiang->mianqi = 0;								//ƥ��ɹ��ǻ��壬��������
					if (computer->player_fangxiang->max_score < qixingku_score[n])		//������С�ڼ�����õķ���
						computer->player_fangxiang->max_score = qixingku_score[n];		//����µ����ο��Ӧ�÷�
					break;
				}
			}
		}
		if (computer->player_fangxiang->max_score == qixingku_score[4])					//�����������ж�
			computer->player_qixing.huosan++;											//����������һ
		if (computer->player_fangxiang->max_score == qixingku_score[8])
			computer->player_qixing.huoer++;											//���������һ
	}
	else if (computer->player_fangxiang->weishu == 5 && computer->player_fangxiang->qishu == 5)
	{																					//���߶������ŵĳ���
		computer->player_fangxiang->max_score = qixingku_score[0];						//�����Ķ�Ӧ����
		computer->player_fangxiang->mianqi = 0;											//��������������
	}
	else if (computer->player_fangxiang->weishu <= 4)									//����
	{
		computer->player_fangxiang->max_score = computer->player_qixing.siqi_score;		//����-5
		computer->player_fangxiang->mianqi = 0;											//�����壬��������
	}
	if (computer->player_fangxiang->mianqi)												//������������ǣ���������
	{
		if (computer->player_fangxiang->qishu == 4)										//����
		{
			computer->player_fangxiang->max_score = computer->player_qixing.miansi_score;//���Ķ�Ӧ����
			computer->player_qixing.miansi++;											//���ĸ�����һ
		}
		else if (computer->player_fangxiang->qishu == 3)								//����
		{
			computer->player_fangxiang->max_score = computer->player_qixing.miansan_score;//������Ӧ����
			computer->player_qixing.miansan++;											//��������������һ
		}
		else if (computer->player_fangxiang->qishu == 2)								//�߶�
		{
			computer->player_fangxiang->max_score = computer->player_qixing.mianer_score;//�߶���Ӧ����
			computer->player_qixing.mianer++;											//�����߶�������һ
		}
	}
	return 0;
}




int judge(int arry[15][15], int y, int x, int bw)										//��Ӯ�ж�
{
	int tempmix = 0, tempmiy = 0;
	int tempmax = 0, tempmay = 0;
	int num = 0;
	int i = 0, j = 0;

	if (x > 4)																			//ȷ�������߽�
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

	for (j = tempmix + 1, num = 0; j <= tempmax; j++)									//�����ж�				
	{
		if ((arry[y][j - 1] == arry[y][j]) && (arry[y][j] == bw))
			num++;
		else
			num = 0;
		if (num >= 4)																	//���������������������Ӯ
			return 1;
	}

	for (i = tempmiy + 1, num = 0; i <= tempmay; i++)									//�����ж�
	{
		if ((arry[i - 1][x] == arry[i][x]) && (arry[i][x] == bw))
			num++;
		else
			num = 0;
		if (num >= 4)																	//���������������������Ӯ
			return 1;
	}

	for (tempmix = x, tempmiy = y; tempmix - 1 >= 0 && tempmiy - 1 >= 0; tempmix--, tempmiy--)
	{
		;																				//ȷ����б���϶���λ��
	}


	for (i = tempmiy + 1, j = tempmix + 1, num = 0; i <= y + 4 && j <= x + 4 && i <= 14 && j <= 14; i++, j++)
	{																					//��б�ж�
		if ((arry[i - 1][j - 1] == arry[i][j]) && (arry[i][j] == bw))
			num++;
		else
			num = 0;
		if (num >= 4)																	//���������������������Ӯ
			return 1;
	}

	for (tempmax = x, tempmiy = y; tempmax + 1 <= 14 && tempmiy - 1 >= 0; tempmax++, tempmiy--)
	{
		;																				//ȷ����б���϶���λ��
	}

	for (i = tempmiy + 1, j = tempmax - 1, num = 0; i <= y + 4 && j >= x - 4 && i <= 14 && j >= 0; i++, j--)
	{																					//��б�ж�
		if ((arry[i - 1][j + 1] == arry[i][j]) && (arry[i][j] == bw))
			num++;
		else
			num = 0;
		if (num >= 4)																	//���������������������Ӯ
			return 1;
	}
	return 0;
}


int win_lose(int bw)																	//��Ӯ��ʾ
{
	const TCHAR* s0 = _T("ƽ�֣�");
	const TCHAR* s1 = _T("����ʤ��"), *s2 = _T("����ʤ��"), *s3 = _T("���ϣ�С���ӿ��԰�����ϲ��û�䣡"), *s4 = _T("�������ˣ�̫���ˣ�");
	const TCHAR* c0 = _T("����ʤ!(����)"), *c1 = _T("����ʤ!(����)");
	const TCHAR* s5 = _T("����");
	if (bw < 4)
	{
		setlinecolor(0X000000);															//���õ�ǰ����ɫ
		setfillcolor(0XFFFFFF);															//���õ�ǰ���ɫ
		fillroundrect(220, 140, 520, 340, 150, 120);									//��Բ�Ǿ���
		settextcolor(0X5555FF);															//����������ɫ
		setbkmode(TRANSPARENT);															//�������屳��ɫ��͸��
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
		settextcolor(0X5555FF);															//����������ɫ
		setbkmode(TRANSPARENT);															//�������屳��ɫ��͸��
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



//Alpha��֦��Beta��֦+MaxMin����
int AlphaBeta(int depth, int alpha, int beta, AlpBet* AB)
{
	int ansx = 0;
	int ansy = 0;
	if (depth == DEPTH)
		return guzhi(AB->chbo, depth % 2 + 1, AB->tempy, AB->tempx, &(AB->y), &(AB->x), AB->count);	//��ֵ����
	if (judge(AB->blbo, AB->y, AB->x, 1))
		return 99999;
	if (judge(AB->whbo, AB->y, AB->x, 2))
		return -99999;


	if (depth & 1)																	//Max��,ȡ�ӽڵ�ļ���ֵΪ���ڵ��alphaֵ,�Լ�
	{
		int ans = AlphaBeta(depth + 1, alpha, beta, AB);

		/*if (AB->play == 1)
		guzhi(AB->chbo, 1, AB->tempy, AB->tempx, &(AB->y), &(AB->x), AB->count);
		else
		guzhi(AB->chbo, 2, AB->tempy, AB->tempx, &(AB->y), &(AB->x), AB->count);*/

		if (ans > alpha)
		{
			alpha = ans;																//ͨ���ӽڵ��betaֵ���ϴ����������ڵ��alphaֵ
			ansx = AB->x;																//��¼����
			ansy = AB->y;
		}
		if (alpha >= beta)																//����alpha��֦
		{
			return alpha;
		}

		return alpha;
	}
	else																				//Min��,ȡ�ӽڵ�ļ�СֵΪ���ڵ��betaֵ,����
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
		menu();																			//���˵�����
	}
	return 0;
}