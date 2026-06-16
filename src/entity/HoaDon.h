#ifndef HOADON_H
#define HOADON_H

#include <iostream>
#include <string>

class HoaDon
{
private:
    std::string maHoaDon;      // Khóa chính
    std::string maPhong;       
    std::string thangNam;      // "mm/yyyy"
    std::string hanThanhToan;  // (dd/mm/yyyy)
    std::string trangThai;     // "chua_thu"/ "da_thu"/ "qua_han"

    double chiSoDienDau;
    double chiSoDienCuoi;
    double chiSoNuocDau;
    double chiSoNuocCuoi;
    double tienDien;
    double tienNuoc;
    double tienPhat;
    double tongTienDichVu; //      

public:
    // Constructor mặc định
    HoaDon()
{
    maHoaDon = "";
    maPhong = "";
    thangNam = "";
    hanThanhToan = "";
    trangThai = "chua_thu";

    chiSoDienDau = 0;
    chiSoDienCuoi = 0;
    chiSoNuocDau = 0;
    chiSoNuocCuoi = 0;
    tienPhat = 0;
    tienDien = 0;
    tienNuoc = 0;
    tongTienDichVu = 0;
}

    HoaDon(std::string maHoaDon, std::string maPhong, std::string thangNam, std::string hanThanhToan, double chiSoDienDau, double chiSoDienCuoi, double chiSoNuocDau, double chiSoNuocCuoi)
    {
        this->maHoaDon = maHoaDon;
        this->maPhong = maPhong;
        this->thangNam = thangNam;
        this->hanThanhToan = hanThanhToan;
        this->trangThai = "chua_thu";

        this->chiSoDienDau = chiSoDienDau;
        this->chiSoDienCuoi = chiSoDienCuoi;
        this->chiSoNuocDau = chiSoNuocDau;
        this->chiSoNuocCuoi = chiSoNuocCuoi;
        this->tienPhat = 0;

        tinhTien();   // tự tính ngay khi khởi tạo
    }

    // Getter
    std::string getMaHoaDon()  const { return maHoaDon; }
    std::string getMaPhong()   const { return maPhong; }
    std::string getThangNam()  const { return thangNam; }
    std::string getTrangThai() const { return trangThai; }
    double getTongTienDV()  const { return tongTienDichVu; }
    double getTienDien()  const { return tienDien; }
    double getTienNuoc()  const { return tienNuoc; }
    double getChiSoDienDau()  const { return chiSoDienDau; }
    double getChiSoDienCuoi() const { return chiSoDienCuoi; }
    double getChiSoNuocDau()  const { return chiSoNuocDau; }
    double getChiSoNuocCuoi() const { return chiSoNuocCuoi; }
    double getTienPhat() const { return tienPhat; }
    std::string getHanThanhToan() const { return hanThanhToan; }

    // Setter
    void setTrangThai(const std::string& tt) { trangThai = tt; }
    void setTienPhat(double tien) { tienPhat = tien; tinhTien(); }
    void setHanThanhToan(const std::string& h) { hanThanhToan = h; }
    void capNhatChiSo(double dienDau, double dienCuoi,double nuocDau, double nuocCuoi)
    {
        chiSoDienDau  = dienDau;
        chiSoDienCuoi = dienCuoi;
        chiSoNuocDau  = nuocDau;
        chiSoNuocCuoi = nuocCuoi;
        tinhTien();
    }

    // Tính tiền điện theo mức
    double tinhTienDien() const
{
    const double GIA_1 = 1984.0; // 0-50
    const double GIA_2 = 2050.0; // 51-100
    const double GIA_3 = 2380.0; // 101-200
    const double GIA_4 = 2998.0; // 201-300

    double luong = chiSoDienCuoi - chiSoDienDau;
    if (luong <= 0) return 0;
    double tien = 0;
    if (luong <= 50){
        tien += luong * GIA_1;
    } else if (luong <= 100) {
        tien += 50 * GIA_1;
        tien += (luong - 50) * GIA_2;
    } else if (luong <= 200) {
        tien += 50 * GIA_1;
        tien += 50 * GIA_2;
        tien += (luong - 100) * GIA_3;
    } else {
        tien += 50 * GIA_1;
        tien += 50 * GIA_2;
        tien += 100 * GIA_3;
        tien += (luong - 200) * GIA_4;
    } return tien;
}

    // Tính tiền nước theo mức
    double tinhTienNuoc() const
{
    const double GIA_1 = 5973.0;
    const double GIA_2 = 7052.0;
    const double GIA_3 = 8669.0;
    const double GIA_4 = 15929.0;

    double luong = chiSoNuocCuoi - chiSoNuocDau;
    if (luong <= 0) return 0;
    double tien = 0;
    if (luong <= 10) {
        tien += luong * GIA_1;
    } else if (luong <= 20) {
        tien += 10 * GIA_1;
        tien += (luong - 10) * GIA_2;
    } else if (luong <= 30) {
        tien += 10 * GIA_1;
        tien += 10 * GIA_2;
        tien += (luong - 20) * GIA_3;
    } else {
        tien += 10 * GIA_1;
        tien += 10 * GIA_2;
        tien += 10 * GIA_3;
        tien += (luong - 30) * GIA_4;
    } return tien;
}

    // Tính và lưu vào tienDien, tienNuoc, tongTien
    void tinhTien()
    {
        tienDien = tinhTienDien();
        tienNuoc = tinhTienNuoc();
        tongTienDichVu = tienDien + tienNuoc + tienPhat;
    }

    // Dùng cho hienThi() trong DanhSachCustom
    friend std::ostream& operator<<(std::ostream& os, const HoaDon& hd)
    {
        os << "Ma HD: "      << hd.maHoaDon
           << " | Phong: "   << hd.maPhong
           << " | Thang: "   << hd.thangNam
           << " | Dien: "    << hd.tienDien
           << " | Nuoc: "    << hd.tienNuoc
           << " | Tien Phat: "  << hd.tienPhat
           << " | TongDV: "    << hd.tongTienDichVu
           << " | Han: "     << hd.hanThanhToan
           << " | TT: "      << hd.trangThai;
        return os;
    }
};

#endif