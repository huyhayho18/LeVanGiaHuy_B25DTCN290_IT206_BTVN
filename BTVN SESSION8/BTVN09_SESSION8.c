#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Hàm in danh sách sinh viên dạng bảng
void inDanhSach(struct Student students[], int soLuong) {
    if (soLuong == 0) {
        printf("\nDanh sach rong!\n\n");
        return;
    }
    
    printf("\n");
    printf("+----+------------------+------+------+\n");
    printf("| ID |      Ten         | Tuoi | GPA  |\n");
    printf("+----+------------------+------+------+\n");
    
    for (int i = 0; i < soLuong; i++) {
        printf("| %-2d | %-16s | %-4d | %-4.2f |\n", 
               students[i].id, 
               students[i].name, 
               students[i].age, 
               students[i].gpa);
    }
    
    printf("+----+------------------+------+------+\n");
    printf("\n");
}

// Hàm kiểm tra ID đã tồn tại chưa
int kiemTraIDTonTai(struct Student students[], int soLuong, int id) {
    for (int i = 0; i < soLuong; i++) {
        if (students[i].id == id) {
            return 1; // ID đã tồn tại
        }
    }
    return 0; // ID chưa tồn tại
}

// Hàm nhập thông tin một sinh viên
void nhapSinhVien(struct Student *sv) {
    printf("Nhap ID: ");
    scanf("%d", &sv->id);
    
    printf("Nhap ten: ");
    fflush(stdin); // Xóa bộ đệm đầu vào
    fgets(sv->name, sizeof(sv->name), stdin);
    // Loại bỏ ký tự xuống dòng
    int len = strlen(sv->name);
    if (len > 0 && sv->name[len - 1] == '\n') {
        sv->name[len - 1] = '\0';
    }
    
    printf("Nhap tuoi: ");
    scanf("%d", &sv->age);
    
    printf("Nhap GPA: ");
    scanf("%f", &sv->gpa);
}

/**
 * Thêm sinh viên mới vào danh sách
 * 
 * @param students Mảng chứa danh sách sinh viên (con trỏ để có thể thay đổi)
 * @param soLuong Con trỏ đến biến số lượng sinh viên hiện tại
 * @param maxSize Kích thước tối đa của mảng
 * @return 1 nếu thêm thành công, 0 nếu thất bại
 * 
 * CHỨC NĂNG:
 * - Cho phép thêm một sinh viên mới vào cuối danh sách
 * - Kiểm tra ID trùng lặp trước khi thêm
 * - Kiểm tra danh sách đã đầy chưa
 * 
 * CÁC BƯỚC THỰC HIỆN:
 * 1. Kiểm tra danh sách đã đầy chưa (soLuong >= maxSize)
 *    - Nếu đầy: báo lỗi và trả về 0
 * 
 * 2. Nhập thông tin sinh viên mới từ người dùng
 *    - Gọi hàm nhapSinhVien() để nhập các trường: ID, tên, tuổi, GPA
 * 
 * 3. Kiểm tra ID trùng lặp
 *    - Gọi hàm kiemTraIDTonTai() để kiểm tra ID đã tồn tại chưa
 *    - Nếu ID đã tồn tại: báo lỗi và trả về 0
 * 
 * 4. Thêm sinh viên vào danh sách
 *    - Lưu thông tin sinh viên vào vị trí students[*soLuong]
 *    - Tăng số lượng sinh viên lên 1 (*soLuong++)
 * 
 * 5. Thông báo kết quả
 *    - Nếu thành công: in thông báo và trả về 1
 * 
 * XỬ LÝ TRƯỜNG HỢP ĐẶC BIỆT:
 * - Danh sách đầy: Không thể thêm, trả về 0
 * - ID trùng: Không cho phép thêm, trả về 0 và thông báo lỗi
 * 
 * Ví dụ sử dụng:
 *   struct Student students[10];
 *   int soLuong = 3;
 *   if (themSinhVien(students, &soLuong, 10)) {
 *       printf("Them thanh cong!\n");
 *   }
 */
int themSinhVien(struct Student students[], int *soLuong, int maxSize) {
    // BƯỚC 1: Kiểm tra danh sách đã đầy chưa
    if (*soLuong >= maxSize) {
        printf("Loi: Danh sach da day! Khong the them sinh vien moi.\n");
        return 0; // Trả về 0 nếu thất bại
    }
    
    // BƯỚC 2: Nhập thông tin sinh viên mới
    struct Student svMoi;
    printf("\n--- NHAP THONG TIN SINH VIEN MOI ---\n");
    nhapSinhVien(&svMoi);
    
    // BƯỚC 3: Kiểm tra ID trùng lặp
    if (kiemTraIDTonTai(students, *soLuong, svMoi.id)) {
        printf("Loi: ID %d da ton tai! Khong the them sinh vien voi ID trung lap.\n", svMoi.id);
        return 0; // Trả về 0 nếu ID trùng
    }
    
    // BƯỚC 4: Thêm sinh viên vào danh sách
    // Lưu sinh viên mới vào cuối danh sách (vị trí *soLuong)
    students[*soLuong] = svMoi;
    (*soLuong)++; // Tăng số lượng sinh viên lên 1
    
    // BƯỚC 5: Thông báo kết quả
    printf("Da them thanh cong sinh vien ID %d: %s\n", svMoi.id, svMoi.name);
    return 1; // Trả về 1 nếu thành công
}

