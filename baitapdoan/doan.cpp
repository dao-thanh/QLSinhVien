#include "doan.h" //goi lai thu vien ben file.h
// doc ngay thang nam tu file
void Doc_Ngay_Thang_Nam(ifstream& FileIn, Date& date) {
	FileIn >> date.Ngay;
	FileIn.seekg(1, 1);
	FileIn >> date.Thang;
	FileIn.seekg(1, 1);
	FileIn >> date.Nam;
}

//tinh diem trung binh cua 1 sinh vien
float Diem_Trung_Binh(SV& sv) {
	float DTB;
	DTB = roundf(((sv.DiemToan + sv.DiemTin + sv.DiemLy) / 3) * 100) / 100;
	return DTB;
}

//tinh hoc bong cua 1 sinh vien
int Hoc_Bong(SV& sv) {
	int hocbong;
	hocbong = sv.DTBinh >= 8 ? 200 : (sv.DTBinh >= 7 ? 100 : 0);
	return hocbong;
}

// tach ho va ten cua 1 sinh vien
void Tach_Ho_Ten(SV& sv) {
	int pos = 0;
	for (int i = sv.Ten.length() - 1; i >= 0; i--)
		if (sv.Ten[i] == ' ') {
			pos = i;
			break;
		}
	sv.Ho = sv.Ten.substr(0, pos);
	sv.Ten = sv.Ten.substr(pos + 1);
}

//doc thong tin 1 sinh vien tu file
void Doc_Thong_Tin_1_Sinh_Vien(ifstream& FileIn, SV& sv) {
	getline(FileIn, sv.MaSV, ',');
	FileIn.seekg(1, 1);
	getline(FileIn, sv.Ten, ',');
	Tach_Ho_Ten(sv);
	Doc_Ngay_Thang_Nam(FileIn, sv.NgaySinh);
	FileIn.seekg(2, 1);
	getline(FileIn, sv.GioiTinh, ',');
	FileIn.seekg(1, 1);
	getline(FileIn, sv.Lop, ',');
	FileIn >> sv.DiemToan;
	FileIn >> sv.DiemLy;
	FileIn >> sv.DiemTin;
	string temp;//tao bien tam de doc ki tu xuong dong o cuoi dong
	getline(FileIn, temp);
}

//them 1 sinh vien theo vi tri
void Them_1_SV_Vao_Mang(SV*& sv, int& n, SV& svThem, int vitri) {
	SV* temp = new SV[n];
	for (int i = 0; i < n; i++)
		temp[i] = sv[i];
	delete[] sv;
	sv = new SV[++n];
	for (int i = 0; i < vitri; i++)
		sv[i] = temp[i];
	for (int i = vitri + 1; i < n; i++)
		sv[i] = temp[i - 1];
	sv[vitri] = svThem;
	delete[] temp;
}

//doc thong tin tat ca sinh vien tu file va luu vao mang sv
void Doc_Danh_Sach_Sinh_Vien(ifstream& FileIn, SV*& sv, int& n) {
	while (!FileIn.eof()) {
		SV svThem;
		Doc_Thong_Tin_1_Sinh_Vien(FileIn, svThem);
		svThem.DTBinh = Diem_Trung_Binh(svThem);
		svThem.HocBong = Hoc_Bong(svThem);
		Them_1_SV_Vao_Mang(sv, n, svThem, n);
	}
}

// xuat thong tin 1 sv
void Xuat_Thong_Tin_1_SV(SV& sv) {
	cout << "||" << sv.MaSV << setw(3) << "||" << sv.Ho << " " << sv.Ten << setw(23 - ((sv.Ho + sv.Ten).length() + 1)) << "||" << sv.NgaySinh.Ngay << "/" << sv.NgaySinh.Thang << "/" << sv.NgaySinh.Nam
		<< "\t||" << sv.GioiTinh << "\t||" << sv.Lop << "\t||" << sv.DiemToan << "\t||" << sv.DiemLy << "\t||" << sv.DiemTin << "\t||" << roundf(sv.DTBinh * 100) / 100
		<< "\t||" << sv.HocBong << "\t||" << endl;
}
//xuat thong tin tat ca sinh vien
void Xuat_Thong_Tin_SV(SV* sv, int n) {

	cout << "  --------------------------+++                 DANH SACH SINH VIEN                   +++-----------------------------" << endl << endl;
	cout << "==================================================================================================================" << endl;
	cout << "|| Stt  ||    MSV   ||        Ho Ten       || Ngay Sinh ||GTinh ||  Lop ||DToan ||DTin  ||DLy   ||DiemTB||HBong ||" << endl;
	cout << "==================================================================================================================" << endl;
	for (int i = 0; i < n; i++) {
		cout << "|| " << i + 1 << "\t";
		Xuat_Thong_Tin_1_SV(sv[i]);
	}
	cout << "==================================================================================================================" << endl;
}

