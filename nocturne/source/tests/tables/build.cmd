@echo off
rem Builds and runs the table test: src/data vs. the executable's bytes.
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b %errorlevel%

set "ROOT=%~dp0..\..\.."
set "SOURCE=%ROOT%\source"
set "OUT=%ROOT%\build\tables"
if not exist "%OUT%" mkdir "%OUT%"
del /q "%OUT%\*.obj" 2>nul

set "CXXFLAGS=/nologo /utf-8 /std:c++20 /O1 /W4 /WX /EHsc /c /I"%SOURCE%\include" /I"%ROOT%\tools\ghidra""
for %%F in ("%SOURCE%\src\data\*_table.cpp" "%SOURCE%\tests\tables\*.cpp") do (
    cl %CXXFLAGS% "%%~F" /Fo"%OUT%\%%~nF.obj" || goto :failed
)
link /nologo /out:"%OUT%\tables.exe" "%OUT%\*.obj" || goto :failed

"%OUT%\tables.exe" "%ROOT%\game\SLUS_209.11"
exit /b %errorlevel%

:failed
echo Build failed.
exit /b 1
