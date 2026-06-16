#include "NghiepVu.h"
#include "ThuatToan.h"
#include <iostream>
#include <iomanip>
using namespace std;

//  QUẢN LÝ SINH VIÊN

bool themSinhVien(DanhSachCustom<SinhVien>& dsSV, const SinhVien& sv)
{
    // Kiểm tra trùng MSSV 
    if (timSVTheoMSSV(dsSV, sv.getMSSV()) != -1)
    {
        cout << "Loi: MSSV " << sv.getMSSV() << " da ton tai!\n";
        return false;
    }

    dsSV.them(sv);
    cout << "Da them sinh vien " << sv.getMSSV() << " thanh cong.\n";
    return true;
}

bool xoaSinhVien(DanhSachCustom<SinhVien>& dsSV, const string& mssv)
{
    // Tìm kiếm vị trí sinh viên 
    int idx = timSVTheoMSSV(dsSV, mssv);
    if (idx != -1)
    {
        if (dsSV.lay(idx).dangThuePhong())
        {
            cout << "Loi: SV " << mssv << " dang thue phong, khong the xoa!\n";
            return false;
        }
        dsSV.xoa(idx);
        cout << "Da xoa sinh vien " << mssv << ".\n";
        return true;
    }

    cout << "Loi: Khong tim thay MSSV " << mssv << ".\n";
    return false;
}

bool suaSinhVien(DanhSachCustom<SinhVien>& dsSV, const string& mssv,
                 const string& hoTenMoi, const string& gioiTinhMoi, const string& ngaySinhMoi, const string& lopMoi,
                 const string& sdtMoi,   const string& emailMoi, const string& dienUuTienMoi)
{
    // Tìm kiếm vị trí sinh viên 
    int idx = timSVTheoMSSV(dsSV, mssv);
    if (idx != -1)
    {
        // Tạo SV mới với dữ liệu cập nhật, giữ nguyên mssv và maPhong
        SinhVien svMoi(mssv, hoTenMoi, gioiTinhMoi, ngaySinhMoi, lopMoi, sdtMoi, emailMoi,
                       dsSV.lay(idx).getMaPhong(), dienUuTienMoi);
        dsSV.capNhat(idx, svMoi, true); //fix
        cout << "Da cap nhat thong tin SV " << mssv << ".\n";
        return true;
    }

    cout << "Loi: Khong tim thay MSSV " << mssv << ".\n";
    return false;
}

//  QUẢN LÝ PHÒNG
bool themPhong(DanhSachCustom<Phong>& dsPhong, const Phong& p)
{
    // Kiểm tra trùng mã phòng bằng
    if (timPhongTheoMa(dsPhong, p.getMaPhong()) != -1)
    {
        cout << "Loi: Ma phong " << p.getMaPhong() << " da ton tai!\n";
        return false;
    }

    dsPhong.them(p);
    cout << "Da them phong " << p.getMaPhong() << " thanh cong.\n";
    return true;
}

bool suaGiaPhong(DanhSachCustom<Phong>& dsPhong, const string& maPhong, double giaMoi)
{
    // Tìm kiếm vị trí phòng 
    int idx = timPhongTheoMa(dsPhong, maPhong);
    if (idx != -1)
    {
        Phong p = dsPhong.lay(idx); // lấy bản sao dữ liệu hiện tại
        Phong pMoi(p.getMaPhong(), p.getLoaiPhong(), giaMoi);
        pMoi.setGioiTinhPhong(p.getGioiTinhPhong());
        // giữ lại số lượng người hiện tại và cập nhật trạng thái phòng tương ứng
        for (int j = 0; j < p.getSoNguoiHienTai(); j++)
            pMoi.themNguoi();
        dsPhong.capNhat(idx, pMoi, true); //fix
        cout << "Da cap nhat gia phong " << maPhong << ".\n";
        return true;
    }

    cout << "Loi: Khong tim thay phong " << maPhong << ".\n";
    return false;
}

