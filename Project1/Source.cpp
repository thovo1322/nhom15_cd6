#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
struct NhanVien
{
	char name[51];
	char id[20];
	int gioitinh;
	int namsinh;
	int ca;

};
struct  Node {
	NhanVien info;
	Node* next;

};
typedef Node* NodePtr;


void init(NodePtr& t) {
	t = NULL;
}

NodePtr makeNode(NhanVien t) {
	NodePtr p = new Node();
	if (p == NULL)
		return NULL;
	else {
		p->info.ca = t.ca;
		strcpy_s(p->info.id, t.id);
		strcpy_s(p->info.name, t.name);
		p->info.namsinh = t.namsinh;
		p->info.gioitinh = t.gioitinh;
		p->next = NULL;
		return p;
	}
}

void themNhanVien(NodePtr& list, NhanVien nv) {
	if (list == NULL) {
		NodePtr p = makeNode(nv);
		p->next = list;
		list = p;
	}
	else
	{
		NodePtr q = list;
		NodePtr p = makeNode(nv);
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = p;
	}
}

bool kiemTraIDTrung(NodePtr list, const char* id) {
	NodePtr p = list;
	while (p != NULL) {
		if (strcmp(p->info.id, id) == 0) {
			return true;
		}
		p = p->next;
	}
	return false;
}

bool nhapInFoNhanVien(NhanVien& n, NodePtr list) {
	cout << "\nNhap Ca: ";
	cin >> n.ca;
	cout << "\nNhap ID: ";
	cin.ignore();
	cin.getline(n.id, 19);
	while (strlen(n.id) == 0 || kiemTraIDTrung(list, n.id)) {
		cout << "ID trung . Ban vui long nhap lai: ";
		cin.getline(n.id, 19);
	}

	cout << "\nNhap ten nhan vien: ";
	cin.getline(n.name, 50);
	cout << "\nNhap nam sinh: ";
	cin >> n.namsinh;
	do {
		cout << "\nNhap gioi tinh (1 la nam, 2 la nu): ";
		cin >> n.gioitinh;
		if (n.gioitinh != 1 && n.gioitinh != 2) {
			cout << "Gioi tinh khong hop le. Ban vui long nhap lai !";
		}
	} while (n.gioitinh != 1 && n.gioitinh != 2);

	return true;
}

void insertDanhSach(NodePtr& l) {
	int n;
	NhanVien nv;
	cout << "\nNhap so luong nhan vien: ";
	cin >> n;
	while (n <= 0) {
		cout << " \nSo luong nhan vien khong hop le! Vui long nhap lai so luong:  ";
		cin >> n;
	}
	for (int i = 0; i < n; i++) {
		cout << "Nhap thong tin nhan vien thu " << i + 1 << endl;
		nhapInFoNhanVien(nv, l);
		themNhanVien(l, nv);
	}
}

void xuat() {
	cout << "Ca" << setw(10) << "ID" << setw(20) << "Ten nhan vien" << setw(15) << "Gioi tinh" << setw(10) << "Tuoi" << endl;
}

void hienGioiTinh(NhanVien nv) {
	switch (nv.gioitinh) {
	case 1:
		cout << "Nam";
		break;
	case 2:
		cout << "Nu";
		break;
	}
}

// Xuat Thong Tin Cua 1  Nhân Viên
void xuatInFo(NhanVien nv) {
	int now = 2023;
	cout << nv.ca << setw(10) << nv.id << setw(20) << nv.name << setw(15);
	hienGioiTinh(nv);
	cout << setw(10) << now - nv.namsinh << endl;
}

// Xuat Danh Sach Nhan Vien
void xuatDanhSach(NodePtr l) {
	NodePtr p = l;
	while (p != NULL)
	{
		xuatInFo(p->info);
		p = p->next;
	}
}

// Doc Danh Sach Nhan Vien
bool docDanhSach(NodePtr& list) {
	ifstream filein("ghiDanhSach.txt");

	if (!filein.is_open()) {
		cout << "\nKhong the mo file.! " << endl;
		return false;
	}

	NhanVien nv;
	while (filein >> nv.ca >> nv.id >> nv.name >> nv.gioitinh >> nv.namsinh) {
		themNhanVien(list, nv);
	}

	filein.close();
	return true;
}

void sapXep(NodePtr p) {
	NodePtr j, i, min;
	for (i = p; i != NULL; i = i->next) {
		min = i;
		for (j = i->next; j != NULL; j = j->next)
		{
			if (strcmp(j->info.id, min->info.id) < 0) {
				min = j;
			}
		}
		if (min != i) {
			NhanVien temp = i->info;
			i->info = min->info;
			min->info = temp;
		}
	}
}


void xoaDau(NodePtr& list) {
	if (list != NULL) {
		NodePtr p = list;
		list = p->next;
		p->next = NULL;
		delete p;
	}
}


