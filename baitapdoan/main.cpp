#include "doan.h"
void menu(); // hien thi menu chinh
void tomau(int, int); // to mau cho hang dang tro toi
void gotoxy(int, int); // di chuyen den toa do x ,y
void in_thong_bao(string);
void get_key(int&, int&, int); // lay phim dieu khien tu ban phim
void timkiem(SV*, int);// hien thi menu tim kiem sv
void sapxep(SV*, int); // hien thi menu sap xep sv
void them_sv(SV*, int);// hien thi menu them sv
void xoa_sv(SV*, int); // hien thi menu xoa sv
void quay_lai(SV*, int, string);// quay lai trang truoc do

int main() {
	menu();
	return 0;
}

void menu() {
	int n = 1;
	ifstream FileIn;
	FileIn.open("ThongTinSinhVien.txt", ios_base::in);
	SV* sv = new SV[n];
	Doc_Thong_Tin_1_Sinh_Vien(FileIn, sv[0]);
	sv[0].DTBinh = Diem_Trung_Binh(sv[0]);
	sv[0].HocBong = Hoc_Bong(sv[0]);
	Doc_Danh_Sach_Sinh_Vien(FileIn, sv, n);
	int key = 0, vt;
	int vitri = 1;
#define MAX_CHOOSE 7
	while (key != 13) {
		system("cls");
		cout << endl << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		cout << "			|     |           CHUONG TRINH QUAN LY SINH VIEN              |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(1, vitri);
		cout << "			|  1  |      Xuat danh sach sinh vien                         |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(2, vitri);
		cout << "			|  2  |      Them sinh vien                                   |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(3, vitri);
		cout << "			|  3  |      Tim kiem sinh vien                               |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(4, vitri);
		cout << "			|  4  |      Sap xep danh sach sinh vien                      |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(5, vitri);
		cout << "			|  5  |      Xoa sinh vien                                    |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(6, vitri);
		cout << "			|  6  |      In bang thong ke theo lop                        |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(7, vitri);
		cout << "			|  7  |      Thoat                                            |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		get_key(key, vitri, MAX_CHOOSE);
	}
	string thongbao;
	switch (vitri) {
	case 1:
		thongbao = "BAN DA CHON IN RA DANH SACH SINH VIEN !!  ";
		in_thong_bao(thongbao);
		Xuat_Thong_Tin_SV(sv, n);
		quay_lai(sv, n, "menu");
		break;
	case 2:
		them_sv(sv, n);
		break;
	case 3:
		timkiem(sv, n);
		break;
	case 4:
		sapxep(sv, n);
		break;
	case 5:
		xoa_sv(sv, n);
		break;
	case 6:
		thongbao = "IN BANG THONG HOC BONG KE THEO LOP:";
		in_thong_bao(thongbao);
		In_Bang_Thong_Ke(sv, n);
		quay_lai(sv, n, "menu");
		break;
	case 7:
		exit(0);
		break;
	}
	FileIn.close();

}

void tomau(int vitri, int muiten) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	if (vitri == muiten)
		SetConsoleTextAttribute(hConsoleColor, 11);
	else
		SetConsoleTextAttribute(hConsoleColor, 15);
}

void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void in_thong_bao(string thongbao) {
	system("cls");
	gotoxy(60 - thongbao.length() / 2, 4);
	cout << thongbao << endl << endl;
}

void get_key(int& key, int& vitri, int max_choose) {
	key = _getch();
	if (key == 80 || key == 77) {
		if (vitri == max_choose)
			vitri = 1;
		else
			vitri++;
	}
	else if (key == 72 || key == 75) {
		if (vitri == 1)
			vitri = max_choose;
		else
			vitri--;
	}
}

