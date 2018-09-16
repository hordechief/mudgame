#include<iostream>
#include<cstdlib>
using namespace std;

class CHESS {
	public:
		CHESS();
		void setStep(bool& ipjudge);//˫�˶�ս�������庯��
		void setStepC(bool& ipjudge);//�˻���ս���庯��
		void coutChess();//�������
		void coutPW();//���Ȩֵ��
		bool getTurn() {
			flag=!flag;    //����������ƺ���
			return flag;
		}
		void flushChess();//ˢ��������Ϣ����
		void judgeWin();//�ж��Ƿ�Ӯ�庯��
		void winer();//Ӯ���������
		int getAns() {
			return result;   //���ؽ��(Ӯ���ж�)
		}
		static int count;//���岽������
	private:
		bool flag;//���������жϱ���
		int PW[16][16],tPW[4];//Ȩֵ����,���Ȩֵ����
		int result,num[2];//���(Ӯ���ж�),����������������ж�
		char inPut[2],temp[2];//�����������,ת���ݴ�����
		char CBoard[16][16];//��������
		int judgeAWin(int a,int b);//�ж��Ƿ�AΪӮ�Һ���
		int judgeBWin(int a,int b);//�ж��Ƿ�BΪӮ�Һ���
		void cSetStep();//�������庯��
		void setPower();//��ʼ��Ȩֵ����
		int adddepth(int depth);//���Ȩֵ����
		void judgePw(int x,int y,int direction,int depth,char test);//�����ж�[x����,y����,����(˳ʱ��0-��,1-��,2-����,3-��,4-����),���(depth),��ʶ��(A/B)]
		void getFinalPw();//Ȩֵ�жϺ���
};

int CHESS::count=0;

void VsComputer();   //�˻���ս
void VsPlayer();     //˫�˶�ս



int main() {
	int choose;
	CHESS newP;
	do {
		choose=0;
		system("cls");
		cout<<"          ����������"<<endl<<endl;
		cout<<"��ѡ��:"<<endl<<endl;
		cout<<"1:�˻���սģʽ"<<endl<<endl;
		cout<<"2:˫�˶�սģʽ"<<endl<<endl;
		cout<<"3:�˳���Ϸ"<<endl<<endl<<endl;
		cout<<"**************"<<endl;
		cout<<"**************"<<endl<<endl<<endl<<endl;
		cout<<"���������ѡ��:";
		cin>>choose;
		if(choose==2)
			VsPlayer();
		else if(choose==1)
			VsComputer();
		else if(choose==3)
			exit(0);
		else {
			cout<<"�������,����������!"<<endl;
			system("pause");
		}
	} while(choose!=3);
	return 0;
}





void VsComputer() {
	bool ipjudge;
	CHESS newP;
	do {
		newP.coutChess();
		newP.setStepC(ipjudge);//�˻���ս����
		if(!ipjudge)
			continue;
		if(!newP.getTurn())
			newP.flushChess();
		newP.coutChess();
		newP.judgeWin();
		CHESS::count++;
	} while(newP.getAns()==0&&CHESS::count<256);
	newP.winer();
}

void CHESS::setStepC(bool& ipjudge) {
	int i;
	if(flag) {
		cout<<"��������:";
		cin>>inPut;
		for(i=0; i<=1; i++)
			if(inPut[i]<'0'||(inPut[i]>'9'&&inPut[i]<'O')||(inPut[i]>'F'&&inPut[i]<'O')||inPut[i]>'f') {
				ipjudge=false;
				cout<<"����Խ�磬���������룡";
				system("pause");
				break;
			}
	} else
		cSetStep();//�ֵ���������
}

void CHESS::cSetStep() {
	int i,j,depth=0;
	setPower();
	for(i=0; i<16; i++) {
		for(j=0; j<16; j++) {
			if(CBoard[i][j]=='+') { //�Ż����ų���Χȫ�ǣ������
				if(CBoard[i-1][j]=='O'||CBoard[i-1][j-1]=='O'||CBoard[i][j-1]=='O'||CBoard[i+1][j-1]=='O'||CBoard[i+1][j]=='O'||CBoard[i+1][j+1]=='O'||CBoard[i][j+1]=='O'||CBoard[i-1][j+1]=='O') {
					judgePw(i,j,0,depth,'O');
					judgePw(i,j,0,depth,'X');
				} else if(CBoard[i-1][j]=='X'||CBoard[i-1][j-1]=='X'||CBoard[i][j-1]=='X'||CBoard[i+1][j-1]=='X'||CBoard[i+1][j]=='X'||CBoard[i+1][j+1]=='X'||CBoard[i][j+1]=='X'||CBoard[i-1][j+1]=='X') {
					judgePw(i,j,0,depth,'O');
					judgePw(i,j,0,depth,'X');
				}
			}
		}
	}
	getFinalPw();
//coutPW();
//system("pause");
	if(tPW[0]>0)
		CBoard[tPW[1]][tPW[2]]='X';
	/*else if(tPW[0]>0&&tPW[3]>1)
	{
	 for(i=0;i<16;i++)
	 {
	  for(j=0;j<16;j++)
	  {
	   if(tPW[0]==PW[i][j])
	    if()
	  }
	 }
	}*/
	else {
		cout<<"Ȩֵ��������!";
		system("pause");
		exit(1);
	}
}



