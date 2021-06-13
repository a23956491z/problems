#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

  class BSTIterator {

  public:
      queue<int> que;

      BSTIterator(TreeNode* root) {
          inorder(root);
      }
      void inorder(TreeNode *root)
      {
        if(root == NULL) return;
        inorder(root->left);
        que.push(root->val);
        inorder(root->right);
      }

      /** @return the next smallest number */
      int next() {
          int ret = que.front();
          que.pop();
          return ret;
      }

      /** @return whether we have a next smallest number */
      bool hasNext() {
          return !que.empty();
      }
  };


/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
