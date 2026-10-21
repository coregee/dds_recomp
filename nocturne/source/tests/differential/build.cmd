@echo off
rem Builds and runs the differential test: rewritten source vs. legacy C.
rem usage: build.cmd [cases per function] [seed]
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b %errorlevel%

set "ROOT=%~dp0..\..\.."
set "SOURCE=%ROOT%\source"
set "LEGACY=%ROOT%\legacy"
set "OUT=%ROOT%\build\differential"
if not exist "%OUT%" mkdir "%OUT%"
del /q "%OUT%\*.obj" 2>nul

set "CFLAGS=/nologo /std:c11 /O2 /W4 /c /I"%LEGACY%\src""
set "CXXFLAGS=/nologo /utf-8 /std:c++20 /O2 /W4 /WX /EHsc /c /I"%SOURCE%\include" /I"%SOURCE%\tests\differential" /I"%LEGACY%\src""

rem Legacy code under comparison, the shared fakes and the EE FPU model.
cl %CFLAGS% "%LEGACY%\src\combat_calculation.c" /Fo"%OUT%\combat_calculation.obj" || goto :failed
cl %CFLAGS% /WX "%SOURCE%\tests\differential\fake_world.c" /Fo"%OUT%\fake_world.obj" || goto :failed
cl %CFLAGS% "%LEGACY%\tests\ee_fpu_values.c" /Fo"%OUT%\ee_fpu_values.obj" || goto :failed
cl %CFLAGS% "%ROOT%\third_party\ps2float\ps2float.c" /Fo"%OUT%\ps2float.obj" || goto :failed

rem The rewrite.
cl %CXXFLAGS% "%SOURCE%\src\battle\calc.cpp" /Fo"%OUT%\calc.obj" || goto :failed
cl %CXXFLAGS% "%SOURCE%\src\platform\legacy_bridge.cpp" /Fo"%OUT%\legacy_bridge.obj" || goto :failed
cl %CXXFLAGS% "%SOURCE%\tests\differential\main.cpp" /Fo"%OUT%\main.obj" || goto :failed

link /nologo /out:"%OUT%\differential.exe" "%OUT%\*.obj" || goto :failed

"%OUT%\differential.exe" "%ROOT%\game\SLUS_209.11" %*
exit /b %errorlevel%

:failed
echo Build failed.
exit /b 1