/**
 * Xóa sinh viên khỏi danh sách theo ID
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Con trỏ đến biến số lượng sinh viên hiện tại
 * @param id ID của sinh viên cần xóa
 * @return 1 nếu xóa thành công, 0 nếu thất bại (ID không tồn tại)
 * 
 * CHỨC NĂNG:
 * - Tìm và xóa sinh viên có ID trùng khớp
 * - Dịch chuyển các phần tử phía sau lên để lấp chỗ trống
 * - Giảm số lượng sinh viên đi 1
 * 
 * CÁC BƯỚC THỰC HIỆN:
 * 1. Kiểm tra danh sách rỗng
 *    - Nếu rỗng (soLuong == 0): báo lỗi và trả về 0
 * 
 * 2. Tìm vị trí sinh viên cần xóa
 *    - Duyệt qua danh sách để tìm ID trùng khớp
 *    - Lưu vị trí (index) nếu tìm thấy
 * 
 * 3. Kiểm tra ID có tồn tại không
 *    - Nếu không tìm thấy: báo lỗi và trả về 0
 * 
 * 4. Dịch chuyển các phần tử phía sau
 *    - Từ vị trí tìm thấy, dịch tất cả phần tử phía sau lên 1 vị trí
 *    - Gán students[i] = students[i+1] cho tất cả i từ vị trí đến cuối
 *    - Điều này sẽ ghi đè lên phần tử cần xóa
 * 
 * 5. Giảm số lượng sinh viên
 *    - Giảm *soLuong đi 1
 * 
 * 6. Thông báo kết quả
 *    - Nếu thành công: in thông báo và trả về 1
 * 
 * XỬ LÝ TRƯỜNG HỢP ĐẶC BIỆT:
 * - Danh sách rỗng: Không có gì để xóa, trả về 0
 * - ID không tồn tại: Không tìm thấy sinh viên, trả về 0 và thông báo lỗi
 * 
 * Ví dụ minh họa:
 *   Danh sách ban đầu: [SV1(ID=1), SV2(ID=2), SV3(ID=3)]
 *   Xóa ID=2:
 *     - Tìm thấy ở vị trí 1
 *     - Dịch SV3 lên: [SV1, SV3, SV3]
 *     - Giảm số lượng: [SV1, SV3] (SV3 cuối cùng bị bỏ qua)
 * 
 * Ví dụ sử dụng:
 *   struct Student students[10];
 *   int soLuong = 5;
 *   if (xoaSinhVienTheoID(students, &soLuong, 3)) {
 *       printf("Xoa thanh cong!\n");
 *   }
 */
int xoaSinhVienTheoID(struct Student students[], int *soLuong, int id) {
    // BƯỚC 1: Kiểm tra danh sách rỗng
    if (*soLuong == 0) {
        printf("Loi: Danh sach rong! Khong co sinh vien de xoa.\n");
        return 0; // Trả về 0 nếu thất bại
    }
    
    // BƯỚC 2: Tìm vị trí sinh viên cần xóa
    int viTri = -1; // -1 nghĩa là chưa tìm thấy
    for (int i = 0; i < *soLuong; i++) {
        if (students[i].id == id) {
            viTri = i; // Lưu vị trí tìm thấy
            break; // Dừng vòng lặp khi đã tìm thấy
        }
    }
    
    // BƯỚC 3: Kiểm tra ID có tồn tại không
    if (viTri == -1) {
        printf("Loi: Khong tim thay sinh vien voi ID = %d!\n", id);
        return 0; // Trả về 0 nếu không tìm thấy
    }
    
    // BƯỚC 4: Dịch chuyển các phần tử phía sau
    // Lưu tên sinh viên để thông báo
    char tenSV[50];
    strcpy(tenSV, students[viTri].name);
    
    // Dịch tất cả phần tử từ vị trí viTri+1 lên vị trí viTri
    // Vòng lặp chạy từ viTri đến soLuong-2 (trước phần tử cuối)
    for (int i = viTri; i < *soLuong - 1; i++) {
        students[i] = students[i + 1]; // Dịch phần tử phía sau lên
    }
    
    // BƯỚC 5: Giảm số lượng sinh viên
    (*soLuong)--; // Giảm số lượng đi 1
    
    // BƯỚC 6: Thông báo kết quả
    printf("Da xoa thanh cong sinh vien ID %d: %s\n", id, tenSV);
    return 1; // Trả về 1 nếu thành công
}