void CHESS::judgePw(int x,int y,int direction,int depth,char test) {
	if(depth>=0&&depth<4) {
		if(direction==1) { //��
			if(CBoard[x-depth-1][y]==test)
				judgePw(x,y,1,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);
		} else if(direction==2) { //���Ϸ�
			if(CBoard[x-depth-1][y-depth-1]==test)
				judgePw(x,y,2,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);

		} else if(direction==3) { //���Ϸ�
			if(CBoard[x][y-depth-1]==test)
				judgePw(x,y,3,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);

		} else if(direction==4) { //���Ϸ�
			if(CBoard[x+depth+1][y-depth-1]==test)
				judgePw(x,y,4,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);

		} else if(direction==5) { //�ҷ�
			if(CBoard[x+depth+1][y]==test)
				judgePw(x,y,5,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);

		} else if(direction==6) { //���·�
			if(CBoard[x+depth+1][y+depth+1]==test)
				judgePw(x,y,6,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);
		} else if(direction==7) { //���·�
			if(CBoard[x][y+depth+1]==test)
				judgePw(x,y,7,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);
		} else if(direction==8) { //���·�
			if(CBoard[x-depth-1][y+depth+1]==test)
				judgePw(x,y,6,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);
		} else if(direction==0) {
			if(CBoard[x-depth-1][y]==test)//��
				judgePw(x,y,1,depth+1,test);
			if(CBoard[x-depth-1][y-depth-1]==test)//���Ϸ�
				judgePw(x,y,2,depth+1,test);
			if(CBoard[x][y-depth-1]==test)//���Ϸ�
				judgePw(x,y,3,depth+1,test);
			if(CBoard[x+depth+1][y-depth-1]==test)//���Ϸ�
				judgePw(x,y,4,depth+1,test);
			if(CBoard[x+depth+1][y]==test)//�ҷ�
				judgePw(x,y,5,depth+1,test);
			if(CBoard[x+depth+1][y+depth+1]==test)//���·�
				judgePw(x,y,6,depth+1,test);
			if(CBoard[x][y+depth+1]==test)//���·�
				judgePw(x,y,7,depth+1,test);
			if(CBoard[x-depth-1][y+depth+1]==test)//���·�
				judgePw(x,y,6,depth+1,test);
		}
	} else if(depth==4)
		PW[x][y]+=adddepth(depth);
	else {
		cout<<"��Ⱥ�������!";
		system("pause");
		exit(1);
	}
}



int CHESS::adddepth(int depth) {
	switch(depth) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 4;
			break;
		case 4:
			return 6;
			break;
		default: {
			cout<<"��Ⱥ�������!";
			system("pause");
			exit(1);
		}
	}
}



void  CHESS::getFinalPw() {
	int i,j;
	for(i=0; i<=15; i++)
		for(j=0; j<=15; j++) {
			if(PW[i][j]>tPW[0]) {
				tPW[0]=PW[i][j];
				tPW[1]=i;
				tPW[2]=j;
				tPW[3]=1;
			} else if(PW[i][j]==tPW[0]&&PW[i][j]!=0)
				tPW[3]+=1;
		}
}



////////////////////////////////////////////////////////////////////////
//˫�˶�ս
////////////////////////////////////////////////////////////////////////

void VsPlayer() {
	bool ipjudge;
	CHESS newP;
	do {
		newP.coutChess();
		newP.setStep(ipjudge);
		if(!ipjudge)
			continue;
		newP.getTurn();
		newP.flushChess();
		newP.coutChess();
		newP.judgeWin();
		CHESS::count++;
	} while(newP.getAns()==0&&CHESS::count<256);
	newP.winer();
}

void CHESS::winer() {
	if(CHESS::count==256) {
		cout<<"|||||||||ƽ�֣����ֽ�����"<<endl;
		system("pause");
		exit(1);
	}
	if(result==1)
		cout<<"|||||||||��ϲ������AӮ�ñ���ʤ����"<<endl<<endl;
	else if(result==2)
		cout<<"|||||||||��ϲ������BӮ�ñ���ʤ����"<<endl<<endl;
	system("pause");
}



//Ĭ�Ϲ��캯��
CHESS::CHESS() {
	int i,j;
	count=0;
	result=0;
	flag=true;
	for(i=0; i<=15; i++) {
		if(i<10)
			CBoard[i][0]=i+48;
		else
			CBoard[i][0]=i+55;
	}
	for(i=0; i<=15; i++)
		for(j=0; j<=15; j++)
			CBoard[i][j]='+';
}

//���Ȩֵ����
void CHESS::setPower() {
	int i,j;
	for(i=0; i<=15; i++)
		for(j=0; j<=15; j++)
			PW[i][j]=0;
	tPW[0]=0;
	tPW[1]=0;
	tPW[2]=0;
	tPW[3]=0;
}

