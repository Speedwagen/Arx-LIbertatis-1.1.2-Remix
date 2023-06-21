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

#ifndef ARX_WINDOW_WIN32WINDOW_H
#define ARX_WINDOW_WIN32WINDOW_H

#include <map>
#include <windows.h>

#include "window/RenderWindow.h"

class Win32Window : public RenderWindow {
	
public:
	
	Win32Window();
	virtual ~Win32Window();
	
	virtual bool initialize(const std::string & title, Vec2i size, bool fullscreen,
	                        unsigned depth = 0);
	
	virtual void * getHandle();
	virtual void setFullscreenMode(Vec2i resolution, unsigned depth = 0);
	virtual void setWindowSize(Vec2i size);
	virtual void tick();
	virtual Vec2i getCursorPosition() const;
	
	virtual void hide();
	
protected:
	
	void updateSize();
	
	virtual void changeDisplay(unsigned _depth) = 0;
	
private:
	
	static bool registerWindowClass();
	static void unregisterWindowClass();
	
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	
	HWND m_hWnd;
	WNDPROC m_HijackedWindowProc;
	
	static WNDCLASS m_WindowClass;
	static int m_WindowClassRegistered;
	static std::map<HWND,Win32Window*> m_WindowsMap;
	
};

#endif // ARX_WINDOW_WIN32WINDOW_H
