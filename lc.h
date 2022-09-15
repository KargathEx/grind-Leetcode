#ifndef LC
#define LC
#include "pprint.h"
#include<iostream>
#include<regex>
#include<sstream>
#include<string>
using std::cout;
using std::endl;
using std::vector;
using std::string;
namespace lc
{
  struct ListNode
  {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next_) : val(x), next{ next_ } {}
  };
  class List
  {
    ListNode* head;
    ListNode* copy(ListNode* p)
    {
      if (!p)return nullptr;
      ListNode* r = new ListNode(p->val);
      r->next = copy(p->next);
      return r;
    }
  public:
    List(const std::string& inputStr);
    List(ListNode* p) { head = copy(p); };
    ~List();
    void print();
    auto get() { return head; }
  };

  const int32_t TREE_NODE_BOUNDNARY = INT_MIN + 1; // replace null
  struct TreeNode
  {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x = 0) : val(x), left(nullptr), right(nullptr) {}
    ~TreeNode() {
      if (left) delete left;
      if (right) delete right;
    }
  };
  template<typename T>
  std::vector<T> Vec(const std::string inputStr)
  {
    std::vector<T> ret;
    const std::string pattern = R"(([+|-]?\w*\.?[\w+|#|(|)|\.]),?)";
    std::smatch match;
    std::string log = inputStr;
    while (regex_search(log, match, (std::regex)pattern)) {
      std::stringstream ss;
      std::string treeNull = match.str(1) == "null" ? std::to_string(TREE_NODE_BOUNDNARY) : match.str(1);
      ss << treeNull;
      T temp;
      ss >> temp;
      ret.push_back(temp);
      log = match.suffix();
    }
    if (ret.empty())
      std::cout << "构造Vector失败" << std::endl;
    return ret;
  }
  template<typename T>
  std::vector<std::vector<T>> Vec2(const std::string inputStr)
  {
    std::vector<std::vector<T>> ret;
    const std::string pattern = R"((\[[^\[\]]*\]))";
    std::smatch match;

    std::string log = inputStr;
    while (regex_search(log, match, (std::regex)pattern)) {
      std::string vec = match.str(1);
      ret.push_back(Vec<T>(vec));
      log = match.suffix();
    }

    if (ret.empty()) {
      std::cout << "构造Matrix失败" << std::endl;
    }
    return ret;
  }
  class Tree
  {
  private:
    void print_Impl(TreeNode* n, bool left, std::string const& indent);
    TreeNode* copyTree(TreeNode* p)
    {
      if (!p)return nullptr;
      auto r = new TreeNode(p->val);
      r->left = copyTree(p->left);
      r->right = copyTree(p->right);
      return r;
    }
  public:
    TreeNode* root;
    Tree(const std::string& input);
    Tree(TreeNode* p) { root = copyTree(p); }
    ~Tree();
    void print();
  };
  void print(TreeNode* p);
  void print(ListNode* p);
}
#endif
