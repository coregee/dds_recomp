@echo off
rem Builds and runs the differential test: rewritten source vs. legacy C.
rem usage: build.cmd [cases per function] [seed] [filter]
rem Another version (docs/versions.md): set NOCTURNE_VARIANT=hardtype first.
setlocal EnableDelayedExpansion
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b %errorlevel%

set "ROOT=%~dp0..\..\.."
set "SOURCE=%ROOT%\source"
set "LEGACY=%ROOT%\legacy"
call "%ROOT%\tools\variant.cmd" || exit /b 1
set "OUT=%ROOT%\build\differential%VARIANT_SUFFIX%"
if not exist "%OUT%" mkdir "%OUT%"
del /q "%OUT%\*.obj" 2>nul

set "CFLAGS=/nologo /std:c11 /O2 /Zi /Fd"%OUT%\\" /W4 /c /I"%LEGACY%\src""
set "CXXFLAGS=/nologo /utf-8 /std:c++20 /O2 /Zi /Fd"%OUT%\\" /W4 /WX /EHsc /c %VARIANT_DEFINE% %VARIANT_INCLUDES% /I"%SOURCE%\tests\differential" /I"%LEGACY%\src""

rem Legacy code under comparison (real implementations on the legacy side),
rem the shared engine-boundary fakes and the EE FPU model.
for %%U in (combat_calculation battle_power battle_effects battle_affinity battle_support_access
            battle_targeting battle_action_status nb_state dat_work dat_queries dat_resources dat_skills
            unit_progression ps2_soft_double ps2_soft_float battle_ai_conditions battle_ai_execution battle_ai_estimates
            unit_neighbors rst_stats stat_neighbors unit_batch inheritance_queries hearts_parameters exp rst_rng_frontier
            ps2_qsort fusion_sort fusion_accident fusion_core
            hearts_menu hearts_inventory fcl_encyc compendium_records compendium_restore
            battle_ai_actions battle_ai_filters battle_ai_selection battle_script_commands) do (
    cl %CFLAGS% "%LEGACY%\src\%%U.c" /Fo"%OUT%\legacy_%%U.obj" || goto :failed
)
cl %CFLAGS% /WX "%SOURCE%\tests\differential\fake_world.c" /Fo"%OUT%\fake_world.obj" || goto :failed
cl %CFLAGS% "%LEGACY%\tests\ee_fpu_values.c" /Fo"%OUT%\ee_fpu_values.obj" || goto :failed
cl %CFLAGS% "%ROOT%\third_party\ps2float\ps2float.c" /Fo"%OUT%\ps2float.obj" || goto :failed

rem The rewrite as this version builds it (tools/sources.py), and the tests.
for /f "usebackq tokens=1,2 delims=|" %%A in (`python "%ROOT%\tools\sources.py" %NOCTURNE_VARIANT% sources`) do (
    cl %CXXFLAGS% "%%A" /Fo"%OUT%\%%B.obj" || goto :failed
)
for %%F in ("%SOURCE%\tests\differential\*.cpp") do (
    cl %CXXFLAGS% "%%~F" /Fo"%OUT%\test_%%~nF.obj" || goto :failed
)

link /nologo /DEBUG /out:"%OUT%\differential.exe" "%OUT%\*.obj" || goto :failed

"%OUT%\differential.exe" "%VARIANT_GAME%" %*
exit /b %errorlevel%

:failed
echo Build failed.
exit /b 1
