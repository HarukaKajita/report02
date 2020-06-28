#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

// ファイルの要素数を取得
int get_nx(char* f_name)
{
	ifstream fp(f_name);  // ファイルオープン

	if (!fp)
	{
		cout << "Can't open file. " << f_name << endl;
		exit(-1);
	}

	// ファイルの要素数を取得
	string line;
	int nx = 0;

	while (fp >> line)
	{
		nx++;
	}

	fp.close();

	return nx;
}

void exchange_pVal(string* a, string* b)
{
	string tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void quick_sort(string a[], int left, int right)
{
	int index1 = left ;
	int index2 = right;
	string x = a[left];

	do
	{
		while (a[index1] < x) index1++;
		while (a[index2] > x) index2--;

		if (index1 <= index2)
		{
			exchange_pVal(&a[index1], &a[index2]);
			index1++;
			index2--;
		}
	} while (index1 < index2);

	if (left < index2) {
		exchange_pVal(&a[left], &a[index2]);
	}

	if (left < index2) {
		quick_sort(a, left, index2);
	}

	if (index1 < right) {
		quick_sort(a, index1, right);
	}
}

int hashfunction(string key, int size) {
	unsigned int v = 0;
	for (int i = 0; i < key.length(); i++) {
		v += key[i];
	}
	return v % size;
}

struct node {
	string key;
	string value;
	struct node* next;
};

struct customHash
{
	int size;
	struct node** table;

	int initialize(customHash* h, int size) {
		h->table = (node * *) new struct node[size];
		h->size = size;
		for (int i = 0; i < size; i++) {
			h->table[i] = NULL;
		}
		return 1;
	}

	void add(customHash* h, string key, string value) {
		int hash_value = hashfunction(key, h->size);
		node* temp;
		temp = new node;
		temp->key = key;
		temp->value = value;

		temp->next = h->table[hash_value];
		h->table[hash_value] = temp;
	}

	string search(customHash* h, string key) {
		int hash_value = hashfunction(key, h->size);
		node* p = h->table[hash_value];
		while (p != NULL) {
			if (p->key == key) {
				return p->value;
			}
			p = p->next;
		}
		return "none";
	}
};

int main(int argc, char* argv[])
{
	if (argc == 1)  // 引数がない場合
	{
		cout << "input file name\n";
		return -1;
	}

	ifstream fp(argv[1]);   // ファイルオープン
	//ファイルオープン失敗でエラー出力し異常終了
	if (!fp) {
		cerr << "failed to open file" << endl;
		return -1;
	}
	// リストのヘッドを定義し初期化
	struct cell* head;
	head = NULL;

	int nx = get_nx(argv[1]);   // ファイルの要素数を取得
	
	//ハッシュの初期化
	customHash* hash_data = new customHash;
	hash_data->initialize(hash_data, nx);

	string* name_data;
	name_data = new string[nx];  // 名前を格納

	string line;
	int count = 0;
	while (fp >> line)
	{
		// 名前と電話番号に分割
		int index = line.find(",");
		string name = line.substr(0, index);
		string tel = line.substr(index + 1);

		hash_data->add(hash_data, name, tel);
		name_data[count++] = name;
	}
	fp.close();

	// 名前をアルファベット順にソート
	quick_sort(name_data, 0, nx-1);

	// 全表示
	for (int ky = 0; ky < nx; ky++)
	{
		string tel = hash_data->search(hash_data, name_data[ky]);
		cout << name_data[ky] << " -> " << tel << "\n";
	}
	// 5件表示
	/*for (int ky = 0; ky < 5; ky++)
	{
		string tel = hash_data->search(hash_data, name_data[ky]);
		cout << name_data[ky] << " -> " << tel << "\n";
	}
	for (int ky = 0; ky < 5; ky++)
	{
		int index = nx - 5 + ky;
		string tel = hash_data->search(hash_data, name_data[index]);
		cout << name_data[index] << " -> " << tel << "\n";
	}*/
	return 0;
}