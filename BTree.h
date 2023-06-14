#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include "MyQueueAndStack.h"

struct Data {
	int Id; int Year; int Deaths;
	string CauseName113; string CauseName; string State;
	float AadRate;// age adjust death rate
	Data() {
		MakeNULL();
	}
	void MakeSame(Data other) {
		Id = other.Id;
		Year = other.Year;
		Deaths = other.Deaths;
		CauseName113 = other.CauseName113;
		CauseName = other.CauseName;
		State = other.State;
		AadRate = other.AadRate;
	}
	void operator=(Data& other) {
		Id = other.Id;
		Year = other.Year;
		Deaths = other.Deaths;
		CauseName113 = other.CauseName113;
		CauseName = other.CauseName;
		State = other.State;
		AadRate = other.AadRate;
	}
	bool operator==(Data& other) {
		if (Id == other.Id)
			return true;
		return false;
	}
	bool operator < (Data& other) {
		if (Id < other.Id)
			return true;
		return false;
	}
	bool operator > (Data& other) {
		if (Id > other.Id)
			return true;
		return false;
	}
	void MakeNULL() {
		Id = 0;
		Year = 0;
		Deaths = 0;
		AadRate = 0;
		CauseName113 = "Empty";
		CauseName = "Empty";
		State = "Empty";
	}
	void Display() {
		cout << "********************************************" << endl;
		cout << "* ID = " << Id << endl;
		cout << "* Year = " << Year << endl;
		cout << "* CauseName113 = " << CauseName113 << endl;
		cout << "* CauseName = " << CauseName << endl;
		cout << "* State = " << State << endl;
		cout << "* Deaths = " << Deaths << endl;
		cout << "* AadRate = " << AadRate << endl;
		cout << "********************************************" << endl;
	}
};

struct BTnodeID {
	const int m;
	Data* key;
	string* path;
	int counter; // keep track of all the available keys
	BTnodeID(int mVal) :m(mVal) {
		counter = 0;
		key = new Data[m - 1]; // keys are less
		path = new string[m];
		for (int i = 0; i < m; i++) {
			path[i] = "NULL";
		}
	}
	~BTnodeID() {
		delete[] key;
		delete[] path;
	}
	void DisplayList() {
		cout << "*************Keys*************" << endl;
		for (int i = 0; i < counter; i++) {
			cout << key[i].Id << endl;
		}
		for (int i = 0; i <= counter; i++) {
			cout << path[i] << endl;
		}
		cout << "*************PATHSEND*************" << endl;
	}
	void AddData(Data& toInsert,string previous="NULL") {
		for (int i = 0; i < counter; i++) {
			if (key[i].Id == toInsert.Id)
				return;
		}
		if (counter == 0) {
			counter++;
			key[0] = toInsert;
			path[1] = previous;
			return;
		}
		if (toInsert < key[0]) {
			for (int i = counter; i > 0; i--) {
				key[i] = key[i - 1];
			}
			key[0] = toInsert;
			for (int i = counter + 1; i > 1; i--) {
				path[i] = path[i - 1];
			}
			path[1] = previous;
			counter++;
			return;
		}
		if (toInsert > key[counter - 1]) {
			key[counter] = toInsert;
			counter++;
			path[counter] = previous;
			return;
		}
		int index = 0;
		for (int i = 0; i < counter - 1; i++) {
			if (toInsert > key[i] && toInsert < key[i + 1]) {
				index = i + 1;
				i = counter - 1; // breaks
			}
		}
		for (int i = counter; i > index; i--) {
			key[i] = key[i - 1];
		}
		key[index] = toInsert;
		for (int i = counter + 1; i > index+1; i--) {
			path[i] = path[i - 1];
		}
		path[index + 1] = previous;
		counter++;
	}
	Data RemoveMedian() {
		int median = (m - 2) / 2;
		Data mid;
		mid = key[(m - 2) / 2];
		return mid;
	}
	void sort() {
		Data min;
		int index;
		for (int i = 0; i < counter; i++) {
			min = key[counter - 1];
			index = counter - 1;
			for (int c = i; c < counter; c++) {
				if (key[c] < min) {
					min = key[c];
					index = c;
				}
			}
			key[index] = key[i];
			key[i] = min;
		}
	}
	bool Isleaf() {
		for (int i = 0; i < (m - 1); i++) {
			if (path[i] != "NULL")
				return false;
		}
		return true;
	}
	bool isPresent(Data& toInsert) {
		for (int i = 0; i < counter; i++) {
			if (toInsert.Id == key[i].Id)
				return true;
		}
		return false;
	}
	void RemoveDataLeaf(int todelete,int index) {
		int median = (m - 1) / 2;
		//if (counter > median) {
			for (int i = index; i < (counter - 1); i++) {
				key[i] = key[i + 1];
			}
			counter--;
		//}
	}
	void operator =(BTnodeID& other) {
		for (int i = 0; i < other.counter; i++) {
			this->key[i] = other.key[i];
			this->path[i] = other.path[i];
		}
		this->path[counter] = other.path[counter];
		this->counter = other.counter;
	}
};

struct BTnode {
	Data key;
	BTnode* next;
	BTnode() {
		next = NULL;
	}
};

struct BTNodeInts {
	int* Heading;
	string* path;
	BTnode** head; // for link list & duplication code
	int counter;
	const int m;
	BTNodeInts(int mval):m(mval) {
		counter = 0;
		path = new string[m];
		head = new BTnode*[m - 1];
		Heading = new int[m - 1];
		for (int i = 0; i < m; i++)
			path[i] = "NULL";
		for (int i = 0; i < (m - 1); i++) {
			head[i] = NULL;
			Heading[i] = 0;
		}
	}
	~BTNodeInts() {
		delete[] path;
		BTnode* temp;

		for (int i = 0; i < counter; i++) {
			while (head[i] != NULL) {
				temp = head[i];
				head[i] = head[i]->next;
				delete temp;
			}
		}
		delete[] head;
	}

	void fillList(string& str,int count) {
		BTnode* temp=head[count];
		while (temp != NULL) {
			str += to_string(temp->key.Id);
			str += '%';
			str += to_string(temp->key.Year);
			str += '%';
			str += to_string(temp->key.Deaths);
			str += '%';
			str += temp->key.CauseName113;
			str += '%';
			str += temp->key.CauseName;
			str += '%';
			str += temp->key.State;
			str += '%';
			str += to_string(temp->key.AadRate);
			str += '%';
			temp = temp->next;
		}
	}
	void CreateNewList(Data keyToInsert, int count,string headingType) {
		head[count] = new BTnode();
		head[count]->key = keyToInsert;
		counter++;
		if (headingType == "Year")
			Heading[count] = keyToInsert.Year;
		if (headingType == "Deaths")
			Heading[count] = keyToInsert.Deaths;

	}

	void CreateNewList(BTnode*& NodeToInsert, int count, string headingType) {
		BTnode* temp = NodeToInsert;
		counter++;
		if (headingType == "Year")
			Heading[count] = NodeToInsert->key.Year;
		if (headingType == "Deaths")
			Heading[count] = NodeToInsert->key.Deaths;
		head[count] = new BTnode;
		BTnode* temp2 = head[count];
		temp2->key = temp->key;
		temp = temp->next;
		while (temp != NULL) {
			temp2->next = new BTnode;
			temp2 = temp2->next;
			temp2->key = temp->key;
			temp = temp->next;
		}
	}

	void insertinList(Data keyToInsert, int count, string type) {
		if (head[count] == NULL) {
			head[count] = new BTnode;
			head[count]->key = keyToInsert;
			if(type=="Year")
				Heading[count] = keyToInsert.Year;
			if (type == "Deaths")
				Heading[count] = keyToInsert.Deaths;
			return;
		}

		BTnode* temp = new BTnode;
		temp->key = keyToInsert;
		temp->next = head[count];
		head[count] = temp;
		if(type=="Year")
			Heading[count] = temp->key.Year;
		if (type == "Deaths")
			Heading[count] = temp->key.Deaths;
	}
	void AddListAutoAdjust(BTnode * & ListToInsert,string type,string previouspath) {
		int count = 0;
		int compareVal=0;
		if (type == "Year")
			compareVal = ListToInsert->key.Year;
		if (type == "Deaths")
			compareVal = ListToInsert->key.Deaths;
		while (compareVal > Heading[count] && Heading[count]!=0) {
			count++;
		}
		for (int i = m-2; i > count; i--) {
			head[i] = head[i - 1];
			Heading[i] = Heading[i - 1];
		}
		CreateNewList(ListToInsert,count,type);
		for (int i = m - 1; i > count+1; i--) {
			path[i] = path[i - 1];
		}
		path[count + 1] = previouspath;
	}
	bool Isleaf() {
		for (int i = 0; i < m; i++) {
			if (path[i][0] != 'N')
				return false;
		}
		return true;
	}
	void RemoveMedian(BTnode* &mymid) {
		delete mymid;
		int median = (m - 2) / 2;
		BTnode* temp=head[median];
		mymid = new BTnode;
		BTnode* temp2 = mymid;
		mymid->key = temp->key;
		temp = temp->next;
		while (temp != NULL) {
			temp2->next = new BTnode;
			temp2 = temp2->next;
			temp2->key = temp->key;
			temp = temp->next;
		}
		return;
	}
	void RemoveDataLeaf(int todelete,int index) {
		delete head[index];
		for (int i = index; i < (counter - 1); i++) {
			Heading[i] = Heading[i + 1];
			head[i] = head[i + 1]; // SUBJECT TO CHANGE
		}
		counter--;
	}
	void Display(int index) {
		BTnode* temp = head[index];
		while (temp != NULL) {
			temp->key.Display();
			temp = temp->next;
		}
	}
};

struct BTnodeStr {
	string* Heading;
	string* path;
	BTnode** head;
	int counter;
	const int m;
	BTnodeStr(int mval) :m(mval) {
		counter = 0;
		path = new string[m];
		head = new BTnode * [m - 1];
		Heading = new string[m - 1];
		for (int i = 0; i < m; i++)
			path[i] = "NULL";
		for (int i = 0; i < (m - 1); i++) {
			head[i] = NULL;
			Heading[i] = "0";
		}
	}
	~BTnodeStr() {
		delete[] path;
		BTnode* temp;

		for (int i = 0; i < counter; i++) {
			while (head[i] != NULL) {
				temp = head[i];
				head[i] = head[i]->next;
				delete temp;
			}
		}
		delete[] head;
	}
	void fillList(string& str, int count) {
		BTnode* temp = head[count];
		while (temp != NULL) {
			str += to_string(temp->key.Id);
			str += '%';
			str += to_string(temp->key.Year);
			str += '%';
			str += to_string(temp->key.Deaths);
			str += '%';
			str += temp->key.CauseName113;
			str += '%';
			str += temp->key.CauseName;
			str += '%';
			str += temp->key.State;
			str += '%';
			str += to_string(temp->key.AadRate);
			str += '%';
			temp = temp->next;
		}
	}
	void CreateNewList(Data keyToInsert, int count, string headingType) {
		head[count] = new BTnode();
		head[count]->key = keyToInsert;
		counter++;
		if (headingType == "CauseName113")
			Heading[count] = keyToInsert.CauseName113;
		if (headingType == "CauseName")
			Heading[count] = keyToInsert.CauseName;
		if (headingType == "State")
			Heading[count] = keyToInsert.State;
	}

