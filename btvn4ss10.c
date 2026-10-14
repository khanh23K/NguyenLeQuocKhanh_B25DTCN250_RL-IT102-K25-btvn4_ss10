
#include <stdio.h>
#include <string.h>

#define MAX_ZONE 50
#define MAX_VE_MUA 4

// ==================== CAU TRUC DU LIEU ====================

struct TicketZone {
    int zone_id;
    char zone_name[50];
    float ticket_price;
    int total_capacity;
    int sold_tickets;
    int is_early_bird;
};

// ==================== FUNCTION PROTOTYPES ====================

// Nhom nhap lieu
int nhapSoNguyen(const char thongBao[]);
float nhapSoThuc(const char thongBao[]);
void nhapChuoi(const char thongBao[], char chuoi[], int kichThuoc);

// Nhom tim kiem
int timZoneTheoId(const struct TicketZone ds[],
                  int soLuong, int zone_id);

// Nhom quan ly Zone - CRUD
void hienThiDanhSachZone(const struct TicketZone ds[], int soLuong);
int themZone(struct TicketZone ds[], int soLuong);
void capNhatGiaVe(struct TicketZone ds[], int soLuong);
int xoaZone(struct TicketZone ds[], int soLuong);

// Nhom nghiep vu dat ve
int kiemTraDonHang(const struct TicketZone ds[],
                   int soLuong, int viTri, int quantity);
float tinhTongTien(float giaVe, int quantity, int earlyBird);
void datVe(struct TicketZone ds[], int soLuong);

// Nhom dieu khien
void hienThiMenu(void);


// ==================== NHAP LIEU AN TOAN ====================

// Doc so nguyen, yeu cau nhap lai neu sai
int nhapSoNguyen(const char thongBao[]) {
    char dong[100];
    char kyTuThua;
    int giaTri;

    while (1) {
        printf("%s", thongBao);

        if (fgets(dong, sizeof(dong), stdin) == NULL) {
            printf("\nKhong doc duoc du lieu.\n");
            return 0;
        }

        if (strchr(dong, '\n') == NULL) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                // Loai bo phan con lai cua dong nhap
            }
        }

        if (sscanf(dong, " %d %c", &giaTri, &kyTuThua) == 1) {
            return giaTri;
        }

        printf("[LOI] Vui long nhap mot so nguyen hop le!\n");
    }
}


// Doc so thuc, yeu cau nhap lai neu sai
float nhapSoThuc(const char thongBao[]) {
    char dong[100];
    char kyTuThua;
    float giaTri;

    while (1) {
        printf("%s", thongBao);

        if (fgets(dong, sizeof(dong), stdin) == NULL) {
            printf("\nKhong doc duoc du lieu.\n");
            return 0.0f;
        }

        if (strchr(dong, '\n') == NULL) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                // Loai bo phan con lai cua dong nhap
            }
        }

        if (sscanf(dong, " %f %c", &giaTri, &kyTuThua) == 1) {
            return giaTri;
        }

        printf("[LOI] Vui long nhap mot so hop le!\n");
    }
}


// Doc chuoi, loai bo ky tu xuong dong
void nhapChuoi(const char thongBao[], char chuoi[], int kichThuoc) {
    size_t doDai;

    printf("%s", thongBao);

    if (fgets(chuoi, kichThuoc, stdin) == NULL) {
        chuoi[0] = '\0';
        return;
    }

    doDai = strlen(chuoi);

    if (doDai > 0 && chuoi[doDai - 1] == '\n') {
        chuoi[doDai - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            // Loai bo phan con lai cua dong nhap
        }
    }
}


// ==================== TIM KIEM ZONE ====================

// Tra ve vi tri neu tim thay, -1 neu khong tim thay
int timZoneTheoId(const struct TicketZone ds[],
                  int soLuong, int zone_id) {
    int i;

    for (i = 0; i < soLuong; i++) {
        if (ds[i].zone_id == zone_id) {
            return i;
        }
    }

    return -1;
}


// ==================== HIEN THI DANH SACH ====================

void hienThiDanhSachZone(const struct TicketZone ds[], int soLuong) {
    int i;
    int veConLai;

    if (soLuong == 0) {
        printf("\nDanh sach Zone dang rong!\n");
        return;
    }

    printf("\n");
    printf("==========================================================================\n");
    printf("%-6s %-18s %-14s %-10s %-10s %-8s\n",
           "ID", "TEN ZONE", "GIA VE", "DA BAN", "CON LAI", "EARLY");
    printf("==========================================================================\n");

    for (i = 0; i < soLuong; i++) {
        veConLai = ds[i].total_capacity - ds[i].sold_tickets;

        printf("%-6d %-18s %-14.0f %-10d %-10d %-8s\n",
               ds[i].zone_id,
               ds[i].zone_name,
               ds[i].ticket_price,
               ds[i].sold_tickets,
               veConLai,
               ds[i].is_early_bird == 1 ? "Co" : "Khong");
    }

    printf("==========================================================================\n");
    printf("Tong so khu vuc: %d/%d\n", soLuong, MAX_ZONE);
}


