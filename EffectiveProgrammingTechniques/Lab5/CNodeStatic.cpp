#include <iostream>
#include <vector>

// Objects of CNodeStatic represent static nodes in the tree
class CNodeStatic {
private: // fields
    std::vector<CNodeStatic> v_children;
    CNodeStatic *pc_parent_node; // pointer to parent node 
    int i_val;
public: // methods 
    CNodeStatic();
    ~CNodeStatic();
    void vSetValue(int i_new_val);
    int iGetChildrenNumber();
    void vAddNewChild();
    CNodeStatic *pcGetChild(int i_child_offset);
    CNodeStatic *getPcParentNode() const;
    int getIVal() const;
    void setPcParentNode(CNodeStatic *pc_new_parent_node);
    void removeChild(CNodeStatic *pc_child_to_remove);
    void removeAllChildren();
    void vPrint();
    void vPrintAllBelow();
    void vPrintUp();
    int printDistanceToRoot();
};

// constructor initializes root with value 0
CNodeStatic::CNodeStatic() {
    i_val = 0;
    pc_parent_node = nullptr;
}

CNodeStatic::~CNodeStatic() { 
    
}

void CNodeStatic::vSetValue(int i_new_val) {
    i_val = i_new_val;
}

int CNodeStatic::iGetChildrenNumber() {
    return v_children.size();
}

// adds a new child to the children vector of the node 
void CNodeStatic::vAddNewChild() {
    CNodeStatic c_node_to_add = CNodeStatic();
    c_node_to_add.pc_parent_node = this;
    v_children.push_back(c_node_to_add);
}

/* method returns a child in a given position, 
   if position is incorrect then returns NULL */
CNodeStatic *CNodeStatic::pcGetChild(int i_child_position) {
    if ((i_child_position < 0) || (i_child_position >= v_children.size())) {
        return nullptr;
    }
    return &v_children[i_child_position];
}

CNodeStatic *CNodeStatic::getPcParentNode() const {
    return pc_parent_node;
}

void CNodeStatic::setPcParentNode(CNodeStatic *pc_new_parent_node) {
    pc_parent_node = pc_new_parent_node;
}

void CNodeStatic::removeChild(CNodeStatic *pc_child_to_remove) {
    for (int i = 0; i < iGetChildrenNumber(); i++) {
        if (&v_children[i] == pc_child_to_remove) {
            v_children.erase(v_children.begin() + i);
        }
    }
}

void CNodeStatic::removeAllChildren() {
    v_children.clear();
}

// prints the value of node 
void CNodeStatic::vPrint() { 
    std::cout << " " << i_val; 
}

// display values of node and its children down the tree
void CNodeStatic::vPrintAllBelow() {
    vPrint();
    for (int i = 0; i < v_children.size(); i++) {
        this->pcGetChild(i)->vPrintAllBelow();
    }
}

/* display values of all its parents, from selected node to root. */
void CNodeStatic::vPrintUp() {
    vPrint();
    int sum = 0;
    if (pc_parent_node != nullptr) {
        pc_parent_node->vPrintUp();
        for (int i = 0; i < v_children.size(); i++) {
            sum++;
        }
        std::cout << std::endl;
        std::cout << "distance: " << sum << std::endl;
    }
}

int CNodeStatic::getIVal() const {
    return i_val;
}

void vTreeTest1() {
    CNodeStatic c_root; 

    c_root.vAddNewChild();
    c_root.vAddNewChild();
    c_root.pcGetChild(0)->vSetValue(1); 
    c_root.pcGetChild(1)->vSetValue(2);

    c_root.pcGetChild(0)->vAddNewChild();
    c_root.pcGetChild(0)->vAddNewChild();
    c_root.pcGetChild(0)->pcGetChild(0)->vSetValue(11);
    c_root.pcGetChild(0)->pcGetChild(1)->vSetValue(12);
    
    c_root.pcGetChild(1)->vAddNewChild();
    c_root.pcGetChild(1)->vAddNewChild();
    c_root.pcGetChild(1)->pcGetChild(0)->vSetValue(21);
    c_root.pcGetChild(1)->pcGetChild(1)->vSetValue(22);
    /*
    std::cout << "Print all below:" << std::endl;
    c_root.vPrintAllBelow();
    std::cout << std::endl;
    */

    std::cout << "Print up:" << std::endl;
    c_root.pcGetChild(0)->pcGetChild(1)->vPrintUp();
    std::cout << std::endl;
    //c_root.pcGetChild(0)->pcGetChild(0)->vPrintUp();
    std::cout << std::endl;
    //c_root.pcGetChild(1)->pcGetChild(0)->vPrintUp();
    std::cout << std::endl;
    //c_root.pcGetChild(1)->pcGetChild(1)->vPrintUp();
    std::cout << std::endl;
}

void v_tree_test()
{
	CNodeStatic c_root;
	c_root.vAddNewChild();
	c_root.vAddNewChild();
	c_root.pcGetChild(0)->vSetValue(1);
	c_root.pcGetChild(1)->vSetValue(2);
	c_root.pcGetChild(0)->vAddNewChild();
	c_root.pcGetChild(0)->vAddNewChild();
	c_root.pcGetChild(0)->pcGetChild(0)->vSetValue(3);
	c_root.pcGetChild(0)->pcGetChild(1)->vSetValue(4);
	c_root.pcGetChild(1)->vAddNewChild();
	c_root.pcGetChild(1)->vAddNewChild();
	c_root.pcGetChild(1)->pcGetChild(0)->vSetValue(6);
	c_root.pcGetChild(1)->pcGetChild(1)->vSetValue(5);

    std::cout << "full tree";
	c_root.vPrintAllBelow();
	std::cout << std::endl;
	std::cout << "distance to the root: ";
	c_root.pcGetChild(0)->pcGetChild(1)->vPrintUp();
    std::cout <<std::endl;
    //std::cout<< "3" <<std::endl;
}