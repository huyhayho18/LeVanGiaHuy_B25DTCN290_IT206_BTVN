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
 * Tạo file dữ liệu cho một lớp học
 * 
 * @param tenFile Tên file cần tạo (ví dụ: "classA.txt")
 * @param students Mảng chứa danh sách sinh viên của lớp
 * @param soLuong Số lượng sinh viên trong lớp
 * 
 * BƯỚC 1: Mở file để ghi
 * - Sử dụng fopen với mode "w" để tạo file mới hoặc ghi đè file cũ
 * - Kiểm tra xem file có mở thành công không (file != NULL)
 * 
 * BƯỚC 2: Ghi tiêu đề bảng vào file
 * - Ghi các dòng tiêu đề và đường viền để định dạng bảng
 * - Format giống như khi in ra màn hình
 * 
 * BƯỚC 3: Ghi dữ liệu từng sinh viên
 * - Duyệt qua mảng students
 * - Ghi từng dòng dữ liệu với format chuẩn
 * - Sử dụng fprintf để ghi có định dạng
 * 
 * BƯỚC 4: Ghi dòng kết thúc bảng
 * - Đóng khung bảng bằng đường viền
 * 
 * BƯỚC 5: Đóng file
 * - Sử dụng fclose để đóng file và giải phóng tài nguyên
 * - Quan trọng: luôn phải đóng file sau khi ghi xong
 */