// ==================== THEM ZONE ====================

// Tra ve so luong Zone moi
int themZone(struct TicketZone ds[], int soLuong) {
    struct TicketZone zoneMoi;
    int viTri;

    if (soLuong >= MAX_ZONE) {
        printf("[LOI] Danh sach da dat gioi han %d Zone!\n", MAX_ZONE);
        return soLuong;
    }

    zoneMoi.zone_id = nhapSoNguyen("Nhap ma Zone: ");

    if (zoneMoi.zone_id <= 0) {
        printf("[LOI] Ma Zone phai lon hon 0!\n");
        return soLuong;
    }

    viTri = timZoneTheoId(ds, soLuong, zoneMoi.zone_id);

    if (viTri != -1) {
        printf("[LOI] Ma Zone da ton tai!\n");
        return soLuong;
    }

    nhapChuoi("Nhap ten Zone: ",
              zoneMoi.zone_name, sizeof(zoneMoi.zone_name));

    if (zoneMoi.zone_name[0] == '\0') {
        printf("[LOI] Ten Zone khong duoc de trong!\n");
        return soLuong;
    }

    zoneMoi.ticket_price = nhapSoThuc("Nhap gia ve goc: ");

    if (zoneMoi.ticket_price <= 0) {
        printf("[LOI] Gia ve phai lon hon 0!\n");
        return soLuong;
    }

    zoneMoi.total_capacity = nhapSoNguyen("Nhap tong so ve phat hanh: ");

    if (zoneMoi.total_capacity <= 0) {
        printf("[LOI] Suc chua phai lon hon 0!\n");
        return soLuong;
    }

    zoneMoi.is_early_bird = nhapSoNguyen("Ap dung Early Bird (1-Co, 0-Khong): ");

    if (zoneMoi.is_early_bird != 0 &&
        zoneMoi.is_early_bird != 1) {
        printf("[LOI] Early Bird chi nhan 0 hoac 1!\n");
        return soLuong;
    }

    zoneMoi.sold_tickets = 0;

    ds[soLuong] = zoneMoi;
    soLuong++;

    printf("[THANH CONG] Da them Zone %s.\n", zoneMoi.zone_name);

    return soLuong;
}


// ==================== CAP NHAT GIA VE ====================

void capNhatGiaVe(struct TicketZone ds[], int soLuong) {
    int zone_id;
    int viTri;
    float giaMoi;

    if (soLuong == 0) {
        printf("[THONG BAO] Chua co Zone nao!\n");
        return;
    }

    zone_id = nhapSoNguyen("Nhap ma Zone can cap nhat gia: ");

    viTri = timZoneTheoId(ds, soLuong, zone_id);

    if (viTri == -1) {
        printf("[LOI] Khong tim thay Zone %d!\n", zone_id);
        return;
    }

    giaMoi = nhapSoThuc("Nhap gia ve moi: ");

    if (giaMoi <= 0) {
        printf("[LOI] Gia ve phai lon hon 0. Khong cap nhat!\n");
        return;
    }

    ds[viTri].ticket_price = giaMoi;

    printf("[THANH CONG] Da cap nhat gia Zone %s: %.0f VND\n",
           ds[viTri].zone_name, giaMoi);
}


// ==================== XOA ZONE ====================

// Tra ve so luong Zone moi
int xoaZone(struct TicketZone ds[], int soLuong) {
    int zone_id;
    int viTri;
    int i;

    if (soLuong == 0) {
        printf("[THONG BAO] Danh sach Zone dang rong!\n");
        return soLuong;
    }

    zone_id = nhapSoNguyen("Nhap ma Zone can xoa: ");

    viTri = timZoneTheoId(ds, soLuong, zone_id);

    if (viTri == -1) {
        printf("[LOI] Khong tim thay Zone %d!\n", zone_id);
        return soLuong;
    }

    if (ds[viTri].sold_tickets > 0) {
        printf("[LOI] Khong the xoa Zone da co ve ban!\n");
        printf("So ve da ban: %d\n", ds[viTri].sold_tickets);
        return soLuong;
    }

    // Don mang sang trai
    for (i = viTri; i < soLuong - 1; i++) {
        ds[i] = ds[i + 1];
    }

    soLuong--;

    printf("[THANH CONG] Da xoa Zone %d.\n", zone_id);

    return soLuong;
}


// ==================== KIEM TRA DON HANG ====================

// Tra ve 1 neu hop le, 0 neu khong hop le
int kiemTraDonHang(const struct TicketZone ds[],
                   int soLuong, int viTri, int quantity) {
    int veConLai;

    if (soLuong <= 0) {
        printf("[LOI] Chua co Zone de ban!\n");
        return 0;
    }

    if (viTri < 0 || viTri >= soLuong) {
        printf("[LOI] Vi tri Zone khong hop le!\n");
        return 0;
    }

    if (quantity < 1 || quantity > MAX_VE_MUA) {
        printf("[LOI] Moi giao dich chi duoc mua tu 1 den %d ve!\n",
               MAX_VE_MUA);
        return 0;
    }

    if (ds[viTri].sold_tickets < 0 ||
        ds[viTri].total_capacity < ds[viTri].sold_tickets) {
        printf("[LOI] Du lieu ton kho khong hop le!\n");
        return 0;
    }

    veConLai = ds[viTri].total_capacity - ds[viTri].sold_tickets;

    if (quantity > veConLai) {
        printf("[LOI] Khong du ve trong Zone %s!\n",
               ds[viTri].zone_name);
        printf("So ve con lai: %d\n", veConLai);
        return 0;
    }

    return 1;
}


