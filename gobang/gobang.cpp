#include<iostream>
#include<cstdlib>
using namespace std;

class CHESS {
	public:
		CHESS();
		void setStep(bool& ipjudge);//双人对战轮流走棋函数
		void setStepC(bool& ipjudge);//人机对战走棋函数
		void coutChess();//输出棋盘
		void coutPW();//输出权值表
		bool getTurn() {
			flag=!flag;    //轮流走棋控制函数
			return flag;
		}
		void flushChess();//刷新棋盘信息函数
		void judgeWin();//判断是否赢棋函数
		void winer();//赢家输出函数
		int getAns() {
			return result;   //返回结果(赢家判断)
		}
		static int count;//走棋步数变量
	private:
		bool flag;//轮流走棋判断变量
		int PW[16][16],tPW[4];//权值变量,最高权值变量
		int result,num[2];//结果(赢家判断),玩家输入棋子坐标判断
		char inPut[2],temp[2];//玩家输入数据,转换暂存数据
		char CBoard[16][16];//棋盘数据
		int judgeAWin(int a,int b);//判断是否A为赢家函数
		int judgeBWin(int a,int b);//判断是否B为赢家函数
		void cSetStep();//电脑走棋函数
		void setPower();//初始化权值函数
		int adddepth(int depth);//填充权值函数
		void judgePw(int x,int y,int direction,int depth,char test);//棋子判断[x坐标,y坐标,方向(顺时针0-无,1-左,2-左上,3-上,4-右上),深度(depth),标识符(A/B)]
		void getFinalPw();//权值判断函数
};

int CHESS::count=0;

void VsComputer();   //人机对战
void VsPlayer();     //双人对战



