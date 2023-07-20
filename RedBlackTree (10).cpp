#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;
enum COLOR { RED, BLACK };

struct RBTree {
	int Data;
	RBTree *Left;
	RBTree *Right;
	RBTree *Parent;
	COLOR color;
};

struct NodeWithHeigh {
	int height;
	RBTree *node;
};

#define NIL &list           /* all leafs are sentinels */
RBTree list = { 0, NIL, NIL, 0, BLACK };
HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);

void Insert_Node(RBTree** Node, int Data);
void Insert_Fixup(RBTree** Node, RBTree* New_Node);
void Rotate_Left(RBTree** Node, RBTree *Current);
void Rotate_Right(RBTree** Node, RBTree *Current);
NodeWithHeigh *Find(RBTree *Node, int Data, int height);

//создание красно-черного дерева
void Make_RBTree(RBTree** Node, int n) {
	int Data;
	while (n > 0) {
		cout << "Введите значение ";
		cin >> Data;
		Insert_Node(Node, Data);
		n--;
	}
}

//добавление узла в красно-черное дерево
void Insert_Node(RBTree** Node, int Data) {
	RBTree **Curent, *Parent, *New_Node;
	Curent = Node;
	Parent = NIL;
	// Поиск местоположения
	while (*Curent != NIL) {
		Parent = (*Curent);
		Curent = Data < (*Curent)->Data ? &((*Curent)->Left) : &((*Curent)->Right);
	}
	// Создание нового узла
	New_Node = new RBTree();
	New_Node->Data = Data;
	New_Node->Parent = Parent;
	New_Node->Left = NIL;
	New_Node->Right = NIL;
	New_Node->color = RED;
	// Вставка элемента в дерево
	if (Parent != NIL) {
		if (Data < Parent->Data) Parent->Left = New_Node;
		else Parent->Right = New_Node;
	}
	else (*Curent) = New_Node;
	Insert_Fixup(Node, New_Node);
}


// Поддержка баланса дерева после вставки нового элемента
void Insert_Fixup(RBTree** Node, RBTree* New_Node) {
	RBTree* Current = New_Node;
	// Проверка свойств дерева
	while (Current != *(Node) && Current->Parent->color == RED) {
		// если есть нарушение
		if (Current->Parent == Current->Parent->Parent->Left) {
			RBTree *ptr = Current->Parent->Parent->Right;
			if (ptr->color == RED) {
				Current->Parent->color = BLACK;
				ptr->color = BLACK;
				Current->Parent->Parent->color = RED;
				Current = Current->Parent->Parent;
			}
			else {
				if (Current == Current->Parent->Right) {
					// сделать Current левым потомком
					Current = Current->Parent;
					Rotate_Left(Node, Current);
				}
				// перекрасить и повернуть
				Current->Parent->color = BLACK;
				Current->Parent->Parent->color = RED;
				Rotate_Right(Node, Current->Parent->Parent);
			}
		}
		else {
			RBTree *ptr = Current->Parent->Parent->Left;
			if (ptr->color == RED) {
				Current->Parent->color = BLACK;
				ptr->color = BLACK;
				Current->Parent->Parent->color = RED;
				Current = Current->Parent->Parent;
			}
			else {
				if (Current == Current->Parent->Left) {
					Current = Current->Parent;
					Rotate_Right(Node, Current);
				}
				Current->Parent->color = BLACK;
				Current->Parent->Parent->color = RED;
				Rotate_Left(Node, Current->Parent->Parent);
			}
		}
	}
	(*Node)->color = BLACK;
}
//поворот узла Current влево
void Rotate_Left(RBTree** Node, RBTree *Current) {
	RBTree *ptr = Current->Right;
	Current->Right = ptr->Left;
	if (ptr->Left != NIL) ptr->Left->Parent = Current;
	if (ptr != NIL) ptr->Parent = Current->Parent;
	if (Current->Parent != NIL) {
		if (Current == Current->Parent->Left)
			Current->Parent->Left = ptr;
		else
			Current->Parent->Right = ptr;
	}
	else {
		(*Node) = ptr;
	}
	ptr->Left = Current;
	if (Current != NIL) Current->Parent = ptr;
}

//поворот узла Current вправо
void Rotate_Right(RBTree** Node, RBTree *Current) {
	RBTree *ptr = Current->Left;
	Current->Left = ptr->Right;
	if (ptr->Right != NIL) ptr->Right->Parent = Current;
	if (ptr != NIL) ptr->Parent = Current->Parent;
	if (Current->Parent != NIL) {
		if (Current == Current->Parent->Right)
			Current->Parent->Right = ptr;
		else
			Current->Parent->Left = ptr;
	}
	else {
		(*Node) = ptr;
	}
	ptr->Right = Current;
	if (Current != NIL) Current->Parent = ptr;
}

//печать красно-черного дерева
void Print_RBTree(RBTree* Node, int l) {

	int i;
	if (Node != NIL) {
		Print_RBTree(Node->Right, l + 1);
		for (i = 0; i < l; i++) cout << "    ";
		if (Node->color == RED) SetConsoleTextAttribute(hStd, FOREGROUND_RED);
		else SetConsoleTextAttribute(hStd, FOREGROUND_INTENSITY);
		_cprintf("%4ld", Node->Data);
		Print_RBTree(Node->Left, l + 1);
	}
	else cout << endl;

	SetConsoleTextAttribute(hStd, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

//освобождение памяти, выделенной под красно-черное дерево
void Delete_RBTree(RBTree* Node) {
	if (Node != NIL) {
		Delete_RBTree(Node->Left);
		Delete_RBTree(Node->Right);
		delete(Node);
	}
}

NodeWithHeigh *Find(RBTree *Node, int Data, int height)
{

	if (Node == NIL) return NULL;

	if (Data > Node->Data) return Find(Node->Right, Data, height+1);

	if (Data < Node->Data) return Find(Node->Left, Data, height+1);

	if (Data == Node->Data)
	{
		NodeWithHeigh *tmp = new NodeWithHeigh;
		tmp->node = Node;
		tmp->height = height;
		return tmp;
	}
}

int main(void)
{
	RBTree *T = NIL;
	int tmp;

	cout << "Input number of elements to create a tree: ";
	cin >> tmp;
	cout << endl;
	srand((unsigned int)time(NULL) * 1000);

	for (int i = 0; i < tmp; i++)
		Insert_Node(&T, rand() % 100);
	cout << "Print RB-tree" << endl;
	Print_RBTree(T, 0);
	cout << endl;

	NodeWithHeigh *tmp_node = NULL;
	cout << "Input data to find: ";
	cin >> tmp;
	cout << endl;
	tmp_node = Find(T, tmp, 0);
	if (tmp_node == NULL) printf("There is no such element.\n");
	else
	{
		printf("We've found the element "); 
		if (tmp_node->node->color == 0) SetConsoleTextAttribute(hStd, FOREGROUND_RED);
		else if (tmp_node->node->color == 1) SetConsoleTextAttribute(hStd, FOREGROUND_INTENSITY);
		
		printf("%i", tmp_node->node->Data);

		SetConsoleTextAttribute(hStd, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf(" on the %i height.\n", tmp_node->height);
	}

	Delete_RBTree(T);
	system("pause");
	return 0;
}