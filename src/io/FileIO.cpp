#include "FileIO.h"
#include "TienIch.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
 // LOAD DATA
void loadData(DanhSachCustom<SinhVien>& dsSV, 
              DanhSachCustom<Phong>& dsPhong, 
              DanhSachCustom<HopDong>& dsHD, 
              DanhSachCustom<HoaDon>& dsHoaDon)
{
    string line;

    // 1. NẠP DANH SÁCH PHÒNG
    ifstream filePhong("data/phong.txt");
    if (filePhong.is_open()) {
        while (getline(filePhong, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            stringstream ss(line);
            string ma, loai, gia, gioiTinh;
            
            getline(ss, ma, ',');
            getline(ss, loai, ',');
            getline(ss, gia, ',');
            getline(ss, gioiTinh,',');  

            Phong p(ma, stoi(loai), stod(gia));
            if (!gioiTinh.empty() && gioiTinh != "\r") {
                p.setGioiTinhPhong(chuanHoaGioiTinh(gioiTinh));
            }
            dsPhong.them(p);

        }
        filePhong.close();
        cout << "[OK] Da nap du lieu Phong.\n";
    }

    // 2. NẠP DANH SÁCH SINH VIÊN
    ifstream fileSV("data/sinhvien.txt");
    if (fileSV.is_open()) {
        while (getline(fileSV, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            stringstream ss(line);
            string mssv, ten, gt, ns, lop, sdt, mail, maPhong, dienUuTien;

            getline(ss, mssv, ',');
            getline(ss, ten, ',');
            getline(ss, gt, ',');
            getline(ss, ns, ',');
            getline(ss, lop, ',');
            getline(ss, sdt, ',');
            getline(ss, mail, ',');
            getline(ss, maPhong, ','); // Có thể rỗng nếu chưa thuê
            getline(ss, dienUuTien, ',');

            if (dienUuTien.empty()) dienUuTien = "binh_thuong";
            // Chuẩn hóa để đồng nhất dữ liệu kể cả file cũ nhập sai
            gt         = chuanHoaGioiTinh(gt);
            dienUuTien = chuanHoaDienUuTien(dienUuTien);
            dsSV.them(SinhVien(mssv, ten, gt, ns, lop, sdt, mail, maPhong, dienUuTien));

            // Nếu SV đang ở một phòng, ta phải tăng số người của phòng đó lên 1
            if (!maPhong.empty()) {
                int idxPhong = timPhongTheoMa(dsPhong, maPhong);
                    if (idxPhong != -1) {
                        Phong p = dsPhong.lay(idxPhong);  // lấy bản sao
                        p.themNguoi();                     // sửa trên bản sao
                        dsPhong.capNhat(idxPhong, p, true); // ghi lại, giữ cờ
                    }
            }
        }
        fileSV.close();
        cout << "[OK] Da nap du lieu Sinh vien.\n";
    }

    // 3. NẠP DANH SÁCH HỢP ĐỒNG
    ifstream fileHD("data/hopdong.txt");
    if (fileHD.is_open()) {
        while (getline(fileHD, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            stringstream ss(line);
            string maHD, mssv, maPhong, tienPhongKy, bd, kt, trangThai;

            getline(ss, maHD, ',');
            getline(ss, mssv, ',');
            getline(ss, maPhong, ',');
            getline(ss, tienPhongKy, ',');
            getline(ss, bd, ',');
            getline(ss, kt, ',');
            getline(ss, trangThai, ',');

            HopDong hd(maHD, mssv, maPhong, bd, kt);
            hd.setTienPhongKy(stod(tienPhongKy));
            hd.setTrangThai(trangThai); // Phục hồi trạng thái (con_hieu_luc / da_huy)
            dsHD.them(hd);
        }
        fileHD.close();
        cout << "[OK] Da nap du lieu Hop dong.\n";
    }

    // 4. NẠP DANH SÁCH HÓA ĐƠN
    ifstream fileHoaDon("data/hoadon.txt");
    if (fileHoaDon.is_open()) {
        while (getline(fileHoaDon, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            stringstream ss(line);
            
            string maHoaDon, maPhong, thang, han, dDau, dCuoi, nDau, nCuoi, tienPhat, tongTienDV, trangThai;
            
            getline(ss, maHoaDon, ',');
            getline(ss, maPhong, ',');
            getline(ss, thang, ',');
            getline(ss, han, ',');
            getline(ss, dDau, ',');
            getline(ss, dCuoi, ',');
            getline(ss, nDau, ',');
            getline(ss, nCuoi, ',');
            getline(ss, tienPhat, ',');
            getline(ss, tongTienDV, ',');
            getline(ss, trangThai, ',');

            // Khởi tạo hóa đơn
            HoaDon hd(maHoaDon, maPhong, thang, han,
                      stod(dDau), stod(dCuoi), 
                      stod(nDau), stod(nCuoi));
                      
            
            hd.setTienPhat(stod(tienPhat)); 
            hd.setTrangThai(trangThai); 
            dsHoaDon.them(hd);
        }
        fileHoaDon.close();
        cout << "[OK] Da nap du lieu Hoa don.\n";
    }
}
// BẢN SAVE DATA 
void saveDataFinal(const DanhSachCustom<SinhVien>& dsSV, 
                   const DanhSachCustom<Phong>& dsPhong, 
                   const DanhSachCustom<HopDong>& dsHD, 
                   const DanhSachCustom<HoaDon>& dsHoaDon)
{
    // 1. Ghi Phòng
    ofstream filePhong("data/phong.txt", ios::trunc);
    for (int i = 0; i < dsPhong.kichThuoc(); i++) {
        Phong p = dsPhong.lay(i);
        filePhong << p.getMaPhong() << "," << p.getLoaiPhong() << "," 
                  << fixed << setprecision(0) << p.getGiaThueThang() << ","
                  << p.getGioiTinhPhong() << "\n"; 
    }
    filePhong.close();

    // 2. Ghi Sinh Viên
    ofstream fileSV("data/sinhvien.txt", ios::trunc);
    for (int i = 0; i < dsSV.kichThuoc(); i++) {
        SinhVien sv = dsSV.lay(i);
        fileSV << sv.getMSSV() << "," << sv.getHoTen() << "," << sv.getGioiTinh() << "," << sv.getNgaySinh() << "," << sv.getLop() << "," << sv.getSoDienThoai() << "," << sv.getEmail() << "," << sv.getMaPhong() << "," << sv.getDienUuTien() << "\n";
    }
    fileSV.close();

    // 3. Ghi Hợp Đồng
    ofstream fileHD("data/hopdong.txt", ios::trunc);
    fileHD << fixed << setprecision(0); // tránh mất dữ liệu lẻ
    for (int i = 0; i < dsHD.kichThuoc(); i++) {
        HopDong hd = dsHD.lay(i);
        fileHD << hd.getMaHopDong() << "," << hd.getMSSV() << "," 
               << hd.getMaPhong() << "," << hd.getTienPhongKy() << "," << hd.getNgayBatDau() << "," 
               << hd.getNgayKetThuc() << "," << hd.getTrangThai() << "\n";
    }
    fileHD.close();

    // 4. Ghi Hóa Đơn
    ofstream fileHoaDon("data/hoadon.txt", ios::trunc);
    fileHoaDon << fixed << setprecision(0); // tránh mất phần lẻ
    for (int i = 0; i < dsHoaDon.kichThuoc(); i++) {
        HoaDon hd = dsHoaDon.lay(i);
        fileHoaDon << hd.getMaHoaDon() << ","
                   << hd.getMaPhong() << "," << hd.getThangNam() << ","
                   << hd.getHanThanhToan() << ","
                   << hd.getChiSoDienDau() << "," << hd.getChiSoDienCuoi() << ","
                   << hd.getChiSoNuocDau() << "," << hd.getChiSoNuocCuoi() << ","
                   << hd.getTienPhat() << ","  
                   << hd.getTongTienDV() << ","
                   << hd.getTrangThai() << "\n";
    }
    fileHoaDon.close();
    
    cout << "\nToan bo du lieu da duoc luu xuong file thanh cong!\n";
}