/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example: Given the below binary tree and sum = 23,

              5
             / \
            9   8
           /   / \
          11  13  4
         /  \    / \
        7    2  6   1
return

[
   [5,8,4,6]
]
*/

#include "common.h"
#include <vector> 

using namespace std;

void pathSumHelper(TreeNode* node, int level, vector<vector<int>>& res, vector<int>& sol, int targetSum) {
    if (node == nullptr) {
        return;
    }
    targetSum -= node->val;

    if (sol.size() > level) {
        sol[sol.size()-1] = node->val;
    } else {
        sol.push_back(node->val);
    }
    if (node->left == nullptr && node->right == nullptr && targetSum == 0) {
        res.push_back(sol);
        return;
    }
    pathSumHelper(node->left, level+1, res, sol, targetSum);
    pathSumHelper(node->right, level+1, res, sol, targetSum);


}

vector<vector<int>> collectPathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> res;
    vector<int> sol;
    int level = 0;
    pathSumHelper(root, level, res, sol, targetSum);
    return res;
}


int main() {
    vector<int> preOrder = {5, 9, 11, 7, 2, 8, 13, 4, 6, 1};
    vector<int> inOrder = {7, 11, 2, 9, 5, 13, 8, 6, 4, 1};

    TreeNode* root = createBinaryTreeInPre(inOrder, preOrder);
    printTree(root);

    int targetSum = 26;
    vector<vector<int>> res = collectPathSum(root, targetSum);
    cout << "targetSum = " << targetSum << ", res= " << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << "[";
        for (int j = 0; j < res[i].size(); ++j) {
            cout << res[i][j] << ",";
        }
        cout << "]" << endl;


    }
    return 0;
}