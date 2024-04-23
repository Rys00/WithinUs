#include <iostream>
#include <windows.h>


static bool running = true;

LRESULT CALLBACK platformWindowCallback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CLOSE:
      running = false;
    break;
  }
  
  return DefWindowProcA(window, msg, wParam, lParam);
}


bool platformCreateWindow(HWND window) {
  HINSTANCE instance = GetModuleHandleA(0);

  WNDCLASS wc = {};
  wc.lpfnWndProc = platformWindowCallback;
  wc.hInstance = instance;
  wc.lpszClassName = "vulkan_engine_class";

  if(!RegisterClassA(&wc)) {
    MessageBoxA(window, "Failed registering window class", "error", MB_ICONEXCLAMATION |  MB_OK);
    return false;
  }

  window = CreateWindowExA(
    WS_EX_APPWINDOW,
    "vulkan_engine_class",
    "WithinUs",
    WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPED,
    100, 100, 600, 300, 0, 0, instance, 0
  );

  if(window == 0) {
    MessageBoxA(window, "Failed creating window", "error", MB_ICONEXCLAMATION |  MB_OK);
    return false;
  }

  ShowWindow(window, SW_SHOW);
  return true;
}


int main() {
  HWND window = 0;
  if(!platformCreateWindow(window)) {
    return -1;
  }

  while(running) {

  }
  return 0;
}