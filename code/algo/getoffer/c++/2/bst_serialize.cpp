#include <queue>
#include <sstream>
#include <string>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
  // Serializes a tree to a single string.
  std::string serialize(TreeNode *root) {
    std::ostringstream sb;
    serializeHelper(root, sb);
    return sb.str();
  }

  // Deserializes your encoded data to tree.
  TreeNode *deserialize(const std::string &data) {
    std::vector<std::string> nodes = split(data, ',');
    int index = 0;
    return deserializeHelper(nodes, index);
  }

private:
  void serializeHelper(TreeNode *node, std::ostringstream &sb) {
    if (!node) {
      sb << "null,";
      return;
    }
    sb << node->val << ',';
    serializeHelper(node->left, sb);
    serializeHelper(node->right, sb);
  }

  TreeNode *deserializeHelper(const std::vector<std::string> &nodes,
                              int &index) {
    if (index >= nodes.size() || nodes[index] == "null") {
      ++index;
      return nullptr;
    }
    TreeNode *node = new TreeNode(std::stoi(nodes[index++]));
    node->left = deserializeHelper(nodes, index);
    node->right = deserializeHelper(nodes, index);
    return node;
  }

  std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
    }
    return tokens;
  }
};
