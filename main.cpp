#include <iostream>
#include <string>
using namespace std;

void Add();
void Remove();
void Undo();
void Redo();

/*---------------------------------------------------------------------
	Shape
*/
class Shape
{
public:
	Shape *next;

public:
	virtual void draw() = 0;
	virtual void setInfo(int rad, int w, int h) = 0;
	virtual string getType() = 0;
	virtual string getStyle() = 0;
	virtual int getRadius() = 0;
	virtual int getHeight() = 0;
	virtual int getWidth() = 0;
};

// Circle 2D
class Circle_2D :
	public Shape
{
private:
	int radius;

public:
	void draw() {
		cout << "Circle 2D " << "radius = " << radius;
	}

	void setInfo(int rad, int w, int h) {
		radius = rad;
	}

	string getType() {
		return "circle";
	}

	string getStyle() {
		return "2d";
	}

	int getRadius() {
		return radius;
	}

	int getHeight() {
		return 0;
	}

	int getWidth() {
		return 0;
	}
};

// Circle 3D
class Circle_3D :
	public Shape
{
private:
	int radius;

public:
	void draw() {
		cout << "Circle 3D " << "radius = " << radius;
	}

	void setInfo(int rad, int w, int h) {
		radius = rad;
	}

	string getType() {
		return "circle";
	}

	string getStyle() {
		return "3d";
	}

	int getRadius() {
		return radius;
	}

	int getHeight() {
		return 0;
	}

	int getWidth() {
		return 0;
	}
};

// Rectangle 2D
class Rectangle_2D :
	public Shape 
{
private:
	int width, height;

public:
	void draw() {
		cout << "Rectangle 2D " << "width = " << width << " height = " << height;
	}

	void setInfo(int rad, int w, int h) {
		width = w;
		height = h;
	}

	string getType() {
		return "rectangle";
	}

	string getStyle() {
		return "2d";
	}

	int getRadius() {
		return 0;
	}

	int getHeight() {
		return height;
	}

	int getWidth() {
		return width;
	}
};

// Rectangle 3D
class Rectangle_3D :
	public Shape
{
private:
	int width, height;

public:
	void draw() {
		cout << "Rectangle 3D " << "width = " << width << " height = " << height;
	}

	void setInfo(int rad, int w, int h) {
		width = w;
		height = h;
	}

	string getType() {
		return "rectangle";
	}

	string getStyle() {
		return "3d";
	}

	int getRadius() {
		return 0;
	}

	int getHeight() {
		return height;
	}

	int getWidth() {
		return width;
	}
};


/*------------------------------------------------------------------------------------
	Abstract Factory
*/
class AbstractFactory {
public:
	virtual Shape* getCircle() = 0;
	virtual Shape* getRectangle() = 0;

};

// Circle Factory
class _2DFactory :
	public AbstractFactory
{
public:
	Shape* getCircle() {
		return new Circle_2D;
	}

	Shape* getRectangle() {
		return new Rectangle_2D;
	}
};

// Rectangle Factory
class _3DFactory :
	public AbstractFactory
{
public:
	Shape* getCircle() {
		return new Circle_3D;
	}

	Shape* getRectangle() {
		return new Rectangle_3D;
	}
};

/*
	Factory Producer
*/
class FactoryProducer 
{
public:
	static AbstractFactory* getFactory(string choice) {
		if (choice == "2d") {
			return new _2DFactory;
		}
		else if (choice == "3d") {
			return new _3DFactory;
		}

		return NULL;
	}
};

class ShapeProducer
{
public:
	static Shape* getShape(AbstractFactory *factory, string choice) {
		if (choice == "circle") {
			return factory->getCircle();
		}
		else if (choice == "rectangle") {
			return factory->getRectangle();
		}

		return NULL;
	}
};

/*------------------------------------------------------------------------------
	Linked List

*/
class LinkedList {
private:
	Shape *head = NULL;
	Shape *last = NULL;

public:
	LinkedList *next;

	bool isEmpty() {
		return head == NULL;
	}

public:

	// Adds an element at the end of the list
	void addLast(string factoryStyle, string shape, int radius, int width, int height) {
		AbstractFactory *factory = FactoryProducer::getFactory(factoryStyle);
		Shape *link = ShapeProducer::getShape(factory, shape);

		link->setInfo(radius, width, height);
		
		if (isEmpty()) {
			head = link;
		}
		else {
			last->next = link;
		}

		link->next = NULL;
		last = link;
	}

	Shape* deletion(int pos) {

		Shape* current = head;
		Shape* previous = NULL;
		static int cnt;

		if (head == NULL) {
			return NULL;
		}

		cnt = 1;
		while (cnt != pos) {

			if (current->next == NULL) {
				return NULL;
			}
			else {
				previous = current;
				current = current->next;
				cnt++;
			}
		}

		if (current == head) {
			head = head->next;
		}
		else {
			previous->next = current->next;
		}

		return current;
	}

	// Show number of Items
	int length() {
		int length = 0;
		Shape *ptr = head;

		while (ptr != NULL) {
			length++;
			ptr = ptr->next;
		}

		return length;
	}

