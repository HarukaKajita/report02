#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

// セルを表わす構造体の定義 
struct cell
{
	string name;   // 名前
	string tel;    // 電話番号

	struct cell* next;	// 次のデータへのポインタ
};

struct cell* make_cell(string name, string tel)
{
	struct cell* mk_cell;

	// cellの領域を確保する 
	mk_cell = new struct cell;

	mk_cell->name = name;
	mk_cell->tel = tel;

	// nextを初期化
	mk_cell->next = NULL;

	return mk_cell;
}


string search_tel(struct cell* head, string name)
{
	struct cell* buf;
	buf = head;

	while (buf != NULL)
	{
		if (buf->name == name)
		{
			return buf->tel;
		}

		buf = buf->next;
	}

	return "none";
}

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

template<class T>
void printArray(T array[], int n) {
	cout << "==============================" << endl;
	for (int i = 0; i < n; i ++) {
		cout << "[" << i << "] : " << array[i] << endl;
	}
	cout << "==============================" << endl;

}

// アルファベット順にソート
void name_sort(string name_data[], int n)
{
	//クイックソート
#ifdef _DEBUG
	cout << "ソート開始" << endl;
	printArray(name_data, n);
#endif // _DEBUG

	if (n == 2) {
		if(name_data[0] > name_data[1])swap(name_data[0], name_data[1]);
#ifdef _DEBUG
		cout << "ソート終了" << endl;
		printArray(name_data, n);
#endif // _DEBUG
		return;
	}
	else if (n <= 1) {
#ifdef _DEBUG
		cout << "ソート終了" << endl;
		printArray(name_data, n);
#endif // _DEBUG
		return;
	}

	string baseString = name_data[0];
#ifdef _DEBUG
	cout << "base : " << baseString << endl;

#endif
	int largeIndex;
	int smallIndex;
	while (true) {
		for (largeIndex=1; largeIndex < n; largeIndex++) {
			string large = name_data[largeIndex];
			if (large > baseString) {
#ifdef _DEBUG
				cout << "large : " << large << endl;
#endif
				break;
			}
		}
		for (smallIndex=n-1; smallIndex > 0; smallIndex--) {
			string small = name_data[smallIndex];
			if (small < baseString) {
#ifdef _DEBUG 
				cout << "small : " << small << endl;
#endif
				break;
			}
		}

		if (smallIndex < largeIndex) {
			swap(name_data[0], name_data[smallIndex]);
			break;
		}
		else {
			if (smallIndex > 0) {
				swap(name_data[smallIndex], name_data[largeIndex]);
			}
		}
	}
#ifdef _DEBUG
	cout << "ソート終了" << endl;
	printArray(name_data, n);
#endif // _DEBUG
	//0~smallIndex
	cout << "sort left" << endl;
	if (smallIndex > 0)name_sort(name_data, smallIndex + 1);
	//largeIndex~n-1
	cout << "sort right" << endl;
	if (largeIndex < n)name_sort(name_data + largeIndex, n - largeIndex);
	
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

	int add(customHash* h, string key, string value) {
		int hash_value = hashfunction(key, h->size);
		node* temp;
		temp = new node;
		temp->key = key;
		temp->value = value;

		temp->next = h->table[hash_value];
		h->table[hash_value] = temp;
	}

	node* search(customHash* h, string key) {
		int hash_value = hashfunction(key, h->size);
		node* p = h->table[hash_value];
		while (p != NULL) {
			if (p->key == key) {
				return p;
			}
			p = p->next;
		}
		return NULL;
	}
};

//int main(int argc, char* argv[])
//{
//	if (argc == 1)  // 引数がない場合
//	{
//		cout << "input file name\n";
//		return -1;
//	}
//
//	ifstream fp(argv[1]);   // ファイルオープン
//	//ファイルオープン失敗でエラー出力し異常終了
//	if (!fp) {
//		cerr << "failed to open file" << endl;
//		return -1;
//	}
//	// リストのヘッドを定義し初期化
//	struct cell* head;
//	head = NULL;
//
//	int nx = get_nx(argv[1]);   // ファイルの要素数を取得
//	
//	//ハッシュの初期化
//	customHash* hash_data = new customHash;
//	hash_data->initialize(hash_data, nx);
//
//#ifdef _DEBUG
//	cout << "データ要素数：" << nx << endl;
//#endif // _DEBUG
//	string* name_data;
//	name_data = new string[nx];  // 名前を格納
//
//	//#ifdef _DEBUG
//	cout << "データ構造構築開始" << endl;
//	//#endif // _DEBUG
//
//	while (fp >> line)
//	{
//		// 名前と電話番号に分割
//		int index = line.find(",");
//		string name = line.substr(0, index);
//		string tel = line.substr(index + 1);
//
//		hash_data->add(hash_data, name, tel);
//	}
//	fp.close();
//
//	//#ifdef _DEBUG
//	cout << "データ構造構築開始" << endl;
//	cout << "ソート開始" << endl;
//	//#endif // _DEBUG
//
//		// 名前をアルファベット順にソート
//	name_sort(name_data, nx);
//
//	//#ifdef _DEBUG
//	cout << "ソート終了" << endl;
//	cout << "全表示開始" << endl;
//	//#endif // _DEBUG
//
//		// 全表示
//	for (int ky = 0; ky < nx; ky++)
//	{
//		string tel = hash_data->search(hash_data, )
//		string tel = search_tel(head, name_data[ky]);
//		cout << name_data[ky] << " -> " << tel << "\n";
//	}
//
//	//#ifdef _DEBUG
//	cout << "全表示終了" << endl;
//	//#endif // _DEBUG
//
//	return 0;
//}


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
#ifdef _DEBUG
	cout << "データ要素数：" << nx << endl;
#endif // _DEBUG
	string* name_data;
	name_data = new string[nx];  // 名前を格納

	string line;
	int i = 0;

//#ifdef _DEBUG
	cout << "データ構造構築開始" << endl;
//#endif // _DEBUG

	while (fp >> line)
	{
		// 名前と電話番号に分割
		int index = line.find(",");
		string name = line.substr(0, index);
		string tel = line.substr(index + 1);

		// リストに名前と電話番号を追加
		struct cell* e_cell;
		e_cell = make_cell(name, tel);

		e_cell->next = head;
		head = e_cell;

		// 名前を配列に格納
		name_data[i] = name;
		i++;
	}
	fp.close();

//#ifdef _DEBUG
	cout << "データ構造構築開始" << endl;
	cout << "ソート開始" << endl;
//#endif // _DEBUG

	// 名前をアルファベット順にソート
name_sort(name_data, nx);

//#ifdef _DEBUG
	cout << "ソート終了" << endl;
	cout << "全表示開始" << endl;
//#endif // _DEBUG

	// 全表示
	for (int ky = 0; ky < nx; ky++)
	{
		string tel = search_tel(head, name_data[ky]);
		cout << name_data[ky] << " -> " << tel << "\n";
	}

//#ifdef _DEBUG
	cout << "全表示終了" << endl;
//#endif // _DEBUG

	return 0;
}
