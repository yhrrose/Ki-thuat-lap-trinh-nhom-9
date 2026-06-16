#ifndef TIENICH_H
#define TIENICH_H

#include <string>

// Cắt khoảng trắng 2 đầu chuỗi
inline std::string trim(const std::string& s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Chuyển ký tự ASCII về chữ thường 
inline std::string toLowerASCII(std::string s)
{
    for (char& c : s)
        if (c >= 'A' && c <= 'Z') c += 32;
    return s;
}

// Chuẩn hóa nhập giới tính về "Nam"/"Nữ"
// Nam or nam or NAM.. về "Nam"...
inline std::string chuanHoaGioiTinh(const std::string& gt)
{
    std::string s = toLowerASCII(trim(gt));
    if (s == "nam") return "Nam";
    if (s == "nu")  return "Nu";
    return trim(gt); // giữ nguyên nếu không khớp
}

// Chuẩn hóa nhập diện ưu tiên
//   "chinh sach"or "chinh_sach" or "CHINH_SACH" or "cs" về "chinh_sach"
//   "uu tien" or "uu_tien" or "UU_TIEN" or "ut" về "uu_tien"
//   còn lại về "binh_thuong"
inline std::string chuanHoaDienUuTien(const std::string& dien)
{
    std::string s = toLowerASCII(trim(dien));

    // Thay dấu cách và dấu gạch ngang thành gạch dưới để so sánh thống nhất
    for (char& c : s)
        if (c == ' ' || c == '-') c = '_';

    if (s == "chinh_sach" || s == "cs") return "chinh_sach";
    if (s == "uu_tien"    || s == "ut") return "uu_tien";
    return "binh_thuong";
}

#endif 