// ==================== TINH TONG TIEN ====================

float tinhTongTien(float giaVe, int quantity, int earlyBird) {
    float tongTien;

    tongTien = giaVe * quantity;

    if (earlyBird == 1) {
        tongTien = tongTien * 0.85f;
    }

    return tongTien;
}


// ==================== DAT VE VA IN HOA DON ====================

void datVe(struct TicketZone ds[], int soLuong) {
    int zone_id;
    int viTri;
    int quantity;
    float tongTien;
    float tienGiam;

    if (soLuong == 0) {
        printf("[THONG BAO] Chua co Zone nao de dat ve!\n");
        return;
    }

    hienThiDanhSachZone(ds, soLuong);

    zone_id = nhapSoNguyen("Nhap ma Zone muon mua: ");

    viTri = timZoneTheoId(ds, soLuong, zone_id);

    if (viTri == -1) {
        printf("[LOI] Ma Zone khong ton tai!\n");
        return;
    }

    quantity = nhapSoNguyen("Nhap so luong ve muon mua (1-4): ");

    if (kiemTraDonHang(ds, soLuong, viTri, quantity) == 0) {
        printf("[GIAO DICH THAT BAI] Khong co du lieu nao bi thay doi.\n");
        return;
    }

    tongTien = tinhTongTien(
        ds[viTri].ticket_price,
        quantity,
        ds[viTri].is_early_bird
    );

    tienGiam = ds[viTri].ticket_price * quantity - tongTien;

    // Chi cap nhat kho sau khi kiem tra hop le
    ds[viTri].sold_tickets += quantity;

    printf("\n");
    printf("============================================\n");
    printf("             HOA DON TICKETBOX              \n");
    printf("          VPOP STAR ARENA                    \n");
    printf("============================================\n");
    printf("Ma Zone       : %d\n", ds[viTri].zone_id);
    printf("Ten Zone      : %s\n", ds[viTri].zone_name);
    printf("Gia mot ve    : %.0f VND\n", ds[viTri].ticket_price);
    printf("So luong      : %d ve\n", quantity);
    printf("Tam tinh      : %.0f VND\n",
           ds[viTri].ticket_price * quantity);

    if (ds[viTri].is_early_bird == 1) {
        printf("Early Bird    : Giam 15%%\n");
        printf("Tien giam     : %.0f VND\n", tienGiam);
    } else {
        printf("Uu dai        : Khong ap dung\n");
        printf("Tien giam     : 0 VND\n");
    }

    printf("--------------------------------------------\n");
    printf("TONG THANH TOAN: %.0f VND\n", tongTien);
    printf("============================================\n");

    printf("[THANH CONG] Giao dich dat ve thanh cong!\n");
    printf("Kho ve hien tai: %d/%d da ban.\n",
           ds[viTri].sold_tickets,
           ds[viTri].total_capacity);
}


// ==================== MENU ====================

void hienThiMenu(void) {
    printf("\n");
    printf("============================================\n");
    printf("       TICKETBOX - VPOP STAR ARENA           \n");
    printf("============================================\n");
    printf("1. Xem danh sach Zone\n");
    printf("2. Them Zone moi\n");
    printf("3. Cap nhat gia ve Zone\n");
    printf("4. Xoa Zone chua co ve ban\n");
    printf("5. Dat ve va in hoa don\n");
    printf("0. Thoat chuong trinh\n");
    printf("============================================\n");
}


// ==================== MAIN ====================

int main(void) {
    struct TicketZone ds[MAX_ZONE] = {
        {1, "Zone SVIP", 3000000.0f, 100, 0, 1},
        {2, "Zone VIP", 2000000.0f, 200, 0, 1},
        {3, "Zone GA", 800000.0f, 500, 0, 0},
        {4, "Zone Standard", 500000.0f, 800, 0, 0}
    };

    int soLuong = 4;
    int luaChon;

    do {
        hienThiMenu();
        luaChon = nhapSoNguyen("Nhap lua chon cua ban: ");

        switch (luaChon) {
            case 1:
                hienThiDanhSachZone(ds, soLuong);
                break;

            case 2:
                soLuong = themZone(ds, soLuong);
                break;

            case 3:
                capNhatGiaVe(ds, soLuong);
                break;

            case 4:
                soLuong = xoaZone(ds, soLuong);
                break;

            case 5:
                datVe(ds, soLuong);
                break;

            case 0:
                printf("Cam on ban da su dung Ticketbox!\n");
                break;

            default:
                printf("[LOI] Lua chon khong hop le. Vui long thu lai!\n");
        }

    } while (luaChon != 0);

    return 0;
}

