## ArxWindows - Libraries and scripts for Arx Libertatis development under Windows

This repository contains everything that you need to build [Arx Libertatis](https://arx-libertatis.org/) in both 32-bit and 64-bit under Windows with MSVC 2015 or newer.
It also contains the necessary to build installers for the game.

[Detailed instructions are available on the wiki.](https://wiki.arx-libertatis.org/Downloading_and_Compiling_under_Windows)
[Forked from ArxWindows.](https://github.com/arx/ArxWindows)

### Libraries

* [Boost](http://www.boost.org/)
* [DirectX SDK](http://msdn.microsoft.com/en-us/directx/aa937788/)
* [FreeType](http://www.freetype.org/)
* [OpenAL](http://connect.creativelabs.com/openal/)
* [OpenGL](http://www.opengl.org/registry/)
* [GLEW](http://glew.sourceforge.net/)
* [SDL](http://www.libsdl.org/)
* [ZLib](http://zlib.net/)

Additionally, you'll need the following libraries to build the Crash Reporter:

* [DbgHelp](http://msdn.microsoft.com/en-us/windows/hardware/gg463009)
* [Qt](http://qt.nokia.com/)


#### How to setup

1. Download the content of this repository to your PC

        Let's say in "C:\git\Arx-LIbertatis-1.1.2-Remix\..."

2. Add the following environment variable:

        CMAKE_PREFIX_PATH
and set its value to

        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\zlib;C:\git\Arx-LIbertatis-1.1.2-Remix\libs\freetype;C:\git\Arx-LIbertatis-1.1.2-Remix\libs\devil;C:\git\Arx-LIbertatis-1.1.2-Remix\libs\openal;C:\git\Arx-LIbertatis-1.1.2-Remix\libs\boost;C:\git\Arx-LIbertatis-1.1.2-Remix\libs\opengl;C:\git\Arx-LIbertatis-1.1.2-Remix\libs\sdl;C:\git\Arx-LIbertatis-1.1.2-Remix\libs\directx;C:\git\Arx-LIbertatis-1.1.2-Remix\libs\dbghelp

3. Copy the necessary DLLs to the game binary folder (arx\bin). Those marked with a (*) are only needed for the Crash Reporter, 

>>For 32-bit:
>>
        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\devil\bin\DevIL32.dll
        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\sdl\bin\SDL32.dll
        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\dbghelp\bin\x86\dbghelp.dll (*)
        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\dbghelp\bin\x86\symserv.dll (*)
        %QTDIR%\bin\QtCore4.dll (*)
        %QTDIR%\bin\QtGui4.dll (*)
        %QTDIR%\bin\QtNetwork4.dll (*)
        
>>For 64-bit:
>>
        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\devil\bin\DevIL64.dll
        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\sdl\bin\SDL64.dll
        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\dbghelp\bin\x64\dbghelp.dll (*)
        C:\git\Arx-LIbertatis-1.1.2-Remix\libs\dbghelp\bin\x64\symserv.dll (*)
        %QTDIR%\bin\QtCore4.dll (*)
        %QTDIR%\bin\QtGui4.dll (*)
        %QTDIR%\bin\QtNetwork4.dll (*)

4. Compile boost or obtain prebuilt libraries
        
        * The easiest solution is to grab them from http://boost.teeks99.com/
        * If you wish to build them yourself, refer to the boost documentation
		

#### CMake Build Command for VS 2019 64bit
		cmake .. -G "Visual Studio 16 2019" -A x64 -DUNITY_BUILD=1
		
#### Visual Studio will present an error - unresolved external symbol _vsnwprintf
To fix this make sure to add the following to your additional dependencies
		
		legacy_stdio_definitions.lib
