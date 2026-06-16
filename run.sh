#!/bin/bash
clear
echo "       DANG BIEN DICH CHUONG TRINH    "
# Bien dich code voi g++
g++ main.cpp src/business/NghiepVu.cpp src/io/FileIO.cpp -I. -Isrc/entity -Isrc/algorithm -Isrc/business -Isrc/io -o ktx

# Kiem tra loi bien dich
if [ $? -ne 0 ]; then
    echo ""
    echo "[X] BIEN DICH THAT BAI! Vui long kiem tra lai code o tren."
    exit 1
fi

echo ""
echo "[OK] BIEN DICH THANH CONG!"
read -p "An Enter de tiep tuc..."

# Xoa man hinh va chay chuong trinh
clear
./ktx