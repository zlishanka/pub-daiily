/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/

#include "common.h"
#include <vector>

using namespace std;

ListNode* removeAllDup(ListNode* head) {
    ListNode* prev = new ListNode(INT_MAX);
    prev->next = head;

    ListNode* dummy = new ListNode(0);
    ListNode* q = dummy;
    ListNode* p = head;

    while (p->next) {
        if (prev->val != p->val && p->val != p->next->val) {
            q->next = p;
            q = q->next;
        }
        prev = p;
        p = p->next;
    }
    // handle last node
    if (prev->val == p->val)
        q->next = nullptr;
    else 
        q->next = p;
    return dummy->next;

}

int main() {
     vector<int> arr = {1,1,2,3,3,6,6,7};
    ListNode* head = initList(arr);
    printList(head);
    ListNode* newHead = removeAllDup(head);
    printList(newHead);
}