//  NGHIỆP VỤ THUÊ PHÒNG
bool dangKyPhong(DanhSachCustom<SinhVien>& dsSV,
                 DanhSachCustom<Phong>&    dsPhong,
                 DanhSachCustom<HopDong>&  dsHD,
                 const string& mssv,
                 const string& maPhong,
                 const string& ngayBatDau,
                 const string& ngayKetThuc)
{
    // tìm sv
    int idxSV = timSVTheoMSSV(dsSV, mssv);
    if (idxSV == -1) {
        cout << "Loi: Khong tim thay MSSV " << mssv << ".\n";
        return false;
    }
    
    SinhVien sv = dsSV.lay(idxSV);
    if (sv.dangThuePhong()) {
        cout << "Loi: SV " << mssv << " dang o phong " << sv.getMaPhong() << "!\n";
        return false;
    }
    // tìm phòng
    int idxPhong = timPhongTheoMa(dsPhong, maPhong);
    if (idxPhong == -1) {
        cout << "Loi: Khong tim thay phong " << maPhong << ".\n";
        return false;
    }
    
    Phong p = dsPhong.lay(idxPhong);
    if (p.soChoTrong() <= 0) {
        cout << "Loi: Phong " << maPhong << " da day!\n";
        return false;
    }
    // khóa giới tính động
    if (p.getSoNguoiHienTai() == 0) {
        // Nếu phòng trống thì cố định giới tính phòng theo sv đầu
        p.setGioiTinhPhong(sv.getGioiTinh());
    } 
    else {
        // Nếu phòng đã có người thì giới tính sv khớp với phòng
        if (p.getGioiTinhPhong() != sv.getGioiTinh()) {
            cout << "Loi: Phong " << maPhong << " hien dang duoc khoa danh cho [" << p.getGioiTinhPhong() << "]!\n";
            cout << "Sinh vien co gioi tinh la [" << sv.getGioiTinh() << "], khong the xep chung!\n";
            return false;
        }
    }
    // hợp đồng và tính tiền
    // mã HD
    string maHD = "HD_" + mssv + "_" + maPhong + "_" + to_string(dsHD.kichThuoc() + 1); 

    HopDong hd(maHD, mssv, maPhong, ngayBatDau, ngayKetThuc);

    // Tính tiền phòng (1 kỳ = 5 tháng) chia đều cho sức chứa của phòng
    double giaThang = p.getGiaThueThang();
    int sucChua = p.getLoaiPhong(); 
    hd.setTienPhongKy((giaThang * 5) / sucChua); 
    
    dsHD.them(hd); // Lưu hợp đồng vào danh sách

    // Cập nhật thông tin sv
    sv.setMaPhong(maPhong);
    dsSV.capNhat(idxSV, sv, true);

    // Cập nhật thông tin phòng 
    p.themNguoi(); 
    dsPhong.capNhat(idxPhong, p, true);

    cout << ">> Dang ky phong thanh cong! Ma hop dong: " << maHD << "\n";
    return true;
}

