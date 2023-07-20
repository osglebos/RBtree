#include "pch.h"
#include <iostream>
#include <Windows.h>
using namespace std;

struct RBtree
{
	int key;
	RBtree* leftNode;
	RBtree* rightNode;
	char color;
};

void print_Tree(RBtree*, int);
void addKnot(RBtree*, RBtree*);
void findkey(RBtree*, int, int);

HANDLE hStdOut;

int main()
{
	setlocale(LC_ALL, "RU");

	RBtree* treeRoot = nullptr;
	int Nodes[14]{ 30,20,15,15,25,23,28,50,70,70,60,74,72,75 };
	char Colors[14]{ 'b','b','b','r','r','b','b','r','b','b','r','r','b','b' };
	RBtree* newKnot = nullptr;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int key;

	//создание корня
	cout << "==СОЗДАНИЕ КОРНЯ ДЕРЕВА==\n";
	treeRoot = new RBtree();
	treeRoot->leftNode = nullptr;
	treeRoot->rightNode = nullptr;
	treeRoot->key = *(Nodes);
	treeRoot->color = Colors[0];

	for (int i = 1; i < 14; i++)
	{
		newKnot = new RBtree();
		newKnot->key = Nodes[i];
		newKnot->color = Colors[i];
		addKnot(treeRoot, newKnot);
	}
	print_Tree(treeRoot, 0);
	//

	while (1)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		cout << "Введите желаемый ключ: "; cin >> key;
		findkey(treeRoot, key, 0);
		cout << endl;
	}
	system("pause");
	return 0;
}

void addKnot(RBtree* ptreeRoot, RBtree* pnewKnot)
{
	if (ptreeRoot)
	{
		if (pnewKnot->key <= ptreeRoot->key)
		{
			addKnot(ptreeRoot->leftNode, pnewKnot);
			if (ptreeRoot->leftNode == nullptr) ptreeRoot->leftNode = pnewKnot;
		}
		else if (pnewKnot->key > ptreeRoot->key)
		{
			addKnot(ptreeRoot->rightNode, pnewKnot);
			if (ptreeRoot->rightNode == nullptr) ptreeRoot->rightNode = pnewKnot;
		}
	}
}
void print_Tree(RBtree* ptreeRoot, int level)
{
	if (ptreeRoot)
	{
		print_Tree(ptreeRoot->rightNode, level + 1);
		for (size_t i = 0; i < level; i++) cout << "  ";
		if (ptreeRoot->color == 'r') SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		else SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << '|' << ptreeRoot->key << '|' << endl;
		print_Tree(ptreeRoot->leftNode, level + 1);
	}
}
void findkey(RBtree* ptreeRoot, int pkey, int lvl)
{
	if (ptreeRoot)
	{
		findkey(ptreeRoot->leftNode, pkey, lvl + 1);

		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		if (ptreeRoot->key == pkey)
		{
			cout << "Нашлось звено:: Уровень: " << lvl << " Звено: ";

			if (ptreeRoot->color == 'r') SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			cout << ptreeRoot->key << endl;
		}

		findkey(ptreeRoot->rightNode, pkey, lvl + 1);
	}
}
