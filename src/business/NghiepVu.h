#ifndef NGHIEPVU_H
#define NGHIEPVU_H

#include "DanhSachCustom.h"
#include "SinhVien.h"
#include "Phong.h"
#include "HopDong.h"
#include "HoaDon.h"
#include <string>

//  QUẢN LÝ SINH VIÊN

//Thêm sinh viên, check trùng MSSV: true nếu thêm thành công, false nếu MSSV đã tồn tại
bool themSinhVien(DanhSachCustom<SinhVien>& dsSV, const SinhVien& sv);

// Xóa SV theo mssv: true nếu xóa thành công, false nếu không tìm thấy
bool xoaSinhVien(DanhSachCustom<SinhVien>& dsSV, const std::string& mssv);

// Sửa thông tin sinh viên theo MSSV (không cho sửa MSSV và maPhong)
bool suaSinhVien(DanhSachCustom<SinhVien>& dsSV, const std::string& mssv,
                 const std::string& hoTenMoi, const std::string& gioiTinhMoi,
                 const std::string& ngaySinhMoi, const std::string& lopMoi,
                 const std::string& sdtMoi, const std::string& emailMoi, const std::string& dienUuTienMoi);

//  QUẢN LÝ PHÒNG

// Thêm phòng mới, kiểm tra trùng mã phòng
bool themPhong(DanhSachCustom<Phong>& dsPhong, const Phong& p);

// Sửa giá thuê phòng
bool suaGiaPhong(DanhSachCustom<Phong>& dsPhong, const std::string& maPhong, double giaMoi);

//  NGHIỆP VỤ THUÊ PHÒNG

// Hàm xếp phòng tự động cho tất cả sinh viên chưa có phòng, dựa trên tiêu chí ưu tiên
void xepPhongTuDong(DanhSachCustom<SinhVien>& dsSV,
                    DanhSachCustom<Phong>&    dsPhong,
                    DanhSachCustom<HopDong>&  dsHD,
                    const std::string& ngayBatDau,
                    const std::string& ngayKetThuc);

// Đăng ký phòng cho sinh viên
bool dangKyPhong(DanhSachCustom<SinhVien>& dsSV,
                 DanhSachCustom<Phong>&    dsPhong,
                 DanhSachCustom<HopDong>&  dsHD,
                 const std::string& mssv,
                 const std::string& maPhong,
                 const std::string& ngayBatDau,
                 const std::string& ngayKetThuc);

// Chuyển phòng cho sinh viên
bool chuyenPhong(DanhSachCustom<SinhVien>& dsSV,
                 DanhSachCustom<Phong>&    dsPhong,
                 DanhSachCustom<HopDong>&  dsHD,
                 const std::string& mssv,
                 const std::string& maPhongMoi,
                 const std::string& ngayBatDau,
                 const std::string& ngayKetThuc);

// Gia hạn hợp đồng (cập nhật ngayKetThuc)
bool giaHanHopDong(DanhSachCustom<HopDong>& dsHD,
                   const std::string& maHD,
                   const std::string& ngayKetThucMoi);

// Hủy hợp đồng (trả phòng)
bool huyHopDong(DanhSachCustom<SinhVien>& dsSV,
                DanhSachCustom<Phong>&    dsPhong,
                DanhSachCustom<HopDong>&  dsHD,
                const DanhSachCustom<HoaDon>& dsHoaDon, 
                const std::string& maHD);

//  NGHIỆP VỤ HÓA ĐƠN

// Lập hóa đơn tháng cho 1 hợp đồng
bool lapHoaDon(DanhSachCustom<HoaDon>&  dsHoaDon,
               DanhSachCustom<Phong>&   dsPhong,
               const std::string& maPhong,
               const std::string& thangNam,
               const std::string& hanThanhToan,
               double chiSoDienDau, double chiSoDienCuoi,
               double chiSoNuocDau, double chiSoNuocCuoi,
               double tienPhat);
// Cộng thêm tiền phạt cơ sở vật chất vào hóa đơn
bool ghiNhanTienPhat(DanhSachCustom<HoaDon>& dsHoaDon, const std::string& maHoaDon, double soTienPhat);

// Thu tiền hóa đơn (đổi trạng thái "da_thu")
bool thuHoaDon(DanhSachCustom<HoaDon>& dsHoaDon, const std::string& maHoaDon);

// Đánh dấu hóa đơn quá hạn (đổi trạng thái "qua_han")
bool danhDauQuaHan(DanhSachCustom<HoaDon>& dsHoaDon, const std::string& maHoaDon);

//  THỐNG KÊ
// Danh sách sinh viên đang quá hạn nộp phí
DanhSachCustom<SinhVien> layDSSVQuaHan(DanhSachCustom<SinhVien>& dsSV, DanhSachCustom<HoaDon>& dsHoaDon);

// Tỉ lệ lấp đầy theo từng loại phòng (4/6/8 người)
void thongKeLapDay(const DanhSachCustom<Phong>& dsPhong);

#endif 