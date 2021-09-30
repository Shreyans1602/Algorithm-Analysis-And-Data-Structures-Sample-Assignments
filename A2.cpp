/**
 * @brief: A2.cpp.
 * 
 * @paragraph: Code Description - This code is used to demonstrate a delete operation from a Binary Search Tree (BST).
 * 
 * @paragraph: Problem Statement - We have discussed Binary Search Trees (BST). Write a program to implement a delete operation from BST. You will have to write the program to insert nodes in the BST also (we already did the algorithm in detail in the class for insert). DO NOT USE ANY LIBRARIES. Insert the following nodes in the order mentioned here. 40, 60, 20, 80, 50, 10, 30, 15, 5, 35, 25, 45, 55, 70, 90, 32, 33, 48, 46. Do an inorder traversal. Now delete 40 (you decide predecessor or successor). Do inorder traversal again. Now delete 20. Do inorder traversal.
 * 
 * @author: Shreyans Patel (SSP210009)
 */

#include <iostream>
#include <stdlib.h>

int DataArr[19] = {40, 60, 20, 80, 50, 10, 30, 15, 5, 35, 25, 45, 55, 70, 90, 32, 33, 48, 46};

int DataArrElementNum = (sizeof(DataArr)/sizeof(DataArr[0]));

//Node structure of the BST. Each node has an integer value and pointers to left child and right child of type "Node".
struct BSTNode
{
    int val;        //val: Variable with integer value.
    BSTNode *left;     //left: Pointer to left child.
    BSTNode *right;     //right: Pointer to right child.
    
    //Initializing structure members with default values.
    BSTNode()
    {
        val = 0;
        left = NULL;
        right = NULL;
    }
};

//Initializing the root pointer for the BST.
BSTNode *pRoot = NULL;

BSTNode* getNewBSTNode(int iVal)
{
    BSTNode *tNode = NULL;

    tNode = new BSTNode;

    if(NULL == tNode)
    {
        std::cout<<"Memory allocation failed.....exiting....."<<std::endl;
    }

    tNode->val = iVal;

    return tNode;
}

void insertBSTNode(BSTNode *iBSTNode)
{
    if(NULL == iBSTNode)
    {
        return;
    }

    if(NULL == pRoot)
    {
        pRoot = iBSTNode;
        return;
    }

    BSTNode *tBSTNode = pRoot;

    while(true)
    {
        if(tBSTNode->val <= iBSTNode->val)
        {
            if(NULL == tBSTNode->right)
            {
                tBSTNode->right = iBSTNode;
                return;
            }

            tBSTNode = tBSTNode->right;
        }

        if(tBSTNode->val > iBSTNode->val)
        {
            if(NULL == tBSTNode->left)
            {
                tBSTNode->left = iBSTNode;
                return;
            }

            tBSTNode = tBSTNode->left;
        }
    }
}

void createRequiredTree(void)
{
    for(int tIterator = 0; tIterator < DataArrElementNum; tIterator++)
    {
        BSTNode *tpBSTNode = getNewBSTNode(DataArr[tIterator]);

        if(NULL == tpBSTNode)
        {
            return;
        }

        insertBSTNode(tpBSTNode);

        tpBSTNode = NULL;
    }
}

/**
 * @brief: printByInorderTraversal.
 * @details: Used to print the array contents.
 * @param: iArr (Input) - Array that needs to be printed.
 * @return none.
 */
void printByInorderTraversal(BSTNode *ipBSTNode)
{
    if(NULL == ipBSTNode)
    {
        return;
    }

    printByInorderTraversal(ipBSTNode->left);
    std::cout<<ipBSTNode->val<<"    ";
    printByInorderTraversal(ipBSTNode->right);
}

