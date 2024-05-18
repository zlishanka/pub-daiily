/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/

#include "common.h"

#include <vector>

using namespace std;

ListNode* removeDuplicate(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* p = head;
    while (p->next) {
        if (p->val == p->next->val) {
            p->next = p->next->next;
        } else {
            p = p->next;
        }
    }

    return head;
}
int main() {
    vector<int> arr = {1,1,2,3,3,6,6};
    ListNode* head = initList(arr);
    printList(head);
    ListNode* newHead = removeDuplicate(head);
    printList(newHead);
}