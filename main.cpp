#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include "DanhSachCustom.h"
#include "SinhVien.h"
#include "Phong.h"
#include "HopDong.h"
#include "HoaDon.h"
#include "ThuatToan.h"
#include "NghiepVu.h"
#include "FileIO.h"
#include "TienIch.h"

using namespace std;

// Hàm bảo vệ nhập số nguyên
int nhapSoNguyen() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Loi: Vui long nhap so nguyen! Nhap lai: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // xóa enter thừa
    return x;
}

// Hàm bảo vệ nhập số thực
double nhapSoThuc() {
    double x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Loi: Vui long nhap so! Nhap lai: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // xóa enter thừa
    return x;
}

// GIAO DIỆN MENU
void inMenuChinh() {
    cout << "\n=========================================\n";
    cout << "      HE THONG QUAN LY KY TUC XA\n";
    cout << "=========================================\n";
    cout << "1. Quan ly Danh muc (Sinh vien, Phong)\n";
    cout << "2. Nghiep vu Thue Phong\n";
    cout << "3. Nghiep vu Hoa Don & Thanh Toan\n";
    cout << "4. Bao cao & Thong ke\n";
    cout << "0. Luu du lieu va Thoat\n";
    cout << "=========================================\n";
    cout << "Nhap lua chon cua ban: ";
}

void inMenuDanhMuc() {
    cout << "\n--- QUAN LY DANH MUC ---\n";
    cout << "1. Xem danh sach Phong\n";
    cout << "2. Xem danh sach Sinh vien chinh thuc o KTX\n";
    cout << "3. Tiep nhan don dang ky KTX moi\n";
    cout << "4. Sua thong tin Sinh vien\n";
    cout << "5. Rut don dang ky / Xoa ho so cho\n";
    cout << "6. Them Phong moi\n";
    cout << "7. Sua gia Phong\n";
    cout << "8. Xem danh sach Ho so dang ky (Cho xep phong)\n";
    cout << "0. Quay lai\n";
    cout << "Chon: ";
}

void inMenuThuePhong() {
    cout << "\n--- NGHIEP VU THUE PHONG ---\n";
    cout << "1. Dang ky phong thu cong\n";
    cout << "2. Xep phong tu dong\n";
    cout << "3. Chuyen phong\n";
    cout << "4. Gia han hop dong\n";
    cout << "5. Tra phong (Huy hop dong)\n";
    cout << "6. Xem Danh sach hop dong\n";
    cout << "0. Quay lai\n";
    cout << "Chon: ";
}

void inMenuBaoCao() {
    cout << "\n--- BAO CAO & THONG KE ---\n";
    cout << "1. Thong ke ti le lap day cua KTX\n";
    cout << "2. Danh sach sinh vien dang no phi\n";
    cout << "0. Quay lai\n";
    cout << "Chon: ";
}