void deleteBSTNode(int iVal)
{
    if(NULL == pRoot)
    {
        return;
    }
    
    BSTNode *tpBSTNode = pRoot;
    BSTNode *tpBSTNodeToDelete = NULL;
    BSTNode *tpBSTSuccessorNodeParent = NULL;
    BSTNode *tpBSTSuccessorNode = NULL;

    while(true)
    {
        if(tpBSTNode->val == iVal)
        {
            tpBSTNodeToDelete = tpBSTNode;
            break;
        }

        if(tpBSTNode->val > iVal)
        {
            if(NULL == tpBSTNode->left)
            {
                return;
            }

            tpBSTSuccessorNodeParent = tpBSTNode;
            tpBSTNode = tpBSTNode->left;
        }

        if(tpBSTNode->val < iVal)
        {
            if(NULL == tpBSTNode->right)
            {
                return;
            }

            tpBSTSuccessorNodeParent = tpBSTNode;
            tpBSTNode = tpBSTNode->right;
        }
    }

    //Leaf Node Handling
    if((NULL == tpBSTNodeToDelete->right) && (NULL == tpBSTNodeToDelete->left))
    {
        //Root Node is the node to delete and it is also the leaf node
        if(pRoot == tpBSTNodeToDelete)
        {
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
            pRoot = NULL;
            return;
        }
        if(tpBSTSuccessorNodeParent->left == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = NULL;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        else if(tpBSTSuccessorNodeParent->right == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->right = NULL;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        return;
    }

    //Node to delete only has left child
    if((NULL == tpBSTNodeToDelete->right) && (NULL != tpBSTNodeToDelete->left))
    {
        //Root Node is the node to delete and it has only a left child
        if(pRoot == tpBSTNodeToDelete)
        {
            pRoot = tpBSTNodeToDelete->left;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
            return;
        }
        if(tpBSTSuccessorNodeParent->left == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = tpBSTNodeToDelete->left;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        else if(tpBSTSuccessorNodeParent->right == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->right = tpBSTNodeToDelete->left;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        return;
    }

    //Node to delete only has right child
    if((NULL != tpBSTNodeToDelete->right) && (NULL == tpBSTNodeToDelete->left))
    {
        //Root Node is the node to delete and it has only a right child
        if(pRoot == tpBSTNodeToDelete)
        {
            pRoot = tpBSTNodeToDelete->right;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
            return;
        }
        if(tpBSTSuccessorNodeParent->left == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = tpBSTNodeToDelete->right;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        else if(tpBSTSuccessorNodeParent->right == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->right = tpBSTNodeToDelete->right;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        return;
    }

    tpBSTSuccessorNode = tpBSTNodeToDelete;
    tpBSTSuccessorNodeParent = tpBSTSuccessorNode;
    tpBSTSuccessorNode = tpBSTSuccessorNode->right;

    while(NULL != tpBSTSuccessorNode->left)
    {
        tpBSTSuccessorNodeParent = tpBSTSuccessorNode;
        tpBSTSuccessorNode = tpBSTSuccessorNode->left;
    }

    tpBSTNodeToDelete->val = tpBSTSuccessorNode->val;

    if(NULL != tpBSTSuccessorNode->right)
    {
        if(tpBSTSuccessorNodeParent != tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = tpBSTSuccessorNode->right;
        }
        else
        {
            tpBSTSuccessorNodeParent->right = tpBSTSuccessorNode->right;
        }
    }
    else
    {
        if(tpBSTSuccessorNodeParent != tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = NULL;
        }
        else
        {
            tpBSTSuccessorNodeParent->right = NULL;
        }
    }

    delete tpBSTSuccessorNode;
    tpBSTSuccessorNode = NULL;
}

int main()
{
    createRequiredTree();
    std::cout<<"====>   ";
    printByInorderTraversal(pRoot);
    std::cout<<std::endl<<std::endl;
    deleteBSTNode(40);
    std::cout<<"====>   ";
    printByInorderTraversal(pRoot);
    std::cout<<std::endl<<std::endl;
    deleteBSTNode(20);
    std::cout<<"====>   ";
    printByInorderTraversal(pRoot);
    std::cout<<std::endl<<std::endl;
    return 0;
}