
#include "common.h"
#include <vector>

using namespace std;

ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* newHead = head->next;
    head->next = swapPairs(newHead->next);
    newHead->next = head;
    return newHead;
}

int main() {
    vector<int> arr = {1,2,3,4,5,6};
    ListNode* head = initList(arr);
    printList(head);
    ListNode* newHead = swapPairs(head);
    printList(newHead);
    
    return 0;
}