// kiem tra so tu nhien
bool Check_STN(string  s) {
	for (int i = 0; i < s.length(); i++)
		if (s[i] < '0' || s[i] > '9')
			return false;
	return true;
}
int  so_ngay_trong_thang(int ngay, int thang, int nam) {
	int so_ngay;
	switch (thang) {
	case 2:
		so_ngay = 28;
		if ((nam % 4 == 0) && (nam % 100 != 0) || nam % 400 == 0) so_ngay = 29;
		break;
	case 4: case 6: case 9: case 11:
		so_ngay = 30;
		break;
	default: so_ngay = 31;
		break;
	}
	return so_ngay;
}


// chuyen chuoi sang so
int convert(string s) {
	int number = 0;
	for (int i = 0; i < s.length(); i++)
		number = number * 10 + ((int)s[i] - 48);
	return number;
}

//nhap thong tin cua 1 sinh vien
void Nhap_Thong_Tin_1_SV(SV& svThem) {
	do {
		cout << "Nhap ma sinh vien:";
		getline(cin, svThem.MaSV);
		if (svThem.MaSV.length() != 9) cout << "Ma sinh vien khong hop le , vui long nhap lap 9 so !" << endl;
	} while (svThem.MaSV.length() != 9);
	cout << "Nhap ho:";
	getline(cin, svThem.Ho);
	cout << "Nhap ten:";
	getline(cin, svThem.Ten);
	int so_ngay;
	string temp;
	do {
		do {
			cout << "Nhap ngay sinh:";
			getline(cin, temp);
			if (Check_STN(temp)) svThem.NgaySinh.Ngay = convert(temp);
			else svThem.NgaySinh.Ngay = -1;
			if ((svThem.NgaySinh.Ngay < 1 || svThem.NgaySinh.Ngay > 31)) cout << "Ngay sinh khong hop le !" << endl;
		} while (svThem.NgaySinh.Ngay < 1 || svThem.NgaySinh.Ngay > 31);
		do {
			cout << "Nhap thang sinh:";
			getline(cin, temp);
			if (Check_STN(temp)) svThem.NgaySinh.Thang = convert(temp);
			else svThem.NgaySinh.Ngay = -1;
			if (svThem.NgaySinh.Thang < 1 || svThem.NgaySinh.Thang >12) cout << "Thang sinh khong hop le !" << endl;
		} while (svThem.NgaySinh.Thang < 1 || svThem.NgaySinh.Thang >12);
		do {
			cout << "Nhap nam sinh:";
			getline(cin, temp);
			if (Check_STN(temp)) svThem.NgaySinh.Nam = convert(temp);
			else svThem.NgaySinh.Ngay = -1;
			if (svThem.NgaySinh.Nam < 1990 || svThem.NgaySinh.Nam > 2019) cout << "Nam sinh khong hop le , vui long nhap lai (1990-2019)!" << endl;
		} while (svThem.NgaySinh.Nam < 1990 || svThem.NgaySinh.Nam > 2019);
		so_ngay = so_ngay_trong_thang(svThem.NgaySinh.Ngay, svThem.NgaySinh.Thang, svThem.NgaySinh.Nam);
		if (svThem.NgaySinh.Ngay > so_ngay) cout << " Thang 2 cua nam nhuan khong duoc qua 29 ngay, vui long nhap lai" << endl;
		//cin.ignore();
	} while (svThem.NgaySinh.Ngay > so_ngay);

	do {
		cout << "Nhap gioi tinh:";
		getline(cin, svThem.GioiTinh);
		if (Hoa_Thanh_Thuong(svThem.GioiTinh) != "nam" && Hoa_Thanh_Thuong(svThem.GioiTinh) != "nu") cout << "Gioi tinh khong hop le !" << endl;
	} while (Hoa_Thanh_Thuong(svThem.GioiTinh) != "nam" && Hoa_Thanh_Thuong(svThem.GioiTinh) != "nu");
	if (Hoa_Thanh_Thuong(svThem.GioiTinh) == "nam") svThem.GioiTinh = "Nam";
	else
		if (Hoa_Thanh_Thuong(svThem.GioiTinh) == "nu") svThem.GioiTinh = "Nu";
	string s;
	do {
		cout << "Nhap ten lop:";
		getline(cin, svThem.Lop);
		s = svThem.Lop.substr(0, 2);
		if (Check_STN(s) == false) cout << "Lop khong hop le !" << endl;
	} while (Check_STN(s) == false);
	do {
		cout << "Diem toan:";
		cin >> svThem.DiemToan;
		if (svThem.DiemToan < 0 || svThem.DiemToan >10) cout << "Diem toan khong hop le , vui long nhap lai (0-10)!" << endl;
	} while (svThem.DiemToan < 0 || svThem.DiemToan >10);
	do {
		cout << "Diem li:";
		cin >> svThem.DiemLy;
		if (svThem.DiemLy < 0 || svThem.DiemLy >10) cout << "Diem li khong hop le , vui long nhap lai (0-10)!" << endl;
	} while (svThem.DiemLy < 0 || svThem.DiemLy >10);
	do {
		cout << "Diem tin:";
		cin >> svThem.DiemTin;
		if (svThem.DiemTin < 0 || svThem.DiemTin >10) cout << "Diem tin khong hop le , vui long nhap lai (0-10)!" << endl;
	} while (svThem.DiemTin < 0 || svThem.DiemTin >10);
	svThem.DTBinh = Diem_Trung_Binh(svThem);
	svThem.HocBong = Hoc_Bong(svThem);

}

