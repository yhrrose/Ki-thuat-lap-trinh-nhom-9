# Hệ thống Quản lý Ký Túc Xá

Một ứng dụng Console viết bằng C++ thuần (Standard C++), được thiết kế theo kiến trúc phân lớp chuẩn mực. Dự án quản lý sinh viên, phòng ở, hợp đồng và hóa đơn dịch vụ, sử dụng các cấu trúc dữ liệu và thuật toán tự xây dựng (không dùng STL) nhằm tối ưu hóa hiệu năng quản lý bộ nhớ. Đây là project cuối kì môn Kỹ thuật lập trình tại Đại học Bách khoa Hà Nội.

## Tính năng nổi bật

* **Quản lý danh mục:** Thêm, sửa, xóa, và tìm kiếm thông tin Sinh viên, Phòng ở với tính năng tự động chuẩn hóa chuỗi đầu vào.
* **Nghiệp vụ Thuê phòng:** Xử lý đăng ký phòng, tự động khóa giới tính phòng động, chuyển phòng và gia hạn hợp đồng. Hỗ trợ **Thuật toán xếp phòng tự động** dựa trên diện ưu tiên.
* **Quản lý Hóa đơn:** Lập hóa đơn tự động tính tiền điện nước theo bậc thang, ghi nhận tiền phạt, và đánh dấu công nợ quá hạn.
* **Báo cáo Thống kê:** Thống kê tỷ lệ lấp đầy KTX theo loại phòng và trích xuất danh sách sinh viên nợ phí.

## Kỹ thuật & Công nghệ sử dụng

* **Ngôn ngữ:** C++ (Standard)
* **Cấu trúc dữ liệu:** Xây dựng mảng động tùy chỉnh `DanhSachCustom<T>` bằng Template Class, quản lý bộ nhớ nghiêm ngặt (Rule of Three) chống Memory Leak.
* **Thuật toán:** Triển khai `QuickSort` kết hợp **Binary Search**, sử dụng `Lambda Function` để tối ưu hóa việc tìm kiếm đối tượng theo nhiều tiêu chí.
* **Thiết kế phần mềm:** Tách bạch luồng dữ liệu theo kiến trúc đa tầng (Entity, Business, Algorithm, IO).
* **Cross-platform:** Hỗ trợ kịch bản khởi chạy tự động trên cả Windows (Batch script) và macOS/Linux (Shell script).

## Cấu trúc thư mục

```text
KTX_Project/
├── data/                       # Chứa cơ sở dữ liệu (txt)
│   ├── hoadon.txt
│   ├── hopdong.txt
│   ├── phong.txt
│   └── sinhvien.txt
├── src/                        # Chứa toàn bộ mã nguồn
│   ├── algorithm/
│   │   └── ThuatToan.h         # Thuật toán QuickSort, BinarySearch
│   ├── business/
│   │   ├── NghiepVu.h
│   │   └── NghiepVu.cpp        # Xử lý logic nghiệp vụ KTX
│   ├── entity/
│   │   ├── HoaDon.h
│   │   ├── HopDong.h
│   │   ├── Phong.h
│   │   └── SinhVien.h          # Định nghĩa thực thể đối tượng
│   └── io/
│       ├── FileIO.h
│       └── FileIO.cpp          # Xử lý luồng đọc/ghi File
├── DanhSachCustom.h            # Cấu trúc dữ liệu mảng động tự viết
├── TienIch.h                   # Tiện ích chuẩn hóa chuỗi đầu vào
├── main.cpp                    # Giao diện Console & Menu chính
├── run.bat                     # Script chạy nhanh cho Windows
└── run.sh                      # Script chạy nhanh cho macOS/Linux

```

## Hướng dẫn cài đặt và chạy

Dự án có thể chạy trực tiếp từ Terminal hoặc thông qua file script tự động định tuyến `include`.

**Yêu cầu:** Trình biên dịch `g++` (GCC) đã được cài đặt trên máy.

### Cách 1: Sử dụng Script tự động

* **Trên Windows:** Click đúp chuột vào file `run.bat` hoặc gõ `./run.bat` trong Terminal.
* **Trên macOS / Linux:**
Mở Terminal và cấp quyền thực thi (chỉ cần làm lần đầu), sau đó chạy file:
```bash
chmod +x run.sh
./run.sh

```



