#include <iostream>
#include <unordered_map>
#include<vector>
#include <algorithm>
#include <string>
#include<cmath>
using namespace std;
//вынесем мапу для декодирования
unordered_map<char, string>MCode;
unordered_map<char, string>MHCode;
//элементраный узел
struct Node {
public:
	char symbol;
	int quantity;
	//конструктор
	Node(char s, int q) {
		this->symbol = s;
		this->quantity = q;
	}
	Node() {}
};
//узел префиксного дерева
struct TreeNode {
	string code;
	Node* data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(Node* node) {
		this->data = node;
		this->code = "";
		this->left = nullptr;
		this->right = nullptr;
	}
	TreeNode(Node* node, string code) {
		this->data = node;
		this->code = code;
		this->left = nullptr;
		this->right = nullptr;
	}
};
//функция сортировки по убыванию вероятности встреть символ
//префикс: на вход подается строка по ссылке, которую нужно закодировать
//постфикс: на выходе имеем массив из Node, отсортированный по убыванию. Длины массива записана в str типа string(пригодится для дальнейших ф - й)
Node* mySort(string& str) {
	//ключ - символ, значение - количество
	unordered_map<char, int>M;
	//заполнить мапу
	for (int i = 0; i < str.size(); i++) { M[str[i]]++; }
	int SIZE = M.size();//кол-во различных символов
	//создадим массив-таблицу
	Node* array = new Node[SIZE];
	int i = 0;
	for (auto& e : M) {
		Node n = Node(e.first, e.second);
		array[i] = n;
		i++;
	}
	//сортировка по убыванию(пузырьком)
	for (i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE - 1; j++) {
			if (array[j].quantity < array[j + 1].quantity) {
				Node b = array[j]; // создали дополнительную переменную
				array[j] = array[j + 1]; // меняем местами
				array[j + 1] = b; // значения элементов
			}
		}
	}
	//вывод на консоль
	cout << "frequency:" << endl;
	for (i = 0; i < SIZE; i++) {
		cout << array[i].symbol << " " << array[i].quantity << endl;
	}
	str = to_string(SIZE);
	return array;
}
//префикс:рекурсивная функция построения префиксного дерева
//постфикс: на выходе будет дерево, у которого на листьях будут коды элементов
void getTree(int len, TreeNode* treeNode) {
	if (len <= 1) {
		return;
	}
	Node* table = treeNode->data;
	//сумма левых и правых вероятностей
	int left = 0;
	int right = 0;
	//массивы левый и правый
	Node* arrayL;
	Node* arrayR;
	//сумма всех элементов массива запишем в правую часть
	for (int i = 0; i < len; i++) {
		right += table[i].quantity;
	}
	int delta = right;//разница в вероятностях
	int i = 0;
	for (i; i < len; i++) {
		left += table[i].quantity;
		right -= table[i].quantity;
		//поиск минимальной разницы между суммарными вероятностями левого и правого подмножеств
			if (abs(right - left) < delta) {
				delta = abs(right - left);
			}
			else {
				arrayL = new Node[i];//длина левого подмассива i
				arrayR = new Node[len - i];//длина правого - len-i
				left -= table[i].quantity;
				//запись левого подмассива
				for (int j = 0; j < i; j++) {
					arrayL[j] = table[j];
				}
				//запись правого подмассива
				right += table[i].quantity;
				int iterator = 0;
				for (int j = i; j < len; j++) {
					arrayR[iterator] = table[j];
					iterator++;
				}
				//добавление к кодам новых бит
				string parrentCode = treeNode->code;
				treeNode->left = new TreeNode(arrayL, parrentCode + to_string(0));
				treeNode->right = new TreeNode(arrayR, parrentCode + to_string(1));
				//рекурсивный вызов
				getTree(i, treeNode->left);
				getTree(len - i, treeNode->right);
				break;//если нашлась наименьшая дельта
			}
	}
}
//префикс:функция для наглядного представления кодов симолов
//постфикс:на консоли выведутся коды и соответствующие символы
void printTree(TreeNode* p)
{
	if (!p) return;
	printTree(p->left); //рекурсивно в левое поддерево
	printTree(p->right);//рекурсивно в правое
	if (!(p->left || p->right)) {
		cout << p->data->symbol << " - " << p->code << endl;
	}
}
//префикс:функция для заполнения мапы по данным листьев дерева
//постфикс:
void getMap(TreeNode* p, unordered_map<char, string>& M) {
	if (!p) return;
	getMap(p->left, M); //рекурсивно в левое поддерево
	getMap(p->right, M);//рекурсивно в правое
	if (!(p->left || p->right)) {
		M[p->data->symbol] = p->code;
	}
}
//префикс:функция кодирования
//постфикс:на выходе стрчка бит - код
string codingShannonFano(string s) {
	string duplicate = s;
	string result = "";
	Node* arr = mySort(s);//после сортировки s - кол-во различных символов тк передача по ссылке
		TreeNode* treeNode = new TreeNode(arr);
	getTree(stoi(s), treeNode);
	cout << endl << "----codes:-------" << endl;
	printTree(treeNode);
	cout << "-----------------" << endl << endl;
	getMap(treeNode, MCode);
	for (int i = 0; i < duplicate.size(); i++) {
		result += MCode.at(duplicate[i]);
	}
	return result;
}
//префикс:функция декодирования по таблице
//постфикс:на выход получим строку в 'человеческом' представлении
string decodingShannonFano(string s) {
	string result = "";
	string currentCode = "";
	currentCode += s[0];
	//лишняя итерация для последнего символа
	for (int i = 1; i < s.size() + 1; i++) {
		for (auto& e : MCode)
		{
			if (e.second == currentCode) {
				result += e.first;
				currentCode = "";
				break;
			}
		}
		currentCode += s[i];
	}
	return result;
}
//-------------------------codingHuffman---------
struct HNode {
public:
	vector<char> line;
	int quantity;
	string code;
	HNode* left;
	HNode* right;
	HNode(vector<char> line, int quantity) {
		this->line = line;
		this->quantity = quantity;
		this->left = nullptr;
		this->right = nullptr;
		this->code = "";
	}
	HNode() {}
};
void setCodes(HNode* headTree);
//префикс:на вход получим вектор из указателей на узлы дерева
//постфикс:результат работы функции - префиксное дерево и мапа с кодами
void getHuffmanTree(vector<HNode*> vH) {
	//если мы дошли до корня - заполним мапу и выведем коды на консоль
	if (vH.size() == 1) {
		setCodes(vH[0]);
		return;
	}
	//считаем новую вероятность для узла
	int newq = vH[vH.size() - 1]->quantity + vH[vH.size() - 2]->quantity;
	//запомним последний и предпоследний элементы-дети нового узла
	HNode* left = vH[vH.size() - 2];
	HNode* right = vH[vH.size() - 1];
	//предпоследний элемент-новый элемент, склеенный из двух последних старого вектора
		vH[vH.size() - 2] = new HNode(vH[vH.size() - 2]->line, newq);
	//дописываем к предпоследнему символы последнего
	for (int i = 0; i < vH[vH.size() - 1]->line.size(); i++) {
		vH[vH.size() - 2]->line.push_back(vH[vH.size() - 1]->line[i]);
	}
	//удаляем из ВЕКТОРА(ссылка остается)
	vH.pop_back();
	//расставим указатели
	vH[vH.size() - 1]->left = left;
	vH[vH.size() - 1]->right = right;
	//поставим на место новый узел
	for (int i = vH.size() - 1; i > 0; i--) {
		if (vH[i]->quantity > vH[i - 1]->quantity) {
			swap(vH[i], vH[i - 1]);
		}
		else {
			break;
		}
	}
	getHuffmanTree(vH);
}
//префикс:функция на вход получает корень дерева
//постфикс:результат работы функции - мапа с кодами и распечатанная таблица кодов
void setCodes(HNode* headTree) {
	if (!(headTree->left || headTree->right)) {
		MHCode[headTree->line[0]] = headTree->code;
		//напечатать коды для наглядности
		cout << headTree->line[0] << " - " << headTree->code << endl;
		return;
	}
	//возьмем код родителя и допишем к нему новый бит
	headTree->left->code = headTree->code + '0';
	headTree->right->code = headTree->code + '1';
	setCodes(headTree->left);
	setCodes(headTree->right);
}
//префикс:функция кодирования
//постфикс:на выходе стрчка бит - код
string codingHuffman(string s) {
	string duplicate = s;
	string result = "";
	Node* arr = mySort(s);//после сортировки s - кол-во различных символов б тк передача по ссылке
		vector<HNode*> vHNodeLists(stoi(s));
	for (int i = 0; i < stoi(s); i++) {
		vHNodeLists[i] = new HNode(vector<char>(1, arr[i].symbol), arr[i].quantity);
	}
	getHuffmanTree(vHNodeLists);
	for (int i = 0; i < duplicate.size(); i++) {
		result += MHCode.at(duplicate[i]);
	}
	return result;
}
//префикс:функция декодирования по таблице
//постфикс:на выход получим строку в 'человеческом' представлении
string decodingHuffman(string s) {
	string result = "";
	string currentCode = "";
	currentCode += s[0];
	//лишняя итерация для последнего символа
	for (int i = 1; i < s.size() + 1; i++) {
		for (auto& e : MHCode)
		{
			if (e.second == currentCode) {
				result += e.first;
				currentCode = "";
				break;
			}
		}
		currentCode += s[i];
	}
	return result;
}
int main()
{
	setlocale(LC_ALL, "rus");
	string str;
	str = "кот пошёл за молоком, а котята кувырком. кот пришёл без молока, а котята ха - ха - ха.";
		// cout << "final code-result:" << endl;
		string codingLine = codingShannonFano(str);
	cout << codingLine << endl;
	cout << codingLine.size() << " bit";
	cout << endl << "decoding:" << endl;
	cout << decodingShannonFano(codingLine);
	cout << endl << endl;
	//////////////////////////////////////
	str = "Припадчев Алексей Анатольевич";
	cout << "final code-result:" << endl;
	string codingLin = codingHuffman(str);
	cout << codingLin << endl;
	cout << codingLin.size() << " bit";
	cout << endl << "decoding:" << endl;
	cout << decodingHuffman(codingLin);
	return 0;
}