// kiem tra ma SV them vao da co hay chua 
bool kiemtraMSV(string msv, SV* sv, int n) {
	for (int i = 0; i < n; i++)
		if (msv == sv[i].MaSV)
			return true;
	return false;
}

// them 1 sinh vien nhap tu ban phim theo vi tri 
void them_sv_theo_vitri(SV*& sv, int& n) {
	SV svThem;
	int vt;
	cout << " nhap vi tri muon them :";
	cin >> vt;
	if (vt <= 0) vt = 1;
	if (vt > n) vt = n + 1;
	do {
		cin.ignore();
		Nhap_Thong_Tin_1_SV(svThem);
		if (kiemtraMSV(svThem.MaSV, sv, n)) {
			cout << (" Ma Sinh vien da ton tai, vui long nhap lai !!\n");
		}
	} while (kiemtraMSV(svThem.MaSV, sv, n));
	Them_1_SV_Vao_Mang(sv, n, svThem, vt - 1);
	cout << " Da them sinh vien vao vi tri thu " << vt << " vao danh sach !" << endl;
	Xuat_Thong_Tin_SV(sv, n);
}

//them nhiu sinh vien tu ban phim
void Them_Nhieu_Sinh_Vien(SV*& sv, int& n) {
	int soluong;
	SV svThem;
	cout << "Nhap so luong sinh vien muon them : ";
	cin >> soluong;
	for (int i = 0; i < soluong; i++) {
		do {
			cout << endl << "Nhap thong tin sinh vien thu " << i + 1 << ": " << endl;
			cin.ignore();
			Nhap_Thong_Tin_1_SV(svThem);
			if (kiemtraMSV(svThem.MaSV, sv, n))
				cout << " Ma sinh vien da ton tai, vu long nhap lai !!" << endl;
		} while (kiemtraMSV(svThem.MaSV, sv, n));
		Them_1_SV_Vao_Mang(sv, n, svThem, n);
	}
	cout << endl << " Da them " << soluong << " sinh vien vao danh sach " << endl << endl;
	Xuat_Thong_Tin_SV(sv, n);
}

// tim kiem chuoi con trong chuoi cha
int sub__str(std::string const str, std::string const substr) {
	int pos = str.rfind(substr);
	return (pos != std::string::npos) ? pos : -1;
}