	//Find Item
	/*Shape* find(int data) {
		Shape *ptr = head;

		while (ptr != NULL) {
			if (ptr->getInfo() == data) {
				return ptr;
			}

			ptr = ptr->next;
		}

		return NULL;
	}*/

	//Print all Items
	int printAll() {
		static int cnt;
		Shape *ptr = head;

		if (head == NULL) {
			return 0;
		}

		cnt = 1;
		while (ptr != NULL) {
			cout << cnt << ". ";
			ptr->draw();
			cout << endl;
			ptr = ptr->next;
			cnt++;
		}

		cout << endl;
		return 1;
	}

	//copy
	LinkedList* copy() {
		LinkedList *list = new LinkedList;
		Shape *ptr = head;

		if (head == NULL)
			return NULL;

		while (ptr != NULL) {
			list->addLast(ptr->getStyle(), ptr->getType(), ptr->getRadius(), ptr->getWidth(), ptr->getHeight());
			ptr = ptr->next;
		}

		return list;
	}

	//reset
	int reset() {
		head = NULL;
		return 1;
	}
};


/*----------------------------------------------------------------------------
	Stack Undo and Redo
*/
class StackOrQueue {
protected:
	LinkedList *head = NULL;
	LinkedList *last = NULL;

public:

	LinkedList* pop() {
		LinkedList *remove = NULL;

		if (isEmpty()) {
			return NULL;
		}
		else {
			remove = head;
			head = head->next;
			remove->next = NULL;

			return remove;
		}
	}

	bool isEmpty() {
		return head == NULL;
	}

	int printAll() {
		LinkedList *ptr = head;

		if (head == NULL) {
			return 0;
		}

		while (ptr != NULL) {
			ptr->printAll();
			ptr = ptr->next;
		}

		cout << endl;
		return 1;
	}

	LinkedList* getLast() {
		return head;
	}

	int reset() {
		head = NULL;
		return 1;
	}
};

class Stack : public StackOrQueue {
public:

	void push(LinkedList *list) {

		if (StackOrQueue::isEmpty()) {
			StackOrQueue::last = list;
		}

		list->next = StackOrQueue::head;
		StackOrQueue::head = list;

	}


};


/*
	MAIN
*/
LinkedList *list = new LinkedList;
Stack *UndoStack = new Stack;
Stack *RedoStack = new Stack;

string style, shape;

int numChoice;

bool isUndoRedo = false;

int main() {
	
	do {
		cout << "\n1. Add ";
		cout << "\n2. Remove ";
		cout << "\n3. Undo ";
		cout << "\n4. Redo ";
		//cout << "\n5. Print ";
		cout << "\n6. Exit ";
		cout << "\nEnter your choice : ";

		cin >> numChoice;
		cin.ignore();
		system("cls");

		switch (numChoice) {
			// Add
		case 1:
			Add();
			break;

			// Remove
		case 2:
			Remove();
			break;

			// Undo
		case 3:
			Undo();
			break;

			// Redo
		case 4:
			Redo();
			break;

		case 5:
			
			break;

			// Exit
		case 6:
			return 0;
		default:
			cout << "Please choose a selection " << endl;
		}

		cout << "\n======================== PANEL =============================" << endl;
		list->printAll();
		//system("pause");
	} while (numChoice != 6);
	
	
	//system("pause");
	return 0;
}



// Add
void Add() {
	LinkedList *newState = new LinkedList;
	int radius = 0;
	int width = 0;
	int height = 0;

	cout << "Style = ";
	fflush(stdin);
	getline(cin, style);

	cout << "\nShape = ";
	fflush(stdin);
	getline(cin, shape);

	if (shape == "circle") {
		cout << "\nRadius = ";
		cin >> radius;
	}
	else if (shape == "rectangle") {
		cout << "Width = ";
		cin >> width;
		cout << "\nHeight = ";
		cin >> height;
	}

	list->addLast(style, shape, radius, width, height);
	newState = list->copy();
	UndoStack->push(newState);

	// while undo redo
	if (isUndoRedo) {
		isUndoRedo = false;

		RedoStack->reset();
	}
}

// Remove
void Remove() {
	static int posDel = 0;
	LinkedList *newState = new LinkedList;

	cout << "Position = ";
	cin >> posDel;

	list->deletion(posDel);
	newState = list->copy();
	UndoStack->push(newState);

	// while undo redo
	if (isUndoRedo) {
		isUndoRedo = false;

		RedoStack->reset();
	}
}

// Undo
void Undo() {
	isUndoRedo = true;

	if (!UndoStack->isEmpty()) {
		RedoStack->push(UndoStack->pop());

		if (!UndoStack->isEmpty()) {
			list = UndoStack->getLast()->copy();
		}
		else {
			list->reset();
		}

		//cout << "============= UNDO Stack ==============" << endl;
		//UndoStack->printAll();
		//cout << endl;
		//
		////list = UndoStack->getLast();
		//cout << "============ REDO Stack ===============" << endl;
		//RedoStack->printAll();
		//cout << endl;
		
	}
}

//Redo
void Redo() {
	isUndoRedo = true;

	if (!RedoStack->isEmpty()) {
		UndoStack->push(RedoStack->pop());

		if (!UndoStack->isEmpty()) {
			list = UndoStack->getLast()->copy();
		}
		else {
			list->reset();
		}

	}
}