@echo off
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86
) else (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\WDExpress\VC\Auxiliary\Build\vcvarsall.bat" x86
)
set compilerflags=/Od /Zi /EHsc /std:c++latest /I .
set linkerflags=/OUT:bin\EntityTest.exe
cl.exe %compilerflags% .\*.cpp /link %linkerflags%
del bin\*.ilk *.obj *.pdb