// chuyen chuoi hoa thanh chuoi thuong
string Hoa_Thanh_Thuong(string s) {
	string st;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
		st = st + s[i];
	}
	return st;
}

// tim kiem sinh vien theo 1 tieu chi
void Timkiem(SV* sv, int n, string tieuchi) {
	string key;
	getline(cin, key);
	int k = 0;
	SV* DSSV = new SV[n];
	if (key == "") {
		for (int i = 0; i < n; i++)
			DSSV[k++] = sv[i];
	}
	else {
		for (int i = 0; i < n; i++) {
			if (tieuchi == "MSV")
				if (sub__str(Hoa_Thanh_Thuong(sv[i].MaSV), Hoa_Thanh_Thuong(key)) != -1)
					DSSV[k++] = sv[i];
			if (tieuchi == "Lop")
				if (sub__str(Hoa_Thanh_Thuong(sv[i].Lop), Hoa_Thanh_Thuong(key)) != -1)
					DSSV[k++] = sv[i];
			if (tieuchi == "Hoten")
				if (sub__str(Hoa_Thanh_Thuong(sv[i].Ho + " " + sv[i].Ten), Hoa_Thanh_Thuong(key)) != -1)
					DSSV[k++] = sv[i];
			if (tieuchi == "Gioitinh")
				if (sub__str(Hoa_Thanh_Thuong(sv[i].GioiTinh), Hoa_Thanh_Thuong(key)) != -1)
					DSSV[k++] = sv[i];
		}
	}
	if (!k) cout << " Khong tim thay sinh vien nhu yeu cau !!";
	else {
		for (int i = 0; i < k; i++) {
			DSSV[i].DTBinh = Diem_Trung_Binh(DSSV[i]);
			DSSV[i].HocBong = Hoc_Bong(DSSV[i]);
		}
		Xuat_Thong_Tin_SV(DSSV, k);
	}

}

void Tim_Kiem_SV(SV* sv, int n) {
	cout << "Ma sinh vien:";
	string msv;
	getline(cin, msv);
	int k = 0;
	SV* DSSV = new SV[n];
	if (msv == "") {
		for (int i = 0; i < n; i++)
			DSSV[k++] = sv[i];
	}
	else {
		for (int i = 0; i < n; i++)
			if (sub__str(Hoa_Thanh_Thuong(sv[i].MaSV), Hoa_Thanh_Thuong(msv)) != -1)
				DSSV[k++] = sv[i];
	}
	if (!k)
		cout << endl << " Khong tim thay sinh vien nhu yeu cau !! " << endl << endl;
	else {
		for (int i = 0; i < k; i++) {
			DSSV[i].DTBinh = Diem_Trung_Binh(DSSV[i]);
			DSSV[i].HocBong = Hoc_Bong(DSSV[i]);
		}
		// tim kiem theo ho ten
		cout << "Ho va Ten:";
		string hoten;
		getline(cin, hoten);
		if (hoten != "") {
			for (int i = 0; i < k; i++)
				if (sub__str(Hoa_Thanh_Thuong(DSSV[i].Ho + " " + DSSV[i].Ten), Hoa_Thanh_Thuong(hoten)) == -1)
					xoa_sv_theo_vitri(DSSV, k, i--);
		}
		if (!k)
			cout << endl << " Khong tim thay sinh vien nhu yeu cau" << endl << endl;
		else {
			// tim kiem theo gioi tinh
			cout << "Gioi tinh:";
			string gioitinh;
			getline(cin, gioitinh);
			if (gioitinh != "") {
				for (int i = 0; i < k; i++)
					if (sub__str(Hoa_Thanh_Thuong(DSSV[i].GioiTinh), Hoa_Thanh_Thuong(gioitinh)) == -1)
						xoa_sv_theo_vitri(DSSV, k, i--);
			}
			if (!k)
				cout << endl << " Khong tim thay sinh vien nhu yeu cau" << endl << endl;
			else {
				// tim kiem theo lop
				cout << "Lop:";
				string lop;
				getline(cin, lop);
				if (lop != "") {
					for (int i = 0; i < k; i++)
						if (sub__str(Hoa_Thanh_Thuong(DSSV[i].Lop), Hoa_Thanh_Thuong(lop)) == -1)
							xoa_sv_theo_vitri(DSSV, k, i--);
				}
				if (!k)
					cout << endl << " Khong tim thay sinh vien nhu yeu cau" << endl << endl;
				else
					Xuat_Thong_Tin_SV(DSSV, k);
			}
		}
	}
}

