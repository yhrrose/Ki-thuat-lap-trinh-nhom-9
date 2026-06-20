#ifndef HOPDONG_H
#define HOPDONG_H

#include <iostream>
#include <string>

class HopDong
{
private:
    std::string maHopDong;   // Khóa chính
    std::string mssv;        // Khóa ngoại
    std::string maPhong;     // Khóa ngoại
    std::string ngayBatDau;  // "dd/mm/yyyy"
    std::string ngayKetThuc; // "dd/mm/yyyy"
    std::string trangThai;   // "con_hieu_luc" or "het_han" or "da_huy"
    
    double tienPhongKy;      

public:
    // Constructor mặc định
    HopDong() {
        maHopDong = "";
        mssv = "";
        maPhong = "";
        ngayBatDau = "";
        ngayKetThuc = "";
        trangThai = "con_hieu_luc";
        tienPhongKy = 0;     
    }

    // Constructor có tham số 
    HopDong(std::string maHopDong, std::string mssv, std::string maPhong, std::string ngayBatDau, std::string ngayKetThuc) {
        this->maHopDong = maHopDong;
        this->mssv = mssv;
        this->maPhong = maPhong;
        this->ngayBatDau = ngayBatDau;
        this->ngayKetThuc = ngayKetThuc;
        this->trangThai = "con_hieu_luc";  
        this->tienPhongKy = 0; 
    }  

    // Getter
    std::string getMaHopDong()   const { return maHopDong; }
    std::string getMSSV()        const { return mssv; }
    std::string getMaPhong()     const { return maPhong; }
    std::string getNgayBatDau()  const { return ngayBatDau; }
    std::string getNgayKetThuc() const { return ngayKetThuc; }
    std::string getTrangThai()   const { return trangThai; }
    double getTienPhongKy()      const { return tienPhongKy; } 

    // Setter
    void setTrangThai(const std::string& tt)      { trangThai  = tt; }
    void setNgayKetThuc(const std::string& ngay)  { ngayKetThuc = ngay; }
    void setTienPhongKy(double tien)              { tienPhongKy = tien; } 
    // Kiểm tra còn hiệu lực không
    bool conHieuLuc() const { return trangThai == "con_hieu_luc"; }

    // Dùng cho hienThi() trong DanhSachCustom
    friend std::ostream& operator<<(std::ostream& os, const HopDong& hd)
    {
        os << "Ma HD: "    << hd.maHopDong
           << " | MSSV: "  << hd.mssv
           << " | Phong: " << hd.maPhong
           << " | Tu: "    << hd.ngayBatDau
           << " -> "       << hd.ngayKetThuc
           << " | Tien ky: " << hd.tienPhongKy 
           << " | TT: "    << hd.trangThai;
        return os;
    }
};

#endif
