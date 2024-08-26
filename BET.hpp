// ***********************************************************************
// * Function Name: BET                                                  *
// * Description: Default constructor, initializes an empty tree         *
// *                                                                     *
// * Parameter Description:                                              *
// * - None                                                              *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
BET<T>::BET() : root(nullptr) {
    
}

// ***********************************************************************
// * Function Name: BET                                                  *
// * Description: One parameter constructor that builds tree from a      *
// *              postfix expression                                     *
// *                                                                     *
// * Parameter Description:                                              *
// * - postfix: Reference to a string containing a postfix expression    *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
BET<T>::BET(const std::string &postfix) : root(nullptr) {
    buildFromPostfix(postfix);
}

// ***********************************************************************
// * Function Name: BET                                                  *
// * Description: Copy constructor makes a deep copy of the tree         *
// *                                                                     *
// * Parameter Description:                                              *
// * - other: Reference to another BET object to be copied               *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
BET<T>::BET(const BET &other) : root(nullptr) {
    root = clone(other.root);
}

// ***********************************************************************
// * Function Name: ~BET                                                 *
// * Description: Destructor whichcleans up all the space in the tree    *
// *                                                                     *
// * Parameter Description:                                              *
// * - None                                                              *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
BET<T>::~BET() {
    makeEmpty(root);
}

// ***********************************************************************
// * Function Name: buildFromPostfix                                     *
// * Description: Constructs a binary expression tree from a postfix     *
// *              expression                                             *
// * Parameter Description:                                              *
// * - postfix: Reference to string with a postfix expression            *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
bool BET<T>::buildFromPostfix(const std::string &postfix) {
    makeEmpty(root);
    std::stack<BinaryNode*> stack;
    std::string token;
    std::istringstream iss(postfix);

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) {
                std::cerr <<  token << "' doesnt have enough operands" << std::endl;
            return false;
            }
            BinaryNode *right = stack.top(); 
            stack.pop();
            
            BinaryNode *left = stack.top(); 
            stack.pop();
            
            BinaryNode *node = new BinaryNode(token, left, right);
            stack.push(node);
            
        } else {
            stack.push(new BinaryNode(token));
        }
    }
    if (stack.size() != 1) {
        std::cerr << "Operands dont match the operators" << std::endl;
        makeEmpty(root);
        return false;
    }
root = stack.top();
return true;
}

// ***********************************************************************
// * Function Name: operator=                                            *
// * Description: deep copies the contents of another BET object         *
// *                                                                     *
// * Parameter Description:                                              *
// * - other: reference to the other BET object copied from              *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
const BET<T> &BET<T>::operator=(const BET &other) {
    if (this != &other) {
        makeEmpty(root);
        root = clone(other.root);
    }
    return *this;
}

// ***********************************************************************
// * Function Name: printInfixExpression                                 *
// * Description: Prints the infix expression of the binary tree         *
// *                                                                     *
// * Parameter Description:                                              *
// * - None                                                              *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
void BET<T>::printInfixExpression() {
    printInfixExpression(root);
    std::cout << std::endl;
}

// ***********************************************************************
// * Function Name: printInfixExpression                                 *
// * Description: Recursively prints the infix expression of the sub-tree*
// *                                                                     *
// * Parameter Description:                                              *
// * - n: pointer to the root of the sub-tree to print                   *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
void BET<T>::printInfixExpression(BinaryNode *n) {
    if (n != nullptr) {
        if (n->left != nullptr || n->right != nullptr) std::cout << "(";
        printInfixExpression(n->left);
        
        std::cout << n->element;
        
        printInfixExpression(n->right);
        if (n->left != nullptr || n->right != nullptr) std::cout << ")";
    }
}

// ***********************************************************************
// * Function Name: printPostfixExpression                               *
// * Description: Prints the postfix expression of the binary tree       *
// *                                                                     *
// * Parameter Description:                                              *
// * - None                                                              *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
void BET<T>::printPostfixExpression() {
    printPostfixExpression(root);
    std::cout << std::endl;
}