void taoFileLop(char tenFile[], struct Student students[], int soLuong) {
    // BƯỚC 1: Mở file để ghi
    // Mode "w" sẽ tạo file mới hoặc ghi đè file cũ nếu đã tồn tại
    FILE *file = fopen(tenFile, "w");
    
    // Kiểm tra xem file có mở thành công không
    if (file == NULL) {
        printf("Loi: Khong the tao file %s!\n", tenFile);
        return;
    }
    
    // BƯỚC 2: Ghi tiêu đề bảng vào file
    // Ghi đường viền trên của bảng
    fprintf(file, "+----+------------------+------+------+\n");
    // Ghi dòng tiêu đề các cột
    fprintf(file, "| ID |      Ten         | Tuoi | GPA  |\n");
    // Ghi đường viền dưới tiêu đề
    fprintf(file, "+----+------------------+------+------+\n");
    
    // BƯỚC 3: Ghi dữ liệu từng sinh viên
    // Duyệt qua tất cả sinh viên trong mảng
    for (int i = 0; i < soLuong; i++) {
        // Ghi từng dòng dữ liệu với format chuẩn
        // %-2d: ID căn trái, chiếm 2 ký tự
        // %-16s: Tên căn trái, chiếm 16 ký tự
        // %-4d: Tuổi căn trái, chiếm 4 ký tự
        // %-4.2f: GPA căn trái, 4 ký tự tổng, 2 chữ số thập phân
        fprintf(file, "| %-2d | %-16s | %-4d | %-4.2f |\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }
    
    // BƯỚC 4: Ghi dòng kết thúc bảng
    // Đóng khung bảng bằng đường viền dưới
    fprintf(file, "+----+------------------+------+------+\n");
    
    // BƯỚC 5: Đóng file
    // Quan trọng: luôn phải đóng file sau khi ghi xong
    // Điều này đảm bảo dữ liệu được lưu vào đĩa và giải phóng tài nguyên
    fclose(file);
    
    printf("Da tao thanh cong file %s voi %d sinh vien!\n", tenFile, soLuong);
}

/**
 * Đọc danh sách sinh viên từ file
 * 
 * @param tenFile Tên file cần đọc (ví dụ: "classA.txt")
 * @param students Mảng để lưu danh sách sinh viên đọc được
 * @return Số lượng sinh viên đọc được từ file
 * 
 * BƯỚC 1: Mở file để đọc
 * - Sử dụng fopen với mode "r" để đọc file
 * - Kiểm tra xem file có tồn tại và mở thành công không
 * 
 * BƯỚC 2: Đọc và bỏ qua dòng tiêu đề
 * - Đọc và bỏ qua 3 dòng đầu (2 đường viền + 1 tiêu đề)
 * - Sử dụng fgets để đọc từng dòng
 * 
 * BƯỚC 3: Đọc dữ liệu từng dòng
 * - Đọc từng dòng cho đến khi hết file hoặc đủ số lượng tối đa
 * - Bỏ qua các dòng đường viền (bắt đầu bằng '+')
 * - Parse dòng dữ liệu có dạng: | ID | Name | Age | GPA |
 * 
 * BƯỚC 4: Parse dữ liệu từ chuỗi
 * - Sử dụng sscanf để tách các trường dữ liệu
 * - Loại bỏ khoảng trắng thừa ở tên
 * - Lưu vào mảng students
 * 
 * BƯỚC 5: Đóng file và trả về kết quả
 * - Đóng file sau khi đọc xong
 * - Trả về số lượng sinh viên đọc được
 */
int docFileLop(char tenFile[], struct Student students[]) {
    // BƯỚC 1: Mở file để đọc
    // Mode "r" chỉ cho phép đọc file, không thể ghi
    FILE *file = fopen(tenFile, "r");
    
    // Kiểm tra xem file có tồn tại và mở thành công không
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de doc!\n", tenFile);
        printf("Vui long kiem tra ten file hoac duong dan.\n");
        return 0; // Trả về 0 nếu không đọc được
    }
    
    // BƯỚC 2: Đọc và bỏ qua dòng tiêu đề
    char line[200]; // Buffer để đọc từng dòng
    int count = 0; // Đếm số sinh viên đã đọc
    int skipHeader = 3; // Bỏ qua 3 dòng đầu (2 đường viền + 1 tiêu đề)
    
    // Đọc và bỏ qua các dòng tiêu đề
    while (skipHeader > 0 && fgets(line, sizeof(line), file) != NULL) {
        skipHeader--;
    }
    
    // BƯỚC 3: Đọc dữ liệu từng dòng
    // Đọc từng dòng cho đến khi hết file hoặc đủ 10 sinh viên (giới hạn mảng)
    while (fgets(line, sizeof(line), file) != NULL && count < 10) {
        // Loại bỏ ký tự xuống dòng ở cuối dòng
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        // Bỏ qua dòng đường viền (bắt đầu bằng '+')
        if (line[0] == '+') {
            continue; // Chuyển sang dòng tiếp theo
        }
        
        // BƯỚC 4: Parse dữ liệu từ chuỗi
        // Kiểm tra xem dòng có phải là dòng dữ liệu không (bắt đầu bằng '|')
        if (line[0] == '|') {
            int id, age;
            float gpa;
            char name[50];
            
            // Sử dụng sscanf để parse dữ liệu
            // Format: | ID | Name | Age | GPA |
            // %[^|] đọc tất cả ký tự cho đến khi gặp dấu |
            if (sscanf(line, "| %d | %[^|] | %d | %f |", &id, name, &age, &gpa) == 4) {
                // Loại bỏ khoảng trắng thừa ở đầu và cuối tên
                // Tìm vị trí ký tự đầu tiên không phải khoảng trắng
                char *start = name;
                while (*start == ' ') start++;
                
                // Loại bỏ khoảng trắng ở cuối
                char *end = name + strlen(name) - 1;
                while (end > name && *end == ' ') {
                    *end = '\0';
                    end--;
                }
                
                // Lưu dữ liệu vào mảng students
                students[count].id = id;
                strcpy(students[count].name, start); // Copy tên đã được trim
                students[count].age = age;
                students[count].gpa = gpa;
                count++; // Tăng số lượng đã đọc
            }
        }
    }
    
    // BƯỚC 5: Đóng file và trả về kết quả
    // Luôn phải đóng file sau khi đọc xong
    fclose(file);
    
    // Trả về số lượng sinh viên đọc được
    return count;
}

// Hàm nhập tên file từ người dùng
void nhapTenFile(char tenFile[]) {
    printf("Nhap ten file can doc (vi du: classA.txt, classB.txt, classC.txt): ");
    // Đọc tên file, giới hạn độ dài 50 ký tự
    scanf("%s", tenFile);
}

int main() {
    printf("=== CHUONG TRINH QUAN LY NHIEU LOP HOC ===\n\n");
    
    // ========== BƯỚC 1: TẠO DỮ LIỆU GIẢ LẬP CHO 3 LỚP ==========
    printf("--- BUOC 1: TAO DU LIEU GIA LAP CHO 3 LOP ---\n\n");
    
    // Tạo dữ liệu cho lớp A
    struct Student classA[4] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2},
        {4, "Pham Thi D", 22, 4.0}
    };
    printf("Tao du lieu cho Lop A:\n");
    inDanhSach(classA, 4);
    taoFileLop("classA.txt", classA, 4);
    
    // Tạo dữ liệu cho lớp B
    struct Student classB[5] = {
        {1, "Hoang Van E", 20, 3.6},
        {2, "Vu Thi F", 21, 3.4},
        {3, "Dao Van G", 19, 3.9},
        {4, "Bui Thi H", 23, 3.7},
        {5, "Dang Van I", 20, 3.3}
    };
    printf("\nTao du lieu cho Lop B:\n");
    inDanhSach(classB, 5);
    taoFileLop("classB.txt", classB, 5);
    
    // Tạo dữ liệu cho lớp C
    struct Student classC[3] = {
        {1, "Ly Thi K", 21, 3.8},
        {2, "Ngo Van L", 20, 3.5},
        {3, "Do Thi M", 22, 4.0}
    };
    printf("\nTao du lieu cho Lop C:\n");
    inDanhSach(classC, 3);
    taoFileLop("classC.txt", classC, 3);
    
    // ========== BƯỚC 2: CHO PHÉP NGƯỜI DÙNG NHẬP TÊN FILE ĐỂ ĐỌC ==========
    printf("\n\n--- BUOC 2: DOC DU LIEU TU FILE ---\n\n");
    
    char tenFile[50]; // Mảng lưu tên file
    struct Student students[10]; // Mảng để lưu dữ liệu đọc được
    int soLuong;
    
    // Nhập tên file từ người dùng
    nhapTenFile(tenFile);
    
    // Đọc dữ liệu từ file
    printf("\nDang doc du lieu tu file %s...\n", tenFile);
    soLuong = docFileLop(tenFile, students);
    
    // Kiểm tra kết quả đọc
    if (soLuong > 0) {
        printf("\nDa doc thanh cong %d sinh vien tu file %s\n", soLuong, tenFile);
        printf("\n=== DANH SACH SINH VIEN TRONG FILE ===\n");
        inDanhSach(students, soLuong);
    } else {
        printf("\nKhong doc duoc du lieu tu file %s\n", tenFile);
        printf("Vui long kiem tra lai ten file!\n");
    }
    
    // ========== BƯỚC 3: THỬ ĐỌC TẤT CẢ CÁC FILE ĐỂ KIỂM TRA ==========
    printf("\n--- BUOC 3: KIEM TRA DOC TAT CA CAC FILE ---\n\n");
    
    char danhSachFile[3][20] = {"classA.txt", "classB.txt", "classC.txt"};
    
    for (int i = 0; i < 3; i++) {
        printf("Doc file %s:\n", danhSachFile[i]);
        soLuong = docFileLop(danhSachFile[i], students);
        
        if (soLuong > 0) {
            printf("So luong sinh vien: %d\n", soLuong);
            inDanhSach(students, soLuong);
        }
        printf("\n");
    }
    
    return 0;
}
