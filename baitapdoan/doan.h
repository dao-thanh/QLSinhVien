#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<windows.h>
#include<conio.h>
using namespace std;
struct date {
	int Ngay;
	int Thang;
	int Nam;
}; typedef date Date;
struct SinhVien {
	string MaSV;
	string Ho;
	string Ten;
	string Lop;
	string GioiTinh;
	Date NgaySinh;
	float DiemToan = 0, DiemLy = 0, DiemTin = 0;
	float DTBinh = 0;
	int HocBong = 0;
}; typedef SinhVien SV;
void Doc_Ngay_Thang_Nam(ifstream& FileIn, Date& date);// doc ngay thang nam tu file
float Diem_Trung_Binh(SV& sv);// tinh diem trung binh cua 1 sinh vien
int Hoc_Bong(SV& sv);// tinh hoc bong cua 1 sinh vien
void Tach_Ho_Ten(SV& sv);// tach ho va ten sinh vien
void Doc_Thong_Tin_1_Sinh_Vien(ifstream& FileIn, SV& sv);//doc thong tin 1 sinh vien tu file
void Them_1_SV_Vao_Mang(SV*& sv, int& n, SV& svThem, int vitri);//them 1 sinh vien vao mang
void Doc_Danh_Sach_Sinh_Vien(ifstream& FileIn, SV*& sv, int& n);//doc thong tin tat ca sinh vien tu file
void Xuat_Thong_Tin_1_SV(SV& sv);//xuat thong tin cua 1 sinh vien
void Xuat_Thong_Tin_SV(SV* sv, int n);//xuat thong tin tat ca sinh vien
void Nhap_Thong_Tin_1_SV(SV& svThem);//nhap thong tin cua 1 sinh vien
string Hoa_Thanh_Thuong(string s); // chuyen chuoi hoa thanh chuoi thuong
void them_sv_theo_vitri(SV*& sv, int& n);// them 1 sinh vien vao vi tri bat ki trong mang
void Them_Nhieu_Sinh_Vien(SV*& sv, int& n);// them 1 sinh vien vao vi tri bat ki trong mang
void Timkiem(SV* sv, int n, string tieuchi);
void Tim_Kiem_SV(SV* sv, int n);//tim kiem sinh vien theo nhieu tieu chi
bool ascending(float left, float right);
bool descending(float left, float right);
void Hoan_Vi(SV& sv1, SV& sv2);// hoan vi 2 sinh vien
void Ghi_Thong_Tin_1_Sinh_Vien(ofstream& FileOut, SV sv);// ghi thong tin 1 sinh vien vao file
void Sap_Xep_Thong_Tin_DTB(SV* sv, int l, int r, bool CompFunc(float, float));// sap xep danh sach sinh vien theo diem trung binh tang hoac giam dan
void Ghi_File(SV* sv, int n);//sap xep danh sach sinh vien theo ma sinh vien theo diem trung binh - sau do luu vao file SapXepSinhVien.txt
void Chen_1_SV_Theo_Thu_Tu(SV*& sv, int& n, bool CompFunc(float, float));// chen 1 sinh vien sao cho mang sinh vien sap xep theo thu tu 
void xoa_sv_theo_MSV(SV* sv, int& n, string MSV);
void xoa_sv_theo_gt_va_khoa(SV*& sv, int& n);
void xoa_sv_theo_vitri(SV*& sv, int& n, int vt);// xoa 1 sinh vien trong danh sach
bool Check(SV sv, string* MangLop, int count);//kiem tra lop o trong mang lop hay chua
void Them_1_Lop_Vao_Mang_Ten_Lop(string*& MangLop, int& count, string lopThem);// them 1 ten lop vao mang lop
void Sap_Xep_Mang_Ten_Lop(string* MangLop, int count);// sap xep ten lop theo thu tu tang dan
void In_Bang_Thong_Ke(SV* sv, int n);//In bang thong ke theo lop