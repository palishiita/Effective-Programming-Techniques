#include <iostream>
#include "CNodeStatic.cpp"

/* The CNodeStatic should not be a class with which the program communicates directly. 
Wrap it with a tree in CTreeStatic class */
class CTreeStatic {
// fields
private:
    CNodeStatic c_root;
// methods    
public:
    CTreeStatic();
    ~CTreeStatic();
    CNodeStatic* pcGetRoot();
    void vPrintTree();
};

CTreeStatic::CTreeStatic() {
    // calling the CNodeStatic constructor 
    c_root = CNodeStatic();
}

CTreeStatic::~CTreeStatic() {
}

CNodeStatic *CTreeStatic::pcGetRoot() { 
    return (&c_root); 
}

void CTreeStatic::vPrintTree() {
    c_root.vPrintAllBelow();
}

// sub tree from the source is copied 
void vCopyTreeRecursive(CNodeStatic *pc_destination, 
                        CNodeStatic *pc_source) {
    // adds a new child to the destination node (parent node)
    pc_destination->vAddNewChild(); 
    // get the child at destination node
    pc_destination->pcGetChild(pc_destination->iGetChildrenNumber()-1)->vSetValue(pc_source->getIVal());
    
    if (pc_source->iGetChildrenNumber() > 0) {
        for (int i = 0; i < pc_source->iGetChildrenNumber(); i++) 
        {
            vCopyTreeRecursive(pc_destination->pcGetChild(pc_destination->iGetChildrenNumber()-1),
            pc_source->pcGetChild(i));
        }
    }
}

/*
Given pcNewChildNode (node and its children form a subtree)
its subtree is removed from source tree .
Its added to a destination tree as a child node of pcParentNode.
*/
bool bMoveSubtree(CNodeStatic *pc_parent_node,     
                  CNodeStatic *pc_new_child_node) {
    if (!pc_parent_node || !pc_new_child_node) {
        return false;
    }
   
    vCopyTreeRecursive(pc_parent_node, pc_new_child_node);
    // Old parent 
    if (pc_new_child_node->getPcParentNode()) {
        // not a root
        pc_new_child_node->getPcParentNode()->removeChild(pc_new_child_node);
    } else {
        // root
        pc_new_child_node->removeAllChildren();
    }
    return true;
}

void printNodeDistance(CNodeStatic node) {
    
} 

void vTreeTest2() {
    // creating c_tree1
    CTreeStatic c_root1;
    c_root1.pcGetRoot()->vSetValue(1); // root
    c_root1.pcGetRoot()->vAddNewChild();
    c_root1.pcGetRoot()->pcGetChild(0)->vSetValue(2); //left 
    c_root1.pcGetRoot()->vAddNewChild();
    c_root1.pcGetRoot()->pcGetChild(1)->vSetValue(3); // right
    c_root1.pcGetRoot()->vAddNewChild();
    c_root1.pcGetRoot()->pcGetChild(2)->vSetValue(4);
    c_root1.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_root1.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(5);
    c_root1.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_root1.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(6);
    
    std::cout << "c_tree_1 before move: " << std::endl;
    c_root1.vPrintTree(); // 1, 2, 3, 4, 5
    std::cout << std::endl;

    // creating c_tree2
    CTreeStatic c_root2;
    c_root2.pcGetRoot()->vSetValue(10);
    c_root2.pcGetRoot()->vAddNewChild();
    c_root2.pcGetRoot()->pcGetChild(0)->vSetValue(20);
    std::cout << "c_tree_2 before move: " << std::endl;
    c_root2.vPrintTree(); // 10, 20
    std::cout << std::endl;

    // moving subtree
    bMoveSubtree(c_root1.pcGetRoot(), // 1
                 c_root2.pcGetRoot()->pcGetChild(0)); // 20
    
    std::cout << "c_tree_1 after move: " << std::endl;
    c_root1.vPrintTree(); 
    
    std::cout << std::endl << "c_tree_2 after move: " << std::endl;
    c_root2.vPrintTree(); 

    std::cout  << std::endl;
}
