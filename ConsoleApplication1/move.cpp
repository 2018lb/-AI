#include"pch.h"
const int  shiftingx = 150;
const int  shiftingy = 100;
const int  wide = 372;
const int  length = 425;
const int gridx = (wide - 20) / 8;
const int gridy = (length - 20) / 9;

using namespace std;

extern int cnt_map[12][12];
extern pieces P[30];//����

void disapp(int x, int y)//Ų������ʱ���ӱ䶯
{
	setlinecolor(RGB(0, 0, 0));
	setlinestyle(PS_SOLID, 2);

	int x_ = x * gridx + 10;//ָx����
	int y_ = y * gridy + 10;//ָy����

	cnt_map[x][y] = 0;
	clearcircle(x_, y_, 21);
	//_getch();
	
	//�ػ���ǰ�����
	if (x != 0 && x != 8 && y != 0 && y != 9 && y != 4 && y != 5)
	{
		line(x_ - 22, y_, x_ + 22, y_);
		line(x_, y_ - 22, x_, y_ + 22);
	}
	if (y == 0 || y == 9 || y == 4 || y == 5)
	{
		int k1 = 22, k2 = 22;
		if (x == 0) k1 = 0;
		if (x == 8) k2 = 0;
		line(x_ - k1, y_, x_ + k2, y_);

		if (x != 0 && x != 8)
		{
			if (y == 0 || y == 5) line(x_, y_, x_, y_ + 22);
			if (y == 9 || y == 4) line(x_, y_ - 22, x_, y_);
		}
	}
	if (x == 0 || x == 8)
	{
		int k1 = 22, k2 = 22;
		if (y == 0) k1 = 0; 
		if (y == 9) k2 = 0;
		line(x_, y_ - k1, x_, y_ + k2);

		if (x) line(x_ - 22, y_, x_, y_);
		else line(x_, y_, x_ + 22, y_);
	}
	
	//�ػ���߿�
	if (x == 0 || x == 8 || y == 0 || y == 9)
	{
		setlinecolor(RGB(0, 0, 0));
		setlinestyle(PS_SOLID, 5);
		rectangle(0, 0, wide, length);

		setlinestyle(PS_SOLID, 2);
		for (int i = 0; i <= 8; i++)
		{
			if (cnt_map[i][0]) P[cnt_map[i][0]].app(i, 0);
			if (cnt_map[i][9]) P[cnt_map[i][9]].app(i, 9);
		}

		for (int i = 0; i <= 9; i++)
		{
			if (cnt_map[0][i]) P[cnt_map[0][i]].app(0, i);
			if (cnt_map[8][i]) P[cnt_map[8][i]].app(8, i);
		}
	}

	//�ػ�����ϸ��
	if (((y == 3 || y == 6) && x % 2 == 0) || ((y == 2 || y == 7) && (x == 1 || x == 7)))
		map_detail(x*gridx + 10, y*gridy + 10);

	//��д��
	if (y == 4 || y == 5)
	{
		LOGFONT f;
		gettextstyle(&f);						// ��ȡ��ǰ��������
		f.lfHeight = 32;						// ��������߶�Ϊ 32
		_tcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����顱
		f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
		settextstyle(&f);

		settextcolor(RGB(0, 0, 0));
		RECT r = { 10 + 44 - 5, 10 + 4 * gridy, 10 + 44 * 3 + 5, 10 + 5 * gridy };
		drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		RECT c = { 10 + 5 * 44 - 5, 10 + 4 * gridy, 10 + 44 * 7 + 5, 10 + 5 * gridy };
		drawtext(_T("��  ��"), &c, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		for (int i = 0; i <= 8; i++)
		{
			if (cnt_map[i][4]) P[cnt_map[i][4]].app(i, 4);
			if (cnt_map[i][5]) P[cnt_map[i][5]].app(i, 5);
		}
	}

	//�ػ����̾Ź���ϸ��
	if ((x == 3 && (y == 0 || y == 7)) || ((x == 4 && (y == 1 || y == 8))))
		line(x_ + 16, y_ + 16, x_, y_);

	if ((x == 5 && (y == 0 || y == 7)) || ((x == 4 && (y == 1 || y == 8))))
		line(x_ - 16, y_ + 16, x_, y_);

	if ((x == 3 && (y == 2 || y == 9)) || ((x == 4 && (y == 1 || y == 8))))
		line(x_ + 16, y_ - 16, x_, y_);

	if ((x == 5 && (y == 2 || y == 9)) || ((x == 4 && (y == 1 || y == 8))))
		line(x_ - 16, y_ - 16, x_, y_);
	
}

x_y chang_coordinate(int x_, int y_)//ͨ��x_y�������ҵ���Ӧ��ͼ��������
{
	x_ -= shiftingx;
	y_ -= shiftingy;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			int kx = i * gridx + 10, ky = j * gridy + 10;
			if ((kx - x_)*(kx - x_) + (ky - y_)*(ky - y_) <= 400)
			{
				x_y ans;
				ans.x = i; ans.y = j;
				return ans;
			}
		}
	}
	x_y ans; 
	ans.x = ans.y = 666;
	return ans;
}