bool chuyenPhong(DanhSachCustom<SinhVien>& dsSV,
                 DanhSachCustom<Phong>&    dsPhong,
                 DanhSachCustom<HopDong>&  dsHD,
                 const string& mssv,
                 const string& maPhongMoi,
                 const string& ngayBatDau,
                 const string& ngayKetThuc)
{
    // Tìm vị trí SV 
    int idxSV = timSVTheoMSSV(dsSV, mssv);

    if (idxSV == -1){
        cout << "Loi: Khong tim thay MSSV " << mssv << ".\n";
        return false;
    }
    if (!dsSV.lay(idxSV).dangThuePhong()){
        cout << "Loi: SV " << mssv << " chua thue phong nao!\n";
        return false;
    }

    string maPhongCu = dsSV.lay(idxSV).getMaPhong();
    if (maPhongCu == maPhongMoi){
        cout << "Loi: SV da dang o phong " << maPhongMoi << " roi!\n";
        return false;
    }

    // Tìm vị trí phòng mới 
    int idxPhongMoi = timPhongTheoMa(dsPhong, maPhongMoi);

    if (idxPhongMoi == -1){
        cout << "Loi: Khong tim thay phong " << maPhongMoi << ".\n";
        return false;
    }
    if (dsPhong.lay(idxPhongMoi).soChoTrong() <= 0){
        cout << "Loi: Phong " << maPhongMoi << " da day!\n";
        return false;
    }

    SinhVien sv = dsSV.lay(idxSV);
    Phong pMoi = dsPhong.lay(idxPhongMoi); 
    // Khóa/kiểm tra giới tính
    if (pMoi.getSoNguoiHienTai() == 0) {
        pMoi.setGioiTinhPhong(sv.getGioiTinh());
    } else {
        if (pMoi.getGioiTinhPhong() != sv.getGioiTinh()) {
            cout << "Loi: Khong the chuyen! Phong moi dang danh cho " << pMoi.getGioiTinhPhong() << "!\n";
            return false;
        }
    }

    // Hủy hợp đồng cũ 
    int idxHDCu = timHDCuaSV(dsHD, mssv);
    if (idxHDCu != -1)
    {
        HopDong hd = dsHD.lay(idxHDCu);
        hd.setTrangThai("da_huy");
        dsHD.capNhat(idxHDCu, hd, true); 
    }

    // Giảm số người phòng cũ 
    int idxPhongCu = timPhongTheoMa(dsPhong, maPhongCu);
    if (idxPhongCu != -1)
    {
        Phong p = dsPhong.lay(idxPhongCu);
        p.xoaNguoi();
        dsPhong.capNhat(idxPhongCu, p, true); 
    }

    // Tạo hợp đồng mới
    string maHDMoi = "HD_" + mssv + "_" + maPhongMoi + "_" + to_string(dsHD.kichThuoc() + 1);
    HopDong hdMoi(maHDMoi, mssv, maPhongMoi, ngayBatDau, ngayKetThuc);

    // Tính lại tiền phòng kỳ cho phòng mới
    double giaThangMoi = dsPhong.lay(idxPhongMoi).getGiaThueThang();
    int sucChuaMoi = dsPhong.lay(idxPhongMoi).getLoaiPhong();
    hdMoi.setTienPhongKy((giaThangMoi * 5) / sucChuaMoi);
    
    dsHD.them(hdMoi);

    // Cập nhật SV
    sv = dsSV.lay(idxSV);
    sv.setMaPhong(maPhongMoi);
    dsSV.capNhat(idxSV, sv, true);

    // Tăng số người phòng mới
    pMoi = dsPhong.lay(idxPhongMoi);
    pMoi.themNguoi();
    dsPhong.capNhat(idxPhongMoi, pMoi, true);

    cout << "Chuyen phong thanh cong! Ma hop dong moi: " << maHDMoi << "\n";
    return true;
}

bool giaHanHopDong(DanhSachCustom<HopDong>& dsHD,
                   const string& maHD,
                   const string& ngayKetThucMoi)
{
    // Tìm kiếm vị trí hợp đồng 
    int idx = timHDTheoMa(dsHD, maHD);
    if (idx != -1)
    {
        if (!dsHD.lay(idx).conHieuLuc())
        {
            cout << "Loi: Hop dong " << maHD << " khong con hieu luc!\n";
            return false;
        }
        HopDong hd = dsHD.lay(idx);
        hd.setNgayKetThuc(ngayKetThucMoi);
        dsHD.capNhat(idx, hd, true); // fix
        cout << "Da gia han hop dong " << maHD << " den " << ngayKetThucMoi << ".\n";
        return true;
    }

    cout << "Loi: Khong tim thay hop dong " << maHD << ".\n";
    return false;
}

