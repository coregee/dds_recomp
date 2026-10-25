@echo off
rem Which version to build (docs/versions.md), from NOCTURNE_VARIANT (empty
rem or maniax: JP Maniax, the reference). Sets, for the calling
rem build script:
rem   VARIANT_DEFINE    the compiler flag naming it (nocturne/variant.hpp)
rem   VARIANT_INCLUDES  its include folders, in search order (tools/sources.py)
rem   VARIANT_GAME      its executable
rem   VARIANT_SUFFIX    for its build folders
rem usage (with ROOT set): call "%ROOT%\tools\variant.cmd" || goto :failed

set "VARIANT_SUFFIX="
if "%NOCTURNE_VARIANT%"=="" set "NOCTURNE_VARIANT=maniax"
if /i "%NOCTURNE_VARIANT%"=="us" (
    set "VARIANT_DEFINE=/DNOCTURNE_VARIANT=Us"
    set "VARIANT_GAME=%ROOT%\game\SLUS_209.11"
) else if /i "%NOCTURNE_VARIANT%"=="hardtype" (
    set "VARIANT_DEFINE=/DNOCTURNE_VARIANT=Hardtype"
    set "VARIANT_GAME=%ROOT%\game\hardtype\SLUS_209.11"
) else if /i "%NOCTURNE_VARIANT%"=="maniax" (
    set "VARIANT_DEFINE=/DNOCTURNE_VARIANT=Maniax"
    set "VARIANT_GAME=%ROOT%\game\jpmaniax\SLPM_654.62"
) else if /i "%NOCTURNE_VARIANT%"=="chronicle" (
    set "VARIANT_DEFINE=/DNOCTURNE_VARIANT=Chronicle"
    set "VARIANT_GAME=%ROOT%\game\chronicle\SLPM_666.81"
) else if /i "%NOCTURNE_VARIANT%"=="vanilla" (
    set "VARIANT_DEFINE=/DNOCTURNE_VARIANT=Vanilla"
    set "VARIANT_GAME=%ROOT%\game\vanilla\SLPM_652.42"
) else (
    echo Unknown NOCTURNE_VARIANT "%NOCTURNE_VARIANT%": maniax, vanilla, chronicle, us or hardtype.
    exit /b 1
)
if /i not "%NOCTURNE_VARIANT%"=="maniax" set "VARIANT_SUFFIX=-%NOCTURNE_VARIANT%"
set "VARIANT_INCLUDES="
for /f "usebackq delims=" %%I in (`python "%ROOT%\tools\sources.py" %NOCTURNE_VARIANT% includes`) do set VARIANT_INCLUDES=!VARIANT_INCLUDES! /I"%%I"
exit /b 0
