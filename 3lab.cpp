#include <iostream>
#include <stack>

template <typename T>
struct Node {
    T key;     
    Node<T> *left;  
    Node<T> *right; 
    int height; 
};

template <typename T>
class BSTTreeIterator
{
public:
    BSTTreeIterator(Node<T> *p) : nodePtr(p) {}
    
    bool operator== (const BSTTreeIterator& item) const
    {
        return item.nodePtr == this->nodePtr;
    }
    
    bool operator!= (const BSTTreeIterator& item) const
    {
        return item.nodePtr != this->nodePtr;
    }
    
    T& operator* () const
    {
        return this->nodePtr->key;
    }
    
    std::stack<Node<T> > node_stack;
    
    BSTTreeIterator& operator++()
    {
        if(nodePtr != nullptr)
        {
            if(nodePtr->right != nullptr)
            {
                node_stack.push(*nodePtr->right);
            }
            if(nodePtr->left != nullptr)
            {
                nodePtr = nodePtr->left;
            }
            else
            {
                nodePtr = node_stack.top();
                node_stack.pop();
            }
        }
        return *this;
    }
    
    BSTTreeIterator operator++(int)
    {
        if(nodePtr != nullptr)
        {
            if(nodePtr->right != nullptr)
            {
                node_stack.push(*nodePtr->right);
            }
            if(nodePtr->left != nullptr)
            {
                nodePtr = nodePtr->left;
            }
            else
            {
                nodePtr = &node_stack.top();
                node_stack.pop();
            }
        }
        return *this;
    }
    
private:
    Node<T> *nodePtr;
};


template <typename T, class Compare = std::less<T>>

class BSTTree {
    
    typedef BSTTreeIterator<T> iterator;
    typedef BSTTreeIterator<T> constIterator;
    
public:
    BSTTree() { 
        head = nullptr;
    }
    
    BSTTree(const BSTTree &BSTTree) {
        head = nullptr;
        head->left = BSTTree.head->left;
        head->right = BSTTree.head->right;
    }
    
    ~BSTTree() { 
        delete head;
    }
    
    BSTTree& operator=(const BSTTree& BSTTree) {
        _size = BSTTree._size;
        head = new Node<T>;
        head->key = BSTTree.head->key;
        head->left = BSTTree.head->left;
        head->right = BSTTree.head->right;
        head->height = BSTTree.head->height;
        
        return *this;
    }
    
    template<class InputIt>
    
    void assign(InputIt first, InputIt last)
    {
        BSTTree<int> tree;
        
        if (head != nullptr)
            delete head;
        
        for (InputIt i = first; i != last; i++)
        {
            insert(*(i));
        }
    }
    
    iterator begin() {
        return iterator(head);
    }
    
    constIterator cbegin() {
        return iterator(head);
    }
    
    iterator end() {
        BSTTreeIterator<T> n = iterator(head);
        int s = _size;
        
        while (s != 1 )
        {
            n++;
            s--;
        }
        return n;
    }
    
    constIterator cend() {
        BSTTreeIterator<T> n = iterator(head);
        int s = _size;
        
        while (s != 1 )
        {
            n++;
            s--;
        }
        return n;
    }
    
    iterator insert(const T &key){
        _size++;
        Node<T> *res = head;
        insertNode(head, key, &res);
        
        return iterator(res);
    }
    
    iterator Delete(const T &key){
        _size--;
        Node<T> *res;
        deleteNode(head, key, &res);
        
        return iterator(res);
    }
    
    iterator find(const int key) {
        if (ExistNode(head, key) != nullptr)
            return iterator(ExistNode(head, key)); 
        else
            std::cout << "Error";
        return 0;
    }
    
    constIterator cfind(const int key) {
        if (ExistNode(head, key) != nullptr)
            return iterator(ExistNode(head, key)); 
        else
            std::cout << "Error";
    }
    
    size_t size() const {
        return _size;
    };
    
    bool empty() const {
        return head == nullptr;
    };
    
private:
    Node<T> *head;
    int _size = 0;
    
    Node<T> *next(Node<T> *node) { 
        Node<T> *current = node->right;
        
        while (current->left != nullptr)
            current = current->left;
        
        return current;
    }
    
    int height(const Node<T> * const node) const{
        return node == nullptr ? 0 : node->height; 
    }
    
