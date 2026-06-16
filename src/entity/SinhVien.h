#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <iostream>
#include <string>

class SinhVien {

private: 
    std::string mssv; // Khóa chính
    std::string hoTen;
    std::string ngaySinh;
    std::string gioiTinh;
    std::string soDienThoai;
    std::string email;
    std::string maPhong;
    std::string lop;
    std::string dienUuTien;
    
public:
    // Constructor
    SinhVien() {
        mssv = hoTen = ngaySinh = gioiTinh =soDienThoai = email = maPhong = lop = "";
        dienUuTien = "binh_thuong";
    }

    SinhVien(std::string mssv, std::string hoTen, std::string gioiTinh, std::string ngaySinh, std::string lop, std::string soDienThoai, std::string email, std::string maPhong = "", std::string dienUuTien = "binh_thuong") {
        this->mssv = mssv;
        this->hoTen = hoTen;
        this->gioiTinh = gioiTinh;
        this->ngaySinh = ngaySinh;
        this->lop = lop;
        this->soDienThoai = soDienThoai;
        this->email = email;
        this->maPhong = maPhong;
        this->dienUuTien = dienUuTien;
    }

    // getter
    std::string getMSSV() const { return mssv; }
    std::string getHoTen() const { return hoTen; }
    std::string getMaPhong() const { return maPhong; }
    std::string getNgaySinh() const { return ngaySinh; }
    std::string getGioiTinh() const { return gioiTinh; }
    std::string getSoDienThoai() const { return soDienThoai; }
    std::string getEmail() const { return email; }
    std::string getLop()  const { return lop; }
    std::string getDienUuTien()  const { return dienUuTien; }

    // setter
    void setMaPhong(std::string phongMoi) { maPhong = phongMoi; }
    bool dangThuePhong() const {
        return !maPhong.empty();
    }
    bool laUuTien()    const { return dienUuTien == "uu_tien"; }
    bool laChinhSach() const { return dienUuTien == "chinh_sach"; }
    bool laThuong()    const { return dienUuTien == "binh_thuong"; }
    // dùng cho hienthi() trong dscustom
    friend std::ostream& operator<<(std::ostream& os, const SinhVien& sv)
    {
        os << "[" << sv.mssv << "] " << sv.hoTen 
           << " (" << sv.gioiTinh << " - " << sv.ngaySinh << ") | Lop: " << sv.lop << "\n"
           << "   -> SDT: " << sv.soDienThoai << " | Email: " << sv.email << "\n"
           << "   -> Phong: " << (sv.maPhong.empty() ? "Chua thue" : sv.maPhong) 
           << " | Uu tien: " << sv.dienUuTien << "\n"
           << "-----------------------------------------------------------------";
        return os;
    }
};

#endif