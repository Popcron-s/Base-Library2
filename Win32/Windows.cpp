#include "Windows.h"

Windows* Windows::m_pSingleton = 0x00;

Windows* Windows::GetSingleton(){
	if(m_pSingleton == 0x00){
		m_pSingleton = new Windows;
	}
	return m_pSingleton;
}
void Windows::Destroy(){
	if(m_pSingleton != 0x00){
		delete m_pSingleton;
		m_pSingleton = 0x00;
	}
}

void Windows::Create(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, int x, int y){
	m_WndClass.hInstance = hInstance;   			// 인스턴스에 대한 핸들
	m_WndClass.lpszClassName = Title;		// Window 클래스 이름
	m_WndClass.lpfnWndProc = WndProc;  			// window 함수
	m_WndClass.style = 0;     					// 기본 스타일 
	m_WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE( IDI_APPLICATION)); // 아이콘 스타일
	m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// 커서 스타일
	m_WndClass.lpszMenuName = NULL;  			// 메뉴 사용하지 않음
	m_WndClass.cbClsExtra = 0;    				// 추가 정보는 필요하지 않음(왼도우가 사용하는 예약 영역)
	m_WndClass.cbWndExtra = 0;    				// 추가 정보는 필요하지 않음
	m_WndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH) ; // 윈도우 배경색을 흰색으로 함

	if(!RegisterClass(&m_WndClass)){
		return;
	}

	// GetSystemMextrics(nInfo)
	// nIndex
	// SM_CXSCREEN = 주 디스플레이 가로사이즈
	// SM_CYSCREEN = 주 디스플레이 세로사이즈
	// SM_CXSIZEFRAME = 가로프레임 사이즈
	// SM_CYSIZEFRAME = 세로프레임 사이즈
	// SM_CYCAPTION = 캡션바의 높이

	m_hwnd = CreateWindow(
		Title,					// 윈도우 클래스 이름
		Title,					// 타이틀
		WS_PCSWINDOW,		// 윈도우 스타일 (normal = WS_OVERLAPPEDWINDOW)
		(GetSystemMetrics(SM_CXSCREEN) - (x + FRAMESIZE_X))/2,//CW_USEDEFAULT,				// X좌표 - Windows가 결정
		(GetSystemMetrics(SM_CYSCREEN) - (y + FRAMESIZE_Y))/2,//CW_USEDEFAULT,				// Y좌표 - Windows가 결정
		x + FRAMESIZE_X,						// 넓이 - windows가 결정
		y + FRAMESIZE_Y,						// 높이 - windows가 결정
		HWND_DESKTOP,				// 부모 window 없음
		NULL,						// 메뉴 사용하지 않음
		hInstance,					// 이 프로그램의 인스턴스 핸들
		(void*)this);						// 추가적인 매개변수 없음

	ShowWindow(m_hwnd, *nCmdShow);
	UpdateWindow(m_hwnd);

	ZeroMemory(&m_msg,sizeof(m_msg));

	m_WinSize.x = x;
	m_WinSize.y = y;

	m_hInstance = hInstance;
}

LRESULT CALLBACK Windows::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	Windows* pWindow = Windows::GetSingleton();
	bool Processed = false;

	switch(iMsg){
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		Processed = pWindow->MessageHandler(hwnd, iMsg, wParam, lParam);
		break;
	}
	if( Processed == false ){
		return DefWindowProc (hwnd, iMsg, wParam, lParam);
	}
	else{
		return 0;
	}
}

void Windows::Run(){
	while(WM_QUIT != m_msg.message){
		if(PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE)){
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		if(MainLoop != NULL){
			MainLoop();
		}
	}
}