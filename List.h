#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <exception>
#include <string>

///definicion
template <class T>
class List{
    private:
        class Node{
            private:
            T* dataPtr;
            Node* prev;
            Node* next;

            public:
                class Exception : public std::exception{
                    private:
                        std::string msg;
                    public:
                        explicit Exception(const char* message) : msg(message) {}

                        explicit Exception(const std::string& message) : msg(message) {}

                        virtual ~Exception() throw() {}

                        virtual const char* what() const throw(){
                            return msg.c_str();
                        }
                };

        Node();
        Node(const T&);

        ~Node();

        T* getDataPtr() const;
        T getData() const;
        Node* getPrev() const;
        Node* getNext() const;

        void setDataPtr(T*);
        void setData(const T&);
        void setPrev(Node*);
        void setNext(Node*);

        };

        Node* header;

        void copyAll(const List<T>&);

        bool isValidPos(Node*) const;

    public:
        typedef Node* Position;

        class Exception : public std::exception{
                private:
                    std::string msg;
                public:
                    explicit Exception(const char* message) : msg(message) {}

                    explicit Exception(const std::string& message) : msg(message) {}

                    virtual ~Exception() throw() {}

                    virtual const char* what() const throw(){
                        return msg.c_str();
                    }

        List();
        List(const List<T>&);

        ~List();

        bool isEmpty() const;

        void insertData(Node*, const T&);

        void deleteData(Node*);

        Node* getFirstPos() const;
        Node* getLastPos() const;
        Node* getPrevPos(Node*) const;
        Node* getNextPos(Node*) const;

        Node* findData(const T&) const;

        T retrieve(Node*) const;

        std::string toString() const;

        void deleteAll();

        List<T>& operator = (const List<T>&);
};

///implementacion

///Nodo
template <class T>
List<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) {}

template <class T>
List<T>;;Node::Node(const T& e) : dataPtr(new T(e)), prev(nullptr), next(nullptr){
    if(dataPtr == nullptr){
        throw Exception( "memoria insuficiente, creando nodo" );
    }
}

template <class T>
List<T>::Node::~Node(){
    delete dataPtr;
}

template <class T>
T* List<T>::Node::getDataPtr() const{
    return dataPtr;
}

template <class T>
T List<T>::Node::getData() const{
    if(dataPtr == nullptr){
        throw Exception("Dato inexistente, getData");
    }

    return *dataPtr;
}

template <class T>
typename List<T>::Node* List<T>::Node::getPrev() const {
    return prev;
}

template <class T>
typename List<T>::Node* List<T>::Node::getNext() const {
    return next;
}

template <class T>
void List<T>::Node::setDataPtr(T* p){
    dataPtr = p;
}

template <class T>
void List<T>::Node::setData(const T& e){
    if(dataPtr == nullptr){
        if((dataPtr = new T(e)) == nullptr){
            throw Exception("memoria no disponible, setData");
        }
    }
    else{
        *dataPtr = e;
    }
}

template <class T>
void List<T>::Node::setPrev(Node* p){
    prev = p;
}

template <class T>
void List<T>::Node::setNext(Node* p){
    next = p;
}

///Lista

template <class T>
void List<T>::copyAll(const List<T>& l){
    Node* aux(l.header->getNext());
    Node* newNode;

    while(aux != l.header){
        try{
            if((newNode = new Node(aux->getData())) == nullptr){
                throw Exception("memoria no disponible, copyAll");
            }
        } catch(typename Node::Exception ex){
            throw Exception(ex.what());
        }

        newNode->setPrev(header->getPrev()):
        newNode->setNext(header);

        header->getPrev()->setNext(newNode);
        header->setPrev(newNode);

        aux = aux->getNext();
    }
}

template <class T>
bool List<T>::isValidPos(Node* p) const {
    Node* aux(header->getNext());

    while(aux != header){
        if(aux == p){
            return true;
        }

        aux = aux->getNext();
    }

    return false;
}

template <class T>
List<T>::List() : header(new Node){
    if(header == nullptr){
        throw Exception("memoria no disponible, inicializando lista");
    }

    header->setPrev(header);
    header->setNext(header);
}

template <class T>
List<T>::List(const List<T>& l) : List(){
    copyAll(l);
}

template <class T>
List<T>::~List(){
    deleteAll();

    delete header;
}

template <class T>
bool List<T>::isEmpty() const{
    return header->getNext() == header;
}

template <class T>
void List<T>::insertData(Node* p, const T& e){
    if(p!=nullptr and !isValidPos(p)){
        throw Exception("Posicion invalida, insertData");
    }

    Node* aux;
    try{
        aux = new Node(e);
    }catch(typename Node::Exception ex) {
        throw Exception(ex.what());
    }

    if(aux == nullptr){
        throw Exception("memoria no disponible, insertData");
    }

    if(p == nullptr){
        p = header;
    }

    aux->setPrev(p);
    aux->setNext(p->getNext());

    p->getNext()->setPrev(aux);
    p->setNext(aux);
}

template <class T>
void List<T>::deleteData(Node* p){
    if(isValidPos(p)){
        throw Exception("posicion invalida, deleteData");
    }

    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());

    delete p;
}

template <class T>
typename List<T>::Node* List<T>::getfirstPos() const{
    if(isEmpty()){
        return nullptr;
    }

    return header->getNext();
}

template <class T>
typename List<T>::Node* List<T>::getLastPos() const{
    if(isEmpty()){
        return nullptr;
    }

    return header->getPrev();
}

template <class T>
typename List<T>::Node* List<T>::getPrevPos(Node* p) const{
    if(isValidPos(p) or p == header->getNext()){
        return nullptr;
    }

    return p->getPrev();
}

template <class T>
typename List<T>::Node* List<T>::getNextPos(Node* p) const{
    if(isValidPos(p) or p == header->getPrev()){
        return nullptr;
    }

    return p->getNext();
}

template <class T>
typename List<T>::Node* List<T>::findData(const T& e) const{
    Node* aux(header->getNext());

    while(aux != header){
        if(aux->getData() == e){
            return aux;
        }

        aux = aux->getNext();
    }

    return nullptr;
}

template <class T>
T List<T>::retrieve(Node* p) const{
    if(!isValidPos(p)){
        throw Exception("posicion invalida, retrieve");
    }

    return p->getData();
}

template <class T>
std::string List<T>::toString() const{
    Node* aux(header->getNext());
    std::string result;

    while(aux != header){
        result+= aux->getData().toString() + "\n";

        aux = aux->getNext();
    }

    return result;
}

template <class T>
void List<T>::deleteAll(){
    Node* aux;

    while(header->getNext() != header){
        aux = header ->getNext();

        header ->setNext(aux->getNext());

        delete aux;
    }

    header->setPrev(header);
}

template <class T>
List<T>& List<T>::operator = (const List<T>& l){
    deleteAll();

    copyAll(l);

    return *this;
}



#endif // LIST_H_INCLUDED
