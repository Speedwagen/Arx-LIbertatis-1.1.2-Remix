@echo off
setlocal

set BRANCH_NAME="master"
set TARGET_NAME="release"

IF NOT (%1)==() set BRANCH_NAME="%1"
IF NOT (%2)==() set TARGET_NAME="%2"

pushd %BRANCH_NAME%

REM ************************************************************
REM * Build Win32
REM ************************************************************
mkdir win32
pushd win32
cmake .. -DQT_QMAKE_EXECUTABLE=%QTDIR32%/bin/qmake.exe
call "%VS100COMNTOOLS%..\IDE\devenv.com" "ArxLibertatis.sln" /Build %TARGET_NAME%
popd

popd