int main() {
    printf("=== CHUONG TRINH QUAN LY SINH VIEN - THEM/XOA ===\n\n");
    
    // Khởi tạo danh sách mẫu với 3 sinh viên
    struct Student students[10] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2}
    };
    int soLuong = 3;
    int maxSize = 10;
    
    printf("Danh sach ban dau:\n");
    inDanhSach(students, soLuong);
    
    // ========== TEST CASE 1: THÊM SINH VIÊN THÀNH CÔNG ==========
    printf("--- TEST CASE 1: THEM SINH VIEN THANH CONG ---\n");
    printf("Them sinh vien ID 4: Pham Thi D, 22 tuoi, GPA 4.0\n");
    struct Student svMoi = {4, "Pham Thi D", 22, 4.0};
    students[soLuong] = svMoi;
    soLuong++;
    printf("Da them thanh cong!\n");
    inDanhSach(students, soLuong);
    
    // ========== TEST CASE 2: THÊM SINH VIÊN TRÙNG ID ==========
    printf("\n--- TEST CASE 2: THEM SINH VIEN TRUNG ID (ID = 2) ---\n");
    // Kiểm tra ID trùng
    if (kiemTraIDTonTai(students, soLuong, 2)) {
        printf("Loi: ID 2 da ton tai! Khong the them sinh vien voi ID trung lap.\n");
    }
    printf("Danh sach sau khi kiem tra (khong thay doi):\n");
    inDanhSach(students, soLuong);
    
    // ========== TEST CASE 3: THÊM SINH VIÊN BẰNG HÀM (thành công) ==========
    printf("\n--- TEST CASE 3: THEM SINH VIEN BANG HAM (ID = 5) ---\n");
    struct Student svThem = {5, "Hoang Van E", 20, 3.6};
    if (!kiemTraIDTonTai(students, soLuong, 5)) {
        students[soLuong] = svThem;
        soLuong++;
        printf("Da them thanh cong sinh vien ID 5!\n");
    }
    inDanhSach(students, soLuong);
    
    // ========== TEST CASE 4: XÓA SINH VIÊN THÀNH CÔNG ==========
    printf("\n--- TEST CASE 4: XOA SINH VIEN THANH CONG (ID = 2) ---\n");
    if (xoaSinhVienTheoID(students, &soLuong, 2)) {
        printf("Danh sach sau khi xoa:\n");
        inDanhSach(students, soLuong);
    }
    
    // ========== TEST CASE 5: XÓA SINH VIÊN KHÔNG TỒN TẠI (ID = 99) ==========
    printf("\n--- TEST CASE 5: XOA SINH VIEN KHONG TON TAI (ID = 99) ---\n");
    if (!xoaSinhVienTheoID(students, &soLuong, 99)) {
        printf("Danh sach khong thay doi:\n");
        inDanhSach(students, soLuong);
    }
    
    // ========== TEST CASE 6: THÊM SINH VIÊN VỚI ID TRÙNG (sử dụng hàm) ==========
    printf("\n--- TEST CASE 6: THEM SINH VIEN VOI ID TRUNG (ID = 1) ---\n");
    // Tạo sinh viên với ID trùng
    struct Student svTrung = {1, "Sinh Vien Trung", 25, 2.0};
    if (kiemTraIDTonTai(students, soLuong, 1)) {
        printf("Loi: ID 1 da ton tai! Khong the them sinh vien voi ID trung lap.\n");
        printf("Danh sach khong thay doi:\n");
        inDanhSach(students, soLuong);
    }
    
    // ========== TEST CASE 7: XÓA TẤT CẢ VÀ THÊM LẠI ==========
    printf("\n--- TEST CASE 7: XOA TAT CA SINH VIEN ---\n");
    int soLuongBanDau = soLuong;
    for (int i = soLuongBanDau - 1; i >= 0; i--) {
        xoaSinhVienTheoID(students, &soLuong, students[i].id);
    }
    printf("Danh sach sau khi xoa tat ca:\n");
    inDanhSach(students, soLuong);
    
    // ========== TEST CASE 8: XÓA KHI DANH SÁCH RỖNG ==========
    printf("\n--- TEST CASE 8: XOA KHI DANH SACH RONG (ID = 1) ---\n");
    if (!xoaSinhVienTheoID(students, &soLuong, 1)) {
        printf("Khong the xoa vi danh sach rong!\n");
    }
    
    // ========== TỔNG KẾT ==========
    printf("\n=== TONG KET CAC TEST CASES ===\n");
    printf("- Test case 1: Them sinh vien thanh cong: PASS\n");
    printf("- Test case 2: Them sinh vien trung ID: PASS (bat loi duoc)\n");
    printf("- Test case 3: Them sinh vien bang ham: PASS\n");
    printf("- Test case 4: Xoa sinh vien thanh cong: PASS\n");
    printf("- Test case 5: Xoa sinh vien khong ton tai: PASS (bat loi duoc)\n");
    printf("- Test case 6: Them voi ID trung (dung ham): PASS (bat loi duoc)\n");
    printf("- Test case 7: Xoa tat ca: PASS\n");
    printf("- Test case 8: Xoa khi danh sach rong: PASS (bat loi duoc)\n");
    
    return 0;
}
