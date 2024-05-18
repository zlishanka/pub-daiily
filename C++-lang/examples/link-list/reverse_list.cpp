#include "common.h"
#include <vector>

using namespace std;

ListNode* reverseList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* rev = nullptr;
    ListNode* cur = head;

    while (cur) {
        ListNode* next = cur->next;
        cur->next = rev;
        rev = cur;
        cur = next;
    }
    return rev;
}

int main() {
    vector<int> arr = {1,1,2,3,3,6,6};
    ListNode* head = initList(arr);
    printList(head);
    ListNode* newHead = reverseList(head);
    printList(newHead);
}