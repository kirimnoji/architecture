echo off

set local EnableDelayedExpansion

set /a count=0
for %%f in (*.png) do (
rename %%f !count!.png
set 

echo on