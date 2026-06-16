#ifndef THUATTOAN_H
#define THUATTOAN_H

#include "DanhSachCustom.h"
#include "SinhVien.h"
#include "Phong.h"
#include "HopDong.h"
#include "HoaDon.h"
#include <functional>
#include <string>
    // pivot bat ki
    // partition: chốt rand, duyệt 2 đầu
template <class T>
int partitionRandom(DanhSachCustom<T>& ds, int left, int right, function<bool(const T&, const T&)> soSanh)
{
    // chọn pivot rand
    int m = left + rand() % (right - left + 1);
    
    // swap(data[m], data[right])
    T tempM = ds.lay(m);
    ds.capNhat(m, ds.lay(right));
    ds.capNhat(right, tempM);

    T pivot = ds.lay(right); 
    
    // Duyệt 2 đầu
    int i = left;
    int j = right - 1;

    while (i <= j)
    {
        // Tìm phần tử bên trái >= pivot
        while (i <= j && soSanh(ds.lay(i), pivot)) {
            i++;
        }
        // Tìm phần tử bên phải <= pivot
        while (i <= j && soSanh(pivot, ds.lay(j))) {
            j--;
        }
        // Đổi chỗ nếu i <= j
        if (i <= j)
        {
            T tmp = ds.lay(i);
            ds.capNhat(i, ds.lay(j));
            ds.capNhat(j, tmp);
            i++;
            j--;
        }
    }

    // swap(data[i], data[right])
    T tmpPivot = ds.lay(i);
    ds.capNhat(i, ds.lay(right));
    ds.capNhat(right, tmpPivot);

    return i; 
}

// quick sort recursive
template <class T>
void quickSort(DanhSachCustom<T>& ds, int left, int right, function<bool(const T&, const T&)> soSanh)
{
    if (left < right)
    {
        // Lấy vị trí partition
        int i = partitionRandom(ds, left, right, soSanh);
        
        // Đệ quy
        quickSort(ds, left, i - 1, soSanh);
        quickSort(ds, i + 1, right, soSanh);
    }
}

template <class T, class Key>
int binarySearch(const DanhSachCustom<T>& ds, const Key& target, std::function<Key(const T&)> layKey)
{
    int left = 0, right = ds.kichThuoc() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        Key k = layKey(ds.lay(mid));
        if (k == target) return mid;
        if (k <  target) left  = mid + 1;
        else             right = mid - 1;
    }
    return -1;
}

// Tiện ích SV

inline void sapXepSVTheoMSSV(DanhSachCustom<SinhVien>& ds)
{
    quickSort<SinhVien>(ds, 0, ds.kichThuoc() - 1,
        [](const SinhVien& a, const SinhVien& b){ return a.getMSSV() < b.getMSSV(); });
    ds.danhDauDaSapXep(); 
}
//
inline void sapXepSVTheoHoTen(DanhSachCustom<SinhVien>& ds)
{
    quickSort<SinhVien>(ds, 0, ds.kichThuoc() - 1,
        [](const SinhVien& a, const SinhVien& b){ return a.getHoTen() < b.getHoTen(); });
    ds.danhDauChuaSapXep(); // Bật cờ dirty vì đã phá vỡ thứ tự MSSV
}

inline int timSVTheoMSSV(DanhSachCustom<SinhVien>& ds, const std::string& mssv)
{
    // LAZY SORT
    if (!ds.daSapXep()) {
        sapXepSVTheoMSSV(ds);
    }
    return binarySearch<SinhVien, std::string>(ds, mssv, [](const SinhVien& sv){ return sv.getMSSV(); });
}

inline int timSVTheoTen(const DanhSachCustom<SinhVien>& ds, const std::string& hoTen)
{
    for (int i = 0; i < ds.kichThuoc(); i++)
        if (ds.lay(i).getHoTen() == hoTen) return i;
    return -1;
}
//hàm so sánh diện

inline int doUuTien(const std::string& dien)
{
    if (dien == "chinh_sach") return 0;  // thương binh, người có công với cách mạng...
    if (dien == "uu_tien")    return 1;  // sinh viên đỗ nghèo khỉ, sinh viên toán tin phải học gts
    return 2;                             // bình thường
}

inline void sapXepTheoUuTien(DanhSachCustom<SinhVien>& ds)
{
    quickSort<SinhVien>(ds, 0, ds.kichThuoc() - 1,
        [](const SinhVien& a, const SinhVien& b){
            return doUuTien(a.getDienUuTien()) < doUuTien(b.getDienUuTien());
        });
    ds.danhDauChuaSapXep();
}
// Tiện ích Phòng

