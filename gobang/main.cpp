
#include <windows.h>
#include <math.h>
#define NUM 1000
#define TWOPI (2*3.14159)

LRESULT CALLBACK WndProc (HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,		//当前实例句柄
                   HINSTANCE hPrevInstance, //先前实例句柄
                   LPSTR lpCmdLine,			//命令行
                   int iCmdShow) {		//显示状态
	static TCHAR szAppName[] = TEXT("画图");
	//窗口句柄
	HWND hwnd;
	//消息
	MSG msg;
	//窗口类
	WNDCLASS wndclass;
	//窗口风格：当移动窗口或者改变大小时重绘窗口
	wndclass.style		   =  CS_HREDRAW | CS_VREDRAW;
	//指明回调函数
	wndclass.lpfnWndProc   = WndProc;
	//额外的比特用来确认下一个窗口类的位置，暂时不用
	wndclass.cbClsExtra    = 0;
	//额外的比特用来确认下一个窗口实例的位置，暂时不用
	wndclass.cbWndExtra    = 0;
	//实例句柄
	wndclass.hInstance     = hInstance;
	//装载图标
	wndclass.hIcon		   = LoadIcon(NULL, IDI_APPLICATION);
	//装载光标
	wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
	//背景为白色
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	//菜单：暂时没有
	wndclass.lpszMenuName  = NULL;
	//窗口类名
	wndclass.lpszClassName = szAppName;

	//注册窗口
	if(!RegisterClass(&wndclass)) {
		return -1;
	}

	//创建窗口
	hwnd = CreateWindow(szAppName,				//窗口类的名称，必须是已经注册的
	                    TEXT("我的画图"),		//窗口标题
	                    WS_OVERLAPPEDWINDOW,	//窗口风格
	                    CW_USEDEFAULT,			//X坐标
	                    CW_USEDEFAULT,			//Y坐标
	                    CW_USEDEFAULT,			//宽度
	                    CW_USEDEFAULT,			//高度
	                    NULL,					//父窗口句柄
	                    NULL,					//菜单窗口句柄
	                    hInstance,				//高级版本的windos忽略
	                    NULL);

	//显示窗口
	//ShowWindow(hwnd,SW_SHOWNA);
	ShowWindow (hwnd, iCmdShow);

	//更新窗口
	UpdateWindow(hwnd);

	//消息循环
	while(GetMessage(&msg,NULL,0,0)) {

		TranslateMessage(&msg);
		//将消息给窗口
		DispatchMessage(&msg);

	}

	return msg.wParam;

}


LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	int i,j;
	static int cxClient,cyClient;
	POINT apt[NUM];
	switch(message) {
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);


			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			/*
			//画出渐变的颜色
			for(i = 0;i < 500;i++)
			{
				for(j = 0; j < 26;j++)
				{
					SetPixel(hdc,200+i,200+j,RGB(i,j*10,0));
				}
			}
			*/
			//划线
			/*
			//用点划线
			for(i = 0; i < 500;i++)
			{
				SetPixel(hdc,0+i,200,RGB(0,0,0));
			}
			*/
			/*
			//用函数划线
			MoveToEx	(hdc,0,			cyClient/2,NULL);
			LineTo		(hdc,cxClient,	cyClient/2);
			for(int i = 0;  i< NUM;i++)
			{
				//把x轴等分成1000份
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int) (cyClient / 2 * (1-sin(TWOPI * i /NUM)));
				//LineTo(hdc,apt[i].x,apt[i].y);


			}
			//Polyline绘制，速度快于在for循环内LineTo
			Polyline(hdc,apt,NUM);
			*/
			//绘制矩形
			Rectangle(hdc,	cxClient / 8,		cyClient / 8,
			          7 * cxClient / 8,	7 * cyClient / 8);
			//绘制对角线
			MoveToEx	(hdc,		0,			0,NULL);
			LineTo		(hdc,cxClient,	cyClient);
			MoveToEx	(hdc,		0,cyClient,NULL);
			LineTo		(hdc,cxClient,		0);
			//绘制椭圆
			Ellipse(hdc,	cxClient / 8,		cyClient / 8,
			        7 * cxClient / 8,	7 * cyClient / 8);
			//绘制圆角矩形
			RoundRect(hdc,	cxClient / 4,		cyClient / 4,
			          3 * cxClient / 4,	3 * cyClient / 4,
			          //最后两个参数是圆角矩形的圆角形成的椭圆的长和宽
			          cxClient / 4,		cyClient / 4);
			EndPaint(hwnd,&ps);
			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
