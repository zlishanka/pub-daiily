#include "common.h"
#include <vector>

using namespace std;

ListNode* reverseBetween(ListNode* head, int left, int right) {
       if (!head || left >= right) {
            return head; // Nothing to reverse or invalid input
        }

        // Create a dummy node to simplify edge cases
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;

        // Move prev to the node just before the left position
        for (int i = 1; i < left; ++i) {
            prev = prev->next;
        }

        // Reverse the sublist from left to right
        ListNode* current = prev->next;
        ListNode* nextNode = nullptr;
        ListNode* prevNode = nullptr;

        for (int j = left; j <= right; ++j) {
            nextNode = current->next;
            current->next = prevNode;
            prevNode = current;
            current = nextNode;
        }

        // Connect the reversed sublist back to the original list
        prev->next->next = current;
        prev->next = prevNode;

        return dummy.next;
}

int main() {
    vector<int> arr = {1,2,3,4,5};
    ListNode* head = initList(arr);
    printList(head);
    ListNode* newHead = reverseBetween(head, 2, 4);
    printList(newHead);
}