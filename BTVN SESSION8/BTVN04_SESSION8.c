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

// Hàm đọc danh sách sinh viên từ file
int loadFromFile(struct Student students[]) {
    FILE *file = fopen("students.txt", "r");
    
    if (file == NULL) {
        printf("Loi: Khong the mo file students.txt de doc!\n");
        return 0;
    }
    
    char line[200];
    int count = 0;
    int skipHeader = 1; // Bỏ qua 3 dòng đầu (đường viền, tiêu đề, đường viền)
    
    // Đọc từng dòng trong file
    while (fgets(line, sizeof(line), file) != NULL && count < 5) {
        // Loại bỏ ký tự xuống dòng
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        // Bỏ qua dòng tiêu đề và đường viền
        if (skipHeader > 0) {
            skipHeader--;
            continue;
        }
        
        // Bỏ qua dòng đường viền (bắt đầu bằng +)
        if (line[0] == '+') {
            continue;
        }
        
        // Parse dòng dữ liệu có dạng: | ID | Name | Age | GPA |
        if (line[0] == '|') {
            int id, age;
            float gpa;
            char name[50];
            
            // Sử dụng sscanf để parse dữ liệu
            // Format: | %d | %[^|] | %d | %f |
            // %[^|] đọc tất cả ký tự cho đến khi gặp dấu |
            if (sscanf(line, "| %d | %[^|] | %d | %f |", &id, name, &age, &gpa) == 4) {
                // Loại bỏ khoảng trắng thừa ở đầu và cuối tên
                // Trim leading spaces
                char *start = name;
                while (*start == ' ') start++;
                
                // Trim trailing spaces
                char *end = name + strlen(name) - 1;
                while (end > name && *end == ' ') {
                    *end = '\0';
                    end--;
                }
                
                // Lưu vào mảng
                students[count].id = id;
                strcpy(students[count].name, start);
                students[count].age = age;
                students[count].gpa = gpa;
                count++;
            }
        }
    }
    
    fclose(file);
    return count;
}

int main() {
    struct Student students[5]; // Mảng tối đa 5 sinh viên
    int soLuong;
    
    printf("=== DOC DANH SACH SINH VIEN TU FILE ===\n");
    
    // Đọc danh sách từ file
    soLuong = loadFromFile(students);
    
    if (soLuong == 0) {
        printf("Khong co du lieu trong file hoac file khong ton tai!\n");
        return 1;
    }
    
    printf("Da doc thanh cong %d sinh vien tu file students.txt\n", soLuong);
    
    // In danh sách sinh viên
    printf("\n=== DANH SACH SINH VIEN ===\n");
    inDanhSach(students, soLuong);
    
    return 0;
}
