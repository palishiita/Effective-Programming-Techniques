#include <iostream>
#include "CNodeDynamic.cpp"
#include <string>

// TEMPLATE CLASS  
template <typename T> class CTreeDynamic {

private:
    CNodeDynamic<T> *pc_root;   

public:
    CTreeDynamic();
    ~CTreeDynamic();
    CNodeDynamic<T> *pcGetRoot();
    void vPrintTree();
    std::string sGetKnownType();
};


// - - - - - Class methods - - - - -

/** constructor */ 
template <typename T>
CTreeDynamic<T>::CTreeDynamic() {
    CNodeDynamic<T> *root = new CNodeDynamic<T>();
    pc_root = root;
}

/** destructor */
template <typename T>
CTreeDynamic<T>::~CTreeDynamic() {
    delete pc_root;
}

/** prints the entire tree starting from the root */
template <typename T> 
void CTreeDynamic<T>::vPrintTree() {
    pc_root->vPrintAllBelow();
}

/** returns the tree root node */
template <typename T> 
CNodeDynamic<T> *CTreeDynamic<T>::pcGetRoot() { 
    return pc_root; 
}

template <typename T>
std::string CTreeDynamic<T>::sGetKnownType() {
    std::string s_type = "Unknown";
    return (s_type);
}

template <>
std::string CTreeDynamic<int>::sGetKnownType() {
    std::string s_type = "INT";
    return (s_type);
}

template <>
std::string CTreeDynamic<double>::sGetKnownType() {
    std::string s_type = "DOUBLE";
    return (s_type);
}

template <>
std::string CTreeDynamic<char>::sGetKnownType() {
    std::string s_type = "CHAR";
    return (s_type);
}

template <>
std::string CTreeDynamic<float>::sGetKnownType() {
    std::string s_type = "FLOAT";
    return (s_type);
}


// - - - - - Additional functions - - - - -

/** moves a subtree from one tree to another tree */
template <typename T> 
bool bMoveSubtree(CNodeDynamic<T> *pc_parent_node, CNodeDynamic<T> *pc_new_child_node) {
    
    if (!pc_parent_node || !pc_new_child_node) {
        return false;
    }
    // adding a new child node to the new parent node
    pc_parent_node->vAddNewChild(pc_new_child_node);
    // removing the new child from old parent 
    if (pc_new_child_node->getPcParentNode()) {
        pc_new_child_node->getPcParentNode()->removeChild(pc_new_child_node);
    }
    // setting the new parent for new child node  
    pc_new_child_node->setPcParentNode(pc_parent_node);
    return true;
}

/** testing tree methods */
void vTreeTest() {

    std::cout << "\n---------> Dynamic Tree Test <---------\n" << std::endl;

    std::cout << "\n\tTESTING     CTreeDynamic<int>\n" << std::endl;

    CTreeDynamic<float> *tree_1;
    tree_1 = new CTreeDynamic<float>();
    tree_1->pcGetRoot()->vSetValue(1); // root 
    tree_1->pcGetRoot()->vAddNewChild();
    tree_1->pcGetRoot()->vAddNewChild();
    tree_1->pcGetRoot()->pcGetChild(0)->vSetValue(3); 
    tree_1->pcGetRoot()->pcGetChild(1)->vSetValue(5); 
    tree_1->pcGetRoot()->pcGetChild(0)->vAddNewChild();
    tree_1->pcGetRoot()->pcGetChild(0)->vAddNewChild();
    tree_1->pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(7);
    tree_1->pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(9);
    std::cout << "tree_1 originally:\t\t";
    tree_1->vPrintTree();

    
    CTreeDynamic<float> *tree_2;
    tree_2 = new CTreeDynamic<float>();
    tree_2->pcGetRoot()->vSetValue(2); 
    tree_2->pcGetRoot()->vAddNewChild();
    tree_2->pcGetRoot()->vAddNewChild();
    tree_2->pcGetRoot()->pcGetChild(0)->vSetValue(4);
    tree_2->pcGetRoot()->pcGetChild(1)->vSetValue(6);
    tree_2->pcGetRoot()->pcGetChild(0)->vAddNewChild();
    tree_2->pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(8);
    tree_2->pcGetRoot()->pcGetChild(1)->vAddNewChild();
    tree_2->pcGetRoot()->pcGetChild(1)->vAddNewChild();
    tree_2->pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(10);
    tree_2->pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(12);
    tree_2->pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vAddNewChild();
    tree_2->pcGetRoot()->pcGetChild(1)->pcGetChild(1)->pcGetChild(0)->vSetValue(14);

    std::cout << std::endl << "tree_2 originally:\t\t";
    tree_2->vPrintTree();

    bMoveSubtree(tree_1->pcGetRoot(), tree_2->pcGetRoot()->pcGetChild(1));

    std::cout << std::endl << "tree_1 after move:\t\t";
    tree_1->vPrintTree();
    std::cout << std::endl << "tree_2 after move:\t\t";
    tree_2->vPrintTree();
    std::cout << std::endl << std::endl;
    std::cout << "tree_1 type:\t\t\t" <<tree_1->sGetKnownType() << std::endl;
    std::cout << "tree_2 type:\t\t\t" <<tree_2->sGetKnownType() << std::endl;
    std::cout << std::endl;



    std::cout << "\n\n\tTESTING     CTreeDynamic<char>\n" << std::endl;

    CTreeDynamic<char> *tree_3;
    tree_3 = new CTreeDynamic<char>();
    tree_3->pcGetRoot()->vSetValue('a'); // root 
    tree_3->pcGetRoot()->vAddNewChild();
    tree_3->pcGetRoot()->vAddNewChild();
    tree_3->pcGetRoot()->pcGetChild(0)->vSetValue('b'); 
    tree_3->pcGetRoot()->pcGetChild(1)->vSetValue('c'); 
    tree_3->pcGetRoot()->pcGetChild(0)->vAddNewChild();
    tree_3->pcGetRoot()->pcGetChild(0)->vAddNewChild();
    tree_3->pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue('d');
    tree_3->pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue('e');
    std::cout << "tree_3 originally:\t\t" ;
    tree_3->vPrintTree();

    CTreeDynamic<char> *tree_4;
    tree_4 = new CTreeDynamic<char>();
    tree_4->pcGetRoot()->vSetValue('f'); // root 
    tree_4->pcGetRoot()->vAddNewChild();
    tree_4->pcGetRoot()->vAddNewChild();
    tree_4->pcGetRoot()->pcGetChild(0)->vSetValue('g'); 
    tree_4->pcGetRoot()->pcGetChild(1)->vSetValue('h'); 
    tree_4->pcGetRoot()->pcGetChild(1)->vAddNewChild();
    tree_4->pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue('i');
    std::cout << std::endl << "tree_4 originally:\t\t";
    tree_4->vPrintTree();

    bMoveSubtree(tree_3->pcGetRoot(), tree_4->pcGetRoot()->pcGetChild(1));

    std::cout << std::endl << "tree_3 after move:\t\t";
    tree_3->vPrintTree();
    std::cout << std::endl << "tree_4 after move:\t\t";
    tree_4->vPrintTree();
    std::cout << std::endl << std::endl;
    std::cout << "tree_3 type:\t\t\t" <<tree_3->sGetKnownType() << std::endl;
    std::cout << "tree_4 type:\t\t\t" <<tree_4->sGetKnownType() << std::endl;
    std::cout << std::endl;

    delete tree_1;
    delete tree_2;
    delete tree_3;
    delete tree_4;
}

int main() {
    vTreeTest();
    return 0;
}