bool huyHopDong(DanhSachCustom<SinhVien>& dsSV,
                DanhSachCustom<Phong>&    dsPhong,
                DanhSachCustom<HopDong>&  dsHD,
                const DanhSachCustom<HoaDon>& dsHoaDon, // Tham số mới
                const string& maHD)
{
    int idxHD = timHDTheoMa(dsHD, maHD);
    if (idxHD == -1) { cout << "Loi: Khong tim thay hop dong " << maHD << ".\n"; return false; }
    if (!dsHD.lay(idxHD).conHieuLuc()) { cout << "Loi: Hop dong " << maHD << " khong con hieu luc!\n"; return false; }

    string mssv    = dsHD.lay(idxHD).getMSSV();
    string maPhong = dsHD.lay(idxHD).getMaPhong();

    //ko đc hủy nếu còn nợ
    for (int i = 0; i < dsHoaDon.kichThuoc(); i++) {
        if (dsHoaDon.lay(i).getMaPhong() == maPhong && 
           (dsHoaDon.lay(i).getTrangThai() == "chua_thu" || dsHoaDon.lay(i).getTrangThai() == "qua_han")) {
            cout << "Loi: Phong " << maPhong << " van con hoa don chua thanh toan! Vui long dong phat/hoa don truoc khi tra phong.\n";
            return false;
        }
    }
    // Hủy hợp đồng 
    HopDong hd = dsHD.lay(idxHD);
    hd.setTrangThai("da_huy");
    dsHD.capNhat(idxHD, hd, true); 
    
    // Xóa maPhong của SV 
    int idxSV = timSVTheoMSSV(dsSV, mssv);
    if (idxSV != -1)
    {
        SinhVien sv = dsSV.lay(idxSV);
        sv.setMaPhong("");
        dsSV.capNhat(idxSV, sv, true); 
    }

    // Giảm số người phòng
    int idxPhong = timPhongTheoMa(dsPhong, maPhong);
    if (idxPhong != -1)
    {
        Phong p = dsPhong.lay(idxPhong);
        p.xoaNguoi();
        dsPhong.capNhat(idxPhong, p, true); 
    }

    cout << "Da huy hop dong " << maHD << ". SV " << mssv << " da tra phong " << maPhong << ".\n";
    return true;
}

// XẾP PHÒNG
void xepPhongTuDong(DanhSachCustom<SinhVien>& dsSV,
                    DanhSachCustom<Phong>&    dsPhong,
                    DanhSachCustom<HopDong>&  dsHD,
                    const string& ngayBatDau,
                    const string& ngayKetThuc)
{
    DanhSachCustom<SinhVien> dsCho; // Danh sách hàng đợi

    // Lọc các sinh viên chưa có phòng
    for (int i = 0; i < dsSV.kichThuoc(); i++) {
        if (!dsSV.lay(i).dangThuePhong()) {
            dsCho.them(dsSV.lay(i));
        }
    }

    if (dsCho.rong()) {
        cout << ">> Khong co sinh vien nao dang cho xep phong.\n";
        return;
    }

    // Sắp xếp danh sách chờ theo diện ưu tiên
    sapXepTheoUuTien(dsCho);

    // Duyệt danh sách và cấp phát phòng
    int countSuccess = 0;
    for (int i = 0; i < dsCho.kichThuoc(); i++) {
        SinhVien svCho = dsCho.lay(i);
        string mssv = svCho.getMSSV();
        string gtSV = svCho.getGioiTinh();

        bool daXepDuoc = false;
        bool conChoTrongKTX = false; // Cờ kiểm tra xem KTX đã đầy chưa

        // Duyệt tất cả các phòng để tìm phòng phù hợp nhất
        for (int j = 0; j < dsPhong.kichThuoc(); j++) {
            Phong p = dsPhong.lay(j);
            
            if (p.soChoTrong() > 0) {
                conChoTrongKTX = true; 
                
                // kiểm tra: Phòng phải rỗng hoặc phải cùng giới tính
                string gtPhong = p.getGioiTinhPhong();
                if (gtPhong == "" || gtPhong == gtSV) {
                    string maP = p.getMaPhong();
                    
                    // Nếu khớp điều kiện, gọi đăng ký
                    if (dangKyPhong(dsSV, dsPhong, dsHD, mssv, maP, ngayBatDau, ngayKetThuc)) {
                        countSuccess++;
                        daXepDuoc = true;
                        break; // Đã xếp thành công cho SV này, thoát để xét SV tiếp theo
                    }
                }
            }
        }

        if (!conChoTrongKTX) {
            cout << "\n>> THONG BAO: KTX DA KIN CHO! Khong the xep tiep.\n";
            break; // Hết sạch phòng thì thoát vòng lặp xét sinh viên luôn
        }

        if (!daXepDuoc) {
            cout << ">> Bo qua SV " << mssv << " (" << gtSV << ") do chua co phong " << gtSV << " nao con cho!\n";
        }
    }

    cout << "\n>> TONG KET: Da xep phong tu dong thanh cong cho " << countSuccess << " sinh vien!\n";
}


