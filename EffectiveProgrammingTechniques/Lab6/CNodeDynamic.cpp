#include <iostream>
#include <vector>

// Objects of CNodeDynamic represent dynamic pointers
template <typename T> class CNodeDynamic {

private:
    std::vector<CNodeDynamic *> v_children; // vector with children nodes
    CNodeDynamic *pc_parent_node;           // a pointer to the parent node
    T i_val;                                // value stored inside the node

public:
    CNodeDynamic();
    ~CNodeDynamic();
    void vSetValue(T i_new_val);
    int iGetChildrenNumber();
    void vAddNewChild();
    void vAddNewChild(CNodeDynamic<T> *c_node_to_append);
    CNodeDynamic<T> *pcGetChild(int i_child_offset);
    void vPrint();
    void vPrintAllBelow();
    CNodeDynamic<T> *getPcParentNode();
    void setPcParentNode(CNodeDynamic<T> *pc_parent_node);
    void removeChild(CNodeDynamic<T> *pc_child_to_remove);
    T getIVal() const;
    CNodeDynamic<T> *getChild(int i_child_offset);
};

/** constructor */
template <typename T> 
CNodeDynamic<T>::CNodeDynamic() {
    i_val = T();    // value initialization of the i_val, performs zero-initialization
    pc_parent_node = nullptr;
}

/** destructor */
template <typename T> 
CNodeDynamic<T>::~CNodeDynamic() {
    if (iGetChildrenNumber() == 0) {
        return;
    } else {
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            delete v_children[i];
        }
    }
}

/** sets the node value to the one given as paramater */
template <typename T> 
void CNodeDynamic<T>::vSetValue(T i_new_val) {
    i_val = i_new_val;
}

/** return the length of the children vector */
template <typename T> 
int CNodeDynamic<T>::iGetChildrenNumber() { 
    return v_children.size(); 
}

/** add a new child node with default value */
template <typename T> 
void CNodeDynamic<T>::vAddNewChild() {
    CNodeDynamic *newNode;
    newNode = new CNodeDynamic();
    newNode->setPcParentNode(this);
    v_children.push_back(newNode);
    newNode = nullptr;
}

/** adds a new child passed as parameter to the children vector */
template <typename T> 
void CNodeDynamic<T>::vAddNewChild(CNodeDynamic *c_node_to_append) {
    v_children.push_back(c_node_to_append);
}

/** returns the child node at given position in children vector */
template <typename T> 
CNodeDynamic<T> *CNodeDynamic<T>::pcGetChild(int i_child_position) {
    if (i_child_position >= iGetChildrenNumber() || i_child_position < 0)
        return nullptr;
    return v_children[i_child_position];
}

/** prints the node value */
template <typename T> 
void CNodeDynamic<T>::vPrint() { 
    std::cout << " " << i_val; 
}

/** prints the node and all sub-nodes in recursive fashion */
template <typename T> 
void CNodeDynamic<T>::vPrintAllBelow() {
    vPrint();
    for (int i = 0; i < iGetChildrenNumber(); i++) {
        v_children[i]->vPrintAllBelow();
    }
}

/** returns the parent node */
template <typename T> 
CNodeDynamic<T> *CNodeDynamic<T>::getPcParentNode() {
    return pc_parent_node;
}

/** sets the given node as parent node */
template <typename T> 
void CNodeDynamic<T>::setPcParentNode(CNodeDynamic<T> *pc_new_parent_node) {
    pc_parent_node = pc_new_parent_node;
}

/** removes the given node from current nodes children vector */
template <typename T> 
void CNodeDynamic<T>::removeChild(CNodeDynamic<T> *pc_child_to_remove) {
    for (int i = 0; i < iGetChildrenNumber(); i++) {
        if ((*v_children[i]).i_val == pc_child_to_remove->i_val) {
            v_children.erase(v_children.begin() + i);
        }
    }
}

/** returns the value stored inside the node */
template <typename T> 
T CNodeDynamic<T>::getIVal() const {
    return i_val;
}

/** returns the child node at given position in the children vector */
template <typename T> 
CNodeDynamic<T> *CNodeDynamic<T>::getChild(int i_child_offset) {
    return v_children[i_child_offset];
}