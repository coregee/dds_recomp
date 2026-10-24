@echo off
rem Builds and runs the table test: the data tables vs. the executable's bytes.
rem Another version (docs/versions.md): set NOCTURNE_VARIANT=hardtype first.
setlocal EnableDelayedExpansion
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b %errorlevel%

set "ROOT=%~dp0..\..\.."
set "SOURCE=%ROOT%\source"
call "%ROOT%\tools\variant.cmd" || exit /b 1
set "OUT=%ROOT%\build\tables%VARIANT_SUFFIX%"
if not exist "%OUT%" mkdir "%OUT%"
del /q "%OUT%\*.obj" 2>nul

set "CXXFLAGS=/nologo /utf-8 /std:c++20 /O1 /W4 /WX /EHsc /c %VARIANT_DEFINE% %VARIANT_INCLUDES% /I"%ROOT%\tools\ghidra""
rem This version's tables (tools/sources.py), and the test.
for /f "usebackq tokens=1,2 delims=|" %%A in (`python "%ROOT%\tools\sources.py" %NOCTURNE_VARIANT% sources`) do (
    set "NAME=%%B"
    if "!NAME:~-6!"=="_table" cl %CXXFLAGS% "%%A" /Fo"%OUT%\%%B.obj" || goto :failed
)
for %%F in ("%SOURCE%\tests\tables\*.cpp") do (
    cl %CXXFLAGS% "%%~F" /Fo"%OUT%\%%~nF.obj" || goto :failed
)
link /nologo /out:"%OUT%\tables.exe" "%OUT%\*.obj" || goto :failed

"%OUT%\tables.exe" "%VARIANT_GAME%"
exit /b %errorlevel%

:failed
echo Build failed.
exit /b 1
