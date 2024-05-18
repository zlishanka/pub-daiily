#include "common.h"
#include <vector>

using namespace std;

int main() {
    vector<int> preOrder = {25, 15, 10, 4, 12, 22, 18, 24, 50, 35, 31, 44, 70, 66, 90};
    vector<int> inOrder = {4, 10, 12, 15, 18, 22, 24, 25, 31, 35, 44, 50, 66, 70, 90};

    TreeNode* root = createBinaryTreeInPre(inOrder, preOrder);
    printTree(root);

    return 0;
}