int main() {
	int choose;
	CHESS newP;
	do {
		choose=0;
		system("cls");
		cout<<"          欢乐五子棋"<<endl<<endl;
		cout<<"请选择:"<<endl<<endl;
		cout<<"1:人机对战模式"<<endl<<endl;
		cout<<"2:双人对战模式"<<endl<<endl;
		cout<<"3:退出游戏"<<endl<<endl<<endl;
		cout<<"**************"<<endl;
		cout<<"**************"<<endl<<endl<<endl<<endl;
		cout<<"请输入你的选择:";
		cin>>choose;
		if(choose==2)
			VsPlayer();
		else if(choose==1)
			VsComputer();
		else if(choose==3)
			exit(0);
		else {
			cout<<"输入错误,请重新输入!"<<endl;
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
		newP.setStepC(ipjudge);//人机对战函数
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
		cout<<"棋手走棋:";
		cin>>inPut;
		for(i=0; i<=1; i++)
			if(inPut[i]<'0'||(inPut[i]>'9'&&inPut[i]<'O')||(inPut[i]>'F'&&inPut[i]<'O')||inPut[i]>'f') {
				ipjudge=false;
				cout<<"输入越界，请重新输入！";
				system("pause");
				break;
			}
	} else
		cSetStep();//轮到电脑走棋
}

void CHESS::cSetStep() {
	int i,j,depth=0;
	setPower();
	for(i=0; i<16; i++) {
		for(j=0; j<16; j++) {
			if(CBoard[i][j]=='+') { //优化：排除周围全是＋的情况
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
		cout<<"权值函数错误!";
		system("pause");
		exit(1);
	}
}



void CHESS::judgePw(int x,int y,int direction,int depth,char test) {
	if(depth>=0&&depth<4) {
		if(direction==1) { //左方
			if(CBoard[x-depth-1][y]==test)
				judgePw(x,y,1,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);
		} else if(direction==2) { //左上方
			if(CBoard[x-depth-1][y-depth-1]==test)
				judgePw(x,y,2,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);

		} else if(direction==3) { //正上方
			if(CBoard[x][y-depth-1]==test)
				judgePw(x,y,3,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);

		} else if(direction==4) { //右上方
			if(CBoard[x+depth+1][y-depth-1]==test)
				judgePw(x,y,4,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);

		} else if(direction==5) { //右方
			if(CBoard[x+depth+1][y]==test)
				judgePw(x,y,5,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);

		} else if(direction==6) { //右下方
			if(CBoard[x+depth+1][y+depth+1]==test)
				judgePw(x,y,6,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);
		} else if(direction==7) { //正下方
			if(CBoard[x][y+depth+1]==test)
				judgePw(x,y,7,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);
		} else if(direction==8) { //左下方
			if(CBoard[x-depth-1][y+depth+1]==test)
				judgePw(x,y,6,depth+1,test);
			else
				PW[x][y]+=adddepth(depth);
		} else if(direction==0) {
			if(CBoard[x-depth-1][y]==test)//左方
				judgePw(x,y,1,depth+1,test);
			if(CBoard[x-depth-1][y-depth-1]==test)//左上方
				judgePw(x,y,2,depth+1,test);
			if(CBoard[x][y-depth-1]==test)//正上方
				judgePw(x,y,3,depth+1,test);
			if(CBoard[x+depth+1][y-depth-1]==test)//右上方
				judgePw(x,y,4,depth+1,test);
			if(CBoard[x+depth+1][y]==test)//右方
				judgePw(x,y,5,depth+1,test);
			if(CBoard[x+depth+1][y+depth+1]==test)//右下方
				judgePw(x,y,6,depth+1,test);
			if(CBoard[x][y+depth+1]==test)//正下方
				judgePw(x,y,7,depth+1,test);
			if(CBoard[x-depth-1][y+depth+1]==test)//左下方
				judgePw(x,y,6,depth+1,test);
		}
	} else if(depth==4)
		PW[x][y]+=adddepth(depth);
	else {
		cout<<"深度函数出错!";
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
			cout<<"深度函数错误!";
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
//双人对战
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
		cout<<"|||||||||平局！本局结束！"<<endl;
		system("pause");
		exit(1);
	}
	if(result==1)
		cout<<"|||||||||恭喜！棋手A赢得本局胜利！"<<endl<<endl;
	else if(result==2)
		cout<<"|||||||||恭喜！棋手B赢得本局胜利！"<<endl<<endl;
	system("pause");
}



//默认构造函数
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

//填充权值函数
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

//输出棋盘函数
void CHESS::coutChess() {
	int i,j;
	system("cls");
	cout<<"          欢乐五子棋"<<endl<<endl;
	cout<<"  0 1 2 3 4 5 6 7 8 9 A B C D E F"<<endl;
	for(i=0; i<=15; i++) {
		if(i>=0&&i<10)
			cout<<i<<' ';
		else if(i>=10)
			cout<<static_cast<char>(i+55)<<' ';
		else
			cout<<"棋盘列序号输出错误!";
		for(j=0; j<=15; j++)
			cout<<CBoard[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl<<endl;
}

//双人对战，棋手轮流走棋函数
void CHESS::setStep(bool& ipjudge) {
	if(flag)
		cout<<"棋手A走棋:";
	else
		cout<<"棋手B走棋:";
	cin>>inPut;
	for(int i=0; i<=1; i++) {
		if(inPut[i]<'0'||(inPut[i]>'9'&&inPut[i]<'O')||(inPut[i]>'F'&&inPut[i]<'O')||inPut[i]>'f') {
			ipjudge=false;
			cout<<"输入越界，请重新输入！";
			system("pause");
			break;
		}
	}
}
//刷新棋盘
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
			cout<<"用户输入未知错误1,请重新输入!";
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
		cout<<"用户输入错误,请重新输入!";
		system("pause");
	}
}





//判断胜出新算法
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
				cout<<"棋盘["<<i<<"]["<<j<<"]位置信息错误!"<<endl;
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



//对棋手A的棋子检测
int CHESS::judgeAWin(int a,int b) {
	if(CBoard[a][b-1]=='O'&&CBoard[a][b-2]=='O'&&CBoard[a][b+1]=='O'&&CBoard[a][b+2]=='O')  //横向五子
		return 1;
	else if(CBoard[a+1][b]=='O'&&CBoard[a+2][b]=='O'&&CBoard[a-1][b]=='O'&&CBoard[a-2][b]=='O')  //纵向五子
		return 1;
	else if(CBoard[a+1][b+1]=='O'&&CBoard[a+2][b+2]=='O'&&CBoard[a-1][b-1]=='O'&&CBoard[a-2][b-2]=='O') { //左上右下五子
		return 1;
	} else if(CBoard[a+1][b-1]=='O'&&CBoard[a+2][b-2]=='O'&&CBoard[a-1][b+1]=='O'&&CBoard[a-2][b+2]=='O') //左下右上五子
		return 1;
	else
		return 0;
}

//对棋手B的棋子检测
int CHESS::judgeBWin(int a,int b) {
	if(CBoard[a][b-1]=='X'&&CBoard[a][b-2]=='X'&&CBoard[a][b+1]=='X'&&CBoard[a][b+2]=='X')  //横向五子
		return 2;
	else if(CBoard[a+1][b]=='X'&&CBoard[a+2][b]=='X'&&CBoard[a-1][b]=='X'&&CBoard[a-2][b]=='X')  //纵向五子
		return 2;
	else if(CBoard[a+1][b+1]=='X'&&CBoard[a+2][b+2]=='X'&&CBoard[a-1][b-1]=='X'&&CBoard[a-2][b-2]=='X')  //左上右下五子
		return 2;
	else if(CBoard[a+1][b-1]=='X'&&CBoard[a+2][b-2]=='X'&&CBoard[a-1][b+1]=='X'&&CBoard[a-2][b+2]=='X')  //左下右上五子
		return 2;
	else
		return 0;
}



//输出权值表
void CHESS::coutPW() {
	int i,j;
	system("cls");
	cout<<"          欢乐五子棋(权值表)"<<endl<<endl;
	cout<<"  0 1 2 3 4 5 6 7 8 9 A B C D E F"<<endl;
	for(i=0; i<=15; i++) {
		if(i>=0&&i<10)
			cout<<i<<' ';
		else if(i>=10)
			cout<<static_cast<char>(i+55)<<' ';
		else
			cout<<"棋盘列序号输出错误!";
		for(j=0; j<=15; j++)
			cout<<PW[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl<<endl;
}


