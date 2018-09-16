
#include <windows.h>
#include <math.h>
#define NUM 1000
#define TWOPI (2*3.14159)

LRESULT CALLBACK WndProc (HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,		//��ǰʵ�����
                   HINSTANCE hPrevInstance, //��ǰʵ�����
                   LPSTR lpCmdLine,			//������
                   int iCmdShow) {		//��ʾ״̬
	static TCHAR szAppName[] = TEXT("��ͼ");
	//���ھ��
	HWND hwnd;
	//��Ϣ
	MSG msg;
	//������
	WNDCLASS wndclass;
	//���ڷ�񣺵��ƶ����ڻ��߸ı��Сʱ�ػ洰��
	wndclass.style		   =  CS_HREDRAW | CS_VREDRAW;
	//ָ���ص�����
	wndclass.lpfnWndProc   = WndProc;
	//����ı�������ȷ����һ���������λ�ã���ʱ����
	wndclass.cbClsExtra    = 0;
	//����ı�������ȷ����һ������ʵ����λ�ã���ʱ����
	wndclass.cbWndExtra    = 0;
	//ʵ�����
	wndclass.hInstance     = hInstance;
	//װ��ͼ��
	wndclass.hIcon		   = LoadIcon(NULL, IDI_APPLICATION);
	//װ�ع��
	wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
	//����Ϊ��ɫ
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	//�˵�����ʱû��
	wndclass.lpszMenuName  = NULL;
	//��������
	wndclass.lpszClassName = szAppName;

	//ע�ᴰ��
	if(!RegisterClass(&wndclass)) {
		return -1;
	}

	//��������
	hwnd = CreateWindow(szAppName,				//����������ƣ��������Ѿ�ע���
	                    TEXT("�ҵĻ�ͼ"),		//���ڱ���
	                    WS_OVERLAPPEDWINDOW,	//���ڷ��
	                    CW_USEDEFAULT,			//X����
	                    CW_USEDEFAULT,			//Y����
	                    CW_USEDEFAULT,			//���
	                    CW_USEDEFAULT,			//�߶�
	                    NULL,					//�����ھ��
	                    NULL,					//�˵����ھ��
	                    hInstance,				//�߼��汾��windos����
	                    NULL);

	//��ʾ����
	//ShowWindow(hwnd,SW_SHOWNA);
	ShowWindow (hwnd, iCmdShow);

	//���´���
	UpdateWindow(hwnd);

	//��Ϣѭ��
	while(GetMessage(&msg,NULL,0,0)) {

		TranslateMessage(&msg);
		//����Ϣ������
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
			//�����������ɫ
			for(i = 0;i < 500;i++)
			{
				for(j = 0; j < 26;j++)
				{
					SetPixel(hdc,200+i,200+j,RGB(i,j*10,0));
				}
			}
			*/
			//����
			/*
			//�õ㻮��
			for(i = 0; i < 500;i++)
			{
				SetPixel(hdc,0+i,200,RGB(0,0,0));
			}
			*/
			/*
			//�ú�������
			MoveToEx	(hdc,0,			cyClient/2,NULL);
			LineTo		(hdc,cxClient,	cyClient/2);
			for(int i = 0;  i< NUM;i++)
			{
				//��x��ȷֳ�1000��
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int) (cyClient / 2 * (1-sin(TWOPI * i /NUM)));
				//LineTo(hdc,apt[i].x,apt[i].y);


			}
			//Polyline���ƣ��ٶȿ�����forѭ����LineTo
			Polyline(hdc,apt,NUM);
			*/
			//���ƾ���
			Rectangle(hdc,	cxClient / 8,		cyClient / 8,
			          7 * cxClient / 8,	7 * cyClient / 8);
			//���ƶԽ���
			MoveToEx	(hdc,		0,			0,NULL);
			LineTo		(hdc,cxClient,	cyClient);
			MoveToEx	(hdc,		0,cyClient,NULL);
			LineTo		(hdc,cxClient,		0);
			//������Բ
			Ellipse(hdc,	cxClient / 8,		cyClient / 8,
			        7 * cxClient / 8,	7 * cyClient / 8);
			//����Բ�Ǿ���
			RoundRect(hdc,	cxClient / 4,		cyClient / 4,
			          3 * cxClient / 4,	3 * cyClient / 4,
			          //�������������Բ�Ǿ��ε�Բ���γɵ���Բ�ĳ��Ϳ�
			          cxClient / 4,		cyClient / 4);
			EndPaint(hwnd,&ps);
			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
