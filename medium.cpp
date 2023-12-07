#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == p || root == q) {
        return root;
    }

    if (!root) {
        return nullptr;
    }

    TreeNode* left = lca(root->left, p, q);
    TreeNode* right = lca(root->right, p, q);

    if (left && right) {
        return root;
    } else if (left) {
        return left;
    } else {
        return right;
    }
}

TreeNode* buildTree(const vector<int>& nodes) {
    unordered_map<int, TreeNode*> nodeMap;
    TreeNode* root = nullptr;

    for (int val : nodes) {
        if (val != -1) {
            TreeNode* node = new TreeNode(val);
            nodeMap[val] = node;

            if (!root) {
                root = node;
            }
        }
    }

    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i] != -1) {
            TreeNode* node = nodeMap[nodes[i]];
            int leftIdx = 2 * i + 1;
            int rightIdx = 2 * i + 2;

            if (leftIdx < nodes.size() && nodes[leftIdx] != -1) {
                node->left = nodeMap[nodes[leftIdx]];
            }

            if (rightIdx < nodes.size() && nodes[rightIdx] != -1) {
                node->right = nodeMap[nodes[rightIdx]];
            }
        }
    }

    return root;
}

vector<int> parseInput(const string& input) {
    vector<int> result;
    istringstream iss(input);
    int num;

    while (iss >> num) {
        result.push_back(num);
    }

    return result;
}

int main() {
    cout << "Enter the tree structure as a space-separated list of values (use -1 for null nodes): ";
    string treeInput;
    getline(cin, treeInput);
    vector<int> nodes = parseInput(treeInput);

    TreeNode* root = buildTree(nodes);

    cout << "Enter the values of two nodes for which to find the lowest common ancestor (space-separated): ";
    string nodesInput;
    getline(cin, nodesInput);
    vector<int> nodeValues = parseInput(nodesInput);

    if (nodeValues.size() != 2) {
        cerr << "Invalid input for nodes. Please provide exactly two values." << endl;
        return 1;
    }

    TreeNode* p = new TreeNode(nodeValues[0]);
    TreeNode* q = new TreeNode(nodeValues[1]);

    TreeNode* result = lca(root, p, q);

    if (result) {
        cout << "Lowest Common Ancestor: " << result->val << endl;
    } else {
        cout << "No common ancestor found." << endl;
    }
 return 0;
}
