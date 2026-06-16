#ifndef DANHSACHCUSTOM_H
#define DANHSACHCUSTOM_H

#include <iostream>
using namespace std;

template <class T>
class DanhSachCustom
{
private:
    T* ds;           // Con trỏ quản lý mảng động
    int soLuong;     // Số phần tử hiện có
    int sucChua;     // Kích thước tối đa hiện tại của mảng
    bool trangThaiSapXep;
    // Hàm mở rộng mảng khi đầy
    void moRong()
    {
        sucChua = (sucChua == 0) ? 1 : sucChua * 2; // fix1 ở đây 

        T* mangMoi = new T[sucChua];

        for(int i = 0; i < soLuong; i++)
        {
            mangMoi[i] = ds[i];
        }

        delete[] ds;
        ds = mangMoi;
    }

public:

    // Constructor
    DanhSachCustom(int kichThuocBanDau = 10)
    {
        sucChua  = (kichThuocBanDau > 0) ? kichThuocBanDau : 1; //fix2 ở đây
        soLuong = 0;
        ds = new T[sucChua];
        trangThaiSapXep = false; 
    }
    // Copy Constructor
    DanhSachCustom(const DanhSachCustom<T>& other)
    {
        sucChua = other.sucChua;
        soLuong = other.soLuong;
        trangThaiSapXep = other.trangThaiSapXep; 
        ds      = new T[sucChua];
 
        for (int i = 0; i < soLuong; i++) { ds[i] = other.ds[i]; }
    }
 
    // assig operator
    DanhSachCustom<T>& operator=(const DanhSachCustom<T>& other)
    {
        if (this == &other) return *this;
        delete[] ds;         
 
        sucChua = other.sucChua;
        soLuong = other.soLuong;
        trangThaiSapXep = other.trangThaiSapXep; 
        ds      = new T[sucChua];
 
        for (int i = 0; i < soLuong; i++) { ds[i] = other.ds[i]; }
        return *this;
    }
    
    // Destructor
    ~DanhSachCustom(){
        delete[] ds;
    }

    // Thêm phần tử vào cuối danh sách
    void them(const T& x)
    {
        if(soLuong == sucChua)
        {
            moRong();
        }

        ds[soLuong] = x;
        soLuong++;
        trangThaiSapXep = false;
    }

    // Xóa phần tử theo vị trí
    bool xoa(int viTri)
    {
        if(viTri < 0 || viTri >= soLuong) return false;

        for(int i = viTri; i < soLuong - 1; i++) {
            ds[i] = ds[i + 1];
        }
        soLuong--;
        return true;
    }
    // fix5
    // Lấy phần tử tại vị trí bất kỳ
     T& lay(int viTri){
        if (viTri < 0 || viTri >= soLuong)
        {
            throw out_of_range("DanhSachCustom: chi so vuot qua gioi han! viTri = "
                               + to_string(viTri)
                               + ", soLuong = "
                               + to_string(soLuong));
        }
        return ds[viTri];
    }
 
    // dùng khi đối tượng là const
    const T& lay(int viTri) const{
        if (viTri < 0 || viTri >= soLuong)
        {
            throw out_of_range("DanhSachCustom: chi so vuot qua gioi han! viTri = "
                               + to_string(viTri)
                               + ", soLuong = "
                               + to_string(soLuong));
        }
        return ds[viTri];
    }

    // Cập nhật phần tử
    // Trong DanhSachCustom.h
    void capNhat(int viTri, const T& giaTriMoi, bool giuCo = false) {
        if (viTri >= 0 && viTri < soLuong) {
            ds[viTri] = giaTriMoi;
            if (!giuCo) trangThaiSapXep = false;
        }
    }
    // getter và setter cho cờ
    bool daSapXep() const { return trangThaiSapXep; }
    // Bật cờ đã sắp xếp
    void danhDauDaSapXep() { trangThaiSapXep = true; }
    // Bật cờ chưa sắp xếp
    void danhDauChuaSapXep() { trangThaiSapXep = false; }

    // Trả về số lượng phần tử
    int kichThuoc() const
    {
        return soLuong;
    }

    // Kiểm tra rỗng
    bool rong() const
    {
        return soLuong == 0;
    }

    // Hiển thị danh sách
    void hienThi() const
    {
        for(int i = 0; i < soLuong; i++)
        {
            cout << ds[i] << endl;
        }
    }
};

#endif