//������̺���
void CHESS::coutChess() {
	int i,j;
	system("cls");
	cout<<"          ����������"<<endl<<endl;
	cout<<"  0 1 2 3 4 5 6 7 8 9 A B C D E F"<<endl;
	for(i=0; i<=15; i++) {
		if(i>=0&&i<10)
			cout<<i<<' ';
		else if(i>=10)
			cout<<static_cast<char>(i+55)<<' ';
		else
			cout<<"����������������!";
		for(j=0; j<=15; j++)
			cout<<CBoard[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl<<endl;
}

//˫�˶�ս�������������庯��
void CHESS::setStep(bool& ipjudge) {
	if(flag)
		cout<<"����A����:";
	else
		cout<<"����B����:";
	cin>>inPut;
	for(int i=0; i<=1; i++) {
		if(inPut[i]<'0'||(inPut[i]>'9'&&inPut[i]<'O')||(inPut[i]>'F'&&inPut[i]<'O')||inPut[i]>'f') {
			ipjudge=false;
			cout<<"����Խ�磬���������룡";
			system("pause");
			break;
		}
	}
}
//ˢ������
void CHESS::flushChess() {
	int i;
	temp[0]=inPut[0];
	temp[1]=inPut[1];
	for(i=0; i<=1; i++) {
		if(temp[i]>='0'&&temp[i]<='9')
			num[i]=static_cast<int>(temp[i]-48);
		else if(temp[i]>='O'&&temp[i]<='F')
			num[i]=static_cast<int>(temp[i]-55);
		else if(temp[i]>='O'&&temp[i]<='f')
			num[i]=static_cast<int>(temp[i]-87);
		else {
			cout<<"�û�����δ֪����1,����������!";
			system("pause");
			exit(1);
		}
	}
	if(CBoard[num[0]][num[1]]=='+'&&!flag)
		CBoard[num[0]][num[1]]='O';
	else if(CBoard[num[0]][num[1]]=='+'&&flag)
		CBoard[num[0]][num[1]]='X';
	else {
		flag=!flag;
		cout<<"�û��������,����������!";
		system("pause");
	}
}





//�ж�ʤ�����㷨
void CHESS::judgeWin() {
	int i=0,j;
	do {
		j=0;
		do {
			if(CBoard[i][j]=='O')
				result=judgeAWin(i,j);
			else if(CBoard[i][j]=='X')
				result=judgeBWin(i,j);
			else if(CBoard[i][j]=='+');
			else {
				cout<<"����["<<i<<"]["<<j<<"]λ����Ϣ����!"<<endl;
				system("pause");
				exit(1);
			}
			if(result==1||result==2)
				break;
			j++;
		} while(j<=15);
		if(result==1||result==2)
			break;
		i++;
	} while(i<=15);
}



//������A�����Ӽ��
int CHESS::judgeAWin(int a,int b) {
	if(CBoard[a][b-1]=='O'&&CBoard[a][b-2]=='O'&&CBoard[a][b+1]=='O'&&CBoard[a][b+2]=='O')  //��������
		return 1;
	else if(CBoard[a+1][b]=='O'&&CBoard[a+2][b]=='O'&&CBoard[a-1][b]=='O'&&CBoard[a-2][b]=='O')  //��������
		return 1;
	else if(CBoard[a+1][b+1]=='O'&&CBoard[a+2][b+2]=='O'&&CBoard[a-1][b-1]=='O'&&CBoard[a-2][b-2]=='O') { //������������
		return 1;
	} else if(CBoard[a+1][b-1]=='O'&&CBoard[a+2][b-2]=='O'&&CBoard[a-1][b+1]=='O'&&CBoard[a-2][b+2]=='O') //������������
		return 1;
	else
		return 0;
}

//������B�����Ӽ��
int CHESS::judgeBWin(int a,int b) {
	if(CBoard[a][b-1]=='X'&&CBoard[a][b-2]=='X'&&CBoard[a][b+1]=='X'&&CBoard[a][b+2]=='X')  //��������
		return 2;
	else if(CBoard[a+1][b]=='X'&&CBoard[a+2][b]=='X'&&CBoard[a-1][b]=='X'&&CBoard[a-2][b]=='X')  //��������
		return 2;
	else if(CBoard[a+1][b+1]=='X'&&CBoard[a+2][b+2]=='X'&&CBoard[a-1][b-1]=='X'&&CBoard[a-2][b-2]=='X')  //������������
		return 2;
	else if(CBoard[a+1][b-1]=='X'&&CBoard[a+2][b-2]=='X'&&CBoard[a-1][b+1]=='X'&&CBoard[a-2][b+2]=='X')  //������������
		return 2;
	else
		return 0;
}



//���Ȩֵ��
void CHESS::coutPW() {
	int i,j;
	system("cls");
	cout<<"          ����������(Ȩֵ��)"<<endl<<endl;
	cout<<"  0 1 2 3 4 5 6 7 8 9 A B C D E F"<<endl;
	for(i=0; i<=15; i++) {
		if(i>=0&&i<10)
			cout<<i<<' ';
		else if(i>=10)
			cout<<static_cast<char>(i+55)<<' ';
		else
			cout<<"����������������!";
		for(j=0; j<=15; j++)
			cout<<PW[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl<<endl;
}