bool ascending(float left, float right) {
	return left > right;
}

bool descending(float left, float right) {
	return left < right;
}

// hoan vi 2 sinh vien
void Hoan_Vi(SV& sv1, SV& sv2) {
	SV temp = sv1;
	sv1 = sv2;
	sv2 = temp;
}

// ghi thong tin 1 sinh vien vao file
void Ghi_Thong_Tin_1_Sinh_Vien(ofstream& FileOut, SV sv) {
	FileOut << sv.MaSV << ", ";
	FileOut << sv.Ho << " ";
	FileOut << sv.Ten << ", ";
	FileOut << sv.NgaySinh.Ngay << "/" << sv.NgaySinh.Thang << "/" << sv.NgaySinh.Nam << ", ";
	FileOut << sv.GioiTinh << ", ";
	FileOut << sv.Lop << ", ";
	FileOut << sv.DiemToan << " ";
	FileOut << sv.DiemLy << " ";
	FileOut << sv.DiemTin;
}

// sap xep danh sach sinh vien theo diem trung binh
void Sap_Xep_Thong_Tin_DTB(SV* sv, int l, int r, bool CompFunc(float, float)) {
	float key = sv[(l + r) / 2].DTBinh;
	int i = l, j = r;
	while (i <= j) {
		while (CompFunc(key, sv[i].DTBinh)) i++;
		while (CompFunc(sv[j].DTBinh, key)) j--;
		if (i <= j) {
			if (i < j)
				Hoan_Vi(sv[i], sv[j]);
			i++;
			j--;
		}
	}
	if (CompFunc(2, 1)) {
		if (l < j)
			Sap_Xep_Thong_Tin_DTB(sv, l, j, ascending);

		if (i < r)  Sap_Xep_Thong_Tin_DTB(sv, i, r, ascending);
	}
	else {
		if (l < j)
			Sap_Xep_Thong_Tin_DTB(sv, l, j, descending);

		if (i < r)  Sap_Xep_Thong_Tin_DTB(sv, i, r, descending);
	}
}

//sap xep danh sach sinh vien theo ma sinh vien theo diem trung binh - sau do luu vao file SapXepSinhVien.txt
void Ghi_File(SV* sv, int n) {
	ofstream FileOut;
	FileOut.open("ThongTinSinhVien.txt", ios_base::out);
	for (int i = 0; i < n; i++) {
		Ghi_Thong_Tin_1_Sinh_Vien(FileOut, sv[i]);
		if (i < n - 1) FileOut << endl;
	}
	FileOut.close();
}

// chen 1 sinh vien sao cho mang sinh vien sap xep theo thu tu 
void Chen_1_SV_Theo_Thu_Tu(SV*& sv, int& n, bool CompFunc(float, float)) {
	int vt = 0;
	SV svChen;
	do {
		Nhap_Thong_Tin_1_SV(svChen);
		for (int i = 0; i < n; i++)
			if (CompFunc(svChen.DTBinh, sv[i].DTBinh))
				vt = i + 1;
		if (kiemtraMSV(svChen.MaSV, sv, n))
			cout << (" Ma Sinh vien da ton tai, vui long nhap lai !!\n");
		cin.ignore();
	} while (kiemtraMSV(svChen.MaSV, sv, n));
	Them_1_SV_Vao_Mang(sv, n, svChen, vt);
	cout << " Da them thanh cong !!" << endl;
	Xuat_Thong_Tin_SV(sv, n);
}

void xoa_sv_theo_MSV(SV* sv, int& n, string MSV) {
	int vitri = -1;
	for (int i = 0; i < n; i++) {
		if (sv[i].MaSV == MSV) {
			xoa_sv_theo_vitri(sv, n, i);
			vitri = i;
			break;
		}
	}
	if (vitri == -1) cout << "	Khong tim thay sinh vien nao nhu yeu cau !!" << endl;
	else {
		cout << endl << "	Da xoa sinh vien co ma sinh vien la " << MSV << " !!" << endl << endl;
		Xuat_Thong_Tin_SV(sv, n);
		Ghi_File(sv, n);
	}
}

