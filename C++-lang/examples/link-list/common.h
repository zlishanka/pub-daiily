#pragma once 

#include <iostream>
#include <vector>
using namespace std; 

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x): val(x), next(nullptr) {}
	ListNode(int x, ListNode* n) : val(x), next(n) {}	
};

void printList(ListNode* head) {
	ListNode* p = head;
	while (p) {
		cout << p->val << "->" ;
		p = p->next;
	}
	cout <<"NULL" << endl;
};

ListNode* initList(const vector<int>& arr) {
	ListNode* dummy = new ListNode(0);
	ListNode* p = dummy;
	for (int i = 0; i < arr.size(); ++i) {
		p->next = new ListNode(arr[i]);
		p = p->next;
	}
	return dummy->next;
};