//  NGHIỆP VỤ HÓA ĐƠN
bool lapHoaDon(DanhSachCustom<HoaDon>&  dsHoaDon,
               DanhSachCustom<Phong>&   dsPhong,  
               const string& maPhong,
               const string& thangNam,
               const string& hanThanhToan,
               double chiSoDienDau, double chiSoDienCuoi,
               double chiSoNuocDau, double chiSoNuocCuoi,
               double tienPhat)
{
    // Kiểm tra phòng có tồn tại không
    int idxPhong = timPhongTheoMa(dsPhong, maPhong);
    if (idxPhong == -1) {
        cout << "Loi: Khong tim thay phong " << maPhong << ".\n";
        return false;
    }

    Phong p = dsPhong.lay(idxPhong);
    if (p.getSoNguoiHienTai() == 0) {
        cout << "Loi: Phong " << maPhong << " hien khong co ai o, khong can lap hoa don!\n";
        return false;
    }

    // điều kiện chỉ số điện nước
    if (chiSoDienDau < 0 || chiSoNuocDau < 0) {
        cout << "Loi: Chi so dien/nuoc khong duoc am!\n";
        return false;
    }
    if (chiSoDienCuoi < chiSoDienDau) {
        cout << "Loi: Chi so dien cuoi (" << chiSoDienCuoi
             << ") khong the nho hon chi so dau (" << chiSoDienDau << ")!\n";
        return false;
    }
    if (chiSoNuocCuoi < chiSoNuocDau) {
        cout << "Loi: Chi so nuoc cuoi (" << chiSoNuocCuoi
             << ") khong the nho hon chi so dau (" << chiSoNuocDau << ")!\n";
        return false;
    }

    // Sinh mã hóa đơn theo phòng (eg: INV_P101_05/2026)
    string maHoaDon = "INV_" + maPhong + "_" + thangNam;

    // Kiểm tra trùng mã hóa đơn 
    if (timHoaDonTheoMa(dsHoaDon, maHoaDon) != -1) {
        cout << "Loi: Hoa don thang " << thangNam << " cho phong " << maPhong << " da ton tai!\n";
        return false;
    }

    // Khởi tạo hóa đơn
    HoaDon hd(maHoaDon, maPhong, thangNam, hanThanhToan,
              chiSoDienDau, chiSoDienCuoi,
              chiSoNuocDau, chiSoNuocCuoi
              );

    // set fine
    hd.setTienPhat(tienPhat);
              
    dsHoaDon.them(hd);
    cout << ">> Da lap hoa don " << maHoaDon << " | Tong tien: "  << hd.getTongTienDV() << " dong\n";
    return true;
}

