#pragma once
#include<iostream>
#include<string>
using namespace std;

template<typename t>
struct NormNode {
	t data;
	NormNode<t>* next;

	NormNode() {
		next = NULL;
	}
};

template<typename t>
class Stack {
private:
	NormNode<t>* head;
public:
	Stack() {
		head = NULL;
	}
	void push(t dataToInsert) {
		if (head == NULL) {
			head = new NormNode<t>;
			head->data = dataToInsert;
			return;
		}
		NormNode<t>* temp= new NormNode<t>;
		temp->data = dataToInsert;
		temp->next = head;
		head = temp;
	}

	void pop() {
		if (head != NULL) {
			NormNode<t> * temp = head;
			head = head->next;
			delete temp;
		}
	}

	t top() {
		return head->data;
	}

	bool isEmpty() {
		if (head == NULL)
			return true;
		return false;
	}

	void MakeEmpty() {
		while (head != NULL) {
			pop();
		}
	}

};

template<typename t>
class Queue {
private:
	NormNode<t>* head;
public:
	Queue() {
		head = NULL;
	}
	void enqueue(t dataToInsert) {
		if (head == NULL) {
			head = new NormNode<t>;
			head->data = dataToInsert;
			return;
		}
		NormNode<t>* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new NormNode<t>;
		temp->next->data = dataToInsert;
	}

	void dequeue() {
		if (head != NULL) {
			NormNode<t>* temp = head;
			while (temp->next != NULL)
				temp = temp->next;
			delete temp;
		}
	}
	
	t first() {
		return head->data;
	}

	bool isEmpty() {
		if (head == NULL)
			return true;
		return false;
	}

	void MakeEmpty() {
		while (head != NULL) {
			dequeue();
		}
	}



};