void quay_lai(SV* sv, int n, string noiquaylai) {
	int key = 0, vt = 1;
	while (key != 13) {
		string str1 = "Quay lai";
		string str2 = "Thoat ";
		gotoxy(50 - str1.length() / 2, 1);
		tomau(1, vt);
		cout << str1 << endl;
		gotoxy(80 - str1.length() / 2, 1);
		tomau(2, vt);
		cout << str2 << endl;
		get_key(key, vt, 2);
	}
	switch (vt) {
	case 1:
		if (noiquaylai == "menu")
			menu();
		if (noiquaylai == "them")
			them_sv(sv, n);
		if (noiquaylai == "timkiem")
			timkiem(sv, n);
		if (noiquaylai == "sapxep")
			sapxep(sv, n);
		if (noiquaylai == "xoa")
			xoa_sv(sv, n);
		break;

	case 2:
		system("cls");
		exit(0);
	}
}

void timkiem(SV* sv, int n) {
	int key = 0, vitri = 1, max_choose = 6;
	string thongbao;
	string const MSV = "MSV", Lop = "Lop", Hoten = "Hoten", Gioitinh = "Gioitinh";
	while (key != 13) {
		thongbao = "BAN MUON TIM KIEM THEO : ";
		in_thong_bao(thongbao);
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(1, vitri);
		cout << "			|  1  |           Ma sinh vien                                |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(2, vitri);
		cout << "			|  2  |           Lop                                         |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(3, vitri);
		cout << "			|  3  |           Ho va ten                                   |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(4, vitri);
		cout << "			|  4  |           Gioi tinh                                   |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(5, vitri);
		cout << "			|  5  |           Theo nhieu tieu chi khac nhau               |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(6, vitri);
		cout << "			|  6  |           Quay lai Menu                               |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;

		get_key(key, vitri, max_choose);
	}
	switch (vitri) {

	case 1:
		thongbao = " BAN DA CHON TIM KIEM THEO MA SINH VIEN ";
		in_thong_bao(thongbao);
		cout << " Nhap ma sinh vien: ";
		Timkiem(sv, n, MSV);
		break;
	case 2:
		thongbao = " BAN DA CHON TIM KIEM THEO LOP ";
		in_thong_bao(thongbao);
		cout << "Nhap lop: ";
		Timkiem(sv, n, Lop);
		break;
	case 3:
		thongbao = " BAN DA CHON TIM KIEM THEO HO TEN ";
		in_thong_bao(thongbao);
		cout << "Nhap ho ten: ";
		Timkiem(sv, n, Hoten);
		break;
	case 4:
		thongbao = " BAN DA CHON TIM KIEM THEO GIOI TINH ";
		in_thong_bao(thongbao);
		cout << "Nhap gioi tinh: ";
		Timkiem(sv, n, Gioitinh);
		break;
	case 5:
		thongbao = "BAN DA CHON TIM KIEM SINH VIEN THEO NHIEU TIEU CHI KHAC NHAU !";
		in_thong_bao(thongbao);
		Tim_Kiem_SV(sv, n);
		break;
	case 6:
		menu();
	}
	quay_lai(sv, n, "timkiem");
}

void sapxep(SV* sv, int n) {
	int key = 0, vitri = 1, max_choose = 3;
	string thongbao;
	while (key != 13) {
		thongbao = "BAN MUON SAP XEP THEO : ";
		in_thong_bao(thongbao);
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(1, vitri);
		cout << "			|  1  |           Diem trung binh tang dan                    |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(2, vitri);
		cout << "			|  2  |           Diem trung binh giam dan                    |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(3, vitri);
		cout << "			|  3  |           Quay lai Menu                               |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		get_key(key, vitri, max_choose);
	}
	switch (vitri) {
	case 1:
		thongbao = " BAN DA CHON SAP XEP DANH SACH TANG DAN THEO DIEM TRUNG BINH ";
		in_thong_bao(thongbao);
		Sap_Xep_Thong_Tin_DTB(sv, 0, n - 1, ascending);
		Ghi_File(sv, n);
		Xuat_Thong_Tin_SV(sv, n);
		break;
	case 2:
		thongbao = " BAN DA CHON SAP XEP DANH SACH GIAM DAN THEO DIEM TRUNG BINH ";
		in_thong_bao(thongbao);
		Sap_Xep_Thong_Tin_DTB(sv, 0, n - 1, descending);
		Ghi_File(sv, n);
		Xuat_Thong_Tin_SV(sv, n);
		break;
	case 3:
		menu();
	}
	quay_lai(sv, n, "sapxep");
}