    int getBalance(const Node<T> * const node) const{ 
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }
// балансировка
    void leftRotate(Node<T>*& node) { 
        Node<T>* result = node->right;
        Node<T>* tmp = result->left;
        
   
        result->left = node;
        node->right = tmp;
        
   
        node->height = std :: max(height(node->left), height(node->right)) + 1;
        result->height = std :: max(height(result->left), height(result->right)) + 1;
        
     
        node = result;
    }
    
    void rightRotate(Node<T>*& node) { 
        Node<T>* result = node->left;
        Node<T>* tmp = result->right;
        
    
        result->right = node;
        node->left = tmp;
        

        node->height = std :: max(height(node->left), height(node->right)) + 1;
        result->height = std :: max(height(result->left), height(result->right)) + 1;
        
    
        node = result;
    }

    
    void insertNode(Node<T>*& node, const T key, Node<T>** res) {
      
        if (node == nullptr) {
            node = new Node<T>;
            node->key = key;
            node->left = nullptr;
            node->right = nullptr;
            node->height = 1;
            *res = node;
        }
        
        if (key < node->key) 
            insertNode(node->left, key, res);
        else if (key > node->key) 
            insertNode(node->right, key, res);
        
        node->height = 1 + std :: max(height(node->left), height(node->right));
        
        int balance = getBalance(node);
        
        if (balance > 1 && key < node->left->key) {
            rightRotate(node);
            return;
        }
        
        if (balance < -1 && key > node->right->key) {
            leftRotate(node);
            return;
        }
        
        if (balance > 1 && key > node->left->key)
        {
            leftRotate(node->left);
            return rightRotate(node);
        }
        
        if (balance < -1 && key < node->right->key)
        {
            rightRotate(node->right);
            return leftRotate(node);
        }
    }
    
    void deleteNode(Node<T>*& node, T key, Node<T>** res) {
        if (node == nullptr)
            return;
        
        if ( key < node->key )
            deleteNode(node->left, key, res);
        
        else if( key > node->key )
            deleteNode(node->right, key, res);
        
        else
        {
            if( (node->left == nullptr) || (node->right == nullptr) )
            {
                Node<T> *temp = node->left ? node->left : node->right;
                
                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                
                *res = temp;
            }
            else
            {
                Node<T>* temp = next(node);
                
                node->key = temp->key;
                
                deleteNode(node->right, temp->key, res);
            }
        }
        
        if (node == nullptr)
            return;
        
        node->height = 1 + std :: max(height(node->left), height(node->right));
        // перестройка для сохранения баланса
        int balance = getBalance(node);
        
        if (balance > 1 && getBalance(node->left) >= 0) {
            rightRotate(node);
            return;
        }
        
        if (balance > 1 && getBalance(node->left) < 0)
        {
            leftRotate(node->left);
            rightRotate(node);
            return;
        }
        
        if (balance < -1 && getBalance(node->right) <= 0) {
            leftRotate(node);
            return;
        }
        
        if (balance < -1 && getBalance(node->right) > 0)
        {
            rightRotate(node->right);
            leftRotate(node);
            return;
        }
    }
    
    Node<T>* ExistNode(Node<T> *& node, const int key) {
        if (node == nullptr)
            return nullptr;
        if (node->key == key)
            return node;
        if (node->key > key)
            return ExistNode(node->left, key);
        else
            return ExistNode(node->right, key);
    }
};

int main() {
   
    BSTTree<int> tree;
    
    std::cout <<  *tree.insert(1) << '\n';
    std::cout <<  *tree.insert(3) << '\n';
    std::cout <<  *tree.insert(2) << '\n';

    
    std::cout << "1-First: " << *tree.begin() << '\n';
    std::cout << "1-Second: " << *tree.begin()++ << '\n';
    std::cout << "1-Last: " << *tree.end() << '\n';

    std::cout << "1-Deleted: " << *tree.Delete(3) << '\n';
    std::cout << "1-Find: " << *tree.find(1) << '\n';
    std::cout << "1-Size: " << tree.size() << '\n';
    std::cout << "1-Is Empty: " << tree.empty() << '\n';

    BSTTree<int> tree1;
    tree1 = tree;
    
    std::cout <<  *tree1.insert(4) << '\n';
    std::cout << *tree1.insert(5) << '\n';
    std::cout << *tree1.insert(0) << '\n';
    std::cout << "1+2-First : " << *tree1.begin() << '\n';
    std::cout << "1+2-Second: " << *tree1.begin()++ << '\n';
    std::cout << "1+2-Last : " << *tree1.end() << '\n';
    std::cout << "1+2-size: " << tree1.size();
    
    return 0;
}
