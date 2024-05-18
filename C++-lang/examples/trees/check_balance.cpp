#include "common.h"
#include <vector> 

using namespace std;

int getDepth(TreeNode* root) {
    if (root==nullptr) {
        return 1;
    }
    int ld = getDepth(root->left);
    if (ld < 0) return -1;

    int rd = getDepth(root->right);
    if (rd < 0) return -1;

    if (abs(ld-rd) > 1) {
        return -1;
    } else {
        return max(ld, rd) + 1; 
    }
}

bool isBalanced(TreeNode* root) {
    if (root == nullptr) return true;
    if (getDepth(root) < 0) return false;

    return true;
}

int main() {
    vector<int> preOrder = {25, 15, 10, 4, 12, 22, 18, 24, 50, 35, 31, 44, 70, 66, 90};
    vector<int> inOrder = {4, 10, 12, 15, 18, 22, 24, 25, 31, 35, 44, 50, 66, 70, 90};

    TreeNode* root = createBinaryTreeInPre(inOrder, preOrder);
    printTree(root);
    string res = isBalanced(root) == true ? "yes" : "no";
    cout << "The above tree is balanced? " <<  res << endl;

    preOrder = {2,1,5,4,3,6,7};
    inOrder = {1, 2, 3, 4, 5, 6, 7};
    root = createBinaryTreeInPre(inOrder, preOrder);
    printTree(root);
    res = isBalanced(root) == true ? "yes" : "no";
    cout << "The above tree is balanced? " <<  res << endl;


}