inline void sapXepPhongTheoMa(DanhSachCustom<Phong>& ds)
{
    quickSort<Phong>(ds, 0, ds.kichThuoc() - 1,
        [](const Phong& a, const Phong& b){ return a.getMaPhong() < b.getMaPhong(); });
    ds.danhDauDaSapXep(); 
}
//
inline void sapXepPhongTheoLoai(DanhSachCustom<Phong>& ds)
{
    quickSort<Phong>(ds, 0, ds.kichThuoc() - 1,
        [](const Phong& a, const Phong& b){ return a.getLoaiPhong() < b.getLoaiPhong(); });
    ds.danhDauChuaSapXep();
}
inline int timPhongTheoMa(DanhSachCustom<Phong>& ds, const std::string& maPhong)
{
    // LAZY SORT
    if (!ds.daSapXep()) {
        sapXepPhongTheoMa(ds);
    }
    return binarySearch<Phong, std::string>(ds, maPhong, [](const Phong& p){ return p.getMaPhong(); });
}

inline int timPhongConCho(const DanhSachCustom<Phong>& ds, int loaiPhong)
{
    for (int i = 0; i < ds.kichThuoc(); i++) {
        const Phong& p = ds.lay(i);
        if (p.getLoaiPhong() == loaiPhong && p.soChoTrong() > 0) return i;
    }
    return -1;
}

// Tiện ích Hợp đồng

inline void sapXepHDTheoMa(DanhSachCustom<HopDong>& ds)
{
    quickSort<HopDong>(ds, 0, ds.kichThuoc() - 1,
        [](const HopDong& a, const HopDong& b){ return a.getMaHopDong() < b.getMaHopDong(); });
    ds.danhDauDaSapXep(); 
}

inline int timHDTheoMa(DanhSachCustom<HopDong>& ds, const std::string& maHD)
{
    // LAZY SORT
    if (!ds.daSapXep()) {
        sapXepHDTheoMa(ds);
    }
    return binarySearch<HopDong, std::string>(ds, maHD, [](const HopDong& hd){ return hd.getMaHopDong(); });
}

inline int timHDCuaSV(const DanhSachCustom<HopDong>& ds, const std::string& mssv)
{
    for (int i = 0; i < ds.kichThuoc(); i++)
        if (ds.lay(i).getMSSV() == mssv && ds.lay(i).conHieuLuc()) return i;
    return -1;
}

inline DanhSachCustom<HopDong> timHDTheoPhong(const DanhSachCustom<HopDong>& ds, const std::string& maPhong)
{
    DanhSachCustom<HopDong> ketQua;
    for (int i = 0; i < ds.kichThuoc(); i++)
        if (ds.lay(i).getMaPhong() == maPhong) ketQua.them(ds.lay(i));
    return ketQua;
}

// Tiện ích Hóa đơn

inline void sapXepHoaDonTheoMa(DanhSachCustom<HoaDon>& ds)
{
    quickSort<HoaDon>(ds, 0, ds.kichThuoc() - 1,
        [](const HoaDon& a, const HoaDon& b){ return a.getMaHoaDon() < b.getMaHoaDon(); });
    ds.danhDauDaSapXep(); 
}

inline void sapXepHoaDonTheoTien(DanhSachCustom<HoaDon>& ds)
{
    quickSort<HoaDon>(ds, 0, ds.kichThuoc() - 1,
        [](const HoaDon& a, const HoaDon& b){ return a.getTongTienDV() < b.getTongTienDV(); });
    ds.danhDauChuaSapXep(); 
}

inline int timHoaDonTheoMa(DanhSachCustom<HoaDon>& ds, const std::string& maHD)
{
    // LAZY SORT
    if (!ds.daSapXep()) {
        sapXepHoaDonTheoMa(ds);
    }
    return binarySearch<HoaDon, std::string>(ds, maHD, [](const HoaDon& hd){ return hd.getMaHoaDon(); });
}

static inline DanhSachCustom<HoaDon> timHoaDonTheoPhong(const DanhSachCustom<HoaDon>& ds, const std::string& maPhong)
{
    DanhSachCustom<HoaDon> ketQua;
    for (int i = 0; i < ds.kichThuoc(); i++)
    {
        if (ds.lay(i).getMaPhong() == maPhong) ketQua.them(ds.lay(i));
    }
    return ketQua;
}

inline DanhSachCustom<HoaDon> timHoaDonChuaThu(const DanhSachCustom<HoaDon>& ds)
{
    DanhSachCustom<HoaDon> ketQua;
    for (int i = 0; i < ds.kichThuoc(); i++) {
        string tt = ds.lay(i).getTrangThai();
        if (tt == "chua_thu" || tt == "qua_han") ketQua.them(ds.lay(i));
    }
    return ketQua;
}

#endif