void highlight(x_y now)//������ѡ�е�����
{
	int x_ = now.x * gridx + 10, y_ = now.y * gridy + 10;

	setlinecolor(RED);
	setlinestyle(PS_SOLID, 2);

	circle(x_, y_, 17);
}

void cancel_highlight(x_y now)//������ȡ������
{
	P[cnt_map[now.x][now.y]].app(now.x, now.y);
}

bool check(x_y k1, x_y k2)//�������� k1 ������ k2�Ƿ�Ϸ�
{
	if (k1.x == 666 || k2.x == 666) return false;

	switch (cnt_map[k1.x][k1.y])
	{
		case 14://����
		{
			if (k1.x == k2.x&&k1.y == k2.y - 1) return true;
			if (abs(k1.x-k2.x) == 1&&k1.y == k2.y&&k1.y>=5) return true;
			return false;
		}
		case 1://����
		{
			if (k1.x != k2.x&&k1.y != k2.y) return false;

			int num = 0;
			if (k1.x == k2.x)
			{
				int a = min(k1.y, k2.y), b = max(k1.y, k2.y);
				for (int i = a + 1; i < b; i++)
				{
					if (cnt_map[k1.x][i]) num++;
				}

				if (cnt_map[k2.x][k2.y] && num == 1) return true;
				if (num == 0 && !cnt_map[k2.x][k2.y]) return true;
				else return false;
			}

			if (k1.y == k2.y)
			{
				int a = min(k1.x, k2.x), b = max(k1.x, k2.x);
				for (int i = a + 1; i < b; i++)
				{
					if (cnt_map[i][k1.y]) num++;
				}

				if (cnt_map[k2.x][k2.y] && num == 1) return true;
				if (num == 0 && !cnt_map[k2.x][k2.y]) return true;
				else return false;
			}
		}
		case 2://�ڳ�
		{
			if (k1.x != k2.x&&k1.y != k2.y) return false;

			int num = 0;
			if (k1.x == k2.x)
			{
				int a = min(k1.y, k2.y), b = max(k1.y, k2.y);
				for (int i = a + 1; i < b; i++)
				{
					if (cnt_map[k1.x][i]) return false;
				}
				return true;
			}

			if (k1.y == k2.y)
			{
				int a = min(k1.x, k2.x), b = max(k1.x, k2.x);
				for (int i = a + 1; i < b; i++)
				{
					if (cnt_map[i][k1.y]) return false;
				}
				return true;
			}
		}
		case 3://����
		{
			if (abs(k1.x - k2.x) + abs(k1.y - k2.y) != 3) return false;
			if (k1.x == k2.x || k1.y == k2.y) return false;
			//�ĸ����
			if (k1.x - k2.x == 2 && cnt_map[k1.x - 1][k1.y]) return false;
			if (k1.x - k2.x == -2 && cnt_map[k1.x + 1][k1.y]) return false;
			if (k1.y - k2.y == 2 && cnt_map[k1.x][k1.y - 1]) return false;
			if (k1.y - k2.y == -2 && cnt_map[k1.x][k1.y + 1]) return false;

			return true;
		}
		case 4://����
		{
			if (k2.y >= 5) return false;
			if (abs(k1.x - k2.x) != 2 || abs(k1.y - k2.y) != 2) return false;
			//�ĸ����
			if (k2.x < k1.x&&k2.y < k1.y&&cnt_map[k1.x - 1][k1.y - 1]) return false;
			if (k2.x > k1.x&&k2.y > k1.y&&cnt_map[k1.x + 1][k1.y + 1]) return false;
			if (k2.x > k1.x&&k2.y < k1.y&&cnt_map[k1.x + 1][k1.y - 1]) return false;
			if (k2.x < k1.x&&k2.y > k1.y&&cnt_map[k1.x - 1][k1.y + 1]) return false;

			return true;
		}
		case 5://��ʿ
		{
			if (k2.x <= 2 && k2.x >= 6 && k2.y >= 3) return false;
			if (abs(k1.x - k2.x) != 1 || abs(k1.y - k2.y) != 1) return false;
			return true;
		}
		case 6://��
		{
			if (k2.x == k1.x && cnt_map[k2.x][k2.y] == 13)
			{
				for (int i = k1.y + 1; i < k2.y; i++) if (cnt_map[k1.x][i]) return false;
				return true;
			}
			if (k2.x <= 2 && k2.x >= 6 && k2.y >= 3) return false;
			if (abs(k1.x - k2.x) + abs(k1.y - k2.y) == 1) return true;
			return false;
		}
		case 7://���
		{
			if (k1.x == k2.x&&k1.y == k2.y + 1) return true;
			if (abs(k1.x - k2.x) == 1 && k1.y == k2.y&&k1.y <= 4) return true;
			return false;
		}
		case 8://����
		{
			if (k1.x != k2.x&&k1.y != k2.y) return false;

			int num = 0;
			if (k1.x == k2.x)
			{
				int a = min(k1.y, k2.y), b = max(k1.y, k2.y);
				for (int i = a + 1; i < b; i++)
				{
					if (cnt_map[k1.x][i]) num++;
				}

				if (cnt_map[k2.x][k2.y] && num == 1) return true;
				if (num == 0 && !cnt_map[k2.x][k2.y]) return true;
				else return false;
			}

			if (k1.y == k2.y)
			{
				int a = min(k1.x, k2.x), b = max(k1.x, k2.x);
				for (int i = a + 1; i < b; i++)
				{
					if (cnt_map[i][k1.y]) num++;
				}

				if (cnt_map[k2.x][k2.y] && num == 1) return true;
				if (num == 0 && !cnt_map[k2.x][k2.y]) return true;
				else return false;
			}
		}
		case 9://�쳵
		{
			if (k1.x != k2.x&&k1.y != k2.y) return false;

			int num = 0;
			if (k1.x == k2.x)
			{
				int a = min(k1.y, k2.y), b = max(k1.y, k2.y);
				for (int i = a + 1; i < b; i++)
				{
					if (cnt_map[k1.x][i]) return false;
				}
				return true;
			}

			if (k1.y == k2.y)
			{
				int a = min(k1.x, k2.x), b = max(k1.x, k2.x);
				for (int i = a + 1; i < b; i++)
				{
					if (cnt_map[i][k1.y]) return false;
				}
				return true;
			}
		}
		case 10://����
		{
			if (abs(k1.x - k2.x) + abs(k1.y - k2.y) != 3) return false;
			if (k1.x == k2.x || k1.y == k2.y) return false;
			//�ĸ����
			if (k1.x - k2.x == 2 && cnt_map[k1.x - 1][k1.y]) return false;
			if (k1.x - k2.x == -2 && cnt_map[k1.x + 1][k1.y]) return false;
			if (k1.y - k2.y == 2 && cnt_map[k1.x][k1.y - 1]) return false;
			if (k1.y - k2.y == -2 && cnt_map[k1.x][k1.y + 1]) return false;

			return true;
		}
		case 11://����
		{
			if (k2.y <= 4) return false;
			if (abs(k1.x - k2.x) != 2 || abs(k1.y - k2.y) != 2) return false;
			//�ĸ����
			if (k2.x < k1.x&&k2.y < k1.y&&cnt_map[k1.x - 1][k1.y - 1]) return false;
			if (k2.x > k1.x&&k2.y > k1.y&&cnt_map[k1.x + 1][k1.y + 1]) return false;
			if (k2.x > k1.x&&k2.y < k1.y&&cnt_map[k1.x + 1][k1.y - 1]) return false;
			if (k2.x < k1.x&&k2.y > k1.y&&cnt_map[k1.x - 1][k1.y + 1]) return false;

			return true;
		}
		case 12://��ʿ
		{
			if (k2.x <= 2 && k2.x >= 6 && k2.y <= 6) return false;
			if (abs(k1.x - k2.x) != 1 || abs(k1.y - k2.y) != 1) return false;
			return true;
		}
		case 13://��
		{
			if (k2.x == k1.x && cnt_map[k2.x][k2.y] == 6)
			{
				for (int i= k2.y + 1; i < k1.y; i++) if (cnt_map[k1.x][i]) return false;
				return true;
			}
			if (k2.x <= 2 && k2.x >= 6 && k2.y <= 6) return false;
			if (abs(k1.x - k2.x) + abs(k1.y - k2.y) == 1) return true;
			return false;
		}
	}
}

void Move_to_cemetery_Black(int Chess_type, int die_num)
{
	int x = die_num % 6, y = die_num / 6;
	P[Chess_type].app(10 + x, y + 7);
}

void Move_to_cemetery_Red(int Chess_type, int die_num)
{
	int x = die_num % 6, y = die_num / 6;
	P[Chess_type].app(10 + x, y);
}