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

// Hàm in thông tin một sinh viên
void inSinhVien(struct Student sv) {
    printf("\n");
    printf("+----+------------------+------+------+\n");
    printf("| ID |      Ten         | Tuoi | GPA  |\n");
    printf("+----+------------------+------+------+\n");
    printf("| %-2d | %-16s | %-4d | %-4.2f |\n", 
           sv.id, sv.name, sv.age, sv.gpa);
    printf("+----+------------------+------+------+\n");
    printf("\n");
}

/**
 * Tìm kiếm sinh viên theo ID trong mảng danh sách sinh viên
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Số lượng sinh viên trong mảng
 * @param id ID của sinh viên cần tìm
 * @return Con trỏ đến sinh viên tìm thấy, NULL nếu không tìm thấy
 * 
 * Hàm này thực hiện tìm kiếm tuyến tính (linear search) trong mảng students
 * để tìm sinh viên có ID trùng khớp với id truyền vào. Nếu tìm thấy, trả về
 * con trỏ đến phần tử đó trong mảng. Nếu không tìm thấy, trả về NULL.
 * 
 * Ví dụ sử dụng:
 *   struct Student *sv = timSinhVienTheoID(students, 5, 3);
 *   if (sv != NULL) {
 *       printf("Tim thay: %s\n", sv->name);
 *   }
 */
struct Student* timSinhVienTheoID(struct Student students[], int soLuong, int id) {
    for (int i = 0; i < soLuong; i++) {
        if (students[i].id == id) {
            return &students[i]; // Trả về địa chỉ của sinh viên tìm thấy
        }
    }
    return NULL; // Không tìm thấy
}

// Hàm nhập ID cần tìm
int nhapID() {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    return id;
}

// Hàm hiển thị kết quả tìm kiếm
void hienThiKetQuaTimKiem(struct Student students[], int soLuong, int id) {
    struct Student *ketQua = timSinhVienTheoID(students, soLuong, id);
    
    if (ketQua != NULL) {
        printf("\n>>> TIM THAY SINH VIEN <<<\n");
        inSinhVien(*ketQua);
    } else {
        printf("\n>>> KHONG TIM THAY SINH VIEN VOI ID = %d <<<\n\n", id);
    }
}

int main() {
    // Khởi tạo dữ liệu mẫu để test
    struct Student students[5] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2},
        {4, "Pham Thi D", 22, 3.9},
        {5, "Hoang Van E", 20, 3.4}
    };
    int soLuong = 5;
    
    printf("=== CHUONG TRINH TRA CUU SINH VIEN THEO ID ===\n");
    printf("\nDanh sach sinh vien hien co:\n");
    printf("ID: 1, 2, 3, 4, 5\n\n");
    
    // Test case 1: ID tồn tại
    printf("--- TEST CASE 1: ID TON TAI (ID = 3) ---\n");
    hienThiKetQuaTimKiem(students, soLuong, 3);
    
    // Test case 2: ID không tồn tại
    printf("--- TEST CASE 2: ID KHONG TON TAI (ID = 10) ---\n");
    hienThiKetQuaTimKiem(students, soLuong, 10);
    
    // Test case 3: ID âm
    printf("--- TEST CASE 3: ID AM (ID = -1) ---\n");
    hienThiKetQuaTimKiem(students, soLuong, -1);
    
    // Cho phép người dùng nhập ID để tìm kiếm
    printf("\n=== NHAP ID DE TIM KIEM ===\n");
    int idTimKiem = nhapID();
    hienThiKetQuaTimKiem(students, soLuong, idTimKiem);
    
    return 0;
}