	void CreateNewList(BTnode*& NodeToInsert, int count, string headingType) {
		BTnode* temp = NodeToInsert;
		counter++;
		if (headingType == "CauseName113")
			Heading[count] = NodeToInsert->key.CauseName113;
		if (headingType == "CauseName")
			Heading[count] = NodeToInsert->key.CauseName;
		if (headingType == "State")
			Heading[count] = NodeToInsert->key.State;
		head[count] = new BTnode;
		BTnode* temp2 = head[count];
		temp2->key = temp->key;
		temp = temp->next;
		while (temp != NULL) {
			temp2->next = new BTnode;
			temp2 = temp2->next;
			temp2->key = temp->key;
			temp = temp->next;
		}
	}

	void insertinList(Data keyToInsert, int count, string type) {
		if (head[count] == NULL) {
			head[count] = new BTnode;
			head[count]->key = keyToInsert;
			if (type == "CauseName113")
				Heading[count] = keyToInsert.CauseName113;
			if (type == "CauseName")
				Heading[count] = keyToInsert.CauseName;
			if (type == "State")
				Heading[count] = keyToInsert.State;
			return;
		}
		BTnode* temp = new BTnode;
		temp->key = keyToInsert;
		temp->next = head[count];
		head[count] = temp;
		if (type == "CauseName113")
			Heading[count] = keyToInsert.CauseName113;
		if (type == "CauseName")
			Heading[count] = keyToInsert.CauseName;
		if (type == "State")
			Heading[count] = keyToInsert.State;
	}
	void AddListAutoAdjust(BTnode*& ListToInsert, string type, string previouspath) {
		int count = 0;
		string compareVal = "0";
		if (type == "CauseName113")
			compareVal = ListToInsert->key.CauseName113;
		if (type == "CauseName")
			compareVal = ListToInsert->key.CauseName;
		if (type == "State")
			compareVal = ListToInsert->key.State;
		while (compareVal > Heading[count] && Heading[count] != "0") {
			count++;
		}
		for (int i = m - 2; i > count; i--) {
			head[i] = head[i - 1];
			Heading[i] = Heading[i - 1];
		}
		CreateNewList(ListToInsert, count, type);
		for (int i = m - 1; i > count + 1; i--) {
			path[i] = path[i - 1];
		}
		path[count + 1] = previouspath;
	}
	bool Isleaf() {
		for (int i = 0; i < m; i++) {
			if (path[i][0] != 'N')
				return false;
		}
		return true;
	}
	void RemoveMedian(BTnode*& mymid) {
		delete mymid;
		int median = (m - 2) / 2;
		BTnode* temp = head[median];
		mymid = new BTnode;
		BTnode* temp2 = mymid;
		mymid->key = temp->key;
		temp = temp->next;
		while (temp != NULL) {
			temp2->next = new BTnode;
			temp2 = temp2->next;
			temp2->key = temp->key;
			temp = temp->next;
		}
		return;
	}
	void RemoveDataLeaf(string todelete, int index) {
		delete head[index];
		for (int i = index; i < (counter - 1); i++) {
			Heading[i] = Heading[i + 1];
			head[i] = head[i + 1]; // SUBJECT TO CHANGE
		}
		counter--;
	}
	void Display(int index) {
		BTnode* temp = head[index];
		while (temp != NULL) {
			temp->key.Display();
			temp = temp->next;
		}
	}
};

struct BTnodeFloat {
	float* Heading;
	string* path;
	BTnode** head;
	int counter;
	const int m;
	BTnodeFloat(int mval) :m(mval) {
		counter = 0;
		path = new string[m];
		head = new BTnode * [m - 1];
		Heading = new float[m - 1];
		for (int i = 0; i < m; i++)
			path[i] = "NULL";
		for (int i = 0; i < (m - 1); i++) {
			head[i] = NULL;
			Heading[i] = 0;
		}
	}
	~BTnodeFloat() {
		delete[] path;
		BTnode* temp;

		for (int i = 0; i < counter; i++) {
			while (head[i] != NULL) {
				temp = head[i];
				head[i] = head[i]->next;
				delete temp;
			}
		}
		delete[] head;
	}
	void fillList(string& str, int count) {
		BTnode* temp = head[count];
		while (temp != NULL) {
			str += to_string(temp->key.Id);
			str += '%';
			str += to_string(temp->key.Year);
			str += '%';
			str += to_string(temp->key.Deaths);
			str += '%';
			str += temp->key.CauseName113;
			str += '%';
			str += temp->key.CauseName;
			str += '%';
			str += temp->key.State;
			str += '%';
			str += to_string(temp->key.AadRate);
			str += '%';
			temp = temp->next;
		}
	}
	void CreateNewList(Data keyToInsert, int count, string headingType) {
		head[count] = new BTnode();
		head[count]->key = keyToInsert;
		counter++;
		Heading[count] = keyToInsert.AadRate;
	}

	void CreateNewList(BTnode*& NodeToInsert, int count, string headingType) {
		BTnode* temp = NodeToInsert;
		counter++;
		Heading[count] = NodeToInsert->key.AadRate;
		head[count] = new BTnode;
		BTnode* temp2 = head[count];
		temp2->key = temp->key;
		temp = temp->next;
		while (temp != NULL) {
			temp2->next = new BTnode;
			temp2 = temp2->next;
			temp2->key = temp->key;
			temp = temp->next;
		}
	}

	void insertinList(Data keyToInsert, int count, string type) {
		if (head[count] == NULL) {
			head[count] = new BTnode;
			head[count]->key = keyToInsert;
			Heading[count] = keyToInsert.AadRate;
			return;
		}

		BTnode* temp = new BTnode;
		temp->key = keyToInsert;
		temp->next = head[count];
		head[count] = temp;
		Heading[count] = keyToInsert.AadRate;
	}
	void AddListAutoAdjust(BTnode*& ListToInsert, string type, string previouspath) {
		int count = 0;
		float compareVal = 0;
		compareVal = ListToInsert->key.AadRate;
		while (compareVal > Heading[count] && Heading[count] != 0) {
			count++;
		}
		for (int i = m - 2; i > count; i--) {
			head[i] = head[i - 1];
			Heading[i] = Heading[i - 1];
		}
		CreateNewList(ListToInsert, count, type);
		for (int i = m - 1; i > count + 1; i--) {
			path[i] = path[i - 1];
		}
		path[count + 1] = previouspath;
	}
	bool Isleaf() {
		for (int i = 0; i < m; i++) {
			if (path[i][0] != 'N')
				return false;
		}
		return true;
	}
	void RemoveMedian(BTnode*& mymid) {
		delete mymid;
		int median = (m - 2) / 2;
		BTnode* temp = head[median];
		mymid = new BTnode;
		BTnode* temp2 = mymid;
		mymid->key = temp->key;
		temp = temp->next;
		while (temp != NULL) {
			temp2->next = new BTnode;
			temp2 = temp2->next;
			temp2->key = temp->key;
			temp = temp->next;
		}
		return;
	}
	void RemoveDataLeaf(float todelete, int index) {
		delete head[index];
		for (int i = index; i < (counter - 1); i++) {
			Heading[i] = Heading[i + 1];
			head[i] = head[i + 1]; // SUBJECT TO CHANGE
		}
		counter--;
	}
	void Display(int index) {
		BTnode* temp = head[index];
		while (temp != NULL) {
			temp->key.Display();
			temp = temp->next;
		}
	}
};

template <typename t>
class BTree {
public:
	t* head;
	int m;
	int nodeCounter;// used for making nodes outside


