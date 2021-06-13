#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

      void print(){
          preorder(this);
      }
      void preorder(TreeNode *root)
      {
        if(root == NULL) return;
        cout << root->val << endl;
        preorder(root->left);
        preorder(root->right);
      }
  };

class BSTIterator {

TreeNode *treeRoot;
TreeNode *curNode;


public:
unordered_map<TreeNode*, TreeNode*> parent;
    BSTIterator(TreeNode* root): treeRoot(root) {
        create_parent(root);
    }
    void create_parent(TreeNode *cur){
        if(!cur) return;
        if(cur->left) {
            parent[cur->left] = cur;
            create_parent(cur->left);
        }
        if(cur->right) {
            parent[cur->right] = cur;
            create_parent(cur->right);
        }
    }

    static TreeNode *leftmost(TreeNode* root){
        TreeNode *ret = root;
        while(ret->left){
            ret = ret->left;
        }

        return ret;
    }



    /** @return the next smallest number */
    int next() {
        if(curNode->right){
            curNode = leftmost(curNode->right);
            return curNode->val;
        }else{

        }

    }

    /** @return whether we have a next smallest number */
    bool hasNext() {

    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

int main(){
    TreeNode *root = new TreeNode(7);
    root->left = new TreeNode(3);

    TreeNode *node2 = root->right = new TreeNode(15);
    node2->left = new TreeNode(9);
    node2->right = new TreeNode(20);

    root->print();

    cout << endl << BSTIterator::leftmost(root)->val << endl;
    cout << endl << BSTIterator::leftmost(node2)->val << endl;

    BSTIterator iter(root);
    cout << iter.parent[node2]->val << endl;

}