int main() {
    srand(time(NULL)); // khởi tạo sinh số random
    
    // Khởi tạo danh sách
    DanhSachCustom<SinhVien> dsSV;
    DanhSachCustom<Phong>    dsPhong;
    DanhSachCustom<HopDong>  dsHD;
    DanhSachCustom<HoaDon>   dsHoaDon;
    
    // Load dữ liệu từ file khi mở phần mềm
    loadData(dsSV, dsPhong, dsHD, dsHoaDon);

    int luaChonChinh;
    do {
        inMenuChinh();
        luaChonChinh = nhapSoNguyen();

        switch (luaChonChinh) {
            case 1: { // QUẢN LÝ DANH MỤC
                int chonDM;
                do {
                    inMenuDanhMuc();
                    chonDM = nhapSoNguyen(); 

                    if (chonDM == 1) { // r
                        cout << "\nDanh sach Phong:\n";
                        dsPhong.hienThi();
                    } 
                    else if (chonDM == 2) { // r
                        cout << "\n======================================================\n";
                        cout << "   DANH SACH SINH VIEN DANG LUU TRU TAI KTX\n";
                        cout << "======================================================\n";
                        bool coSinhVienNoiTru = false;
                        int stt = 1;
                        for (int i = 0; i < dsSV.kichThuoc(); i++) {
                            if (dsSV.lay(i).dangThuePhong()) { 
                                cout << stt++ << ". ";
                                cout << dsSV.lay(i) << "\n";
                                coSinhVienNoiTru = true;
                            }
                        }
                        if (!coSinhVienNoiTru) cout << "Hien tai ki tuc xa chua co sinh vien nao den o (Danh sach trong).\n";
                        cout << "======================================================\n";
                    } 
                    else if (chonDM == 3) { // w
                        string mssv, ten, gt, ns, lop, sdt, mail, dienUuTien;
                        cout << "MSSV: "; getline(cin, mssv);
                        cout << "Ho Ten: "; getline(cin, ten);
                        cout << "Gioi tinh (Nam/Nu): "; getline(cin, gt);
                        cout << "Ngay sinh (dd/mm/yyyy): "; getline(cin, ns);
                        cout << "Lop: "; getline(cin, lop);
                        cout << "SDT: "; getline(cin, sdt);
                        cout << "Email: "; getline(cin, mail);
                        cout << "Dien uu tien (binh_thuong / uu_tien / chinh_sach): "; getline(cin, dienUuTien);
                        // Chuẩn hóa trước khi lưu
                        gt = chuanHoaGioiTinh(gt);
                        dienUuTien = chuanHoaDienUuTien(dienUuTien);
                        string maPhongTrong = "";
                        themSinhVien(dsSV, SinhVien(mssv, ten, gt, ns, lop, sdt, mail, maPhongTrong, dienUuTien));
                    } 
                    else if (chonDM == 4) { // Update
                        string mssv, ten, gt, ns, lop, sdt, mail, dienUuTien;
                        cout << "Nhap MSSV can sua: "; getline(cin, mssv);
                        cout << "Ho Ten moi: "; getline(cin, ten);
                        cout << "Gioi tinh moi (Nam/Nu): "; getline(cin, gt);
                        cout << "Ngay sinh moi (dd/mm/yyyy): "; getline(cin, ns);
                        cout << "Lop moi: "; getline(cin, lop);
                        cout << "SDT moi: "; getline(cin, sdt);
                        cout << "Email moi: "; getline(cin, mail);
                        cout << "Dien uu tien moi (binh_thuong / uu_tien / chinh_sach): "; getline(cin, dienUuTien);
                        // Chuẩn hóa trước khi lưu
                        gt = chuanHoaGioiTinh(gt);
                        dienUuTien = chuanHoaDienUuTien(dienUuTien);
                        suaSinhVien(dsSV, mssv, ten, gt, ns, lop, sdt, mail, dienUuTien);
                    } 
                    else if (chonDM == 5) { // w
                        string mssv;
                        cout << "Nhap MSSV can xoa: "; getline(cin, mssv);
                        xoaSinhVien(dsSV, mssv);
                    } 
                    else if (chonDM == 6) { // w
                        string ma; int loai; double gia;
                        cout << "Ma phong: "; getline(cin, ma);
                        cout << "Loai phong (4/6/8): "; loai = nhapSoNguyen();
                        cout << "Gia thue/thang: "; gia = nhapSoThuc();
                        themPhong(dsPhong, Phong(ma, loai, gia));
                    }
                    else if (chonDM == 7) { // Update
                        string ma; double giaMoi;
                        cout << "Ma phong can sua gia: "; getline(cin, ma);
                        cout << "Gia moi: "; giaMoi = nhapSoThuc(); 
                        suaGiaPhong(dsPhong, ma, giaMoi);
                    }
                    else if (chonDM == 8) { // r
                        cout << "\n======================================================\n";
                        cout << "   DANH SACH HO SO SINH VIEN DANG KY (CHO XEP PHONG)\n";
                        cout << "======================================================\n";
                        bool coNguoiCho = false;
                        int stt = 1;
                        for (int i = 0; i < dsSV.kichThuoc(); i++) {
                            if (!dsSV.lay(i).dangThuePhong()) { 
                                cout << stt++ << ". " << dsSV.lay(i) << "\n";
                                coNguoiCho = true;
                            }
                        }
                        if (!coNguoiCho) cout << "Hien tai khong co don dang ky nao dang cho duyet.\n";
                        cout << "======================================================\n";
                    }
                    
                    // 3 đến 7
                    if (chonDM >= 3 && chonDM <= 7) {
                        saveDataFinal(dsSV, dsPhong, dsHD, dsHoaDon);
                    }
                } while (chonDM != 0);
                break;
            }
            case 2: { // NGHIỆP VỤ THUÊ PHÒNG
                int chonTP;
                do {
                    inMenuThuePhong();
                    chonTP = nhapSoNguyen();
                    
                    if (chonTP == 1) { // Write
                        string mssv, maPhong, ngayBD, ngayKT;
                        cout << "MSSV: "; getline(cin, mssv);
                        cout << "Ma Phong: "; getline(cin, maPhong);
                        cout << "Ngay BD (dd/mm/yyyy): "; getline(cin, ngayBD);
                        cout << "Ngay KT (dd/mm/yyyy): "; getline(cin, ngayKT);
                        dangKyPhong(dsSV, dsPhong, dsHD, mssv, maPhong, ngayBD, ngayKT);
                    } 
                    else if (chonTP == 2){ // Write
                        string ngayBD, ngayKT;
                        cout << "Nhap Ngay BD cho dot xep (dd/mm/yyyy): "; getline(cin, ngayBD);
                        cout << "Nhap Ngay KT cho dot xep (dd/mm/yyyy): "; getline(cin, ngayKT);
                        xepPhongTuDong(dsSV, dsPhong, dsHD, ngayBD, ngayKT);
                        cout << "\nDanh sach Sinh vien sau khi xep phong:\n";
                        dsSV.hienThi();
                    } 
                    else if (chonTP == 3) { // Write
                        string mssv, maPhongMoi, ngayBD, ngayKT;
                        cout << "MSSV can chuyen: "; getline(cin, mssv);
                        cout << "Ma Phong moi: "; getline(cin, maPhongMoi);
                        cout << "Ngay BD (dd/mm/yyyy): "; getline(cin, ngayBD);
                        cout << "Ngay KT (dd/mm/yyyy): "; getline(cin, ngayKT);
                        chuyenPhong(dsSV, dsPhong, dsHD, mssv, maPhongMoi, ngayBD, ngayKT);
                    } 
                    else if (chonTP == 4) { // Update
                        string maHD, ngayKTMoi;
                        cout << "Nhap Ma Hop Dong can gia han: "; getline(cin, maHD);
                        cout << "Ngay ket thuc moi (dd/mm/yyyy): "; getline(cin, ngayKTMoi);
                        giaHanHopDong(dsHD, maHD, ngayKTMoi);
                    } 
                    else if (chonTP == 5) { // Update
                        string maHD;
                        cout << "Nhap Ma Hop Dong can huy: "; getline(cin, maHD);
                        huyHopDong(dsSV, dsPhong, dsHD, dsHoaDon, maHD); 
                    } 
                    else if (chonTP == 6) { // r
                        cout << "\n--- DANH SACH HOP DONG ---\n";
                        dsHD.hienThi();
                    }

                    // 1 đến 5
                    if (chonTP >= 1 && chonTP <= 5) {
                        saveDataFinal(dsSV, dsPhong, dsHD, dsHoaDon);
                    }
                } while (chonTP != 0);
                break;
            }
            case 3: { // NGHIỆP VỤ HÓA ĐƠN
                int chonHD;
                do {
                    cout << "\n--- NGHIEP VU HOA DON ---\n";
                    cout << "1. Lap hoa don le cho 1 Phong\n";
                    cout << "2. Thu tien hoa don (Cap nhat trang thai)\n";
                    cout << "3. Danh dau hoa don qua han\n"; 
                    cout << "4. Xem danh sach toan bo Hoa don\n";
                    cout << "5. Ghi nhan them tien phat vao hoa don da lap\n";
                    cout << "0. Quay lai\n";
                    cout << "Chon: ";
                    chonHD = nhapSoNguyen();

                    if (chonHD == 1) { // Write
                        string maPhong, thangNam, hanThanhToan;
                        double dDau, dCuoi, nDau, nCuoi, tienPhat;
                        cout << "Nhap Ma Phong: "; getline(cin, maPhong);
                        cout << "Thang/Nam (mm/yyyy): "; getline(cin, thangNam);
                        cout << "Han thanh toan (dd/mm/yyyy): "; getline(cin, hanThanhToan);
                        cout << "Chi so dien dau: "; dDau = nhapSoThuc();
                        cout << "Chi so dien cuoi: "; dCuoi = nhapSoThuc();
                        cout << "Chi so nuoc dau: "; nDau = nhapSoThuc();
                        cout << "Chi so nuoc cuoi: "; nCuoi = nhapSoThuc();
                        cout << "Tien phat: "; tienPhat = nhapSoThuc(); 
                        
                        lapHoaDon(dsHoaDon, dsPhong, maPhong, thangNam, hanThanhToan, dDau, dCuoi, nDau, nCuoi, tienPhat);
                    } 
                    else if (chonHD == 2) { // Update
                        string maHoaDon;
                        cout << "Nhap Ma Hoa Don can thu tien: "; getline(cin, maHoaDon);
                        thuHoaDon(dsHoaDon, maHoaDon);
                    }
                    else if (chonHD == 3) { // Update
                        string maHoaDon;
                        cout << "Nhap Ma Hoa Don qua han: "; getline(cin, maHoaDon);
                        danhDauQuaHan(dsHoaDon, maHoaDon);
                    }
                    else if (chonHD == 4) { // r
                        cout << "\n=== DANH SACH HOA DON ===\n";
                        if (dsHoaDon.kichThuoc() == 0) cout << "Chua co hoa don nao!\n";
                        else dsHoaDon.hienThi();
                    }
                    else if (chonHD == 5) { // Update
                        string maHoaDon;
                        double tienPhatThem;
                        cout << "Nhap Ma Hoa Don can ghi nhan phat: "; getline(cin, maHoaDon);
                        cout << "Nhap so tien phat can cong them: "; tienPhatThem = nhapSoThuc();
                        
                        ghiNhanTienPhat(dsHoaDon, maHoaDon, tienPhatThem);
                    }

                    // trừ 4
                    if (chonHD == 1 || chonHD == 2 || chonHD == 3 || chonHD == 5) {
                        saveDataFinal(dsSV, dsPhong, dsHD, dsHoaDon);
                    }
                } while (chonHD != 0);
                break;
            }
            case 4: { // BÁO CÁO THỐNG KÊ 
                int chonBC;
                do {
                    inMenuBaoCao();
                    chonBC = nhapSoNguyen();

                    if (chonBC == 1) {
                        cout << "\n--- THONG KE TY LE LAP DAY ---\n";
                        thongKeLapDay(dsPhong);
                    } 
                    else if (chonBC == 2) {
                        cout << "\n--- DANH SACH SV NO PHI ---\n";
                        DanhSachCustom<SinhVien> dsNo = layDSSVQuaHan(dsSV, dsHoaDon);
                        if (dsNo.kichThuoc() == 0) {
                            cout << "Khong co sinh vien nao dang no phi!\n";
                        } else {
                            dsNo.hienThi();
                        }
                    }
                } while (chonBC != 0);
                break;
            }
            case 0:
                cout << "Luu du lieu va thoat chuong trinh...\n";
                saveDataFinal(dsSV, dsPhong, dsHD, dsHoaDon);
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai!\n";
        }
    } while (luaChonChinh != 0);

    return 0;
}