void xoaNhanVienTheoId(NodePtr& list) {
	char xoa[30];
	NodePtr p = list;
	NodePtr prev = NULL;
	cout << "\n=> Nhap ID nhan vien can xoa:";
	cin >> xoa;

	// Kiểm tra xem danh sách có trống không
	if (list != NULL) {
		// Nếu nút đầu tiên chứa ID cần xóa
		if (strcmp(p->info.id, xoa) == 0) {
			list = p->next;
			p->next = NULL;
			delete p;
			cout << "\n Da xoa nhan vien co ID: " << xoa << endl;
			return;
		}

		//Duyệt qua danh sách để tìm nút có ID được chọn 
		while (p != NULL && strcmp(p->info.id, xoa) != 0) {
			prev = p;
			p = p->next;
		}

		// Nếu tìm thấy nút có ID được chọn thì tiến hành xóa nút
		if (p != NULL) {
			prev->next = p->next;
			p->next = NULL;
			delete p;
			cout << "\n Da xoa nhan vien co ID: " << xoa << endl;
			cout << endl;

		}
		else {
			// Nếu Id không có trong danh sách thì thông báo ra cho nguời dùng biết
			cout << "\n Khong tim thay nhan vien co ID: " << xoa << endl;
		}
	}

	else {
		cout << "\n Danh sach nhan vien dang rong." << endl;
	}
}

void timNhanVienTheoId(NodePtr list) {
	NodePtr p = list;
	char tim[30];
	cout << "\n=> Nhap id nhan vien can tim: ";
	cin >> tim;
	bool flag = false;
	while (p != NULL) {
		if (strcmp(p->info.id, tim) == 0) {
			cout << " \n -------------------- Thong tin  nhan vien can tim ------------------------" << endl;
			cout << endl;
			xuat();
			xuatInFo(p->info);
			flag = true;
			break;
		}
		p = p->next;
	}
	if (flag == false)
		cout << "\n------------ Khong tin thay nhan vien ------------------ ";
}


void xuatNhanVienTheoCa(NodePtr list) {
	NodePtr p = list;
	int tim;
	cout << "\n=> Nhap ca can tim: ";
	cin >> tim;
	bool flag = false;
	cout << "\n ----------------------- Thong tin  nhan vien can tim -------------------- " << endl;
	xuat();
	while (p != NULL) {
		if (p->info.ca == tim) {

			xuatInFo(p->info);
			flag = true;

		}
		p = p->next;
	}
	if (flag == false)
		cout << "\n------------ Khong tin thay nhan vien ------------------ ";
}

// Ghi Danh Sach Nhan Vien
bool ghiDanhSach(NodePtr l) {
	FILE* f;
	fopen_s(&f, "ghiDanhSach.txt", "wt");
	if (f == NULL)
		return false;
	else
	{
		NodePtr q = l;
		while (q != NULL)
		{
			fprintf_s(f, "%i ", q->info.ca);
			fprintf_s(f, "%s ", q->info.id);
			fprintf_s(f, "%s ", q->info.name);
			fprintf_s(f, "%i ", q->info.gioitinh);
			fprintf_s(f, "%i ", q->info.namsinh);

			q = q->next;
			fprintf_s(f, "\n");

		}
	}
	fclose(f);
	return true;
}

bool hoiGhiFile() {
	char chon;
	cout << "\n=> Ban co muon ghi File khong ? (Y/N)";
	cin >> chon;
	return (chon == 'y' || chon == 'Y');
}


void main() {
	NhanVien a;
	NodePtr l;
	init(l);
	int menu;
	int n;
	ifstream filein;
	if (docDanhSach(l) == true) {
		do
		{
			cout << endl;
			xuat();
			xuatDanhSach(l);
			cout << "\n**********************************Bang Chuc Nang**********************************";
			cout << "\n 1.them 1 nhan vien.";
			cout << "\n 2.Nhap N nhan vien.";
			cout << "\n 3.Xuat danh sach nhan vien.";
			cout << "\n 4.Tim nhan vien theo id";
			cout << "\n 5.Sap xep nhan vien theo thuat toan Selection Sort";
			cout << "\n 6.Xoa nhan vien theo id";
			cout << "\n 0. Thoat chuong trinh";
			cout << "\n***********************************************************************************";
			cout << "\n=> Nhap chuc nang: ";
			cin >> menu;
			switch (menu)
			{
			case 1:
				system("cls");
				NhanVien nv;
				nhapInFoNhanVien(nv, l);
				themNhanVien(l, nv);

				system("pause");
				break;
			case 2:
				system("cls");
				insertDanhSach(l);
				system("pause");
				break;
			case 3:
				system("cls");
				cout << " \n-------------------- Danh Sach Nhan Vien ---------------" << endl;
				xuat();
				xuatDanhSach(l);
				system("pause");
				cout << endl;
				break;
			case 4:
				system("cls");
				timNhanVienTheoId(l);
				system("pause");
				break;
			case 5:
				system("cls");
				sapXep(l);
				cout << "\n---------- Danh Sach Da Sap Xep ------------" << endl;
				xuat();
				xuatDanhSach(l);
				system("pause");
				break;
			case 6:
				system("cls");
				xoaNhanVienTheoId(l);
				xuat();
				xuatDanhSach(l);
				system("pause");
				break;
			}
			if (menu != 0 && hoiGhiFile()) {
				if (ghiDanhSach(l) == true) {
					cout << "----------------- Ghi thanh cong ----------------";
				}
				else
				{
					cout << " --------------- Ghi khong thanh cong -------------------";
				}
			}
		} while (menu != 0);
	}
}

