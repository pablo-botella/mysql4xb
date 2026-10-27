@echo off
rem Rebuild the documentation database of mysql4xb from its sources and the
rem examples. The .doc-tool says what to collect and how the documentation is
rem organized; the .doc-tool.user, personal and never tracked, says where the
rem database lands - today the xbwin-site repository, whose build writes the
rem site from the .db alone. The Markdown reference is regenerated too, into
rem mysql4xb\out\md.

cd /d "%~dp0"
set TOOL=C:\HD\F\__pbnprj\xbwin\ot4xb-tool\ot4xb-tool.exe
set DOCTOOL=%~dp0mysql4xb.doc-tool

if not exist "%TOOL%" goto :notool
if not exist "%~dp0mysql4xb\out" mkdir "%~dp0mysql4xb\out"

echo === compile ===
"%TOOL%" doc compile -doctool "%DOCTOOL%"
if errorlevel 1 goto :failed

echo === resolve ===
"%TOOL%" doc resolve -doctool "%DOCTOOL%"
if errorlevel 1 goto :failed

echo === markdown ===
"%TOOL%" doc gen -doctool "%DOCTOOL%" -out "%~dp0mysql4xb\out\md"
if errorlevel 1 goto :failed

echo.
echo Database rebuilt. Run the build of the site repository.
pause
exit /b 0

:notool
echo ERROR: %TOOL% not found - build it with "go build ." in the ot4xb-tool repository.
pause
exit /b 1

:failed
echo.
echo FAILED - the database was not rebuilt.
pause
exit /b 1
