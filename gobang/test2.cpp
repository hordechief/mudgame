#include<iostream>
#include<stdlib.h>
#include<iomanip>     //��ʽ�����
using namespace std;
const int N = 9;       //����NΪ����
static int A=0, B=0;
char command;


class jiemian {
	public:


		void Jiemainbuzhi();
		void initBoard();
		void Qijubuzhi();
		void Chesspainter(int x,int y);
		int check(int x, int y);
		int checkcommand(int x, int y);
		void  chessicont(int x);
		int Checkzuobiao(int i, int j, char flag);
		int x, y;    //����·��
	protected:

		bool flag = 0;      //�����������
		char  chessBord[N + 1][N + 1];
};


void jiemian::chessicont(int x) {
	if (x == 1)
		A++;
	if (x == 2)
		B++;
	cout << "A : B ��" << A << ":" << B << '\t';
}


void jiemian::Jiemainbuzhi() {
	cout << "����������������Ϸ��������ZXL" << endl;
	cout << "################################" << endl;
	cout << "#     1.������Ϸ   E           # " << endl;
	cout << "#     2.�˳���Ϸ   0 0         # " << endl;
	cout << "#     3.ѡ��ؿ�   C           # " << endl;
	cout << "################################" << endl;
}


void jiemian::Qijubuzhi() {
	cout << "plaese entry �� x �� y " << endl;
	cout << setw(3) << setfill(' ') << left << 0;
	for (int i = 1; i < N + 1; i++) {
		cout << setw(6) << setfill(' ') << right << i;
	}
	cout << endl;
	cout << "   |";
	for (int i = 1; i < N + 1; i++) {
		cout << "-----|";
	}
	cout << endl;
	for (int i = 1; i < N + 1; i++) {
		for (int j = 0; j < N + 1; j++) {
			if (j == 0) {
				cout << setw(3) << setfill(' ') << left << i << '|';
			} else {
				cout << "  " << chessBord[i][j] << "  |";
			}
		}
		cout << endl;
		cout << "   |";
		for (int i = 1; i < N + 1; i++) {
			cout << "-----|";
		}
		cout << endl;
	}
}


void jiemian::initBoard() {
	for (int i = 0; i < N + 1; i++)
		for (int j = 0; j < N + 1; j++) {
			chessBord[i][j] = ' ';     //��ʼ��
		}
}


void  jiemian::Chesspainter(int x, int y) {  //����


	if (-1 == check(x, y)) {
		cout << "��������������֮�����"<<endl;
	} else if (0 == check(x, y)) {
		cout << "�����Ѿ���������벻Ҫ�ظ�����" << endl;
	} else {
		system("CLS");
		if (flag == 0) {
			chessBord[x][y] = 'x';
			cout << "Palyer " << "A with 'x' IS " << "X ," << x << "Y ," << y << endl;
			flag = 1;
		} else if (flag == 1) {
			chessBord[x][y] = 'o';
			cout << "Palyer " << "B with 'o' IS " << "X ," << x << "Y ," << y << endl;
			flag = 0;
		}
		Qijubuzhi();
	}
}


int  jiemian::checkcommand(int x,int y) {  //ȱ���ݴ����
	if(0==x&&0==y) {
		return 1;
	} else
		return 0;
}


int  jiemian::check(int x, int y) {
	if (x > N + 1 || y > N + 1 || x < 1 || y < 1) {
		return -1;
	}
	if (chessBord[x][y] != ' ') {
		return 0;
	}
	return 1;
}