// ***********************************************************************
// * Function Name: printPostfixExpression                                *
// * Description: Recursively prints the postfix expression of the subtree*
// *                                                                      *
// *                                                                      *
// * Parameter Description:                                               *
// * - n: pointer to the root of the sub-tree to print                    *
// * Date: 7/8/2024                                                       *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template<typename T>
void BET<T>::printPostfixExpression(BinaryNode *n) {
    if (n != nullptr) {
        printPostfixExpression(n -> left);
        printPostfixExpression(n -> right);
        
        std::cout << n -> element << " ";
    }
}

// ***********************************************************************
// * Function Name: size                                                 *
// * Description: Returns the number of nodes in the binary tree         *
// *                                                                     *
// * Parameter Description:                                              *
// * - None                                                              *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
size_t BET<T>::size() {
    return size(root);
}

// ***********************************************************************
// * Function Name: size                                                  *
// * Description: Recursively gives the number of nodes in the sub-tree   *
// *               rooted at the given node                               *
// *                                                                      *
// * Parameter Description:                                               *
// * - t: pointer to the root of the subtree                              *
// * Date: 7/8/2024                                                       *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template<typename T>
size_t BET<T>::size(BinaryNode *t) {
    if (t == nullptr) return 0;
    
    return 1 + size(t -> left) + size(t -> right);
}

// ***********************************************************************
// * Function Name: leaf_nodes                                            *
// * Description: Returns the number of leaf nodes in the binary tree     *
// *                                                                      *
// * Parameter Description:                                               *
// * - None                                                               *
// * Date: 7/8/2024                                                       *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template<typename T>
size_t BET<T>::leaf_nodes() {
    return leaf_nodes(root);
}

// ***********************************************************************
// * Function Name: leaf_nodes                                            *
// * Description: Recursively calculates the number of leaf nodes in the  *
// *              subtree                                                 *
// * Parameter Description:                                               *
// * - t: pointer to the root of the subtree                              *
// * Date: 7/8/2024                                                       *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template<typename T>
size_t BET<T>::leaf_nodes(BinaryNode *t) {
    if (t == nullptr) return 0;

    if (t -> left == nullptr && t -> right == nullptr) return 1;
    
    return leaf_nodes(t -> left) + leaf_nodes(t -> right);
}

// ***********************************************************************
// * Function Name: empty                                                *
// * Description: Checks if the binary tree is empty                     *
// *                                                                     *
// * Parameter Description:                                              *
// * - None                                                              *
// * Date: 7/8/2024                                                      *
// * Author: Dallas Toth                                                 *
// * References: None                                                    *
// ***********************************************************************
template<typename T>
bool BET<T>::empty() {
    return root == nullptr;
}

// ***********************************************************************
// * Function Name: makeEmpty                                             *
// * Description: Deallocates all nodes in the binary tree                *
// *                                                                      *
// * Parameter Description:                                               *
// * - t: reference to a pointer to the root of the subtree               *
// * Date: 7/8/2024                                                       *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template<typename T>
void BET<T>::makeEmpty(BinaryNode* &t) {
    if (t != nullptr) {
        makeEmpty(t -> left);
        makeEmpty(t -> right);
        delete t;
        
        t = nullptr;
    }
}

// ***********************************************************************
// * Function Name: clone                                                 *
// * Description: Recursively creates a deep copy of the subtree          *
// *                                                                      *
// * Parameter Description:                                               *
// * - t: pointer to the root of the subtree to deep copy                 *
// * Date: 7/8/2024                                                       *
// * Author: Dallas Toth                                                  *
// * References: None                                                     *
// ***********************************************************************
template<typename T>
typename BET<T>::BinaryNode *BET<T>::clone(BinaryNode *t) const{
    if (t == nullptr) return nullptr;
    return new BinaryNode(t -> element, clone(t -> left), clone(t -> right));
}
