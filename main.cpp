#pragma comment(linker,"/opt:nowin98")
#pragma comment(lib,"vfw32.lib")
#include <windows.h>
#include <vfw.h>

CHAR szClassName[]="window";

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static HWND hWndCap;
	switch (msg){
	case WM_CREATE:
		hWndCap=capCreateCaptureWindow("Captrue Window",WS_CHILD|WS_VISIBLE,0,0,0,0,hWnd,NULL);
		capDriverConnect(hWndCap,0);
		capPreviewRate(hWndCap,1);
		capPreview(hWndCap,TRUE);
		break;
	case WM_SIZE:
		MoveWindow(hWndCap,0,0,LOWORD(lParam),HIWORD(lParam),TRUE);
		break;
	case WM_DESTROY:
		capDriverDisconnect(hWndCap);
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd,msg,wParam,lParam));
	}
	return (0L);
}

int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hPreInst,
				   LPSTR pCmdLine,int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;
	if(!hPreInst){
		wndclass.style=CS_HREDRAW|CS_VREDRAW;
		wndclass.lpfnWndProc=WndProc;
		wndclass.cbClsExtra=0;
		wndclass.cbWndExtra=0;
		wndclass.hInstance =hinst;
		wndclass.hIcon=NULL;
		wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
		wndclass.lpszMenuName=NULL;
		wndclass.lpszClassName=szClassName;
		if(!RegisterClass(&wndclass))
			return FALSE;
	}
	hWnd=CreateWindow(szClassName,
		"Video for Windows を使ったビデオキャプチャー",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinst,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}