### Cách 2: Biên dịch thủ công qua Terminal

Tại thư mục gốc của dự án, chạy lệnh sau để biên dịch:

```bash
g++ main.cpp src/business/NghiepVu.cpp src/io/FileIO.cpp -I. -Isrc/entity -Isrc/algorithm -Isrc/business -Isrc/io -o ktx

```

Sau khi biên dịch thành công, chạy ứng dụng:

* Windows: `ktx.exe`
* macOS/Linux: `./ktx`

*Lưu ý: Phải đảm bảo thư mục `data/` tồn tại ở gốc dự án để hệ thống có thể lưu trữ cơ sở dữ liệu dưới dạng text.*
## Tác giả & Phân công nhiệm vụ
Dự án được thực hiện bởi nhóm 3 thành viên, phối hợp phát triển theo trình tự tích hợp mã nguồn chặt chẽ. Khối lượng công việc được chia thành các module chuyên biệt:

* **Trần Thùy Linh - Phụ trách Core Data & File I/O**
  * **Xây dựng Core Data:** Xây dựng lõi cấu trúc dữ liệu mảng động tự mở rộng (`DanhSachCustom<T>`) và định nghĩa các lớp thực thể cốt lõi của hệ thống.
  * **Xử lý File I/O:** Cài đặt luồng đọc/ghi dữ liệu (File I/O) cho 4 file văn bản độc lập: `sinhvien.txt`, `phong.txt`, `hopdong.txt`, `hoadon.txt`.
  * **Nghiệp vụ cơ bản:** Xây dựng các nghiệp vụ quản lý danh mục cơ bản (Thêm, Xóa, Sửa) tích hợp bắt lỗi trùng lặp mã.

* **Bùi Thu Phương - Phụ trách Thuật toán & Logic Nghiệp vụ**
  * **Thiết kế thuật toán cốt lõi:** Cài đặt thuật toán Sắp xếp (Quick Sort) và Tìm kiếm nhị phân (Binary Search) trên cấu trúc mảng động tùy chỉnh.
  * **Nghiệp vụ Thuê phòng:** Cài đặt thuật toán Xếp phòng tự động (dựa trên diện ưu tiên), Đăng ký phòng thủ công, Chuyển phòng, Gia hạn hợp đồng, Hủy hợp đồng (trả phòng).
  * **Nghiệp vụ Hóa đơn & Thu phí:** Lập hóa đơn dịch vụ hàng tháng (áp dụng tính tiền điện/nước theo đơn giá lũy tiến), Ghi nhận tiền phạt cơ sở vật chất, Cập nhật trạng thái đã thu tiền và Đánh dấu hóa đơn quá hạn.
  * **Lọc dữ liệu & Thống kê:** Xây dựng thuật toán quét và trích xuất danh sách sinh viên nợ phí quá hạn, Tính toán tỷ lệ lấp đầy thực tế của từng loại phòng trong hệ thống.

* **Nguyễn Thị Diệu Linh - Phụ trách Giao diện Menu, Kiểm thử & Báo cáo**
  * **Giao diện Console:** Thiết kế hệ thống Menu điều hướng phân tầng (Menu chính -> Menu con Quản lý SV / Phòng / Hóa đơn / Thống kê).
  * **Bắt lỗi nhập liệu:** Lập trình cơ chế bảo vệ luồng nhập xuất (dùng `cin.clear()`, `cin.ignore()`) để chống crash hệ thống khi nhập sai kiểu dữ liệu (chữ vào số), và rào chắn logic.
  * **Trình bày Thống kê:** Tiếp nhận dữ liệu trả về từ khối nghiệp vụ, thiết kế giao diện bảng biểu thống kê tự động căn lề chuẩn xác (`setw`) và in tỷ lệ %.
  * **Đảm bảo chất lượng:** Xây dựng các tình huống kiểm thử (Test cases) để chạy thử nghiệm toàn bộ hệ thống. Chịu trách nhiệm tổng hợp, biên soạn tài liệu kỹ thuật, phụ lục code và trình bày báo cáo đồ án cuối kỳ.
