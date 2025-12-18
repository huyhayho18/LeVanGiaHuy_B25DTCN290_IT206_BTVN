#include <stdio.h>
#include <string.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

int main() {
    // Khởi tạo mảng 3 sinh viên mẫu
    struct Student students[3] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2}
    };
    
    // In tiêu đề bảng
    printf("\n");
    printf("+----+------------------+------+------+\n");
    printf("| ID |      Ten         | Tuoi | GPA  |\n");
    printf("+----+------------------+------+------+\n");
    
    // In thông tin từng sinh viên
    for (int i = 0; i < 3; i++) {
        printf("| %-2d | %-16s | %-4d | %-4.2f |\n", 
               students[i].id, 
               students[i].name, 
               students[i].age, 
               students[i].gpa);
    }
    
    // In dòng kết thúc bảng
    printf("+----+------------------+------+------+\n");
    printf("\n");
    
    return 0;
}
