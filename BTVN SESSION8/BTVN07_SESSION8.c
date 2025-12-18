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
 * Sắp xếp danh sách sinh viên theo GPA giảm dần (từ cao xuống thấp)
 * sử dụng thuật toán Bubble Sort
 * 
 * @param students Mảng chứa danh sách sinh viên cần sắp xếp
 * @param soLuong Số lượng sinh viên trong mảng
 * 
 * THUẬT TOÁN BUBBLE SORT:
 * 
 * Bubble Sort là một thuật toán sắp xếp đơn giản hoạt động bằng cách:
 * 1. So sánh các cặp phần tử liền kề trong mảng
 * 2. Nếu phần tử trước nhỏ hơn phần tử sau (theo thứ tự giảm dần), 
 *    thì đổi chỗ chúng
 * 3. Lặp lại quá trình này cho đến khi không còn cặp nào cần đổi chỗ
 * 
 * LOGIC CỤ THỂ:
 * - Vòng lặp ngoài (i): Chạy từ 0 đến soLuong-1, đại diện cho số lần duyệt
 * - Vòng lặp trong (j): Chạy từ 0 đến soLuong-2-i, so sánh cặp liền kề
 * - So sánh: students[j].gpa < students[j+1].gpa
 *   + Nếu đúng (GPA trước < GPA sau), đổi chỗ để GPA cao hơn lên trước
 *   + Kết quả: Sau mỗi lần duyệt, phần tử có GPA thấp nhất sẽ "nổi" lên cuối
 * 
 * ĐỘ PHỨC TẠP:
 * - Thời gian: O(n²) trong trường hợp xấu nhất
 * - Không gian: O(1) - sắp xếp tại chỗ
 * 
 * VÍ DỤ MINH HỌA:
 * Mảng ban đầu: [3.5, 4.0, 3.2, 3.8]
 * 
 * Lần duyệt 1:
 *   [3.5, 4.0, 3.2, 3.8] -> 3.5 < 4.0? Có -> đổi: [4.0, 3.5, 3.2, 3.8]
 *   [4.0, 3.5, 3.2, 3.8] -> 3.5 < 3.2? Không -> giữ nguyên
 *   [4.0, 3.5, 3.2, 3.8] -> 3.2 < 3.8? Có -> đổi: [4.0, 3.5, 3.8, 3.2]
 * 
 * Lần duyệt 2:
 *   [4.0, 3.5, 3.8, 3.2] -> 4.0 < 3.5? Không -> giữ nguyên
 *   [4.0, 3.5, 3.8, 3.2] -> 3.5 < 3.8? Có -> đổi: [4.0, 3.8, 3.5, 3.2]
 * 
 * Lần duyệt 3:
 *   [4.0, 3.8, 3.5, 3.2] -> 4.0 < 3.8? Không -> hoàn thành
 * 
 * Kết quả: [4.0, 3.8, 3.5, 3.2] - đã sắp xếp giảm dần
 * 
 * XỬ LÝ TRƯỜNG HỢP GPA BẰNG NHAU:
 * - Khi GPA bằng nhau, thuật toán không đổi chỗ
 * - Thứ tự ban đầu được giữ nguyên (stable sort trong trường hợp này)
 * 
 * Ví dụ sử dụng:
 *   struct Student students[5] = {...};
 *   sapXepTheoGPAGiamDan(students, 5);
 *   inDanhSach(students, 5); // In danh sách đã sắp xếp
 */
