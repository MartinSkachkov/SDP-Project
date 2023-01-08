#ifndef _SKIP_LIST_HPP_
#define _SKIP_LIST_HPP_
#include <cstdlib>
#include <iostream>
using namespace std;

// --------------------
// |key|town|jump|next|
// --------------------
template <typename T>
struct SkipListEl {
    size_t mKey;
    T mTown;
    SkipListEl<T> *mJump;
    SkipListEl<T> *mNext;

    SkipListEl(const size_t &key, const T &town, SkipListEl<T> *jump = nullptr, SkipListEl<T> *next = nullptr) : mKey(key), mTown(town), mJump(jump), mNext(next) {}
};

template <typename T>
class SkipList {
private:
    SkipListEl<T> *mHead; // pointer to the first node
    SkipListEl<T> *mTail; // pointer to the last node
    size_t mSize;

    void free();
    void copy(const SkipList<T> &other);

public:
    SkipList();
    SkipList(const SkipList<T> &other);
    SkipList(SkipList<T> &&other);
    SkipList<T> &operator=(const SkipList<T> &other);
    SkipList<T> &operator=(SkipList<T> &&other);
    ~SkipList();

    void linkTowns(const T &town1, const T &town2);
    void pushBack(const int &key, const T &town);
    void popBack();

    const SkipListEl<T> *getHead() const;
    const SkipListEl<T> *getTail() const;
    size_t getSize() const;
    size_t getKey(const T &town) const;
    const SkipListEl<T> *getElem(const T &town) const;

    const T &back() const;
    T &back();
    const T &front() const;
    T &front();

    void print() const;
    bool empty() const;
};

template <typename T>
SkipList<T>::SkipList() : mHead(nullptr), mTail(nullptr), mSize(0) {}

template <typename T>
SkipList<T>::SkipList(const SkipList<T> &other) : mHead(nullptr), mTail(nullptr) {
    copy(other);
}

template <typename T>
SkipList<T>::SkipList(SkipList<T> &&other) {
    mHead = other.mHead;
    mTail = other.mTail;
    mSize = other.mSize;

    other.mHead = other.mTail = nullptr;
    other.mSize = 0;
}

template <typename T>
SkipList<T> &SkipList<T>::operator=(const SkipList<T> &other) {
    if (this == &other) {
        return *this;
    }
    free();
    copy(other);
    return *this;
}

template <typename T>
SkipList<T> &SkipList<T>::operator=(SkipList<T> &&other) {
    if (this == &other) {
        return *this;
    }
    free();
    mHead = other.mHead;
    mTail = other.mTail;
    mSize = other.mSize;

    other.mHead = other.mTail = nullptr;
    other.mSize = 0;

    return *this;
}

template <typename T>
SkipList<T>::~SkipList() {
    free();
}

template <typename T>
void SkipList<T>::free() {
    while (mHead != nullptr) {
        SkipListEl<T> *toDelete = mHead;
        mHead = mHead->mNext;
        delete toDelete;
    }
    mSize = 0;
}

template <typename T>
void SkipList<T>::copy(const SkipList<T> &other) {
    mSize = other.mSize;
    SkipListEl<T> *it = other.mHead;
    size_t i = 0;

    while (it != nullptr) {
        pushBack(i, it->mTown);
        i++;
        it = it->mNext;
    }
}

template <typename T>
void SkipList<T>::pushBack(const int &key, const T &town) {
    SkipListEl<T> *newElem = new SkipListEl<T>(key, town);

    if (empty()) {
        mHead = newElem;
        mTail = newElem;
    } else {
        mTail->mNext = newElem; // link the previous to the new one
        mTail = newElem;        // update the last element
    }
    mSize++;
}

template <typename T>
void SkipList<T>::linkTowns(const T &town1, const T &town2) {
    if (empty()) {
        throw "Can't link two towns since the list is empty!";
    }

    SkipListEl<T> *it1 = mHead;
    SkipListEl<T> *it2 = mHead;

    while (it1 != nullptr && it1->mTown != town1) {
        it1 = it1->mNext;
    }

    while (it2 != nullptr && it2->mTown != town2) {
        it2 = it2->mNext;
    }

    // as written in the task the input is always correct and the town we search for will always be found and can be linked to the second town
    it1->mJump = it2;
}

template <typename T>
void SkipList<T>::popBack() {
    if (empty()) {
        throw "Empty skip list, can't pop back!";
    }
    if (mHead == mTail) {
        delete mHead;
        mHead = mTail = nullptr;
    } else {
        SkipListEl<T> *tmp = mHead;
        while (tmp->mNext != mTail) {
            tmp = tmp->mNext;
        }
        delete mTail;
        mTail = tmp;
        mTail->mNext = nullptr;
    }
    mSize--;
}

template <typename T>
const SkipListEl<T> *SkipList<T>::getHead() const {
    return mHead;
}

template <typename T>
const SkipListEl<T> *SkipList<T>::getTail() const {
    return mTail;
}

template <typename T>
size_t SkipList<T>::getSize() const {
    return mSize;
}

template <typename T>
size_t SkipList<T>::getKey(const T &town) const {
    if (empty()) {
        throw "Empty list, can't get the key!";
    }

    SkipListEl<T> *it = mHead;

    while (it != nullptr && it->mTown != town) {
        it = it->mNext;
    }
    return it->mKey;
}

template <typename T>
const SkipListEl<T> *SkipList<T>::getElem(const T &town) const {
    if (empty()) {
        throw "Empty list, can't get the element!";
    }

    SkipListEl<T> *it = mHead;
    while (it != nullptr && it->mTown != town) {
        it = it->mNext;
    }
    return it;
}

template <typename T>
const T &SkipList<T>::back() const {
    if (empty()) {
        throw "Can't get the last element of an empty list!";
    }
    return mTail->mTown;
}

template <typename T>
T &SkipList<T>::back() {
    if (empty()) {
        throw "Can't get the last element of an empty list!";
    }
    return mTail->mTown;
}

template <typename T>
const T &SkipList<T>::front() const {
    if (empty()) {
        throw "Can't get the first element of an empty list!";
    }
    return mHead->mTown;
}

template <typename T>
T &SkipList<T>::front() {
    if (empty()) {
        throw "Can't get the first element of an empty list!";
    }
    return mHead->mTown;
}

template <typename T>
void SkipList<T>::print() const {
    if (empty()) {
        throw "Can't traverse an empty list!";
    }

    SkipListEl<T> *slow = mHead;

    cout << "Slow lane:\n";
    while (slow != nullptr) {
        cout << slow->mTown << ' ';
        slow = slow->mNext;
    }
}

template <typename T>
bool SkipList<T>::empty() const {
    return mHead == nullptr && mTail == nullptr;
}

#endif