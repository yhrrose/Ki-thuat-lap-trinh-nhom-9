#ifndef FILEIO_H
#define FILEIO_H

#include "DanhSachCustom.h"
#include "SinhVien.h"
#include "Phong.h"
#include "HopDong.h"
#include "HoaDon.h"
#include "ThuatToan.h" 


 // LOAD DATA
void loadData(DanhSachCustom<SinhVien>& dsSV, 
              DanhSachCustom<Phong>& dsPhong, 
              DanhSachCustom<HopDong>& dsHD, 
              DanhSachCustom<HoaDon>& dsHoaDon);

// SAVE DATA 
void saveDataFinal(const DanhSachCustom<SinhVien>& dsSV, 
                   const DanhSachCustom<Phong>& dsPhong, 
                   const DanhSachCustom<HopDong>& dsHD, 
                   const DanhSachCustom<HoaDon>& dsHoaDon);
#endif
