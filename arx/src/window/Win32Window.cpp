/*
 * Copyright 2011-2013 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "window/Win32Window.h"

#include <windows.h>
#include <map>

#include "graphics/Renderer.h"
#include "io/log/Logger.h"
#include "math/Rectangle.h"

// MinGW doesn't define this
#ifndef GET_SC_WPARAM
#define GET_SC_WPARAM(x) (int(x) & 0x0000fff0)
#endif

#define IDI_MAIN 106

WNDCLASS Win32Window::m_WindowClass;
int Win32Window::m_WindowClassRegistered = 0;
std::map<HWND, Win32Window *>  Win32Window::m_WindowsMap;
const char * ARX_WINDOW_CLASS = "ARX_WINDOW_CLASS";

Win32Window::Win32Window() : m_hWnd(NULL) , m_HijackedWindowProc(0) { }

Win32Window::~Win32Window() {
	
	if(m_hWnd) {
		DestroyWindow(m_hWnd);
	}
	
	unregisterWindowClass();
}

bool Win32Window::registerWindowClass() {
	
	m_WindowClassRegistered++;
	
	if(m_WindowClassRegistered != 1) {
		return true;
	}
	
	memset(&m_WindowClass, 0, sizeof(m_WindowClass));
	
	// Fill all the info for our window class.
	m_WindowClass.style   = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	m_WindowClass.lpfnWndProc = Win32Window::WindowProc;
	m_WindowClass.hInstance  = (HINSTANCE)GetModuleHandle(NULL);
	m_WindowClass.hCursor  = LoadCursor(NULL, IDC_ARROW);
	m_WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_WindowClass.lpszMenuName = MAKEINTRESOURCE(NULL);
	m_WindowClass.lpszClassName = ARX_WINDOW_CLASS;
	m_WindowClass.hIcon   = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAIN));
	
	// Register our window class.
	bool ret = RegisterClassA(&m_WindowClass) != 0;
	
	return ret;
}

void Win32Window::unregisterWindowClass() {
	
	m_WindowClassRegistered--;
	if(m_WindowClassRegistered != 0) {
		return;
	}
	
	UnregisterClassA(ARX_WINDOW_CLASS, GetModuleHandle(0));
	
	m_WindowsMap.clear();
}

bool Win32Window::initialize(const std::string & title, Vec2i size, bool fullscreen,
                             unsigned depth) {
	ARX_UNUSED(depth);
	
	if(!registerWindowClass()) {
		LogError << "Failed to register the Win32 window class";
		return false;
	}
	
	DWORD windowStyle = fullscreen ?  (WS_POPUP | WS_VISIBLE) : WS_OVERLAPPEDWINDOW;
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;
	
	RECT rcWnd;
	SetRect(&rcWnd, 0, 0, size.x, size.y);
	BOOL hasMenu = GetMenu(m_hWnd) != NULL;
	if(AdjustWindowRectEx(&rcWnd, windowStyle, hasMenu, windowExtendedStyle) != TRUE) {
		LogError << "AdjustWindowRectEx() failed";
		return false;
	}
	
	// Bound the window size to the desktop
	HWND hWndDesktop = GetDesktopWindow();
	RECT rcDesktop;
	GetWindowRect(hWndDesktop, &rcDesktop);
	LONG maxWidth = rcDesktop.right - rcDesktop.left;
	LONG maxHeight = rcDesktop.bottom - rcDesktop.top;
	
	LONG wndWidth = rcWnd.right - rcWnd.left;
	LONG wndHeight = rcWnd.bottom - rcWnd.top;
	wndWidth = std::min(wndWidth, maxWidth);
	wndHeight = std::min(wndHeight, maxHeight);
	
	// Create a window using our window class.
	m_hWnd = CreateWindowEx(windowExtendedStyle, m_WindowClass.lpszClassName, "",
	                        windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, wndWidth, wndHeight, 
	                        0, NULL, (HINSTANCE)GetModuleHandle(NULL), this);
	if(!m_hWnd) {
		LogError << "Couldn't create window";
		return false;
	}
	
	if(SetWindowText(m_hWnd, title.c_str()) == TRUE) {
		title_ = title;
	} else {
		LogWarning << "Couldn't change the window's title";
	}
	
	ShowWindow(m_hWnd, SW_SHOW);
	
	isVisible_ = true;
	isFullscreen_ = fullscreen;
	size_ = size;
	
	return true;
}

LRESULT CALLBACK Win32Window::WindowProc(HWND hWnd, UINT iMsg, WPARAM wParam,
                                         LPARAM lParam) {
	
	static Win32Window* currentWindow = NULL;
	if(!currentWindow || currentWindow->m_hWnd != hWnd) {
		std::map<HWND, Win32Window *>::iterator it = m_WindowsMap.find(hWnd);
		if(it != m_WindowsMap.end()) {
			currentWindow = it->second;
		}
	}
	
	if(currentWindow == NULL && iMsg != WM_NCCREATE) {
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}
	
	bool bProcessed = false;
	switch(iMsg) {
		
		// Sent prior to the WM_CREATE message when a window is first created.
		case WM_NCCREATE: {
			currentWindow = (Win32Window *)((LPCREATESTRUCT)lParam)->lpCreateParams;
			m_WindowsMap[hWnd] = currentWindow;
			return 1;
		}
		
		// Sent when an application requests that a window be created.
		case WM_CREATE: {
			currentWindow->onCreate();
			break;
		}
		
		// Paint the window's client area.
		case WM_PAINT: {
			currentWindow->onPaint();
			break;
		}
		
		// Sent after a window has been moved.
		case WM_MOVE: {
			currentWindow->onMove((short)LOWORD(lParam), (short)HIWORD(lParam));
			break;
		}
		
		// Sent to a window after its size has changed.
		case WM_SIZE: {
			switch(wParam) {
				case SIZE_MINIMIZED: {
					currentWindow->onMinimize();
					break;
				}
				case SIZE_MAXIMIZED: {
					currentWindow->onMaximize();
					break;
				}
				case SIZE_RESTORED: {
					currentWindow->onRestore();
					break;
				}
			}
			break;
		}
		
		// Sent to both the window being activated and the window being deactivated.
		case WM_ACTIVATE: {
			currentWindow->onFocus(LOWORD(wParam) != WA_INACTIVE);
			break;
		}
		
		// Sent when the window is about to be hidden or shown.
		case WM_SHOWWINDOW: {
			currentWindow->onShow(wParam == TRUE);
			break;
		}
		
		// Sent just before a window is destroyed.
		// Informs a window that its nonclient area is being destroyed.
		// Window is about to be destroyed, clean up window-specific data objects.
		case WM_DESTROY: {
			currentWindow->onDestroy();
			currentWindow->m_hWnd = NULL;
			break;
		}
		
		// Sent as a signal that a window or an application should terminate.
		case WM_CLOSE: {
			if(!currentWindow->onClose()) {
				bProcessed = true;
			}
			break;
		}
		
		// To avoid screensaver / monitorpower interference
		case WM_SYSCOMMAND: {
			if(GET_SC_WPARAM(wParam) == SC_SCREENSAVE
			   || GET_SC_WPARAM(wParam) == SC_MONITORPOWER) {
				bProcessed = true;
			}
			break;
		}
		
		case WM_SETCURSOR: {
			SetCursor(NULL);
			bProcessed = true;
			break;
		}
		
	}
	
	// If the window proc was hijacked, always forward messages to the original WindowProc
	if(currentWindow->m_HijackedWindowProc != NULL) {
		return CallWindowProc(currentWindow->m_HijackedWindowProc, hWnd, iMsg, wParam, lParam);
	} else {
		// If processed, return 0,
		// otherwise, send all the other messages to the default WindowProc.
		if(bProcessed) {
			return 0;
		} else {
			return DefWindowProc(hWnd, iMsg, wParam, lParam);
		}
	}
}

void Win32Window::tick() {
	
	// Check if window was destroyed...
	arx_assert(m_hWnd != NULL);
	
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0) {
		if(msg.message == WM_QUIT) {
			DestroyWindow(m_hWnd); // Destroy window and quit
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg); // Send message to the WindowProc.
	}
	
	// Check if window was destroyed...
	if(m_hWnd == NULL) {
		return;
	}
	
	if(hasFocus() && !isFullScreen()) {
		updateSize();
	}
}

Vec2i Win32Window::getCursorPosition() const {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);
	return Vec2i(pt.x, pt.y);
}

void * Win32Window::getHandle() {
	return m_hWnd;
}

void Win32Window::updateSize() {
	
	RECT rcClient;
	BOOL ret = GetClientRect(m_hWnd, &rcClient);
	
	if(!ret || rcClient.right == rcClient.left || rcClient.bottom == rcClient.top) {
		LogWarning << "Ignoring bad window size: (" << rcClient.left << ", " << rcClient.top
		           << ") -- (" << rcClient.right << ", " << rcClient.bottom << ")";
	}
	
	Vec2i newSize = Vec2i(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
	
	if(newSize != size_) {
		onResize(newSize.x, newSize.y);
		changeDisplay(0);
	}
}

void Win32Window::setFullscreenMode(Vec2i resolution, unsigned _depth) {
	
	SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	
	depth_ = _depth;
	
	SetWindowPos(m_hWnd, HWND_TOP, 0, 0, resolution.x, resolution.y, SWP_SHOWWINDOW);
	
	if(!isFullscreen_) {
		isFullscreen_ = true;
		onToggleFullscreen();
	}
	
	onResize(resolution.x, resolution.y);
}

void Win32Window::setWindowSize(Vec2i size) {
	
	SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
	
	depth_ = 0;
	
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;
	
	RECT rcWnd;
	
	SetRect(&rcWnd, 0, 0, size.x, size.y);
	AdjustWindowRectEx(&rcWnd, windowStyle, GetMenu(m_hWnd) != NULL, windowExtendedStyle);
	
	int dx = rcWnd.right - rcWnd.left - size.x;
	int dy = rcWnd.bottom - rcWnd.top - size.y;
	
	SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, size.x + dx, size.y + dy, SWP_SHOWWINDOW);
	
	if(isFullscreen_) {
		isFullscreen_ = false;
		onToggleFullscreen();
	}
	
	onResize(size.x, size.y);
}

void Win32Window::hide() {
	ShowWindow(m_hWnd, SW_MINIMIZE | SW_HIDE);
	onShow(false);
}
