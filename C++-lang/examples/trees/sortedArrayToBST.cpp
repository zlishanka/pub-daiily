#include "common.h"
#include <vector>

using namespace std;

TreeNode* BSTHelper(vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start+end)/2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = BSTHelper(nums, start, mid-1);
    root->right = BSTHelper(nums, mid+1, end);

    return root;
}

TreeNode* createBSTFromSortedArray(vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return BSTHelper(nums, 0, nums.size()-1);
}

int main() {

     vector<int> nums = {4, 10, 12, 15, 18, 22, 24, 25, 31, 35, 44, 50, 66, 70, 90};    
     TreeNode* root = createBSTFromSortedArray(nums);

     printTree(root);

     return 0;
}