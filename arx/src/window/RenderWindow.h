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

#ifndef ARX_WINDOW_RENDERWINDOW_H
#define ARX_WINDOW_RENDERWINDOW_H

#include <vector>

#include "window/Window.h"

class Renderer;

class RenderWindow : public Window {
	
public:
	
	struct DisplayMode {
		
		Vec2i resolution;
		unsigned depth;
		
		DisplayMode() { }
		DisplayMode(const DisplayMode & o) : resolution(o.resolution), depth(o.depth) { }
		DisplayMode(Vec2i res, unsigned bits) : resolution(res), depth(bits) { }
		bool operator<(const DisplayMode & other) const;
		bool operator==(const DisplayMode & other) const {
			return resolution == other.resolution && depth == other.depth;
		}
		
	};
	
	typedef std::vector<DisplayMode> DisplayModes;
	
	RenderWindow() : renderer(NULL) { }
	virtual ~RenderWindow() { }
	
	class RendererListener {
		
	public:
		
		virtual ~RendererListener() { }
		
		virtual void onRendererInit(RenderWindow &) { }
		virtual void onRendererShutdown(RenderWindow &) { }
		
	};
	
	/*!
	 * Initialize the framework.
	 * This needs to be called before init() or getDisplayModes()
	 */
	virtual bool initializeFramework() = 0;
	
	Renderer * getRenderer() { return renderer; }
	
	//! Get a sorted list of supported fullscreen display modes.
	const DisplayModes & getDisplayModes() { return displayModes; }
	
	void addRenderListener(RendererListener * listener);
	void removeRenderListener(RendererListener * listener);
	
	virtual void showFrame() = 0;
	
protected:
	
	Renderer * renderer;
	DisplayModes displayModes; //! Available fullscreen modes.
	
	void onRendererInit();
	void onRendererShutdown();
	
private:
	
	typedef std::vector<RendererListener *> RendererListeners;
	
	RendererListeners renderListeners; //! Listeners for renderer events
	
};

#endif // ARX_WINDOW_RENDERWINDOW_H
