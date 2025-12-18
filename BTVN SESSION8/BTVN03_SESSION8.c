#include <stdio.h>
#include <string.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Hàm nhập thông tin một sinh viên
void nhapSinhVien(struct Student *sv, int id) {
    sv->id = id;
    printf("\nNhap thong tin sinh vien thu %d:\n", id);
    
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

// Hàm in danh sách sinh viên dạng bảng
void inDanhSach(struct Student students[], int soLuong) {
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

// Hàm lưu danh sách sinh viên vào file
void saveToFile(struct Student students[], int soLuong) {
    FILE *file = fopen("students.txt", "w");
    
    if (file == NULL) {
        printf("Loi: Khong the mo file students.txt de ghi!\n");
        return;
    }
    
    // Ghi tiêu đề vào file
    fprintf(file, "+----+------------------+------+------+\n");
    fprintf(file, "| ID |      Ten         | Tuoi | GPA  |\n");
    fprintf(file, "+----+------------------+------+------+\n");
    
    // Ghi thông tin từng sinh viên
    for (int i = 0; i < soLuong; i++) {
        fprintf(file, "| %-2d | %-16s | %-4d | %-4.2f |\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }
    
    // Ghi dòng kết thúc
    fprintf(file, "+----+------------------+------+------+\n");
    
    fclose(file);
    printf("Da luu danh sach sinh vien vao file students.txt thanh cong!\n");
}

int main() {
    struct Student students[5]; // Mảng tối đa 5 sinh viên
    int soLuong;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    printf("Nhap so luong sinh vien (toi da 5): ");
    scanf("%d", &soLuong);
    
    // Kiểm tra số lượng hợp lệ
    if (soLuong < 1 || soLuong > 5) {
        printf("So luong khong hop le! Chi cho phep tu 1 den 5 sinh vien.\n");
        return 1;
    }
    
    // Nhập thông tin từng sinh viên
    for (int i = 0; i < soLuong; i++) {
        nhapSinhVien(&students[i], i + 1);
    }
    
    // In danh sách sinh viên
    printf("\n=== DANH SACH SINH VIEN ===\n");
    inDanhSach(students, soLuong);
    
    // Lưu danh sách vào file
    saveToFile(students, soLuong);
    
    return 0;
}
