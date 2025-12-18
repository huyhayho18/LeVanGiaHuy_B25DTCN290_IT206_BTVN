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

/**
 * Tính GPA trung bình của danh sách sinh viên
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Số lượng sinh viên trong mảng
 * @return GPA trung bình (float), hoặc -1.0 nếu danh sách rỗng
 * 
 * Hàm này tính toán điểm GPA trung bình bằng cách:
 * 1. Kiểm tra nếu danh sách rỗng (soLuong <= 0), trả về -1.0
 * 2. Tính tổng GPA của tất cả sinh viên
 * 3. Chia tổng cho số lượng sinh viên để lấy giá trị trung bình
 * 
 * Ví dụ sử dụng:
 *   float gpaTB = tinhGPATrungBinh(students, 5);
 *   if (gpaTB >= 0) {
 *       printf("GPA trung binh: %.2f\n", gpaTB);
 *   } else {
 *       printf("Danh sach rong!\n");
 *   }
 */
float tinhGPATrungBinh(struct Student students[], int soLuong) {
    // Xử lý trường hợp danh sách rỗng
    if (soLuong <= 0) {
        return -1.0; // Trả về -1.0 để đánh dấu danh sách rỗng
    }
    
    float tongGPA = 0.0;
    
    // Tính tổng GPA của tất cả sinh viên
    for (int i = 0; i < soLuong; i++) {
        tongGPA += students[i].gpa;
    }
    
    // Tính và trả về GPA trung bình
    return tongGPA / soLuong;
}

// Hàm hiển thị kết quả GPA trung bình
void hienThiGPATrungBinh(struct Student students[], int soLuong) {
    float gpaTB = tinhGPATrungBinh(students, soLuong);
    
    if (gpaTB < 0) {
        printf("Khong the tinh GPA trung binh: Danh sach rong!\n");
    } else {
        printf("GPA trung binh cua %d sinh vien: %.2f\n", soLuong, gpaTB);
    }
}

int main() {
    printf("=== CHUONG TRINH TINH GPA TRUNG BINH ===\n");
    
    // Khởi tạo 10 sinh viên giả lập với GPA khác nhau
    struct Student students[10] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2},
        {4, "Pham Thi D", 22, 4.0},
        {5, "Hoang Van E", 20, 2.9},
        {6, "Vu Thi F", 21, 3.7},
        {7, "Dao Van G", 19, 3.6},
        {8, "Bui Thi H", 23, 3.9},
        {9, "Dang Van I", 20, 2.5},
        {10, "Ly Thi K", 21, 3.4}
    };
    int soLuong = 10;
    
    // Test case 1: Danh sách có dữ liệu (10 sinh viên)
    printf("\n--- TEST CASE 1: DANH SACH CO DU LIEU (10 SINH VIEN) ---\n");
    printf("Danh sach sinh vien:\n");
    inDanhSach(students, soLuong);
    hienThiGPATrungBinh(students, soLuong);
    
    // Test case 2: Danh sách rỗng
    printf("\n--- TEST CASE 2: DANH SACH RONG (soLuong = 0) ---\n");
    struct Student danhSachRong[1]; // Mảng rỗng
    inDanhSach(danhSachRong, 0);
    hienThiGPATrungBinh(danhSachRong, 0);
    
    // Test case 3: Danh sách với 1 sinh viên
    printf("\n--- TEST CASE 3: DANH SACH 1 SINH VIEN ---\n");
    struct Student motSV[1] = {{1, "Nguyen Van A", 20, 3.5}};
    inDanhSach(motSV, 1);
    hienThiGPATrungBinh(motSV, 1);
    
    // Test case 4: Danh sách với 5 sinh viên đầu tiên
    printf("\n--- TEST CASE 4: 5 SINH VIEN DAU TIEN ---\n");
    inDanhSach(students, 5);
    hienThiGPATrungBinh(students, 5);
    
    // Tính và hiển thị chi tiết GPA từng sinh viên
    printf("\n--- CHI TIET GPA TUNG SINH VIEN ---\n");
    float tong = 0.0;
    for (int i = 0; i < soLuong; i++) {
        printf("Sinh vien %d (%s): GPA = %.2f\n", 
               students[i].id, students[i].name, students[i].gpa);
        tong += students[i].gpa;
    }
    printf("\nTong GPA: %.2f\n", tong);
    printf("GPA trung binh: %.2f\n", tong / soLuong);
    
    return 0;
}