	Data getMin(string path) {
		Stack<string> mystack;
		mystack.push(path);
		bool found = false;
		string tempPath;
		t* temp;
		if (path == "ROOT")
			temp = head;
		else
			temp = getNodeID(path);
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodeID(tempPath);
			if (temp->Isleaf())
				found = true;
			else {
				mystack.push(temp->path[0]);
			}
		}
		deleteId(temp->key[temp->counter - 1].Id); // cause IT is leaf
		mystack.MakeEmpty();
		return temp->key[temp->counter - 1];
	}
	Data getMax(string path) {
		Stack<string> mystack;
		mystack.push(path);
		bool found = false;
		string tempPath;
		t* temp;
		if (path == "ROOT")
			temp = head;
		else
			temp = getNodeID(path);
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodeID(tempPath);
			if (temp->Isleaf())
				found = true;
			else {
				mystack.push(temp->path[temp->counter]);
			}
		}
		deleteId(temp->key[0].Id); // cause IT is leaf
		mystack.MakeEmpty();
		return temp->key[0];

	}
	BTnode*& getMinListInt(string path, string type) {
		Stack<string> mystack;
		mystack.push(path);
		bool found = false;
		string tempPath;
		t* temp;
		if (path == "ROOT")
			temp = head;
		else
			temp = getNodeOthers(path, type);
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodeOthers(tempPath, type);
			if (temp->Isleaf())
				found = true;
			else {
				mystack.push(temp->path[0]);
			}
		}
		deleteInts(temp->Heading[temp->counter - 1], type); // cause IT is leaf
		mystack.MakeEmpty();
		return temp->head[temp->counter - 1];
	}
	BTnode*& getMaxListInt(string path, string type) {
		Stack<string> mystack;
		mystack.push(path);
		bool found = false;
		string tempPath;
		t* temp;
		if (path == "ROOT")
			temp = head;
		else
			temp = getNodeOthers(path, type);
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodeOthers(tempPath, type);
			if (temp->Isleaf())
				found = true;
			else {
				mystack.push(temp->path[temp->counter]);
			}
		}
		deleteInts(temp->Heading[0], type); // cause IT is leaf
		mystack.MakeEmpty();
		return temp->head[0];
	}
	BTnode*& getMinListStr(string path, string type) {
		Stack<string> mystack;
		mystack.push(path);
		bool found = false;
		string tempPath;
		t* temp;
		if (path == "ROOT")
			temp = head;
		else
			temp = getNodeStr(path, type);
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodeStr(tempPath, type);
			if (temp->Isleaf())
				found = true;
			else {
				mystack.push(temp->path[0]);
			}
		}
		deleteStr(temp->Heading[temp->counter - 1], type); // cause IT is leaf
		mystack.MakeEmpty();
		return temp->head[temp->counter - 1];
	}
	BTnode*& getMaxListStr(string path, string type) {
		Stack<string> mystack;
		mystack.push(path);
		bool found = false;
		string tempPath;
		t* temp;
		if (path == "ROOT")
			temp = head;
		else
			temp = getNodeStr(path, type);
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodeStr(tempPath, type);
			if (temp->Isleaf())
				found = true;
			else {
				mystack.push(temp->path[temp->counter]);
			}
		}
		deleteStr(temp->Heading[0], type); // cause IT is leaf
		mystack.MakeEmpty();
		return temp->head[0];
	}
	BTnode*& getMinListFlt(string path, string type) {
		Stack<string> mystack;
		mystack.push(path);
		bool found = false;
		string tempPath;
		t* temp;
		if (path == "ROOT")
			temp = head;
		else
			temp = getNodefloat(path, type);
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodefloat(tempPath, type);
			if (temp->Isleaf())
				found = true;
			else {
				mystack.push(temp->path[0]);
			}
		}
		deleteFlt(temp->Heading[temp->counter - 1], type); // cause IT is leaf
		mystack.MakeEmpty();
		return temp->head[temp->counter - 1];
	}
	BTnode*& getMaxListFlt(string path, string type) {
		Stack<string> mystack;
		mystack.push(path);
		bool found = false;
		string tempPath;
		t* temp;
		if (path == "ROOT")
			temp = head;
		else
			temp = getNodefloat(path, type);
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodefloat(tempPath, type);
			if (temp->Isleaf())
				found = true;
			else {
				mystack.push(temp->path[temp->counter]);
			}
		}
		deleteFlt(temp->Heading[0], type); // cause IT is leaf
		mystack.MakeEmpty();
		return temp->head[0];
	}

	void CopyList(BTnode*& toInsert, BTnode*& median) {
		BTnode* temp1 = toInsert;
		BTnode* temp2 = median;
		temp1->key = temp2->key;
		temp2 = temp2->next;
		while (temp2 != NULL) {
			temp1->next = new BTnode;
			temp1 = temp1->next;
			temp1->key = temp2->key;
			temp2 = temp2->next;
		}
	}
	void SplitNodes(Data& median, Data& keyToInsert, t*& temp2, string firstPath, string previous) {
		string path;
		int count = 0;
		t* firstHalf = new t(m);
		bool below = false;
		int newVal = 0;
		while (temp2->key[count] < median)
		{
			if (keyToInsert < temp2->key[count] && !below) {
				firstHalf->AddData(keyToInsert, previous);
				below = true;
				newVal = count;
			}
			firstHalf->AddData(temp2->key[count]);
			count++;
		}
		if (!below) {
			for (int i = 0; i <= count; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
		}
		else {
			for (int i = 0; i <= newVal; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
			for (int i = newVal + 2; i <= count + 1; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
		}
		setNodeID(firstPath, firstHalf);
		delete firstHalf;

		t* secondHalf = new t(m);
		nodeCounter++;
		MakePathID(path, nodeCounter);
		int index = 0;
		if (!below) {
			for (int i = count + 1; i < m - 1; i++, index++) {
				if (keyToInsert < temp2->key[i] && !below) {
					below = true;
					secondHalf->AddData(temp2->key[i], previous);
					newVal = index;
				}
				secondHalf->AddData(temp2->key[i]);
			}
			index = 0;
			if (!below) {
				for (int i = count + 1; i < m; i++, index++) {
					secondHalf->path[index] = temp2->path[i];
				}
				secondHalf->AddData(keyToInsert, previous);
			}
		}
		else {
			index = 0;
			for (int i = count + 1; i < m - 1; i++) {
				secondHalf->AddData(temp2->key[i]);
			}
			for (int i = count + 1; i < m; i++, index++) {
				secondHalf->path[index] = temp2->path[i];
			}
		}
		setNodeID(path, secondHalf);
		delete secondHalf;
	}
	void SplitRoot(Data& median, Data& keyToInsert, string previous = "NULL") {
		string path;
		nodeCounter++;
		MakePathID(path, nodeCounter);
		int count = 0;
		t* firstHalf = new t(m);
		bool below = false;
		int newVal = 0;
		while (head->key[count] < median)
		{
			if (keyToInsert < head->key[count] && !below) {
				firstHalf->AddData(keyToInsert, previous);
				below = true;
				newVal = count;
			}
			firstHalf->AddData(head->key[count]);
			count++;
		}
		if (!below) {
			for (int i = 0; i <= count; i++) {
				firstHalf->path[i] = head->path[i];
			}
		}
		else {
			for (int i = 0; i <= newVal; i++) {
				firstHalf->path[i] = head->path[i];
			}
			for (int i = newVal + 2; i <= count + 1; i++) {
				firstHalf->path[i] = head->path[i];
			}
		}
		setNodeID(path, firstHalf);
		delete firstHalf;

		t* secondHalf = new t(m);
		nodeCounter++;
		MakePathID(path, nodeCounter);
		int index = 0;
		if (!below) {
			for (int i = count + 1; i < m - 1; i++, index++) {
				if (keyToInsert < head->key[i] && !below) {
					below = true;
					secondHalf->AddData(head->key[i], previous);
					newVal = index;
				}
				secondHalf->AddData(head->key[i]);
			}
			secondHalf->path[newVal] = previous;
			if (!below) {
				index = 0;
				for (int i = count + 1; i < m; i++, index++) {
					secondHalf->path[index] = head->path[i];
				}
				secondHalf->AddData(keyToInsert, previous);
			}
		}
		else {
			index = 0;
			for (int i = count + 1; i < m - 1; i++) {
				secondHalf->AddData(head->key[i]);
			}
			for (int i = count + 1; i < m; i++, index++) {
				secondHalf->path[index] = head->path[i];
			}
		}
		setNodeID(path, secondHalf);
		delete secondHalf;
	}
	void SplitNodeInts(Data& median, t*& temp2, string firstPath, string previous, BTnode*& ListToInsert, string type) {
		string path;
		int count = 0;
		int valNew = 0;
		t* firstHalf = new t(m);
		bool below = false;
		int compareValmid = 0;
		int compareValList = 0;
		if (type == "Year") {
			compareValmid = median.Year;
			compareValList = ListToInsert->key.Year;
		}
		if (type == "Deaths") {
			compareValmid = median.Deaths;
			compareValList = ListToInsert->key.Deaths;
		}
		while (temp2->Heading[count] < compareValmid) {
			if (compareValList < temp2->Heading[count] && !below) {
				firstHalf->CreateNewList(ListToInsert, firstHalf->counter, type);
				valNew = count;
				below = true;
			}
			firstHalf->CreateNewList(temp2->head[count], firstHalf->counter, type);
			temp2->head[count] = NULL;
			count++;
		}
		if (below) {
			for (int i = 0; i <= valNew; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
			firstHalf->path[valNew + 1] = previous;
			for (int i = valNew + 2; i <= count + 1; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
		}
		else {
			for (int i = 0; i <= count; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
		}
		setNodeOthers(firstPath, firstHalf, type);
		delete firstHalf;
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		t* secondHalf = new t(m);
		int index = 0;
		if (!below) {
			for (int i = count + 1; i < (m - 1); i++) {
				if (compareValList < temp2->Heading[i] && !below) {
					secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
					valNew = i;
					below = true;
				}
				secondHalf->CreateNewList(temp2->head[i], secondHalf->counter, type);
				temp2->head[i] = NULL;
			}
			if (!below) {
				secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
				valNew = secondHalf->counter;
				below = true;
			}
			below = false;
			for (int i = count + 1; i < m; i++, index++) {
				if (index == valNew) {
					secondHalf->path[index] = previous;
					index++;
					below = true;
				}
				secondHalf->path[index] = temp2->path[i];
			}
			if (!below) {
				secondHalf->path[secondHalf->counter] = previous;
			}
			setNodeOthers(path, secondHalf, type);
			delete secondHalf;
		}
		else {
			for (int i = count + 1; i < (m - 1); i++) {
				secondHalf->CreateNewList(temp2->head[i], secondHalf->counter, type);
				temp2->head[i] = NULL;
			}
			for (int i = count + 1; i < m; i++, index++) {
				secondHalf->path[index] = temp2->path[i];
			}
			setNodeOthers(path, secondHalf, type);
			delete secondHalf;
		}
	}
	void SplitRootInts(Data& median, BTnode*& ListToInsert, string previous, string type) {
		string path;
		int count = 0;
		int valNew = 0;
		t* firstHalf = new t(m);
		bool below = false;
		int compareValmid = 0;
		int compareValList = 0;
		if (type == "Year") {
			compareValmid = median.Year;
			compareValList = ListToInsert->key.Year;
		}
		if (type == "Deaths") {
			compareValmid = median.Deaths;
			compareValList = ListToInsert->key.Deaths;
		}
		while (head->Heading[count] < compareValmid) {
			if (compareValList < head->Heading[count] && !below) {
				firstHalf->CreateNewList(ListToInsert, firstHalf->counter, type);
				valNew = count;
				below = true;
			}
			firstHalf->CreateNewList(head->head[count], firstHalf->counter, type);
			head->head[count] = NULL;
			count++;
		}
		if (below) {
			for (int i = 0; i <= valNew; i++) {
				firstHalf->path[i] = head->path[i];
			}
			firstHalf->path[valNew + 1] = previous;
			for (int i = valNew + 2; i <= count + 1; i++) {
				firstHalf->path[i] = head->path[i];
			}
		}
		else {
			for (int i = 0; i <= count; i++) {
				firstHalf->path[i] = head->path[i];
			}
		}
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		setNodeOthers(path, firstHalf, type);
		delete firstHalf;
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		t* secondHalf = new t(m);
		int index = 0;
		if (!below) {
			for (int i = count + 1; i < (m - 1); i++) {
				if (compareValList < head->Heading[i] && !below) {
					secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
					valNew = i;
					below = true;
				}
				secondHalf->CreateNewList(head->head[i], secondHalf->counter, type);
				head->head[i] = NULL;
			}
			if (!below) {
				secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
				valNew = secondHalf->counter;
				below = true;
			}
			below = false;
			for (int i = count + 1; i < m; i++, index++) {
				if (index == valNew) {
					secondHalf->path[index] = previous;
					index++;
					below = true;
				}
				secondHalf->path[index] = head->path[i];
			}
			if (!below)
				secondHalf->path[secondHalf->counter] = previous;
			setNodeOthers(path, secondHalf, type);
			delete secondHalf;
		}
		else {
			for (int i = count + 1; i < (m - 1); i++) {
				secondHalf->CreateNewList(head->head[i], secondHalf->counter, type);
				head->head[i] = NULL;
			}
			for (int i = count + 1; i < m; i++, index++) {
				secondHalf->path[index] = head->path[i];
			}
			setNodeOthers(path, secondHalf, type);
			delete secondHalf;
		}
	}
	void SplitNodesStr(Data& median, t*& temp2, string firstPath, string previous, BTnode*& ListToInsert, string type) {
		string path;
		int count = 0;
		int valNew = 0;
		t* firstHalf = new t(m);
		bool below = false;
		string compareValmid;
		string compareValList;
		if (type == "CauseName113") {
			compareValmid = median.CauseName113;
			compareValList = ListToInsert->key.CauseName113;
		}
		if (type == "CauseName") {
			compareValmid = median.CauseName;
			compareValList = ListToInsert->key.CauseName;
		}
		if (type == "State") {
			compareValmid = median.State;
			compareValList = ListToInsert->key.State;
		}
		while (temp2->Heading[count] < compareValmid) {
			if (compareValList < temp2->Heading[count] && !below) {
				firstHalf->CreateNewList(ListToInsert, firstHalf->counter, type);
				valNew = count;
				below = true;
			}
			firstHalf->CreateNewList(temp2->head[count], firstHalf->counter, type);
			temp2->head[count] = NULL;
			count++;
		}
		if (below) {
			for (int i = 0; i <= valNew; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
			firstHalf->path[valNew + 1] = previous;
			for (int i = valNew + 2; i <= count + 1; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
		}
		else {
			for (int i = 0; i <= count; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
		}
		setNodeStr(firstPath, firstHalf, type);
		delete firstHalf;
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		t* secondHalf = new t(m);
		int index = 0;
		if (!below) {
			for (int i = count + 1; i < (m - 1); i++) {
				if (compareValList < temp2->Heading[i] && !below) {
					secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
					valNew = i;
					below = true;
				}
				secondHalf->CreateNewList(temp2->head[i], secondHalf->counter, type);
				temp2->head[i] = NULL;
			}
			if (!below) {
				secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
				valNew = secondHalf->counter;
				below = true;
			}
			below = false;
			for (int i = count + 1; i < m; i++, index++) {
				if (index == valNew) {
					secondHalf->path[index] = previous;
					index++;
					below = true;
				}
				secondHalf->path[index] = temp2->path[i];
			}
			if (!below) {
				secondHalf->path[secondHalf->counter] = previous;
			}
			setNodeStr(path, secondHalf, type);
			delete secondHalf;
		}
		else {
			for (int i = count + 1; i < (m - 1); i++) {
				secondHalf->CreateNewList(temp2->head[i], secondHalf->counter, type);
				temp2->head[i] = NULL;
			}
			for (int i = count + 1; i < m; i++, index++) {
				secondHalf->path[index] = temp2->path[i];
			}
			setNodeStr(path, secondHalf, type);
			delete secondHalf;
		}
	}
	void SplitRootStr(Data& median, BTnode*& ListToInsert, string previous, string type) {
		string path;
		int count = 0;
		int valNew = 0;
		t* firstHalf = new t(m);
		bool below = false;
		string compareValmid;
		string compareValList;
		if (type == "CauseName113") {
			compareValmid = median.CauseName113;
			compareValList = ListToInsert->key.CauseName113;
		}
		if (type == "CauseName") {
			compareValmid = median.CauseName;
			compareValList = ListToInsert->key.CauseName;
		}
		if (type == "State") {
			compareValmid = median.State;
			compareValList = ListToInsert->key.State;
		}
		while (head->Heading[count] < compareValmid) {
			if (compareValList < head->Heading[count] && !below) {
				firstHalf->CreateNewList(ListToInsert, firstHalf->counter, type);
				valNew = count;
				below = true;
			}
			firstHalf->CreateNewList(head->head[count], firstHalf->counter, type);
			head->head[count] = NULL;
			count++;
		}
		if (below) {
			for (int i = 0; i <= valNew; i++) {
				firstHalf->path[i] = head->path[i];
			}
			firstHalf->path[valNew + 1] = previous;
			for (int i = valNew + 2; i <= count + 1; i++) {
				firstHalf->path[i] = head->path[i];
			}
		}
		else {
			for (int i = 0; i <= count; i++) {
				firstHalf->path[i] = head->path[i];
			}
		}
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		setNodeStr(path, firstHalf, type);
		delete firstHalf;
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		t* secondHalf = new t(m);
		int index = 0;
		if (!below) {
			for (int i = count + 1; i < (m - 1); i++) {
				if (compareValList < head->Heading[i] && !below) {
					secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
					valNew = i;
					below = true;
				}
				secondHalf->CreateNewList(head->head[i], secondHalf->counter, type);
				head->head[i] = NULL;
			}
			if (!below) {
				secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
				valNew = secondHalf->counter;
				below = true;
			}
			below = false;
			for (int i = count + 1; i < m; i++, index++) {
				if (index == valNew) {
					secondHalf->path[index] = previous;
					index++;
					below = true;
				}
				secondHalf->path[index] = head->path[i];
			}
			if (!below)
				secondHalf->path[secondHalf->counter] = previous;
			setNodeStr(path, secondHalf, type);
			delete secondHalf;
		}
		else {
			for (int i = count + 1; i < (m - 1); i++) {
				secondHalf->CreateNewList(head->head[i], secondHalf->counter, type);
				head->head[i] = NULL;
			}
			for (int i = count + 1; i < m; i++, index++) {
				secondHalf->path[index] = head->path[i];
			}
			setNodeStr(path, secondHalf, type);
			delete secondHalf;
		}
	}
	void SplitNodesFlt(Data& median, t*& temp2, string firstPath, string previous, BTnode*& ListToInsert, string type) {
		string path;
		int count = 0;
		int valNew = 0;
		t* firstHalf = new t(m);
		bool below = false;
		float compareValmid;
		float compareValList;

		compareValmid = median.AadRate;
		compareValList = ListToInsert->key.AadRate;

		while (temp2->Heading[count] < compareValmid) {
			if (compareValList < temp2->Heading[count] && !below) {
				firstHalf->CreateNewList(ListToInsert, firstHalf->counter, type);
				valNew = count;
				below = true;
			}
			firstHalf->CreateNewList(temp2->head[count], firstHalf->counter, type);
			temp2->head[count] = NULL;
			count++;
		}
		if (below) {
			for (int i = 0; i <= valNew; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
			firstHalf->path[valNew + 1] = previous;
			for (int i = valNew + 2; i <= count + 1; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
		}
		else {
			for (int i = 0; i <= count; i++) {
				firstHalf->path[i] = temp2->path[i];
			}
		}
		setNodeOthers(firstPath, firstHalf, type);
		delete firstHalf;
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		t* secondHalf = new t(m);
		int index = 0;
		if (!below) {
			for (int i = count + 1; i < (m - 1); i++) {
				if (compareValList < temp2->Heading[i] && !below) {
					secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
					valNew = i;
					below = true;
				}
				secondHalf->CreateNewList(temp2->head[i], secondHalf->counter, type);
				temp2->head[i] = NULL;
			}
			if (!below) {
				secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
				valNew = secondHalf->counter;
				below = true;
			}
			below = false;
			for (int i = count + 1; i < m; i++, index++) {
				if (index == valNew) {
					secondHalf->path[index] = previous;
					index++;
					below = true;
				}
				secondHalf->path[index] = temp2->path[i];
			}
			if (!below) {
				secondHalf->path[secondHalf->counter] = previous;
			}
			setNodeOthers(path, secondHalf, type);
			delete secondHalf;
		}
		else {
			for (int i = count + 1; i < (m - 1); i++) {
				secondHalf->CreateNewList(temp2->head[i], secondHalf->counter, type);
				temp2->head[i] = NULL;
			}
			for (int i = count + 1; i < m; i++, index++) {
				secondHalf->path[index] = temp2->path[i];
			}
			setNodeOthers(path, secondHalf, type);
			delete secondHalf;
		}
	}
	void SplitRootFlt(Data& median, BTnode*& ListToInsert, string previous, string type) {
		string path;
		int count = 0;
		int valNew = 0;
		t* firstHalf = new t(m);
		bool below = false;
		float compareValmid;
		float compareValList;
		compareValmid = median.AadRate;
		compareValList = ListToInsert->key.AadRate;
		while (head->Heading[count] < compareValmid) {
			if (compareValList < head->Heading[count] && !below) {
				firstHalf->CreateNewList(ListToInsert, firstHalf->counter, type);
				valNew = count;
				below = true;
			}
			firstHalf->CreateNewList(head->head[count], firstHalf->counter, type);
			head->head[count] = NULL;
			count++;
		}
		if (below) {
			for (int i = 0; i <= valNew; i++) {
				firstHalf->path[i] = head->path[i];
			}
			firstHalf->path[valNew + 1] = previous;
			for (int i = valNew + 2; i <= count + 1; i++) {
				firstHalf->path[i] = head->path[i];
			}
		}
		else {
			for (int i = 0; i <= count; i++) {
				firstHalf->path[i] = head->path[i];
			}
		}
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		setNodeOthers(path, firstHalf, type);
		delete firstHalf;
		nodeCounter++;
		MakePathInts(path, nodeCounter, type);
		t* secondHalf = new t(m);
		int index = 0;
		if (!below) {
			for (int i = count + 1; i < (m - 1); i++) {
				if (compareValList < head->Heading[i] && !below) {
					secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
					valNew = i;
					below = true;
				}
				secondHalf->CreateNewList(head->head[i], secondHalf->counter, type);
				head->head[i] = NULL;
			}
			if (!below) {
				secondHalf->CreateNewList(ListToInsert, secondHalf->counter, type);
				valNew = secondHalf->counter;
				below = true;
			}
			below = false;
			for (int i = count + 1; i < m; i++, index++) {
				if (index == valNew) {
					secondHalf->path[index] = previous;
					index++;
					below = true;
				}
				secondHalf->path[index] = head->path[i];
			}
			if (!below)
				secondHalf->path[secondHalf->counter] = previous;
			setNodeOthers(path, secondHalf, type);
			delete secondHalf;
		}
		else {
			for (int i = count + 1; i < (m - 1); i++) {
				secondHalf->CreateNewList(head->head[i], secondHalf->counter, type);
				head->head[i] = NULL;
			}
			for (int i = count + 1; i < m; i++, index++) {
				secondHalf->path[index] = head->path[i];
			}
			setNodeOthers(path, secondHalf, type);
			delete secondHalf;
		}
	}

	t* getNodeID(string path) {
		string tempstr;
		ifstream myfile(path);
		getline(myfile, tempstr);
		myfile.close();
		t* temp = new t(m);
		string str = "";
		int count = 0;

		while (tempstr[count] != '$') {
			str += tempstr[count];
			count++;
		}
		temp->counter = stoi(str);
		count++;
		for (int i = 0; i < temp->counter; i++) {
			str = "";
			while (tempstr[count] != '$') {
				str += tempstr[count];
				count++;
			}
			count++;
			temp->key[i].Id = stoi(str);
			str = "";
			while (tempstr[count] != '$') {
				str += tempstr[count];
				count++;
			}
			count++;
			temp->key[i].Year = stoi(str);
			str = "";
			while (tempstr[count] != '$') {
				str += tempstr[count];
				count++;
			}
			count++;
			temp->key[i].Deaths = stoi(str);
			str = "";
			while (tempstr[count] != '$') {
				str += tempstr[count];
				count++;
			}
			count++;
			temp->key[i].CauseName113 = str;
			str = "";
			while (tempstr[count] != '$') {
				str += tempstr[count];
				count++;
			}
			count++;
			temp->key[i].CauseName = str;
			str = "";
			while (tempstr[count] != '$') {
				str += tempstr[count];
				count++;
			}
			count++;
			temp->key[i].State = str;
			str = "";
			while (tempstr[count] != '$') {
				str += tempstr[count];
				count++;
			}
			count++;
			temp->key[i].AadRate = stof(str);
		}
		for (int i = 0; i < temp->counter; i++) {
			str = "";
			while (tempstr[count] != '$') {
				str += tempstr[count];
				count++;
			}
			count++;
			temp->path[i] = str;
		}
		str = "";
		for (int i = count; count < tempstr.length(); count++)
			str += tempstr[count];
		temp->path[temp->counter] = str;
		return temp;
	}
	void setNodeID(string path, t*& tempNode) {
		string str = "";
		str += to_string(tempNode->counter);
		str += "$";
		for (int i = 0; i < tempNode->counter; i++) {
			str += to_string(tempNode->key[i].Id);
			str += "$";
			str += to_string(tempNode->key[i].Year);
			str += "$";
			str += to_string(tempNode->key[i].Deaths);
			str += "$";;
			str += tempNode->key[i].CauseName113;
			str += "$";
			str += tempNode->key[i].CauseName;
			str += "$";
			str += tempNode->key[i].State;
			str += "$";
			str += to_string(tempNode->key[i].AadRate);
			str += "$";
		}
		for (int i = 0; i < tempNode->counter; i++) {
			str += tempNode->path[i];
			str += "$";
		}
		str += tempNode->path[tempNode->counter];
		ofstream myfile(path);
		myfile << str;
		myfile.close();
	}
	void setNodeOthers(string path, t*& tempNode, string type) {
		string str = "";
		str += to_string(tempNode->counter);
		str += "$";

		for (int i = 0; i < tempNode->counter; i++) {
			str += to_string(tempNode->Heading[i]);
			str += "$";
			tempNode->fillList(str, i);
			str += "$";
		}
		bool nulcase = false;
		bool pathcase = false;
		for (int i = 0; i < tempNode->counter; i++) {
			if (tempNode->path[i] == "NULL")
				nulcase = true;
			if (tempNode->path[i] != "NULL")
				pathcase = true;
			str += tempNode->path[i];
			str += "$";
		}
		if (tempNode->path[tempNode->counter] == "NULL")
			nulcase = true;
		if (tempNode->path[tempNode->counter] != "NULL")
			pathcase = true;
		str += tempNode->path[tempNode->counter];
		ofstream myfile(path);
		myfile << str;
		myfile.close();
		if (nulcase && pathcase)
			cout << str << endl;
		//cout << "SETNODE =  " << str << endl;
	}
	void setNodeStr(string path, t*& tempNode, string type) {
		string str = "";
		str += to_string(tempNode->counter);
		str += "$";

		for (int i = 0; i < tempNode->counter; i++) {
			str += tempNode->Heading[i];
			str += "$";
			tempNode->fillList(str, i);
			str += "$";
		}
		bool nulcase = false;
		bool pathcase = false;
		for (int i = 0; i < tempNode->counter; i++) {
			if (tempNode->path[i] == "NULL")
				nulcase = true;
			if (tempNode->path[i] != "NULL")
				pathcase = true;
			str += tempNode->path[i];
			str += "$";
		}
		if (tempNode->path[tempNode->counter] == "NULL")
			nulcase = true;
		if (tempNode->path[tempNode->counter] != "NULL")
			pathcase = true;
		str += tempNode->path[tempNode->counter];
		ofstream myfile(path);
		myfile << str;
		myfile.close();
		if (nulcase && pathcase)
			cout << str << endl;
	}
	t* getNodeStr(string path, string type) {
		string str;
		string tempstr;
		ifstream myfile(path);
		getline(myfile, str);
		myfile.close();
		t* node = new t(m);
		int count = 0;
		while (str[count] != '$') {
			tempstr += str[count];
			count++;
		}
		count++;
		node->counter = stoi(tempstr);
		tempstr = "";
		Data key;
		for (int i = 0; i < node->counter; i++) {
			tempstr = "";
			while (str[count] != '$') {
				tempstr += str[count];
				count++;
			}
			count++;
			node->Heading[i] = tempstr;
			while (str[count] != '$') {
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Id = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Year = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Deaths = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.CauseName113 = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.CauseName = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.State = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.AadRate = stof(tempstr);
				node->insertinList(key, i, type);
			}
			count++;
			tempstr = "";
		}
		for (int i = 0; i < node->counter; i++) {
			tempstr = "";
			while (str[count] != '$') {
				tempstr += str[count];
				count++;
			}
			node->path[i] = tempstr;
			count++;
		}
		tempstr = "";
		while (count < str.length()) {
			tempstr += str[count];
			count++;
		}
		count++;
		node->path[node->counter] = tempstr;
		return node;
	}
	t* getNodeOthers(string path, string type) {
		string str;
		string tempstr;
		ifstream myfile(path);
		getline(myfile, str);
		myfile.close();
		t* node = new t(m);
		int count = 0;
		while (str[count] != '$') {
			tempstr += str[count];
			count++;
		}
		count++;
		node->counter = stoi(tempstr);
		tempstr = "";
		Data key;
		for (int i = 0; i < node->counter; i++) {
			tempstr = "";
			while (str[count] != '$') {
				tempstr += str[count];
				count++;
			}
			count++;
			node->Heading[i] = stoi(tempstr);
			while (str[count] != '$') {
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Id = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Year = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Deaths = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.CauseName113 = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.CauseName = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.State = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.AadRate = stof(tempstr);
				node->insertinList(key, i, type);
			}
			count++;
			tempstr = "";
		}
		for (int i = 0; i < node->counter; i++) {
			tempstr = "";
			while (str[count] != '$') {
				tempstr += str[count];
				count++;
			}
			node->path[i] = tempstr;
			count++;
		}
		tempstr = "";
		while (count < str.length()) {
			tempstr += str[count];
			count++;
		}
		count++;
		node->path[node->counter] = tempstr;
		return node;
	}
	t* getNodefloat(string path, string type) {
		string str;
		string tempstr;
		ifstream myfile(path);
		getline(myfile, str);
		myfile.close();
		t* node = new t(m);
		int count = 0;
		while (str[count] != '$') {
			tempstr += str[count];
			count++;
		}
		count++;
		node->counter = stoi(tempstr);
		tempstr = "";
		Data key;
		for (int i = 0; i < node->counter; i++) {
			tempstr = "";
			while (str[count] != '$') {
				tempstr += str[count];
				count++;
			}
			count++;
			node->Heading[i] = stof(tempstr);
			while (str[count] != '$') {
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Id = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Year = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.Deaths = stoi(tempstr);
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.CauseName113 = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.CauseName = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.State = tempstr;
				tempstr = "";
				while (str[count] != '%') {
					tempstr += str[count];
					count++;
				}
				count++;
				key.AadRate = stof(tempstr);
				node->insertinList(key, i, type);
			}
			count++;
			tempstr = "";
		}
		for (int i = 0; i < node->counter; i++) {
			tempstr = "";
			while (str[count] != '$') {
				tempstr += str[count];
				count++;
			}
			node->path[i] = tempstr;
			count++;
		}
		tempstr = "";
		while (count < str.length()) {
			tempstr += str[count];
			count++;
		}
		count++;
		node->path[node->counter] = tempstr;
		return node;
	}
	void MakePathID(string& path, int mycount) {
		path = "";
		path = "BTree/BTreeID/node";
		path += to_string(mycount);
		path += ".txt";
	}
	void MakePathInts(string& path, int mycount, string type) {
		path = "";
		path = "BTree/BTree";
		path += type;
		path += "/node";
		path += to_string(mycount);
		path += ".txt";
	}

public:
	BTree(int mVal) {
		head = NULL;
		m = mVal;
		nodeCounter = 0;
	}
	void insertById(Data keyToInsert) { // type tells the type of indexing

		// CASE IF NO DATA EXISTS IN THE BTREE
		if (head == NULL) {
			head = new t(m);
			head->key[0] = keyToInsert;
			head->counter++;
			return;
		}
		// FINDING THE LEAF
		Stack<string> mystack;
		t* temp = NULL;
		string tempPath;
		bool found = false;
		mystack.push("ROOT");
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else
				temp = getNodeID(tempPath);
			if (temp->Isleaf()) { // found leaf;
				found = true;
			}
			else {
				if (keyToInsert < temp->key[0])
					mystack.push(temp->path[0]);
				else {
					if (keyToInsert > temp->key[temp->counter - 1])
						mystack.push(temp->path[temp->counter]);
					else {
						if (temp->counter == 1 && temp->key[0].Id == keyToInsert.Id) {
							return;
						}
						else {
							for (int i = 0; i < temp->counter - 1; i++) {
								if (keyToInsert.Id == temp->key[i + 1].Id || keyToInsert.Id == temp->key[i].Id) {
									mystack.MakeEmpty();
									if (tempPath != "ROOT") {
										setNodeID(tempPath, temp);
										delete temp;
									}
									return;
								}
								if (keyToInsert<temp->key[i + 1] && keyToInsert>temp->key[i]) {
									mystack.push(temp->path[i + 1]);
									i = temp->counter + 1;//break the loop
								}
							}
						}
					}
				}
			}
		} // when loop ends we have found the leaf node

		for (int i = 0; i < temp->counter; i++) {
			if (temp->key[i].Id == keyToInsert.Id) {
				mystack.MakeEmpty();
				return; // duplicate value
			}
		}
		if (temp->counter < (m - 1)) { // there is room for key to be added in leaf
			temp->AddData(keyToInsert);
			if (tempPath!="ROOT")
				setNodeID(tempPath, temp);
		}
		else { // leaf is full and needs splitting
			Data median;
			string mpath;
			string pPath = "NULL";
			found = false;
			while (!found) {
				tempPath = mystack.top();
				mystack.pop();
				if (tempPath == "ROOT") {
					temp = head;
					if (temp->counter < (m - 1)) {
						found = true;
						temp->AddData(keyToInsert,pPath);
						mystack.MakeEmpty();
						return;
					}
					else {
						found = true;
						t* temp2 = new t(m);
						int middle = (m - 2) / 2;
						temp2->key[0] = head->key[middle];
						temp2->counter++;
						SplitRoot(temp2->key[0], keyToInsert, pPath); // splitting heads and making files
						delete head;// previous head now stored in the files
						head = temp2;
						MakePathID(mpath, nodeCounter - 1);
						head->path[0] = mpath;
						MakePathID(mpath, nodeCounter);
						head->path[1] = mpath;
						return;
					}
				}
				else {
					temp = getNodeID(tempPath);
					if (temp->counter < (m - 1)) {
						found = true;
						MakePathID(mpath, nodeCounter);
						temp->AddData(keyToInsert, mpath);
						setNodeID(tempPath, temp);
						mystack.MakeEmpty();
						return;
					}
					else {
						median.MakeSame(temp->RemoveMedian());
						SplitNodes(median, keyToInsert,temp, tempPath, pPath);
						MakePathID(pPath, nodeCounter);
						keyToInsert = median; 
					}
				}
			}
		}
	}
	void insertByints(Data keyToInsert,string type) {
		if (head == NULL) {
			head = new t(m);
			head->CreateNewList(keyToInsert,0,type);
			return;
		}
		int compareVal;
		if (type == "Year")
			compareVal = keyToInsert.Year;
		if (type == "Deaths")
			compareVal = keyToInsert.Deaths;

		// finding the leaf
		Stack<string> mystack;
		t* temp = NULL;
		string tempPath="ROOT";
		bool found = false;
		mystack.push("ROOT");
		while (!found) {
			if (tempPath != "ROOT") {
				delete temp;
			}
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				temp = getNodeOthers(tempPath, type);
			}
			if (temp->Isleaf()) { // found leaf;
				found = true;
			}
			else {
				if (compareVal < temp->Heading[0]) {
					mystack.push(temp->path[0]);
				}
				else {
					if (compareVal > temp->Heading[temp->counter - 1]) {
						mystack.push(temp->path[temp->counter]);
					}
					else {
						if (temp->counter == 1 && temp->Heading[0]==compareVal) {
							temp->insertinList(keyToInsert,0,type);
							if (tempPath != "ROOT") {
								setNodeOthers(tempPath, temp,type);
								delete temp;
							}
							mystack.MakeEmpty();
							return;
						}
						else {
							for (int i = 0; i < temp->counter - 1; i++) {
								if (compareVal == temp->Heading[i]) {
									found = true;
									temp->insertinList(keyToInsert, i, type);
									if (tempPath != "ROOT") {
										setNodeOthers(tempPath, temp,type);
										delete temp;
									}
									mystack.MakeEmpty();
									return;
								}
								if (compareVal == temp->Heading[i + 1]) {
									found = true;
									temp->insertinList(keyToInsert, i + 1, type);
									if (tempPath != "ROOT") {
										setNodeOthers(tempPath, temp,type);
										delete temp;
									}
									mystack.MakeEmpty();
									return;
								}
								if (compareVal<temp->Heading[i + 1] && compareVal>temp->Heading[i]) {
									mystack.push(temp->path[i + 1]);
									i = temp->counter + 1;//break the loop
								}
							}
						}
					}
				}
			}
		} // when loop ends we have found the leaf node

		for (int i = 0; i < temp->counter; i++) {
			if (temp->Heading[i] == compareVal) {
				temp->insertinList(keyToInsert,i,type);
				if (tempPath != "ROOT") {
					setNodeOthers(tempPath, temp,type);
					delete temp;
				}
				mystack.MakeEmpty();
				return;
			}					
		}
		BTnode* ListToInsert = new BTnode;
		ListToInsert->key = keyToInsert;

		if (temp->counter < (m - 1)) { // has space
			temp->AddListAutoAdjust(ListToInsert, type,"NULL");
			if (tempPath != "ROOT") {
				setNodeOthers(tempPath, temp,type);
				delete temp;
			}
			mystack.MakeEmpty();
			return;
		}
		BTnode* median= new BTnode;
		string mpath;
		string pPath = "NULL";
		found = false;
		while (!found) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT") {
				if (temp != NULL && temp!=head) {
					delete temp;
					temp = NULL;
				}
				temp = head;
				if (temp->counter < (m - 1)) {
					found = true;
					temp->AddListAutoAdjust(ListToInsert, type, pPath);
					mystack.MakeEmpty();
				} // have to do it
				else {
					found = true;
					t* temp2 = new t(m);
					int middle = (m - 2) / 2;
					temp2->AddListAutoAdjust(head->head[middle], type,"NULL");
					temp2->Heading[0] = head->Heading[middle];
					SplitRootInts(temp2->head[0]->key,ListToInsert,pPath,type); 
					delete head;
					head = temp2;
					MakePathInts(mpath, nodeCounter - 1,type);
					head->path[0] = mpath;
					MakePathInts(mpath, nodeCounter,type);
					head->path[1] = mpath;
					return;
				}
			}
			else {
				if (temp != NULL) {
					delete temp;
					temp = NULL;
				}
				temp = getNodeOthers(tempPath,type);
				if (temp->counter < (m - 1)) {
					found = true;
					MakePathInts(mpath, nodeCounter, type);
					temp->AddListAutoAdjust(ListToInsert, type, mpath);
					setNodeOthers(tempPath, temp,type);
					mystack.MakeEmpty();
					return;
				}
				else {
					temp->RemoveMedian(median); // MEDIAN gets the middle value of the BTREE in temp// passed by reference
					SplitNodeInts(median->key, temp, tempPath, pPath,ListToInsert,type);
					MakePathInts(pPath, nodeCounter,type);
					CopyList(ListToInsert,median);
				}
			}
		}	
	}
	void insertByStr(Data keyToInsert,string type) {
		if (head == NULL) {
			head = new t(m);
			head->CreateNewList(keyToInsert, 0, type);
			return;
		}
		string compareVal;
		if (type == "CauseName113")
			compareVal = keyToInsert.CauseName113;
		if (type == "CauseName")
			compareVal = keyToInsert.CauseName;
		if (type == "State")
			compareVal = keyToInsert.State;

		// finding the leaf
		Stack<string> mystack;
		t* temp = NULL;
		string tempPath = "ROOT";
		bool found = false;
		mystack.push("ROOT");
		while (!found) {
			if (tempPath != "ROOT") {
				delete temp;
			}
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				temp = getNodeStr(tempPath, type);
			}
			if (temp->Isleaf()) { // found leaf;
				found = true;
			}
			else {
				if (compareVal < temp->Heading[0]) {
					mystack.push(temp->path[0]);
				}
				else {
					if (compareVal > temp->Heading[temp->counter - 1]) {
						mystack.push(temp->path[temp->counter]);
					}
					else {
						if (temp->counter == 1 && temp->Heading[0] == compareVal) {
							temp->insertinList(keyToInsert, 0, type);
							if (tempPath != "ROOT") {
								setNodeStr(tempPath, temp, type);
								delete temp;
							}
							mystack.MakeEmpty();
							return;
						}
						else {
							for (int i = 0; i < temp->counter - 1; i++) {
								if (compareVal == temp->Heading[i]) {
									found = true;
									temp->insertinList(keyToInsert, i, type);
									if (tempPath != "ROOT") {
										setNodeStr(tempPath, temp, type);
										delete temp;
									}
									mystack.MakeEmpty();
									return;
								}
								if (compareVal == temp->Heading[i + 1]) {
									found = true;
									temp->insertinList(keyToInsert, i + 1, type);
									if (tempPath != "ROOT") {
										setNodeStr(tempPath, temp, type);
										delete temp;
									}
									mystack.MakeEmpty();
									return;
								}
								if (compareVal<temp->Heading[i + 1] && compareVal>temp->Heading[i]) {
									mystack.push(temp->path[i + 1]);
									i = temp->counter + 1;//break the loop
								}
							}
						}
					}
				}
			}
		} // when loop ends we have found the leaf node

		for (int i = 0; i < temp->counter; i++) {
			if (temp->Heading[i] == compareVal) {
				temp->insertinList(keyToInsert, i, type);
				if (tempPath != "ROOT") {
					setNodeStr(tempPath, temp, type);
					delete temp;
				}
				mystack.MakeEmpty();
				return;
			}
		}
		BTnode* ListToInsert = new BTnode;
		ListToInsert->key = keyToInsert;

		if (temp->counter < (m - 1)) { // has space
			temp->AddListAutoAdjust(ListToInsert, type, "NULL");
			if (tempPath != "ROOT") {
				setNodeStr(tempPath, temp, type);
				delete temp;
			}
			mystack.MakeEmpty();
			return;
		}
		BTnode* median = new BTnode;
		string mpath;
		string pPath = "NULL";
		found = false;
		while (!found) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT") {
				if (temp != NULL && temp != head) {
					delete temp;
					temp = NULL;
				}
				temp = head;
				if (temp->counter < (m - 1)) {
					found = true;
					temp->AddListAutoAdjust(ListToInsert, type, pPath);
					mystack.MakeEmpty();
				} // have to do it
				else {
					found = true;
					t* temp2 = new t(m);
					int middle = (m - 2) / 2;
					temp2->AddListAutoAdjust(head->head[middle], type, "NULL");
					temp2->Heading[0] = head->Heading[middle];
					SplitRootStr(temp2->head[0]->key, ListToInsert, pPath, type);
					delete head;
					head = temp2;
					MakePathInts(mpath, nodeCounter - 1, type);
					head->path[0] = mpath;
					MakePathInts(mpath, nodeCounter, type);
					head->path[1] = mpath;
					return;
				}
			}
			else {
				if (temp != NULL) {
					delete temp;
					temp = NULL;
				}
				temp = getNodeStr(tempPath, type);
				if (temp->counter < (m - 1)) {
					found = true;
					MakePathInts(mpath, nodeCounter, type);
					temp->AddListAutoAdjust(ListToInsert, type, mpath);
					setNodeStr(tempPath, temp, type);
					mystack.MakeEmpty();
					return;
				}
				else {
					temp->RemoveMedian(median); // MEDIAN gets the middle value of the BTREE in temp// passed by reference
					SplitNodesStr(median->key, temp, tempPath, pPath, ListToInsert, type);
					MakePathInts(pPath, nodeCounter, type);
					CopyList(ListToInsert, median);
				}
			}
		}
	}
	void insertByFlt(Data keyToInsert, string type) {
		if (head == NULL) {
			head = new t(m);
			head->CreateNewList(keyToInsert, 0, type);
			return;
		}
		float compareVal;
		compareVal = keyToInsert.AadRate;
		// finding the leaf
		Stack<string> mystack;
		t* temp = NULL;
		string tempPath = "ROOT";
		bool found = false;
		mystack.push("ROOT");
		while (!found) {
			if (tempPath != "ROOT") {
				delete temp;
			}
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				temp = getNodefloat(tempPath, type);
			}
			if (temp->Isleaf()) { // found leaf;
				found = true;
			}
			else {
				if (compareVal < temp->Heading[0]) {
					mystack.push(temp->path[0]);
				}
				else {
					if (compareVal > temp->Heading[temp->counter - 1]) {
						mystack.push(temp->path[temp->counter]);
					}
					else {
						if (temp->counter == 1 && temp->Heading[0] == compareVal) {
							temp->insertinList(keyToInsert, 0, type);
							if (tempPath != "ROOT") {
								setNodeOthers(tempPath, temp, type);
								delete temp;
							}
							mystack.MakeEmpty();
							return;
						}
						else {
							for (int i = 0; i < temp->counter - 1; i++) {
								if (compareVal == temp->Heading[i]) {
									found = true;
									temp->insertinList(keyToInsert, i, type);
									if (tempPath != "ROOT") {
										setNodeOthers(tempPath, temp, type);
										delete temp;
									}
									mystack.MakeEmpty();
									return;
								}
								if (compareVal == temp->Heading[i + 1]) {
									found = true;
									temp->insertinList(keyToInsert, i + 1, type);
									if (tempPath != "ROOT") {
										setNodeOthers(tempPath, temp, type);
										delete temp;
									}
									mystack.MakeEmpty();
									return;
								}
								if (compareVal<temp->Heading[i + 1] && compareVal>temp->Heading[i]) {
									mystack.push(temp->path[i + 1]);
									i = temp->counter + 1;//break the loop
								}
							}
						}
					}
				}
			}
		} // when loop ends we have found the leaf node

		for (int i = 0; i < temp->counter; i++) {
			if (temp->Heading[i] == compareVal) {
				temp->insertinList(keyToInsert, i, type);
				if (tempPath != "ROOT") {
					setNodeOthers(tempPath, temp, type);
					delete temp;
				}
				mystack.MakeEmpty();
				return;
			}
		}
		BTnode* ListToInsert = new BTnode;
		ListToInsert->key = keyToInsert;

		if (temp->counter < (m - 1)) { // has space
			temp->AddListAutoAdjust(ListToInsert, type, "NULL");
			if (tempPath != "ROOT") {
				setNodeOthers(tempPath, temp, type);
				delete temp;
			}
			mystack.MakeEmpty();
			return;
		}
		BTnode* median = new BTnode;
		string mpath;
		string pPath = "NULL";
		found = false;
		while (!found) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT") {
				if (temp != NULL && temp != head) {
					delete temp;
					temp = NULL;
				}
				temp = head;
				if (temp->counter < (m - 1)) {
					found = true;
					temp->AddListAutoAdjust(ListToInsert, type, pPath);
					mystack.MakeEmpty();
				} // have to do it
				else {
					found = true;
					t* temp2 = new t(m);
					int middle = (m - 2) / 2;
					temp2->AddListAutoAdjust(head->head[middle], type, "NULL");
					temp2->Heading[0] = head->Heading[middle];
					SplitRootFlt(temp2->head[0]->key, ListToInsert, pPath, type);
					delete head;
					head = temp2;
					MakePathInts(mpath, nodeCounter - 1, type);
					head->path[0] = mpath;
					MakePathInts(mpath, nodeCounter, type);
					head->path[1] = mpath;
					return;
				}
			}
			else {
				if (temp != NULL) {
					delete temp;
					temp = NULL;
				}
				temp = getNodefloat(tempPath, type);
				if (temp->counter < (m - 1)) {
					found = true;
					MakePathInts(mpath, nodeCounter, type);
					temp->AddListAutoAdjust(ListToInsert, type, mpath);
					setNodeOthers(tempPath, temp, type);
					mystack.MakeEmpty();
					return;
				}
				else {
					temp->RemoveMedian(median); // MEDIAN gets the middle value of the BTREE in temp// passed by reference
					SplitNodesFlt(median->key, temp, tempPath, pPath, ListToInsert, type);
					MakePathInts(pPath, nodeCounter, type);
					CopyList(ListToInsert, median);
				}
			}
		}
	}

	void deleteId(int todelete) {
		if (head == NULL)
			return;
		t* temp= head;
		string tempPath="ROOT";
		bool found = false;
		int index=0;
		int previousIndex = 0;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL") {
					cout << " ***********Not Deleted********** " << endl;
					return;
				}
				temp = getNodeID(tempPath);
			}
			if (todelete < temp->key[0].Id) {
				mystack.push(temp->path[0]);
				previousIndex = 0;
			}
			if (todelete > temp->key[temp->counter - 1].Id) {
				mystack.push(temp->path[temp->counter]);
				previousIndex = temp->counter;
			}
			if (temp->key[0].Id == todelete) {
				found = true;
				index=0;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->key[i].Id == todelete) {
					found = true;		
					index = i;
				}
				if (temp->key[i + 1].Id == todelete) {
					found = true;	
					index = i+1;
				}
				if (todelete > temp->key[i].Id && todelete < temp->key[i + 1].Id) {
					mystack.push(temp->path[i + 1]);
					previousIndex = i + 1;
				}
			}
		}
		// COMES HERE WHEN FOUND the node where key present

		int median = (m - 1) / 2;
		Data midData;
		t* LeftNode;
		t* RightNode;
		if (temp->Isleaf()) {
			temp->RemoveDataLeaf(todelete,index);
			if(tempPath!="ROOT")
				setNodeID(tempPath, temp);
			return;
		}
		else {
			// comes here if it isnt leaf
			LeftNode = getNodeID(temp->path[index]);
			RightNode = getNodeID(temp->path[index+1]);
			if (LeftNode->counter >= median) {
				midData.MakeSame(getMin(temp->path[index]));
				temp->key[index] = midData;
				if (tempPath != "ROOT")
					setNodeID(tempPath,temp);
			}
			else {
				if (RightNode->counter >= median) {
					midData.MakeSame(getMax(temp->path[index+1]));
					temp->key[index] = midData;
					if (tempPath != "ROOT")
						setNodeID(tempPath, temp);
				}
			}
		}

	}
	void deleteInts(int todelete,string type) {
		if (head == NULL)
			return;
		t* temp = head;
		string tempPath = "ROOT";
		bool found = false;
		int index = 0;
		int previousIndex = 0;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL") {
					cout << " ***********Not Deleted********** " << endl;
					return;
				}
				temp = getNodeOthers(tempPath,type);
			}
			if (todelete < temp->Heading[0]) {
				mystack.push(temp->path[0]);
				previousIndex = 0;
			}
			if (todelete > temp->Heading[temp->counter - 1]) {
				mystack.push(temp->path[temp->counter]);
				previousIndex = temp->counter;
			}
			if (temp->Heading[0] == todelete) {
				found = true;
				index = 0;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->Heading[i] == todelete) {
					found = true;
					index = i;
				}
				if (temp->Heading[i + 1] == todelete) {
					found = true;
					index = i + 1;
				}
				if (todelete > temp->Heading[i] && todelete < temp->Heading[i + 1]) {
					mystack.push(temp->path[i + 1]);
					previousIndex = i + 1;
				}
			}
		}
		// COMES HERE WHEN FOUND the node where key present

		int median = (m - 1) / 2;
		t* LeftNode;
		t* RightNode;
		if (temp->Isleaf()) {
			temp->RemoveDataLeaf(todelete,index);
			if (tempPath != "ROOT")
				setNodeOthers(tempPath, temp,type);
		}
		else {
			// comes here if it isnt leaf
			LeftNode = getNodeOthers(temp->path[index],type);
			RightNode = getNodeOthers(temp->path[index + 1],type);
			if (LeftNode->counter >= median) {
				CopyList(temp->head[index],getMinListInt(temp->path[index],type));
				if (type == "Year")
					temp->Heading[index] = temp->head[index]->key.Year;
				if (type == "Deaths")
					temp->Heading[index] = temp->head[index]->key.Deaths;
				if (tempPath != "ROOT")
					setNodeOthers(tempPath, temp,type);
			}
			else {
				if (RightNode->counter >= median) {
					CopyList(temp->head[index], getMaxListInt(temp->path[index+1],type));
					if (tempPath != "ROOT")
						setNodeOthers(tempPath, temp,type);
					if (type == "Year")
						temp->Heading[index] = temp->head[index]->key.Year;
					if (type == "Deaths")
						temp->Heading[index] = temp->head[index]->key.Deaths;
					if (tempPath != "ROOT")
						setNodeOthers(tempPath, temp, type);
				}
			}
		}
	}
	void deleteStr(string todelete, string type) {
		if (head == NULL)
			return;
		t* temp = head;
		string tempPath = "ROOT";
		bool found = false;
		int index = 0;
		int previousIndex = 0;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL") {
					cout << " ***********Not Deleted********** " << endl;
					return;
				}
				temp = getNodeStr(tempPath, type);
			}
			if (todelete < temp->Heading[0]) {
				mystack.push(temp->path[0]);
				previousIndex = 0;
			}
			if (todelete > temp->Heading[temp->counter - 1]) {
				mystack.push(temp->path[temp->counter]);
				previousIndex = temp->counter;
			}
			if (temp->Heading[0] == todelete) {
				found = true;
				index = 0;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->Heading[i] == todelete) {
					found = true;
					index = i;
				}
				if (temp->Heading[i + 1] == todelete) {
					found = true;
					index = i + 1;
				}
				if (todelete > temp->Heading[i] && todelete < temp->Heading[i + 1]) {
					mystack.push(temp->path[i + 1]);
					previousIndex = i + 1;
				}
			}
		}
		// COMES HERE WHEN FOUND the node where key present

			int median = (m - 1) / 2;
			t* LeftNode;
			t* RightNode;
			if (temp->Isleaf()) {
				temp->RemoveDataLeaf(todelete, index);
				if (tempPath != "ROOT")
					setNodeStr(tempPath, temp, type);
			}
			else {
				// comes here if it isnt leaf
				LeftNode = getNodeStr(temp->path[index], type);
				RightNode = getNodeStr(temp->path[index + 1], type);
				if (LeftNode->counter >= median) {
					CopyList(temp->head[index], getMinListStr(temp->path[index], type));
					if (type == "CauseName113")
						temp->Heading[index] = temp->head[index]->key.CauseName113;
					if (type == "CauseName")
						temp->Heading[index] = temp->head[index]->key.CauseName;
					if (type == "State")
						temp->Heading[index] = temp->head[index]->key.State;
					if (tempPath != "ROOT")
						setNodeStr(tempPath, temp, type);
				}
				else {
					if (RightNode->counter >= median) {
						CopyList(temp->head[index], getMaxListStr(temp->path[index + 1], type));
						if (tempPath != "ROOT")
							setNodeStr(tempPath, temp, type);
						if (type == "CauseName113")
							temp->Heading[index] = temp->head[index]->key.CauseName113;
						if (type == "CauseName")
							temp->Heading[index] = temp->head[index]->key.CauseName;
						if (type == "State")
							temp->Heading[index] = temp->head[index]->key.State;
						if (tempPath != "ROOT")
							setNodeStr(tempPath, temp, type);
					}
				}
			}
	}
	void deleteFlt(float todelete, string type) {
		if (head == NULL)
			return;
		t* temp = head;
		string tempPath = "ROOT";
		bool found = false;
		int index = 0;
		int previousIndex = 0;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!found) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL") {
					cout << " ***********Not Deleted********** " << endl;
					return;
				}
				temp = getNodefloat(tempPath, type);
			}
			if (todelete < temp->Heading[0]) {
				mystack.push(temp->path[0]);
				previousIndex = 0;
			}
			if (todelete > temp->Heading[temp->counter - 1]) {
				mystack.push(temp->path[temp->counter]);
				previousIndex = temp->counter;
			}
			if (temp->Heading[0] == todelete) {
				found = true;
				index = 0;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->Heading[i] == todelete) {
					found = true;
					index = i;
				}
				if (temp->Heading[i + 1] == todelete) {
					found = true;
					index = i + 1;
				}
				if (todelete > temp->Heading[i] && todelete < temp->Heading[i + 1]) {
					mystack.push(temp->path[i + 1]);
					previousIndex = i + 1;
				}
			}
		}
		// COMES HERE WHEN FOUND the node where key present

		int median = (m - 1) / 2;
		t* LeftNode;
		t* RightNode;
		if (temp->Isleaf()) {
			temp->RemoveDataLeaf(todelete, index);
			if (tempPath != "ROOT")
				setNodeOthers(tempPath, temp, type);
		}
		else {
			// comes here if it isnt leaf
			LeftNode = getNodefloat(temp->path[index], type);
			RightNode = getNodefloat(temp->path[index + 1], type);
			if (LeftNode->counter >= median) {
				CopyList(temp->head[index], getMinListFlt(temp->path[index], type));
				temp->Heading[index] = temp->head[index]->key.AadRate;
				if (tempPath != "ROOT")
					setNodeOthers(tempPath, temp, type);
			}
			else {
				if (RightNode->counter >= median) {
					CopyList(temp->head[index], getMaxListFlt(temp->path[index + 1], type));
					if (tempPath != "ROOT")
						setNodeOthers(tempPath, temp, type);
					temp->Heading[index] = temp->head[index]->key.AadRate;
					if (tempPath != "ROOT")
						setNodeOthers(tempPath, temp, type);
				}
				else {
					// this case is for merge
				}
			}
		}
	}

	void UpdateId(int previous,Data newdata) {
		deleteId(previous);
		insertById(newdata);
	}
	void UpdateOthers(Data previous,Data newdata,string type) {
		if (type == "Year") {
			deleteInts(previous.Year,type);
			insertByints(newdata,type);
		}
		if (type == "Deaths") {
			deleteInts(previous.Deaths,type);
			insertByints(newdata,type);
		}
		if (type == "CauseName113") {
			deleteStr(previous.CauseName113,type);
			insertByStr(newdata,type);
		}
		if (type == "CauseName") {
			deleteStr(previous.CauseName,type);
			insertByStr(newdata,type);
		}
		if (type == "State") {
			deleteStr(previous.State,type);
			insertByStr(newdata,type);
		}
		if (type == "AadRate") {
			deleteFlt(previous.AadRate,type);
			insertByFlt(newdata,type);
		}
	}
	bool SearchById(int toSearch) {
		if (head == NULL)
			return false;
		t* temp;
		string tempPath;
		bool found = false;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!mystack.isEmpty()) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL")
					return false;
				temp = getNodeID(tempPath);
			}
			if (toSearch < temp->key[0].Id) {
				mystack.push(temp->path[0]);
			}
			if (toSearch > temp->key[temp->counter - 1].Id) {
				mystack.push(temp->path[temp->counter]);
			}
			if (temp->key[0].Id == toSearch) {
				temp->key[0].Display();
				return true;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->key[i].Id == toSearch) {
					temp->key[i].Display();// call display
					return true;
				}
				if (temp->key[i + 1].Id == toSearch) {
					temp->key[i + 1].Display();// call display
					return true;
				}
				if (toSearch > temp->key[i].Id && toSearch < temp->key[i + 1].Id) {
					mystack.push(temp->path[i + 1]);
				}
			}
		}
		return false;
	}
	bool SearchByInt(int toSearch,string type) {
		if (head == NULL)
			return false;
		t* temp;
		string tempPath;
		bool found = false;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!mystack.isEmpty()) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL")
					return false;
				temp = getNodeOthers(tempPath,type);
			}
			if (toSearch < temp->Heading[0]) {
				mystack.push(temp->path[0]);
			}
			if (toSearch > temp->Heading[temp->counter - 1]) {
				mystack.push(temp->path[temp->counter]);
			}
			if (temp->Heading[0] == toSearch) {
				temp->Display(0);
				return true;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->Heading[i] == toSearch) {
					temp->Display(i);// call display
					return true;
				}
				if (temp->Heading[i + 1] == toSearch) {
					temp->Display(i+1);// call display
					return true;
				}
				if (toSearch > temp->Heading[i] && toSearch < temp->Heading[i + 1]) {
					mystack.push(temp->path[i + 1]);
				}
			}
		}
		return false;
	}
	bool SearchByStr(string toSearch, string type) {
		if (head == NULL)
			return false;
		t* temp;
		string tempPath;
		bool found = false;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!mystack.isEmpty()) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL")
					return false;
				temp = getNodeStr(tempPath, type);
			}
			if (toSearch < temp->Heading[0]) {
				mystack.push(temp->path[0]);
			}
			if (toSearch > temp->Heading[temp->counter - 1]) {
				mystack.push(temp->path[temp->counter]);
			}
			if (temp->Heading[0] == toSearch) {
				temp->Display(0);
				return true;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->Heading[i] == toSearch) {
					temp->Display(i);// call display
					return true;
				}
				if (temp->Heading[i + 1] == toSearch) {
					temp->Display(i + 1);// call display
					return true;
				}
				if (toSearch > temp->Heading[i] && toSearch < temp->Heading[i + 1]) {
					mystack.push(temp->path[i + 1]);
				}
			}
		}
		return false;
	}
	bool SearchByFlt(float toSearch, string type) {
		if (head == NULL)
			return false;
		t* temp;
		string tempPath;
		bool found = false;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!mystack.isEmpty()) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL")
					return false;
				temp = getNodefloat(tempPath, type);
			}
			if (toSearch < temp->Heading[0]) {
				mystack.push(temp->path[0]);
			}
			if (toSearch > temp->Heading[temp->counter - 1]) {
				mystack.push(temp->path[temp->counter]);
			}
			if (temp->Heading[0] == toSearch) {
				temp->Display(0);
				return true;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->Heading[i] == toSearch) {
					temp->Display(i);// call display
					return true;
				}
				if (temp->Heading[i + 1] == toSearch) {
					temp->Display(i + 1);// call display
					return true;
				}
				if (toSearch > temp->Heading[i] && toSearch < temp->Heading[i + 1]) {
					mystack.push(temp->path[i + 1]);
				}
			}
		}
		return false;
	}
	void RangeSearchFlt(float start, float finish, string type) {
		if (head == NULL)
			return;
		t* temp;
		string tempPath;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!mystack.isEmpty()) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				temp = getNodefloat(tempPath, type);
			}
			if (temp->Isleaf()) {
				for (int i = 0; i < temp->counter; i++) {
					if (temp->Heading[i] >= start && temp->Heading[i] <= finish)
						temp->Display(i);
				}
				mystack.pop();
			}
			else {
				for (int i = 0; i < temp->counter; i++) {
					if (temp->Heading[i] >= start && temp->Heading[i] <= finish)
						temp->Display(i);
				}
				mystack.pop();
				for (int i = 0; i <= temp->counter; i++) {
					mystack.push(temp->path[i]);
				}
			}
		}
	}
	void RangeSearchStr(string start, string finish, string type) {
		if (head == NULL)
			return;
		t* temp;
		string tempPath;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!mystack.isEmpty()) {
			tempPath = mystack.top();
			if (tempPath == "ROOT")
				temp = head;
			else {
				temp = getNodeStr(tempPath, type);
			}
			if (temp->Isleaf()) {
				for (int i = 0; i < temp->counter; i++) {
					if (temp->Heading[i] >= start && temp->Heading[i] <= finish)
						temp->Display(i);
				}
				mystack.pop();
			}
			else {
				for (int i = 0; i < temp->counter; i++) {
					if (temp->Heading[i] >= start && temp->Heading[i] <= finish)
						temp->Display(i);
				}
				mystack.pop();
				for (int i = 0; i <= temp->counter; i++) {
					mystack.push(temp->path[i]);
				}
			}
		}
	}

	Data getId(int toSearch) {
		Data tempData;
		if (head == NULL)
			return tempData;
		t* temp;
		string tempPath;
		bool found = false;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!mystack.isEmpty()) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL")
					return tempData;
				temp = getNodeID(tempPath);
			}
			if (toSearch < temp->key[0].Id) {
				mystack.push(temp->path[0]);
			}
			if (toSearch > temp->key[temp->counter - 1].Id) {
				mystack.push(temp->path[temp->counter]);
			}
			if (temp->key[0].Id == toSearch) {
				tempData = temp->key[0];
				return tempData;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->key[i].Id == toSearch) {
					tempData = temp->key[i];
					return tempData;
				}
				if (temp->key[i + 1].Id == toSearch) {
					tempData = temp->key[i + 1];
					return tempData;
				}
				if (toSearch > temp->key[i].Id && toSearch < temp->key[i + 1].Id) {
					mystack.push(temp->path[i + 1]);
				}
			}
		}
		return tempData;
	}
	Data getFlt(float toSearch) {
		Data tempData;
		if (head == NULL)
			return tempData;
		t* temp;
		string tempPath;
		bool found = false;
		Stack<string> mystack;
		mystack.push("ROOT");
		while (!mystack.isEmpty()) {
			tempPath = mystack.top();
			mystack.pop();
			if (tempPath == "ROOT")
				temp = head;
			else {
				if (tempPath == "NULL")
					return tempData;
				temp = getNodefloat(tempPath,"AadRate");
			}
			if (toSearch < temp->Heading[0]) {
				mystack.push(temp->path[0]);
			}
			if (toSearch > temp->Heading[temp->counter - 1]) {
				mystack.push(temp->path[temp->counter]);
			}
			if (temp->Heading[0] == toSearch) {
				tempData = temp->head[0]->key;
				return tempData;
			}
			for (int i = 0; i < (temp->counter - 1); i++) {
				if (temp->Heading[i] == toSearch) {
					tempData = temp->head[i]->key;
					return tempData;
				}
				if (temp->Heading[i + 1] == toSearch) {
					tempData = temp->head[i + 1]->key;
					return tempData;
				}
				if (toSearch > temp->Heading[i] && toSearch < temp->Heading[i + 1]) {
					mystack.push(temp->path[i + 1]);
				}
			}
		}
		return tempData;
	}

};



