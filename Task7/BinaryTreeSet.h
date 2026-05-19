#ifndef BINARY_TREE_SET_IMPL_H
#define BINARY_TREE_SET_IMPL_H

#include "SetImplementation.h"

template <typename Object>
class BinaryTreeSetImpl : public SetImplementation<Object>
{
private:
    struct Node
    {
        Object data;
        Node *left;
        Node *right;

        Node(const Object &obj) : data(obj), left(nullptr), right(nullptr) {}
    };

    Node *root;
    int count;
    static const int MIN_TREE_SIZE = 50;

    Node *insertRec(Node *node, const Object &obj)
    {
        if (node == nullptr)
        {
            count++;
            return new Node(obj);
        }

        if (obj < node->data)
        {
            node->left = insertRec(node->left, obj);
        }
        else if (obj > node->data)
        {
            node->right = insertRec(node->right, obj);
        }
        return node;
    }

    Node *findMin(Node *node) const
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node *removeRec(Node *node, const Object &obj)
    {
        if (node == nullptr)
            return nullptr;

        if (obj < node->data)
        {
            node->left = removeRec(node->left, obj);
        }
        else if (obj > node->data)
        {
            node->right = removeRec(node->right, obj);
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                count--;
                return nullptr;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                count--;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                count--;
                return temp;
            }
            else
            {
                Node *minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = removeRec(node->right, minNode->data);
            }
        }
        return node;
    }

    bool containsRec(Node *node, const Object &obj) const
    {
        if (node == nullptr)
            return false;
        if (obj < node->data)
            return containsRec(node->left, obj);
        if (obj > node->data)
            return containsRec(node->right, obj);
        return true;
    }

    void clearRec(Node *node)
    {
        if (node == nullptr)
            return;
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }

    Node *cloneRec(Node *node) const
    {
        if (node == nullptr)
            return nullptr;
        Node *newNode = new Node(node->data);
        newNode->left = cloneRec(node->left);
        newNode->right = cloneRec(node->right);
        return newNode;
    }

    void collectElementsRec(Node *node, Object *arr, int &index) const
    {
        if (node == nullptr)
            return;
        collectElementsRec(node->left, arr, index);
        arr[index++] = node->data;
        collectElementsRec(node->right, arr, index);
    }

public:
    BinaryTreeSetImpl() : root(nullptr), count(0) {}

    BinaryTreeSetImpl(const BinaryTreeSetImpl &other) : count(other.count)
    {
        root = cloneRec(other.root);
    }

    ~BinaryTreeSetImpl()
    {
        clearRec(root);
    }

    void insert(const Object &obj) override
    {
        if (contains(obj))
            return;
        root = insertRec(root, obj);
    }

    void remove(const Object &obj) override
    {
        root = removeRec(root, obj);
    }

    bool contains(const Object &obj) const override
    {
        return containsRec(root, obj);
    }

    int size() const override
    {
        return count;
    }

    bool isEmpty() const override
    {
        return count == 0;
    }

    void clear() override
    {
        clearRec(root);
        root = nullptr;
        count = 0;
    }

    SetImplementation<Object> *clone() const override
    {
        return new BinaryTreeSetImpl<Object>(*this);
    }

    const Object *getElements() const override
    {
        Object *arr = new Object[count];
        int index = 0;
        collectElementsRec(root, arr, index);
        return arr;
    }

    bool shouldSwitchToBinaryTree() const override
    {
        return false;
    }

    bool shouldSwitchToArray() const override
    {
        return count < MIN_TREE_SIZE;
    }
};

#endif