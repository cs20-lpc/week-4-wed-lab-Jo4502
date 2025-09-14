template <typename T>
LinkedList<T>::LinkedList()
: head(nullptr) { }

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::append(const T& elem) {
    Node* n = new Node(elem);

    if (head == nullptr) {
        head = n;
    }
    else {
        Node* curr = head;

        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = n;
    }

    this->length++;
}

template <typename T>
void LinkedList<T>::clear() {
    Node* prev = nullptr;

    while (head != nullptr) {
        prev = head;
        head = head->next;
        delete prev;
    }

    this->length = 0;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& copyObj) {
    // TODO

    head = nullptr;              //making sure list is empty
    this->length = 0;

    if (copyObj.head == nullptr) {
        return;                      // If the list we are copying from has no nodes, just return
    }

    head = new Node(copyObj.head->value);       // Create a new node for 1st of this list and increment 1 = lenght 
    this->length++;

    Node* old = copyObj.head->next;
    Node* currNew = head;

    while (old != nullptr) {                // loop until the end of list

        currNew->next = new Node(old->value);           // make a new node with same as an old node
        currNew = currNew->next;                        // move the new pointer forward to the new node
        old = old->next;
        this->length++;                                 // increase lenght b/c new node
    }
}

template <typename T>
T LinkedList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }
    
    Node* curr = head;

    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    return curr->value;
}

template <typename T>
int LinkedList<T>::getLength() const {
    return this->length;
}

template <typename T>
void LinkedList<T>::insert(int position, const T& elem) {
    // TODO
    if (position < 0 || position > this->length) {
        throw string("insert = error");
    }

    if (position == 0) {                                             // make one at the front of the list
        Node* n = new Node(elem, head);
        head = n;
    }
    else {                      //start from the head
        Node* curr = head;

        for (int i = 0; i < position - 1; i++) {                    // stop one before the one we are inserting
            curr = curr->next;
        }

        Node* n = new Node(elem, curr->next);                       // make a node that points to the next one so the one we need
        curr->next = n;
    }
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
void LinkedList<T>::remove(int position) {
    // TODO
    if (position < 0 || position >= this->length) {
        throw string("remove = error"); 
    }
    Node* Delete = nullptr;                 // make a pointer for the one being removed

    if (position == 0) {
        Delete = head;                // mark the head to be removed
        head = head->next;              // move head to the next node
    }
    else {
        Node* curr = head;              // start moving from head

        for (int i = 0; i < position - 1; i++) {        // stop one before the one being deleted
            curr = curr->next;
        }

        Delete = curr->next;              // the one being deleted is the next one
        curr->next = Delete->next;      
    }
    delete Delete;                  // free memeory
    this->length--;                 // decreaselenght since we deleted one
}

template <typename T>
void LinkedList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }

    Node* curr = head;

    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    curr->value = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const LinkedList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename LinkedList<T>::Node* curr = myObj.head;
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
                outStream << " --> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}