void sapXepTheoGPAGiamDan(struct Student students[], int soLuong) {
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (soLuong <= 1) {
        return; // Không cần sắp xếp
    }
    
    // Bubble Sort: sắp xếp giảm dần (GPA cao -> thấp)
    for (int i = 0; i < soLuong - 1; i++) {
        // Duyệt từ đầu đến phần tử chưa được sắp xếp
        for (int j = 0; j < soLuong - 1 - i; j++) {
            // So sánh GPA: nếu GPA trước < GPA sau thì đổi chỗ
            if (students[j].gpa < students[j + 1].gpa) {
                // Đổi chỗ hai sinh viên
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
        // Sau mỗi lần duyệt, phần tử có GPA thấp nhất sẽ ở cuối
    }
}

int main() {
    printf("=== CHUONG TRINH SAP XEP SINH VIEN THEO GPA GIAM DAN ===\n");
    
    // Test case 1: GPA ngẫu nhiên
    printf("\n--- TEST CASE 1: GPA NGẪU NHIÊN ---\n");
    struct Student test1[5] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 4.0},
        {3, "Le Van C", 19, 2.8},
        {4, "Pham Thi D", 22, 3.8},
        {5, "Hoang Van E", 20, 3.2}
    };
    int soLuong1 = 5;
    
    printf("Danh sach truoc khi sap xep:\n");
    inDanhSach(test1, soLuong1);
    
    sapXepTheoGPAGiamDan(test1, soLuong1);
    
    printf("Danh sach sau khi sap xep (GPA giam dan):\n");
    inDanhSach(test1, soLuong1);
    
    // Test case 2: GPA bằng nhau
    printf("\n--- TEST CASE 2: GPA BẰNG NHAU ---\n");
    struct Student test2[4] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.5},
        {3, "Le Van C", 19, 3.5},
        {4, "Pham Thi D", 22, 3.5}
    };
    int soLuong2 = 4;
    
    printf("Danh sach truoc khi sap xep (tat ca GPA = 3.5):\n");
    inDanhSach(test2, soLuong2);
    
    sapXepTheoGPAGiamDan(test2, soLuong2);
    
    printf("Danh sach sau khi sap xep (GPA bang nhau, giu nguyen thu tu):\n");
    inDanhSach(test2, soLuong2);
    
    // Test case 3: GPA tăng dần sẵn (cần đảo ngược)
    printf("\n--- TEST CASE 3: GPA TĂNG DẦN SẴN (cần đảo ngược) ---\n");
    struct Student test3[5] = {
        {1, "Nguyen Van A", 20, 2.5},
        {2, "Tran Thi B", 21, 3.0},
        {3, "Le Van C", 19, 3.5},
        {4, "Pham Thi D", 22, 3.8},
        {5, "Hoang Van E", 20, 4.0}
    };
    int soLuong3 = 5;
    
    printf("Danh sach truoc khi sap xep (GPA tang dan: 2.5 -> 4.0):\n");
    inDanhSach(test3, soLuong3);
    
    sapXepTheoGPAGiamDan(test3, soLuong3);
    
    printf("Danh sach sau khi sap xep (GPA giam dan: 4.0 -> 2.5):\n");
    inDanhSach(test3, soLuong3);
    
    // Test case 4: Một số GPA bằng nhau, một số khác
    printf("\n--- TEST CASE 4: MỘT SỐ GPA BẰNG NHAU, MỘT SỐ KHÁC ---\n");
    struct Student test4[6] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 4.0},
        {3, "Le Van C", 19, 3.5},
        {4, "Pham Thi D", 22, 3.8},
        {5, "Hoang Van E", 20, 3.5},
        {6, "Vu Thi F", 21, 3.2}
    };
    int soLuong4 = 6;
    
    printf("Danh sach truoc khi sap xep (co nhieu GPA = 3.5):\n");
    inDanhSach(test4, soLuong4);
    
    sapXepTheoGPAGiamDan(test4, soLuong4);
    
    printf("Danh sach sau khi sap xep:\n");
    inDanhSach(test4, soLuong4);
    printf("(Cac sinh vien co GPA = 3.5 giu nguyen thu tu ban dau)\n");
    
    // Test case 5: Danh sách rỗng
    printf("\n--- TEST CASE 5: DANH SÁCH RỖNG ---\n");
    struct Student test5[1];
    int soLuong5 = 0;
    
    printf("Danh sach rong:\n");
    inDanhSach(test5, soLuong5);
    
    sapXepTheoGPAGiamDan(test5, soLuong5);
    printf("Sau khi sap xep (khong co loi):\n");
    inDanhSach(test5, soLuong5);
    
    // Test case 6: Danh sách 1 phần tử
    printf("\n--- TEST CASE 6: DANH SÁCH 1 PHẦN TỬ ---\n");
    struct Student test6[1] = {{1, "Nguyen Van A", 20, 3.5}};
    int soLuong6 = 1;
    
    printf("Danh sach truoc khi sap xep:\n");
    inDanhSach(test6, soLuong6);
    
    sapXepTheoGPAGiamDan(test6, soLuong6);
    
    printf("Danh sach sau khi sap xep (khong thay doi):\n");
    inDanhSach(test6, soLuong6);
    
    return 0;
}