// xoa sinh vien theo khoa va gioi tinh
void xoa_sv_theo_gt_va_khoa(SV*& sv, int& n) {
	string khoa, gioitinh;
	cout << "nhap khoa: ";
	getline(cin, khoa);
	cout << "nhap gioi tinh: ";
	getline(cin, gioitinh);
	bool check = false;
	string khoaSS;
	for (int i = 0; i < n; i++) {
		if (sub__str(sv[i].Lop, khoa) == 0 && Hoa_Thanh_Thuong(sv[i].GioiTinh) == Hoa_Thanh_Thuong(gioitinh)) {
			check = true;
			xoa_sv_theo_vitri(sv, n, i);
			i--;
		}
	}
	if (check == false) cout << " khong tim thay sinh vien nhu yeu cau!!" << endl;
	else {
		cout << " da xoa cac sinh vien co gioi tinh " << gioitinh << " thuoc khoa " << khoa << " !!" << endl << endl;
		Xuat_Thong_Tin_SV(sv, n);
		Ghi_File(sv, n);
	}
}

// xoa 1 sinh vien trong danh sach
void xoa_sv_theo_vitri(SV*& sv, int& n, int vt) {
	SV* temp = new SV[n];
	for (int i = 0; i < n; i++)
		temp[i] = sv[i];
	delete[] sv;
	for (int i = vt; i < n - 1; i++)
		temp[i] = temp[i + 1];
	sv = new SV[--n];
	for (int i = 0; i < n; i++)
		sv[i] = temp[i];
	delete[] temp;
}

//kiem tra lop o trong mang lop hay chua
bool Check(SV sv, string* MangLop, int count) {
	for (int i = 0; i < count; i++)
		if (MangLop[i] == sv.Lop)
			return false;
	return true;
}

// them 1 ten lop vao mang lop
void Them_1_Lop_Vao_Mang_Ten_Lop(string*& MangLop, int& count, string lopThem)
{
	string* temp = new string[count];
	for (int i = 0; i < count; i++) {
		temp[i] = MangLop[i];
	}
	delete[] MangLop;
	MangLop = new string[++count];
	for (int i = 0; i < count - 1; i++) {
		MangLop[i] = temp[i];
	}
	MangLop[count - 1] = lopThem;
	delete[] temp;
}

// sap xep ten lop theo thu tu tang dan
void Sap_Xep_Mang_Ten_Lop(string* MangLop, int count) {
	string temp;
	for (int i = 0; i < count - 1; i++)
		for (int j = i + 1; j < count; j++)
			if (MangLop[i] > MangLop[j]) {
				temp = MangLop[i];
				MangLop[i] = MangLop[j];
				MangLop[j] = temp;
			}
}

//In bang thong ke theo lop
void In_Bang_Thong_Ke(SV* sv, int n)
{
	int count = 1;
	string* MangLop = new string[count];
	MangLop[0] = sv[0].Lop;
	for (int i = 1; i < n; i++)
		if (Check(sv[i], MangLop, count))
			Them_1_Lop_Vao_Mang_Ten_Lop(MangLop, count, sv[i].Lop);
	Sap_Xep_Mang_Ten_Lop(MangLop, count);
	int* SoLuong = new int[count];
	int* TongHocBong = new int[count];
	for (int i = 0; i < count; i++) {
		SoLuong[i] = 0;
		TongHocBong[i] = 0;
		for (int j = 0; j < n; j++)
			if (MangLop[i] == sv[j].Lop) {
				SoLuong[i] += 1;
				TongHocBong[i] += sv[j].HocBong;
			}
	}
	cout << "				==================================================" << endl;
	cout << "				||\tLop\t||" << " SoLuong\t||" << "TongHocBong\t||" << endl;
	cout << "				==================================================" << endl;
	for (int i = 0; i < count; i++) {
		cout << "				||\t" << MangLop[i] << "\t||\t" << SoLuong[i] << "\t||\t" << TongHocBong[i] << "\t||";
		cout << endl;
	}
	cout << "				==================================================" << endl;
}
