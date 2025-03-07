@echo off
Title change 123 to 321

setlocal enabledelayedexpansion

set /p "folder=Write the path to the folder: "

if not exist "%folder%" (
    echo folder doesn't exist.
    pause
    exit
)

for /r "%folder%" %%F in (*) do (
    set "file=%%~nxF"
    set "file_path=%%F"
    
    ( 
        for /f "tokens=*" %%A in ('type "%%F"') do (
            set "line=%%A"
            set "line=!line:123=321!"
            echo !line!
        )
    ) > "%%F.new"
    
    move /y "%%F.new" "%%F"
)
echo completed.
pause