bool ghiNhanTienPhat(DanhSachCustom<HoaDon>& dsHoaDon, const string& maHoaDon, double soTienPhat)
{
    int idx = timHoaDonTheoMa(dsHoaDon, maHoaDon);
    if (idx != -1)
    {
        if (dsHoaDon.lay(idx).getTrangThai() == "da_thu") {
            cout << "Loi: Hoa don nay da thanh toan, khong the cong them tien phat!\n";
            return false;
        }
        
        HoaDon hd = dsHoaDon.lay(idx);
        // Cộng dồn tiền phạt (trường hợp 1 tháng hỏng nhiều thứ)
        double tienPhatMoi = hd.getTienPhat() + soTienPhat; 
        hd.setTienPhat(tienPhatMoi); 
        
        dsHoaDon.capNhat(idx, hd, true);
        cout << ">> Da ghi nhan " << soTienPhat << " dong tien phat vao hoa don " << maHoaDon << ".\n";
        cout << ">> Tong tien moi phai dong: " << hd.getTongTienDV() << " dong.\n";
        return true;
    }
    cout << "Loi: Khong tim thay hoa don " << maHoaDon << ".\n";
    return false;
}

bool thuHoaDon(DanhSachCustom<HoaDon>& dsHoaDon, const string& maHoaDon)
{
    // Tìm kiếm vị trí hóa đơn cần thu 
    int idx = timHoaDonTheoMa(dsHoaDon, maHoaDon);
    if (idx != -1)
    {
        if (dsHoaDon.lay(idx).getTrangThai() == "da_thu")
        {
            cout << "Loi: Hoa don " << maHoaDon << " da duoc thu roi!\n";
            return false;
        }
        HoaDon hd = dsHoaDon.lay(idx);
        hd.setTrangThai("da_thu");
        dsHoaDon.capNhat(idx, hd, true); 
        cout << "Da thu hoa don " << maHoaDon << ".\n";
        return true;
    }

    cout << "Loi: Khong tim thay hoa don " << maHoaDon << ".\n";
    return false;
}

bool danhDauQuaHan(DanhSachCustom<HoaDon>& dsHoaDon, const string& maHoaDon)
{
    // Tìm kiếm vị trí hóa đơn
    int idx = timHoaDonTheoMa(dsHoaDon, maHoaDon);
    if (idx != -1)
    {
        if (dsHoaDon.lay(idx).getTrangThai() == "da_thu")
        {
            cout << "Loi: Hoa don " << maHoaDon << " da duoc thu, khong the danh dau qua han!\n";
            return false;
        }
        HoaDon hd = dsHoaDon.lay(idx);
        hd.setTrangThai("qua_han");
        dsHoaDon.capNhat(idx, hd, true); 
        cout << "Da danh dau hoa don " << maHoaDon << " la qua han.\n";
        return true;
    }

    cout << "Loi: Khong tim thay hoa don " << maHoaDon << ".\n";
    return false;
}

// THỐNG KÊ
// TÌM SV QUÁ HẠN NỘP PHÍ (Quét theo phòng đang ở)
DanhSachCustom<SinhVien> layDSSVQuaHan(DanhSachCustom<SinhVien>& dsSV, DanhSachCustom<HoaDon>& dsHoaDon)
{
    DanhSachCustom<SinhVien> ketQua;
    for (int i = 0; i < dsSV.kichThuoc(); i++) {
        string maPhong = dsSV.lay(i).getMaPhong();
        if (maPhong.empty()) continue; 

        for (int j = 0; j < dsHoaDon.kichThuoc(); j++) {
            // ---> CHỈ KIỂM TRA TRẠNG THÁI "qua_han" (Bỏ "chua_thu") <---
            if (dsHoaDon.lay(j).getMaPhong() == maPhong && dsHoaDon.lay(j).getTrangThai() == "qua_han")
            {
                ketQua.them(dsSV.lay(i));
                break; 
            }
        }
    }
    return ketQua;
}

