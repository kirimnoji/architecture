echo off

setlocal enabledlayedexpansion
set /a count = 0

FOR %%F IN  (*.png) DO (
	echo %%F !count!.png
	set /a count = count + 1
)
echo on