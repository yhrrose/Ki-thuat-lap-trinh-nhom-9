@echo off
title Bien dich va Chay He Thong KTX

echo       DANG BIEN DICH CHUONG TRINH
:: Gom tat ca cac file .cpp va chi duong dan toi cac file .h bang co -I
g++ main.cpp src/business/NghiepVu.cpp src/io/FileIO.cpp -I. -Isrc/entity -Isrc/algorithm -Isrc/business -Isrc/io -o ktx.exe

:: Kiem tra xem qua trinh bien dich co bi loi khong
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [X] BIEN DICH THAT BAI! Vui long kiem tra lai loi code o tren.
    pause
    exit /b
)

echo.
echo [OK] BIEN DICH THANH CONG!
echo.
pause

:: Xoa man hinh console cho sach se va chay phan mem
cls
ktx.exe