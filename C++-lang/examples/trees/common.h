#pragma once 

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

void traverseInorder(vector<int>& res, TreeNode* node) {

    if (node == nullptr) {
        return;
    }
    traverseInorder(res, node->left);
    res.push_back(node->val);
    traverseInorder(res, node->right);
}

void traversePreorder(vector<int>& res, TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    res.push_back(node->val);
    traversePreorder(res, node->left);
    traversePreorder(res, node->right);
}

void traversePostorder(vector<int>& res, TreeNode* node) {
    
    if (node == nullptr) {
        return;
    }
    res.push_back(node->val);
    traversePostorder(res, node->left);
    traversePostorder(res, node->right);
}

void printTree(TreeNode* root) {
    cout << "Tree inorder - ";
    
    vector<int> res;
    traverseInorder(res, root);
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }
    cout << endl;
    res.clear();
    
    cout << "Tree preorder - ";
    traversePreorder(res, root);
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }
    cout << endl;
    return;
}

 TreeNode* createTreeHelper(vector<int>& preorder, unordered_map<int, int> inOrderToIndex, int& preIndex, int inStart, int inEnd) {
        if (inStart > inEnd) {
            return nullptr;
        }
        int rootVal = preorder[preIndex];
        TreeNode* root = new TreeNode(rootVal);
        int inOrder = inOrderToIndex[rootVal];

        preIndex++;
    
        root->left = createTreeHelper(preorder, inOrderToIndex, preIndex, inStart, inOrder-1);
        root->right = createTreeHelper(preorder, inOrderToIndex, preIndex, inOrder+1, inEnd);

        return root;
}

// Create a binary tree from inorder & preorder arrays
TreeNode* createBinaryTreeInPre(vector<int>&  inorder, vector<int>& preorder) {
    unordered_map<int, int> inOrderToIndex;

    for (int i = 0; i < inorder.size(); ++i) {
        inOrderToIndex[inorder[i]] = i;
    }

    int preIndex = 0;
    return createTreeHelper(preorder, inOrderToIndex, preIndex, 0, inorder.size()-1);


}