int  jiemian::Checkzuobiao(int i,int j ,char flag) { //��������ѡ�ֵ�����
	int x = i, y = j;
	int begin = 0;
	int end = 0;

	int begin1 = 0;
	int end1 = 0;

//�ж����Ƿ���������  hao
	(i - 4) > 0 ? begin = i - 4 : begin = 1; //�Ѿ����м�4 ���ߴӱ߽���
	(i + 4) < N ? end = N : end = (i + 4);


	for (j, i = begin; i + 4 <= end; i++) {
		if (chessBord[i][j] == flag&&chessBord[i + 1][j] == flag&&chessBord[i + 2][j] == flag&&chessBord[i + 3][j] == flag&&chessBord[i + 4][j] == flag) {
			return 1;
		}
	}

//�ж����Ƿ��������� hao
	i = x, j = y;
	(j - 4) > 0 ? begin = j - 4 : begin = 1;  //�Ѿ����������4
	(j + 4) < N ? end = N : end = (j + 4); //���ĩβ����N�򣬴�N�����һ��


	for (i, j = begin; j + 4 <= end; j++) {
		if (chessBord[i][j] == flag&&chessBord[i][j + 1] == flag&&chessBord[i][j + 2] == flag&&chessBord[i][j + 3] == flag&&chessBord[i][j + 4] == flag) {
			return 1;
		}
	}




//�ж����Խ����Ƿ����� HAO
	int len = 0;
	i = x, j = y;
	i >j ? len = j - 1 : len = i - 1;   //�ж�i>j�����ã�������߾�С�����������ʼֵ
	if (len > 4)
		len = 4;
	begin = i - len;       //���������ʼλ��
	begin1 = j - len;      //�����꣬����Ϊ����б����������Ҫ����ͬ��


	i > j ? len = (N - i) : len = (N - j);   //��������ҲҪ���վ���߽���ĵ�ȥ��
	if (len>4)
		len = 4;
	end= i + len;       //������Ľ���λ��
	end1 = j + len;      //������Ľ���λ��


	for (int i = begin, j = begin1; (i + 4 < end) && (j + 4 < end1); i++, j++) {
		if (chessBord[i][j] == flag&&chessBord[i + 1][j + 1] == flag&&chessBord[i + 2][j + 2] == flag&&chessBord[i + 3][j + 3] == flag&&chessBord[i + 4][j + 4] == flag) {
			return 1;
		}
	}


//�жϸ��Խ����Ƿ����� HAO
	i = x, j = y;
	(i - 1) >(N - j) ? len = (N - j) : len = i - 1;  //�жϸ��Խ��������λ���Ƿ������¼�С�ľ���
	if (len > 4)
		len = 4;
	begin = i - len;       //���������ʼλ��
	begin1 = j + len;      //���������ʼλ��


	(N - i) > (j - 1) ? len = (j - 1) : len = (N - i);
	if (len>4)
		len = 4;
	end = i + len;       //������Ľ���λ��
	end1 = j - len;      //������Ľ���λ��


	for (int i = begin, j = begin1; (i + 4 < end) && (j - 4 > end1); i++, j--) {
		if (chessBord[i][j] == flag&&chessBord[i + 1][j - 1] == flag&&chessBord[i + 2][j - 2] == flag&&chessBord[i + 3][j - 3] == flag&&chessBord[i + 4][j - 4] == flag) {
			return 1;
		}
	}

//�ж������Ƿ����� .ZUIHOU
	for (int z = 1; z < N + 1; z++) {         //������û������
		for (int l = 1; l < N + 1; l++) {
			if (chessBord[z][l] == ' ')
				return -1;      //˵�������л��пո�


		}
	}


	return 0;
}






int main() {
	jiemian obj;
	obj.Jiemainbuzhi();
	while(1) {
		int x=0, y=0;
		char flager;
		cout << "���������� ��";
		cin >> command;
		if ('E' == command) {
			system("CLS");
			obj.initBoard();
			obj.Qijubuzhi();
			while ('E' == command) {
				cout << "����������";
				cin >> x >> y;
				if (1 == obj.checkcommand(x, y)) {
					break;
				}
				obj.Chesspainter(x, y);

				if (0 == obj.Checkzuobiao(x, y, ' ')) {   //�ж������Ƿ�����HAO
					cout << "DRAW: againt ?  Y  OR  N  " << endl;
					cin >> flager;
					if (flager == 'N') {
						break;
					} else {
						system("CLS");
						obj.initBoard();
					}
				}
				if (1== obj.Checkzuobiao(x, y,'x')|| 1== obj.Checkzuobiao(x, y, 'o')) {
					if (1 == obj.Checkzuobiao(x, y, 'x')) {
						obj.chessicont(1);     //��ʾ�ȷ�
						cout << "   A IS WIN" << endl;
					}
					if (1 == obj.Checkzuobiao(x, y, 'o')) {
						obj.chessicont(2);
						cout << "   B IS WIN" << endl;
					}
					cout << "againt ?  Y  OR  N  " << endl;
					cin >> flager;
					if (flager == 'N') {
						break;
					} else {
						obj.initBoard();
					}
				}
			}
		} else if ('C' == command) {
			system("CLS");
			cout << "please waitting___" << endl;
		} else {
			system("CLS");
			cout << "��������ȷ������" << endl;
			obj.Jiemainbuzhi();
		}


	}
}