void thongKeLapDay(const DanhSachCustom<Phong>& dsPhong)
{
    cout << "\n+------------+----------+-----------+-----------+-----------+---------------+---------------+\n";
    cout << "| Loai Phong | Ma Phong | Suc Chua  | Dang Thue | Ti le (%) | Gioi Tinh     | Trang Thai    |\n";
    cout << "+------------+----------+-----------+-----------+-----------+---------------+---------------+\n";

    int cacLoaiPhong[] = {4, 6, 8};
    int tongKTXChua = 0, tongKTXDangO = 0, tongKTXSoPhong = 0;

    for (int i = 0; i < 3; i++) {
        int loai = cacLoaiPhong[i];
        int tongChuaLoai = 0, tongOLoai = 0, soPhongLoai = 0;
        
        // Quét kiểm tra xem có phòng loại này trong danh sách không
        bool hasRoom = false;
        for (int j = 0; j < dsPhong.kichThuoc(); j++) {
            if (dsPhong.lay(j).getLoaiPhong() == loai) { hasRoom = true; break; }
        }
        if (!hasRoom) continue; // Không có thì bỏ qua để bảng đỡ rối

        // In danh sách chi tiết các phòng thuộc Loại này
        for (int j = 0; j < dsPhong.kichThuoc(); j++) {
            Phong p = dsPhong.lay(j);
            if (p.getLoaiPhong() == loai) {
                soPhongLoai++;
                tongChuaLoai += p.getLoaiPhong();
                tongOLoai += p.getSoNguoiHienTai();
                
                // Tính phần trăm lấp đầy của từng phòng
                double tiLePhong = (p.getLoaiPhong() > 0) ? (p.getSoNguoiHienTai() * 100.0 / p.getLoaiPhong()) : 0.0;
                string gt = p.getGioiTinhPhong().empty() ? "Tu do" : p.getGioiTinhPhong();

                cout << "| " << setw(10) << left << ("Loai " + to_string(loai))
                     << " | " << setw(8) << left << p.getMaPhong() 
                     << " | " << setw(9) << right << p.getLoaiPhong()
                     << " | " << setw(9) << right << p.getSoNguoiHienTai()
                     << " | " << setw(8) << right << fixed << setprecision(1) << tiLePhong << "%"
                     << " | " << setw(13) << left << gt 
                     << " | " << setw(13) << left << p.getTrangThai() << " |\n";
            }
        }
        
        // In dòng TỔNG KẾT cho nhóm phòng này
        double tiLeLoai = (tongChuaLoai > 0) ? (tongOLoai * 100.0 / tongChuaLoai) : 0.0;
        cout << "+------------+----------+-----------+-----------+-----------+---------------+---------------+\n";
        cout << "| " << setw(10) << left << ("TONG L" + to_string(loai))
             << " | " << setw(8) << left << (to_string(soPhongLoai) + " p")
             << " | " << setw(9) << right << tongChuaLoai
             << " | " << setw(9) << right << tongOLoai
             << " | " << setw(8) << right << fixed << setprecision(1) << tiLeLoai << "%"
             << " | " << setw(13) << left << "-" 
             << " | " << setw(13) << left << "-" << " |\n";
        cout << "+------------+----------+-----------+-----------+-----------+---------------+---------------+\n";

        // Cộng dồn vào Grand Total của toàn KTX
        tongKTXChua += tongChuaLoai;
        tongKTXDangO += tongOLoai;
        tongKTXSoPhong += soPhongLoai;
    }

    // In dòng TỔNG TOÀN KÝ TÚC XÁ
    double tiLeTong = (tongKTXChua > 0) ? (tongKTXDangO * 100.0 / tongKTXChua) : 0.0;
    cout << "| " << setw(10) << left << "TONG KTX"
         << " | " << setw(8) << left << (to_string(tongKTXSoPhong) + " p")
         << " | " << setw(9) << right << tongKTXChua
         << " | " << setw(9) << right << tongKTXDangO
         << " | " << setw(8) << right << fixed << setprecision(1) << tiLeTong << "%"
         << " | " << setw(13) << left << "-" 
         << " | " << setw(13) << left << "-" << " |\n";
    cout << "+------------+----------+-----------+-----------+-----------+---------------+---------------+\n\n";
}