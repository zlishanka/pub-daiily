#include <iostream>

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) {
            return head; // Nothing to reverse or invalid input
        }

        // Create a dummy node to simplify edge cases
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev_group_end = &dummy;
        ListNode* curr = head;
        int count = 0;

        while (curr) {
            count++;
            if (count % k == 0) {
                prev_group_end = reverseSublist(prev_group_end->next, curr->next);
                curr = prev_group_end->next;
            } else {
                curr = curr->next;
            }
        }

        return dummy.next;
    }

private:
    // Helper function to reverse a sublist
    ListNode* reverseSublist(ListNode* start, ListNode* end) {
        ListNode* prev = nullptr;
        ListNode* curr = start;
        while (curr != end) {
            ListNode* next_node = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_node;
        }
        start->next = curr; // Connect the reversed sublist back to the original list
        
        return prev;
    }
};

// Helper function to print the linked list
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    // Example usage
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    Solution sol;
    int k = 2;
    ListNode* reversedList = sol.reverseKGroup(head, k);

    std::cout << "Reversed list (k = " << k << "): ";
    printList(reversedList);

    // Clean up memory (not shown in the example)
    // ...

    return 0;
}