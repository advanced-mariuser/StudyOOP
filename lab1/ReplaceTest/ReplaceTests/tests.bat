@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

echo Tests passed