void them_sv(SV* sv, int n) {
	int key = 0, vitri = 1, max_choose = 5;
	string thongbao;
	while (key != 13) {
		thongbao = " BAN DA CHON THEM SINH VIEN : ";
		in_thong_bao(thongbao);
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(1, vitri);
		cout << "			|  1  |    Them nhieu sinh vien                               |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(2, vitri);
		cout << "			|  2  |    Them theo vi tri                                   |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(3, vitri);
		cout << "			|  3  |    Them sao cho diem trung binh van sap xep tang dan  |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(4, vitri);
		cout << "			|  4  |    Them sao cho diem trung binh van sap xep giam dan  |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		tomau(5, vitri);
		cout << "			|  5  |    Quay lai Menu                                      |" << endl;
		cout << "			+-----+-------------------------------------------------------+" << endl;
		get_key(key, vitri, max_choose);
	}
	switch (vitri) {
	case 1:
		thongbao = " BAN DA CHON THEM NHIEU SINH VIEN ";
		in_thong_bao(thongbao);
		Them_Nhieu_Sinh_Vien(sv, n);
		Ghi_File(sv, n);
		cin.ignore();
		break;
	case 2:
		thongbao = " BAN DA CHON THEM SINH VIEN THEO VI TRI ";
		in_thong_bao(thongbao);
		them_sv_theo_vitri(sv, n);
		Ghi_File(sv, n);
		cin.ignore();
		break;
	case 3:
		thongbao = " BAN DA CHON THEM SV SAO CHO DIEM TRUNG BINH VAN SAP XEP TANG DAN";
		in_thong_bao(thongbao);
		cout << "Nhap thong tin sinh vien can chen !" << endl;
		Sap_Xep_Thong_Tin_DTB(sv, 0, n - 1, ascending);
		Chen_1_SV_Theo_Thu_Tu(sv, n, ascending);
		Ghi_File(sv, n);
		break;

	case 4:
		thongbao = " BAN DA CHON THEM SV SAO CHO DIEM TRUNG BINH VAN SAP XEP GIAM DAN";
		in_thong_bao(thongbao);
		cout << "Nhap thong tin sinh vien can chen !" << endl;
		Sap_Xep_Thong_Tin_DTB(sv, 0, n - 1, descending);
		Chen_1_SV_Theo_Thu_Tu(sv, n, descending);
		Ghi_File(sv, n);
		break;
	case 5:
		menu();
	}
	quay_lai(sv, n, "them");
}

void xoa_sv(SV* sv, int n) {
	int key = 0, vitri = 1, max_choose = 3;
	string thongbao;
	while (key != 13) {
		thongbao = "BAN DA CHON CHUC NANG XOA SINH VIEN : ";
		in_thong_bao(thongbao);
		cout << "			+-----+-----------------------------------------------+" << endl;
		tomau(1, vitri);
		cout << "			|  1  |          Xoa theo ma sinh vien                |" << endl;
		cout << "			+-----+-----------------------------------------------+" << endl;
		tomau(2, vitri);
		cout << "			|  2  |          Xoa theo gioi tinh va khoa           |" << endl;
		cout << "			+-----+-----------------------------------------------+" << endl;
		tomau(3, vitri);
		cout << "			|  3  |          Quay lai menu                        |" << endl;
		cout << "			+-----+-----------------------------------------------+" << endl;
		get_key(key, vitri, max_choose);
	}
	string khoa, gioitinh, hoten, lop, msv;
	switch (vitri) {
	case 1:

		thongbao = " BAN DA CHON XOA SINH VIEN THEO MA SINH VIEN ";
		in_thong_bao(thongbao);
		cout << "Nhap ma sinh vien muon xoa : ";
		getline(cin, msv);
		xoa_sv_theo_MSV(sv, n, msv);
		break;
	case 2:
		thongbao = " BAN DA CHON XOA SINH VIEN THEO GIOI TINH VA KHOA ";
		in_thong_bao(thongbao);
		xoa_sv_theo_gt_va_khoa(sv, n);
		break;
	case 3:
		menu();
	}
	quay_lai(sv, n, "xoa");
}