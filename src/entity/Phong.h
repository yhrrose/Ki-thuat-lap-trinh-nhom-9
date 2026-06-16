#ifndef PHONG_H
#define PHONG_H

#include <iostream>
#include <string>

class Phong{

private:
    std::string maPhong;       // Khóa chính
    int    loaiPhong;    
    int    soNguoiHienTai;
    double giaThueThang;  // Giá cố định theo loại phòng
    std::string trangThai;    
    std::string gioiTinhPhong; // phân chia nam nữ 

public:
    // Constructor mặc định
    Phong(){
        maPhong = "";
        loaiPhong = 0;
        soNguoiHienTai = 0;
        giaThueThang = 0.0;
        trangThai = "trong";
        gioiTinhPhong ="" ;
    }
    // Constructor có tham số
    Phong(std::string maPhong, int loaiPhong, double giaThueThang)
    {
        this->maPhong = maPhong;
        
        // Ép loại phòng chỉ được là 4, 6, 8
        if (loaiPhong == 4 || loaiPhong == 6 || loaiPhong == 8) {
            this->loaiPhong = loaiPhong;
        } else {
            this->loaiPhong = 4; // Gán mặc định nếu nhập sai 
            std::cout << "Canh bao: Loai phong khong hop le. Da tu dong gan ve phong 4 giuong.\n";
        }
        
        this->soNguoiHienTai = 0;
        this->giaThueThang = giaThueThang;
        this->trangThai = "trong";
        this->gioiTinhPhong = "";
    }

    // getter
    std::string getMaPhong() const { return maPhong; }
    int getLoaiPhong() const { return loaiPhong; }
    int getSoNguoiHienTai() const { return soNguoiHienTai; }
    double getGiaThueThang() const { return giaThueThang; }
    std::string getTrangThai() const { return trangThai; }

    std::string getGioiTinhPhong() const { return gioiTinhPhong; }
    void setGioiTinhPhong(std::string gtp) { gioiTinhPhong = gtp; }

    // logic phòng trống, còn chỗ, hay đầy
    
    // Số chỗ còn trống
    int soChoTrong() const
    {
        return loaiPhong - soNguoiHienTai;
    }

    // Cập nhật trạng thái tự động dựa vào số người
    void capNhatTrangThai()
    {
        if (soNguoiHienTai == 0)
            trangThai = "trong"; // trống
        else if (soNguoiHienTai < loaiPhong)
            trangThai = "con_cho"; // còn chỗ
        else
            trangThai = "day"; // full
    }

    // Thêm 1 người vào phòng, false nếu đầy
    bool themNguoi()
    {
        if (soNguoiHienTai >= loaiPhong)
            return false;
        soNguoiHienTai++;
        capNhatTrangThai();
        return true;
    }

    // Xóa 1 người khỏi phòng, false nếu trống
    bool xoaNguoi()
    {
        if (soNguoiHienTai <= 0)
            return false;
        soNguoiHienTai--;
        if (soNguoiHienTai == 0) {
            gioiTinhPhong = ""; 
        } // mở khóa giới tính khi phòng trống
        capNhatTrangThai();
        return true;
    }

    // Tương thích với hàm hienThi() của DanhSachCustom
    friend ostream& operator<<(ostream& os, const Phong& p)
    {
        os << "Ma phong: "    << p.maPhong
           << " | Loai: "     << p.loaiPhong << " nguoi"
           << " | So nguoi: " << p.soNguoiHienTai << "/" << p.loaiPhong
           << " | Gia/thang: " << p.giaThueThang
           << " | Gioi tinh phong: "       << (p.gioiTinhPhong.empty() ? "Tu do" : p.gioiTinhPhong)
           << " | Trang thai: " << p.trangThai;
        return os;
    }
};

#endif 