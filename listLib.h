/*
 * =========================================================================================
 * Name        : listLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List(){};

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    L1Item<T>* getHead(){return _pHead;} // get pHead
    L1Item<T>* getLast();

    T&      at(int i);
    T&      operator[](int i);

    bool    find(T& a, int& idx);
    int     insert(int i, T& a);
    int     remove(int i);
    L1List<T>* copyList();

    int     push_back(T& a);
    L1Item<T>* pushBack(T& a,L1Item<T>* pLast);//sau moi lan push se lay con tro last cho lan push ke tiep
    int     insertHead(T& a);

    int     removeHead();
    int     removeLast();

    void    reverse();

    void    traverse(void (*op)(T&)) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

template <class T>
L1Item<T>* L1List<T>::pushBack(T& a,L1Item<T>* pLast){
	if(pLast == NULL){
		pLast = new L1Item<T>(a);
		 _size++;
		 _pHead = pLast;
		 return pLast;
	}
	else{
		  L1Item<T> *p = pLast;
		  p->pNext = new L1Item<T>(a);
		  _size++;
		  return p->pNext;
	}
}


/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}


template<class T>
L1Item<T>* L1List<T>::getLast(){
	if(_pHead == NULL) return 0;
	L1Item<T>* p = _pHead;
	while(p->pNext){
		p = p->pNext;
	}
	return p;
}


template<class T>
T& L1List<T>::operator [](int idx)
{
	//if(_pHead == NULL)
	L1Item<T>* p = _pHead;
	while(idx>0 &&p)
	{
		p = p->pNext;
		idx--;
	}
	if(p) return p->data;
}

template<class T>
L1List<T>* L1List<T>::copyList(){
	L1List<T>* p = new L1List<T>();
	L1Item<T>* pLast = p->getHead();
	L1Item<T>* temp = _pHead;
	while(temp){
		pLast = p->pushBack(temp->data,pLast);
		//p->push_back(temp->data);
		temp = temp->pNext;
	}
	return p;
}



#endif //A01_LISTLIB_H
