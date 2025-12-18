#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define FILE_NAME "students.txt"

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// ========== CÁC HÀM TIỆN ÍCH ==========

/**
 * In menu chính của chương trình
 */
void inMenu() {
    printf("\n");
    printf("===== Student Manager =====\n");
    printf("1. Nhap sinh vien\n");
    printf("2. In danh sach\n");
    printf("3. Ghi file\n");
    printf("4. Doc file\n");
    printf("5. Tim kiem\n");
    printf("6. Sap xep\n");
    printf("7. Them sinh vien\n");
    printf("8. Xoa sinh vien\n");
    printf("0. Thoat\n");
    printf("===========================\n");
    printf("Chon chuc nang: ");
}

/**
 * In danh sách sinh viên dạng bảng
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Số lượng sinh viên trong danh sách
 */
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
 * Kiểm tra ID đã tồn tại trong danh sách chưa
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Số lượng sinh viên
 * @param id ID cần kiểm tra
 * @return 1 nếu ID đã tồn tại, 0 nếu chưa
 */
int kiemTraIDTonTai(struct Student students[], int soLuong, int id) {
    for (int i = 0; i < soLuong; i++) {
        if (students[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// ========== CHỨC NĂNG 1: NHẬP SINH VIÊN ==========

/**
 * Chức năng 1: Nhập sinh viên từ bàn phím
 * - Cho phép nhập nhiều sinh viên
 * - Kiểm tra ID trùng lặp
 * - Kiểm tra danh sách đầy
 * 
 * @param students Mảng để lưu danh sách sinh viên
 * @param soLuong Con trỏ đến số lượng sinh viên hiện tại
 * @param maxSize Kích thước tối đa của mảng
 */
void nhapSinhVien(struct Student students[], int *soLuong, int maxSize) {
    int n;
    printf("\n--- NHAP SINH VIEN ---\n");
    printf("Nhap so luong sinh vien can them: ");
    scanf("%d", &n);
    
    if (*soLuong + n > maxSize) {
        printf("Loi: Khong du cho trong! Chi co the them toi da %d sinh vien.\n", 
               maxSize - *soLuong);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        struct Student sv;
        printf("\nSinh vien thu %d:\n", *soLuong + 1);
        
        printf("Nhap ID: ");
        scanf("%d", &sv.id);
        
        // Kiểm tra ID trùng
        if (kiemTraIDTonTai(students, *soLuong, sv.id)) {
            printf("Loi: ID %d da ton tai! Vui long nhap ID khac.\n", sv.id);
            i--; // Giảm i để nhập lại
            continue;
        }
        
        printf("Nhap ten: ");
        fflush(stdin);
        fgets(sv.name, sizeof(sv.name), stdin);
        int len = strlen(sv.name);
        if (len > 0 && sv.name[len - 1] == '\n') {
            sv.name[len - 1] = '\0';
        }
        
        printf("Nhap tuoi: ");
        scanf("%d", &sv.age);
        
        printf("Nhap GPA: ");
        scanf("%f", &sv.gpa);
        
        students[*soLuong] = sv;
        (*soLuong)++;
        printf("Da them sinh vien ID %d thanh cong!\n", sv.id);
    }
    
    printf("\nDa nhap thanh cong %d sinh vien!\n", n);
}

// ========== CHỨC NĂNG 3: GHI FILE ==========

/**
 * Chức năng 3: Ghi danh sách sinh viên vào file
 * - Ghi toàn bộ danh sách vào file students.txt
 * - Định dạng bảng giống như in ra màn hình
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Số lượng sinh viên
 */
void ghiFile(struct Student students[], int soLuong) {
    if (soLuong == 0) {
        printf("\nDanh sach rong! Khong co du lieu de ghi.\n");
        return;
    }
    
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de ghi!\n", FILE_NAME);
        return;
    }
    
    // Ghi tiêu đề bảng
    fprintf(file, "+----+------------------+------+------+\n");
    fprintf(file, "| ID |      Ten         | Tuoi | GPA  |\n");
    fprintf(file, "+----+------------------+------+------+\n");
    
    // Ghi dữ liệu từng sinh viên
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
    printf("\nDa ghi thanh cong %d sinh vien vao file %s!\n", soLuong, FILE_NAME);
}

// ========== CHỨC NĂNG 4: ĐỌC FILE ==========

/**
 * Chức năng 4: Đọc danh sách sinh viên từ file
 * - Đọc từ file students.txt
 * - Parse dữ liệu và lưu vào mảng
 * - Trả về số lượng sinh viên đọc được
 * 
 * @param students Mảng để lưu danh sách sinh viên
 * @param soLuong Con trỏ đến số lượng sinh viên
 * @param maxSize Kích thước tối đa của mảng
 */
void docFile(struct Student students[], int *soLuong, int maxSize) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de doc!\n", FILE_NAME);
        printf("File khong ton tai hoac khong co quyen truy cap.\n");
        return;
    }
    
    char line[200];
    int count = 0;
    int skipHeader = 3; // Bỏ qua 3 dòng đầu
    
    // Bỏ qua dòng tiêu đề
    while (skipHeader > 0 && fgets(line, sizeof(line), file) != NULL) {
        skipHeader--;
    }
    
    // Đọc dữ liệu
    while (fgets(line, sizeof(line), file) != NULL && count < maxSize) {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        if (line[0] == '+') continue;
        
        if (line[0] == '|') {
            int id, age;
            float gpa;
            char name[50];
            
            if (sscanf(line, "| %d | %[^|] | %d | %f |", &id, name, &age, &gpa) == 4) {
                // Trim khoảng trắng ở tên
                char *start = name;
                while (*start == ' ') start++;
                
                char *end = name + strlen(name) - 1;
                while (end > name && *end == ' ') {
                    *end = '\0';
                    end--;
                }
                
                students[count].id = id;
                strcpy(students[count].name, start);
                students[count].age = age;
                students[count].gpa = gpa;
                count++;
            }
        }
    }
    
    fclose(file);
    *soLuong = count;
    printf("\nDa doc thanh cong %d sinh vien tu file %s!\n", count, FILE_NAME);
}

// ========== CHỨC NĂNG 5: TÌM KIẾM ==========

/**
 * Chức năng 5: Tìm kiếm sinh viên theo ID
 * - Nhập ID từ người dùng
 * - Tìm và hiển thị thông tin sinh viên
 * - Báo không tìm thấy nếu ID không tồn tại
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Số lượng sinh viên
 */
void timKiem(struct Student students[], int soLuong) {
    if (soLuong == 0) {
        printf("\nDanh sach rong! Khong co du lieu de tim kiem.\n");
        return;
    }
    
    int id;
    printf("\n--- TIM KIEM SINH VIEN ---\n");
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    
    int timThay = 0;
    for (int i = 0; i < soLuong; i++) {
        if (students[i].id == id) {
            printf("\n>>> TIM THAY SINH VIEN <<<\n");
            printf("+----+------------------+------+------+\n");
            printf("| ID |      Ten         | Tuoi | GPA  |\n");
            printf("+----+------------------+------+------+\n");
            printf("| %-2d | %-16s | %-4d | %-4.2f |\n", 
                   students[i].id, students[i].name, students[i].age, students[i].gpa);
            printf("+----+------------------+------+------+\n");
            timThay = 1;
            break;
        }
    }
    
    if (!timThay) {
        printf("\nKhong tim thay sinh vien voi ID = %d!\n", id);
    }
}

// ========== CHỨC NĂNG 6: SẮP XẾP ==========

/**
 * Chức năng 6: Sắp xếp sinh viên theo GPA giảm dần
 * - Sử dụng thuật toán Bubble Sort
 * - Sắp xếp tại chỗ (in-place)
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Số lượng sinh viên
 */
void sapXep(struct Student students[], int soLuong) {
    if (soLuong <= 1) {
        printf("\nDanh sach khong du de sap xep.\n");
        return;
    }
    
    // Bubble Sort - sắp xếp giảm dần theo GPA
    for (int i = 0; i < soLuong - 1; i++) {
        for (int j = 0; j < soLuong - 1 - i; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                // Đổi chỗ
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    printf("\nDa sap xep thanh cong theo GPA giam dan!\n");
}

// ========== CHỨC NĂNG 7: THÊM SINH VIÊN ==========

/**
 * Chức năng 7: Thêm một sinh viên mới vào danh sách
 * - Nhập thông tin từ người dùng
 * - Kiểm tra ID trùng lặp
 * - Kiểm tra danh sách đầy
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Con trỏ đến số lượng sinh viên
 * @param maxSize Kích thước tối đa của mảng
 */
void themSinhVien(struct Student students[], int *soLuong, int maxSize) {
    if (*soLuong >= maxSize) {
        printf("\nLoi: Danh sach da day! Khong the them sinh vien moi.\n");
        return;
    }
    
    struct Student sv;
    printf("\n--- THEM SINH VIEN MOI ---\n");
    
    printf("Nhap ID: ");
    scanf("%d", &sv.id);
    
    if (kiemTraIDTonTai(students, *soLuong, sv.id)) {
        printf("Loi: ID %d da ton tai! Khong the them sinh vien voi ID trung lap.\n", sv.id);
        return;
    }
    
    printf("Nhap ten: ");
    fflush(stdin);
    fgets(sv.name, sizeof(sv.name), stdin);
    int len = strlen(sv.name);
    if (len > 0 && sv.name[len - 1] == '\n') {
        sv.name[len - 1] = '\0';
    }
    
    printf("Nhap tuoi: ");
    scanf("%d", &sv.age);
    
    printf("Nhap GPA: ");
    scanf("%f", &sv.gpa);
    
    students[*soLuong] = sv;
    (*soLuong)++;
    printf("\nDa them thanh cong sinh vien ID %d: %s\n", sv.id, sv.name);
}

// ========== CHỨC NĂNG 8: XÓA SINH VIÊN ==========

/**
 * Chức năng 8: Xóa sinh viên khỏi danh sách theo ID
 * - Nhập ID từ người dùng
 * - Tìm và xóa sinh viên
 * - Dịch chuyển các phần tử phía sau lên
 * - Báo lỗi nếu ID không tồn tại
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param soLuong Con trỏ đến số lượng sinh viên
 */
void xoaSinhVien(struct Student students[], int *soLuong) {
    if (*soLuong == 0) {
        printf("\nDanh sach rong! Khong co sinh vien de xoa.\n");
        return;
    }
    
    int id;
    printf("\n--- XOA SINH VIEN ---\n");
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    
    int viTri = -1;
    for (int i = 0; i < *soLuong; i++) {
        if (students[i].id == id) {
            viTri = i;
            break;
        }
    }
    
    if (viTri == -1) {
        printf("Loi: Khong tim thay sinh vien voi ID = %d!\n", id);
        return;
    }
    
    // Lưu tên để thông báo
    char tenSV[50];
    strcpy(tenSV, students[viTri].name);
    
    // Dịch chuyển các phần tử phía sau lên
    for (int i = viTri; i < *soLuong - 1; i++) {
        students[i] = students[i + 1];
    }
    
    (*soLuong)--;
    printf("\nDa xoa thanh cong sinh vien ID %d: %s\n", id, tenSV);
}

// ========== HÀM MAIN - LUỒNG CHẠY CHƯƠNG TRÌNH ==========

/**
 * LUỒNG CHẠY CHƯƠNG TRÌNH:
 * 
 * 1. KHỞI TẠO:
 *    - Khai báo mảng students với kích thước MAX_STUDENTS
 *    - Khởi tạo 10 sinh viên giả lập để test
 *    - Khởi tạo biến soLuong = 10
 * 
 * 2. VÒNG LẶP MENU:
 *    - Hiển thị menu chính (inMenu)
 *    - Đọc lựa chọn từ người dùng
 *    - Xử lý từng chức năng dựa trên lựa chọn
 *    - Lặp lại cho đến khi chọn 0 (thoát)
 * 
 * 3. CÁC CHỨC NĂNG:
 *    - 1: Nhập sinh viên - Thêm nhiều sinh viên từ bàn phím
 *    - 2: In danh sách - Hiển thị tất cả sinh viên dạng bảng
 *    - 3: Ghi file - Lưu danh sách vào students.txt
 *    - 4: Đọc file - Đọc danh sách từ students.txt
 *    - 5: Tìm kiếm - Tìm sinh viên theo ID
 *    - 6: Sắp xếp - Sắp xếp theo GPA giảm dần
 *    - 7: Thêm sinh viên - Thêm một sinh viên mới
 *    - 8: Xóa sinh viên - Xóa một sinh viên theo ID
 *    - 0: Thoát - Kết thúc chương trình
 * 
 * 4. KẾT THÚC:
 *    - In thông báo cảm ơn
 *    - Return 0 để kết thúc chương trình
 */
int main() {
    // Khai báo mảng và biến
    struct Student students[MAX_STUDENTS];
    int soLuong = 0;
    
    // Khởi tạo 10 sinh viên giả lập để test
    struct Student danhSachMau[10] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.8},
        {3, "Le Van C", 19, 3.2},
        {4, "Pham Thi D", 22, 4.0},
        {5, "Hoang Van E", 20, 3.6},
        {6, "Vu Thi F", 21, 3.4},
        {7, "Dao Van G", 19, 3.9},
        {8, "Bui Thi H", 23, 3.7},
        {9, "Dang Van I", 20, 2.9},
        {10, "Ly Thi K", 21, 3.3}
    };
    
    // Copy dữ liệu mẫu vào mảng chính
    for (int i = 0; i < 10; i++) {
        students[i] = danhSachMau[i];
    }
    soLuong = 10;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    printf("Da khoi tao san 10 sinh vien de test.\n");
    
    int luaChon;
    
    // Vòng lặp menu chính
    do {
        inMenu(); // Hiển thị menu
        scanf("%d", &luaChon); // Đọc lựa chọn
        
        // Xử lý từng chức năng
        switch (luaChon) {
            case 1:
                nhapSinhVien(students, &soLuong, MAX_STUDENTS);
                break;
                
            case 2:
                printf("\n--- DANH SACH SINH VIEN ---\n");
                inDanhSach(students, soLuong);
                break;
                
            case 3:
                ghiFile(students, soLuong);
                break;
                
            case 4:
                docFile(students, &soLuong, MAX_STUDENTS);
                break;
                
            case 5:
                timKiem(students, soLuong);
                break;
                
            case 6:
                sapXep(students, soLuong);
                printf("\nDanh sach sau khi sap xep:\n");
                inDanhSach(students, soLuong);
                break;
                
            case 7:
                themSinhVien(students, &soLuong, MAX_STUDENTS);
                break;
                
            case 8:
                xoaSinhVien(students, &soLuong);
                break;
                
            case 0:
                printf("\nCam on ban da su dung chuong trinh!\n");
                printf("Hen gap lai!\n");
                break;
                
            default:
                printf("\nLua chon khong hop le! Vui long chon tu 0 den 8.\n");
                break;
        }
        
        // Tạm dừng để người dùng xem kết quả (trừ khi chọn thoát)
        if (luaChon != 0) {
            printf("\nNhan Enter de tiep tuc...");
            fflush(stdin);
            getchar();
        }
        
    } while (luaChon != 0); // Lặp lại cho đến khi chọn 0
    
    return 0;
}
