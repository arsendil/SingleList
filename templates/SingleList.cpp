#include "../headers/SingleList.hpp"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <limits>

template <typename T>
SingleList<T>::SingleList()
    : begin_(new Node(T(), NULL))
    , end_(begin_)
{
    end_->next_ = begin_;
}

template <typename T>
SingleList<T>::SingleList(const size_type newSize, const_reference value)
    : begin_(new Node(T(), NULL))
    , end_(begin_)

{
    end_->next_ = begin_;
    resize(newSize, value);
}

template <typename T>
SingleList<T>::SingleList(const long newSize, const_reference value)
    : begin_(new Node(T(), NULL))
    , end_(begin_)

{
    end_->next_ = begin_;
    resize(newSize, value);
}

template <typename T>
SingleList<T>::SingleList(const int newSize, const_reference value)
    : begin_(new Node(T(), NULL))
    , end_(begin_)

{
    end_->next_ = begin_;
    resize(newSize, value);
}

template <typename T>
SingleList<T>::SingleList(const SingleList<T>& rhv)
    : begin_(new Node(T(), NULL))
    , end_(begin_)

{
    end_->next_ = begin_;
    copyHelper(rhv.begin(), rhv.end());
}

template <typename T>
template <typename InputIterator>
SingleList<T>::SingleList(InputIterator first, InputIterator last)
    : begin_(new Node(T(), NULL))
    , end_(begin_)
{
    end_->next_ = begin_;
    copyHelper(first, last);
}

template <typename T>
SingleList<T>::~SingleList()
{
    clear();
    delete end_;
    begin_ = NULL;
    end_ = NULL;
}

template <typename T>
SingleList<T>&
SingleList<T>::operator=(const SingleList<T>& rhv)
{
    if (this == &rhv) return *this;
    clear(); 
    copyHelper(rhv.begin(), rhv.end());
    return *this;
}

template <typename T>
bool 
SingleList<T>::operator==(const SingleList<T>& rhv) const
{
    SingleList<T>::const_iterator first = begin();
    SingleList<T>::const_iterator second = rhv.begin();
    while (first != end() && second != rhv.end()) {
        if (*first != *second) {
            return false;
        }
        ++first;
        ++second;
    }
    return end() == first && rhv.end() == second;
}

template <typename T>
bool 
SingleList<T>::operator!=(const SingleList<T>& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool 
SingleList<T>::operator<(const SingleList<T>& rhv) const
{
    SingleList<T>::const_iterator first = begin();
    SingleList<T>::const_iterator second = rhv.begin();
      
    while (first != end() && second != rhv.end()) {
        if (*first != *second) {
            return *first < *second;
        }
        ++first;
        ++second;
    }
    return end() == first && rhv.end() != second;
}

template <typename T>
bool 
SingleList<T>::operator>(const SingleList<T>& rhv) const
{
    return rhv < *this;
}

template <typename T>
bool 
SingleList<T>::operator>=(const SingleList<T>& rhv) const
{
    return !(*this < rhv); 
}

template <typename T>
bool 
SingleList<T>::operator<=(const SingleList<T>& rhv) const
{
    return !(rhv < *this);
}

template <typename T>
typename SingleList<T>::size_type
SingleList<T>::size() const
{
    size_type count = 0;
    Node* current = begin_;
    while (current != end_) {
        current = current->next_;
        ++count;
    }
    return count;
}


template <typename T>
typename SingleList<T>::size_type
SingleList<T>::max_size() const
{
    return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename T>
bool
SingleList<T>::empty() const
{
    return end_ == begin_;
}

template <typename T>
void
SingleList<T>::clear()
{
    while (begin_ != end_) {
        pop_front();
    }
}

template <typename T>
void
SingleList<T>::push_front(const_reference value)
{
    begin_ = new Node(value, begin_);
    end_->next_ = begin_;
}

template <typename T>
void
SingleList<T>::pop_front()
{
    assert(!empty());
    Node* ptr = begin_;
    begin_ = begin_->next_;
    end_->next_ = begin_;
    delete ptr;
}

template <typename T>
void
SingleList<T>::resize(const size_type newSize, const_reference initialValue)
{
    size_type currentSize = size();
    if (currentSize == newSize)  return;
    if (0 == newSize) {
        clear(); 
        return;
    }

    if (currentSize < newSize) {
        while (currentSize++ < newSize) {
            insert(end(), initialValue);
        }
        return;
    }
    iterator temp = begin();
    for (size_type i = 1; i < newSize; ++i) {
        ++temp;
    } 
    iterator ptr = temp; 
    while (temp.next() != end()) {
        erase_after(temp);
    }
}

template <typename T>
void
SingleList<T>::resize(const int newSize, const_reference initialValue)
{
    int currentSize = size();
    if (currentSize == newSize)  return;
    if (0 == newSize) {
        clear(); 
        return;
    }

    if (currentSize < newSize) {
        while (currentSize++ < newSize) {
            insert(end(), initialValue);
        }
        return;
    }
    iterator temp = begin();
    for (int i = 1; i < newSize; ++i) {
        ++temp;
    } 
    iterator ptr = temp; 
    while (temp.next() != end()) {
        erase_after(temp);
    }
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::insert_after(iterator position, const_reference value)
{
    Node* newNode = new Node(value, position.next().getPtr());
    position.next(iterator(newNode));
    return iterator(newNode);
}

template <typename T>
template <typename InputIterator>
void
SingleList<T>::insert_after(iterator position, InputIterator first, InputIterator last)
{
    while (first != last) {
        position = insert_after(position, *first++);
    }
}

template <typename T>
void
SingleList<T>::insert_after(iterator position, const int size, const_reference value)
{
    for (int i = 0; i < size; ++i) {
        insert_after(position, value);
    }
}

template <typename T>
void
SingleList<T>::insert_after(iterator position, const size_type size, const_reference value)
{
    for (size_type i = 0; i < size; ++i) {
        insert_after(position, value);
    }
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::insert(iterator position, const_reference value)
{
    if (empty()) {
        push_front(value);
        return begin();
    }
    insert_after(position, value);
    std::swap(*position, *position.next());
    if (position == end()) {
        end_ = end_->next_; 
    }
    return ++position; 
}

template <typename T>
void
SingleList<T>::insert(iterator position, const size_type size, const_reference value)
{
    for (size_type i = 0; i < size; ++i) {
        insert(position, value);
    }
}

template <typename T>
void
SingleList<T>::insert(iterator position, const int size, const_reference value)
{
    for (int i = 0; i < size; ++i) {
        insert(position, value);
    }
}

template <typename T>
template <typename InputIterator>
void
SingleList<T>::insert(iterator position, InputIterator first, InputIterator last)
{
    while (first != last) {
        position = insert(position, *first);
    }
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::erase_after(iterator position)
{
    assert(position != end()); 
    assert(position != iterator(NULL));
    assert(position.next() != end());
    
    //iterator temp = position.next();
    //position.next(temp.next());
    //delete temp.getPtr();
    //return position;
    
    Node* temp = position.getPtr()->next_;
    position.getPtr()->next_ = temp->next_;
    delete temp;
    return position;
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::erase_after(iterator first, iterator last)
{
    while(first != last) {
        first = erase_after(first);
    }
    return first;
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::erase(iterator position)
{
    assert(position != end());
    assert(position != iterator(NULL));
    if (position == begin()) {
        pop_front();
        return begin();
    }
    iterator it = begin();
    while (it.next() != position) {
        ++it;
    }
    it.next(position.next());
    delete position.getPtr();
    return it.next();
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::erase(iterator first, iterator last)
{
    const bool isFirstEqualToBegin = (begin() == first);
    iterator it = begin();
    if (!isFirstEqualToBegin) {
        while (it.next() != first) {
            ++it;
        }
    } else {
        ++first;
    }
    
    while (first != last && it.next() != end()) {
        ++first;
        erase_after(it);
    }
    if (isFirstEqualToBegin) {
        pop_front();
    }
    return last;
}

template <typename T>
void
SingleList<T>::splice(iterator position, SingleList& rhv)
{
    assert(this != &rhv);
    if (rhv.empty()) return;

    iterator rhvEnd = rhv.begin();
    while (rhvEnd.next() != rhv.end()) { 
        ++rhvEnd; 
    }
    
    if (begin() == position) {
        rhvEnd.next(begin());
        begin_ = rhv.begin_;
        rhv.begin_ = rhv.end_;
        return;
    }
    iterator it = begin();
    while (it.next() != position) {
        ++it; 
    }
    it.next(rhv.begin());
    rhvEnd.next(position);
    rhv.begin_ = rhv.end_;
}

template <typename T>
void
SingleList<T>::splice(iterator position, SingleList& rhv, iterator it)
{
    if (rhv.empty()) return; 
    iterator rhvIt = rhv.begin();
    while (rhvIt.next() != it) {
        ++rhvIt;
    }
    rhvIt.next(it.next());

    iterator positionPrev = begin();
    while (positionPrev.next() != position) { 
        ++positionPrev;
    }
    positionPrev.next(it);
    it.next(position);
    begin_ = end_->next_;
    rhv.begin_ = rhv.end_->next_;
}

template <typename T>
void
SingleList<T>::splice(iterator position, SingleList& rhv, iterator first, iterator last)
{
    if (rhv.empty()) return;
    iterator positionPrev = begin();
    while (positionPrev.next() != position) {
        ++positionPrev;
    }
    iterator prevLast = rhv.begin();
    while (prevLast.next() != last) {
        ++prevLast;
    }
    iterator prevFirst = rhv.begin();
    while (prevFirst.next() != first) {
        ++prevFirst;
    }
    
    positionPrev.next(first);
    prevLast.next(position);
    prevFirst.next(last);  
    begin_ = end_->next_;
    rhv.begin_ = rhv.end_->next_;
}

template <typename T>
void
SingleList<T>::splice_after(iterator position, iterator previous)
{
    assert(position != end() && previous != end());
    iterator previousNext = previous.next();
    
    previous.next(previousNext.next());
    previousNext.next(position.next());
    position.next(previousNext);
}

template <typename T>
void
SingleList<T>::splice_after(iterator position, iterator first, iterator last)
{
    assert(position != end() && first != end() && last != end());
    iterator positionNext = position.next();
    iterator last1 = last.next();
    iterator first1 = first.next();
    
    position.next(first1);
    last.next(positionNext);
    first.next(last1);
}

template <typename T>
typename SingleList<T>::reference
SingleList<T>::front()
{
    assert(!empty());
    return begin_->data_;
}

template <typename T>
typename SingleList<T>::const_reference
SingleList<T>::front() const
{
    assert(!empty());
    return begin_->data_;
}

template <typename T>
typename SingleList<T>::const_iterator
SingleList<T>::begin() const
{
    return const_iterator(begin_);
}

template <typename T>
typename SingleList<T>::const_iterator
SingleList<T>::end() const
{
    return const_iterator(end_);
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::begin()
{
    return iterator(begin_);
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::end()
{
    return iterator(end_);
}

template <typename T>
template <typename InputIterator>
void 
SingleList<T>::copyHelper(InputIterator first, InputIterator last)
{
    iterator it = begin();
    while (first != last && it != end()) { 
        *it++ = *first++;
    }
    while (first != last)
    { 
        insert(end(), *first++);
    }
}

template <typename T>
void 
SingleList<T>::swap(SingleList<T>& rhv)
{
    std::swap(begin_, rhv.begin_);
    std::swap(end_, rhv.end_);
}

template <typename T>
void 
SingleList<T>::remove(const_reference value)
{
    iterator previous;
    for (iterator it = begin(); it != end(); ) {
        if (value == *it) {
            if (it == begin()) {
                pop_front();
                it = begin();
                continue;
            }
            ++it;
            erase_after(previous);
            continue;
        }
        previous = it;
        ++it;
    }
}

template <typename T>
void 
SingleList<T>::unique()
{
    for (iterator it = begin(); it != end(); ) {
        if (it.next() != end() && *it == *it.next()) {
            erase_after(it);
            continue;
        }
        ++it;
    }
}

template <typename T>
void 
SingleList<T>::merge(SingleList<T>& rhv)
{
    if (this == &rhv) return;
    iterator it1 = begin();
    iterator it2 = rhv.begin();

    iterator temp;
    while (it1 != end() && it2 != end()) {
        if (it1.next() == end()) {
            temp = it1;
        }
        if (*it1 >= *it2) {
            it1 = insert(it1, *it2);
            ++it2;
            continue;
        } 
        ++it1;
    }
    it1 = temp;
    while (it2 != rhv.end()) {
        it1 = insert_after(it1, *it2);
        ++it2;
    }
    rhv.begin_ = rhv.end_; 
}

template <typename T>
void 
SingleList<T>::sort()
{
    for (iterator it1 = begin(); it1 != end(); ++it1) {
        iterator it2 = it1;
        ++it2;
        while (it2 != end()) {
            if (*it1 > *it2) {
                std::swap(*it1, *it2);
            }
            ++it2;
        }
    }
}

template <typename T>
void 
SingleList<T>::reverse()
{
    iterator first = end();
    iterator second = begin();
    iterator temp = iterator(begin_->next_);
    while (second != end()) {
        second.next(first);
        first = second;
        second = temp;
        ++temp;
    }
    begin_ = first.getPtr();
}

///==================================CONST_ITERATOR===============================
template <typename T>
SingleList<T>::const_iterator::const_iterator()
    : ptr_(NULL)
{}

template <typename T>
SingleList<T>::const_iterator::const_iterator(Node* ptr)
    : ptr_(ptr)
{}

template <typename T>
SingleList<T>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr_(rhv.ptr_)
{}

template <typename T>
SingleList<T>::const_iterator::~const_iterator()
{
    destroy();
}

template <typename T>
void 
SingleList<T>::const_iterator::destroy()
{
    ptr_ = NULL;
}

template <typename T>
typename SingleList<T>::const_iterator&
SingleList<T>::const_iterator::operator=(const const_iterator& rhv)
{
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
typename SingleList<T>::const_reference 
SingleList<T>::const_iterator::operator*() const
{
    return ptr_->data_;
}

template <typename T>
typename SingleList<T>::value_type* 
SingleList<T>::const_iterator::operator->() const
{
    return &ptr_->data_;
}

template <typename T>
typename SingleList<T>::const_iterator
SingleList<T>::const_iterator::operator++()
{
    return const_iterator(ptr_ = ptr_->next_);
}

template <typename T>
typename SingleList<T>::const_iterator
SingleList<T>::const_iterator::operator++(int)
{
    Node* temp = ptr_;
    ptr_ = ptr_->next_;
    return const_iterator(temp);
}

template <typename T>
bool 
SingleList<T>::const_iterator::operator==(const const_iterator& rhv) const
{
    return ptr_ == rhv.ptr_;
}

template <typename T>
bool 
SingleList<T>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool 
SingleList<T>::const_iterator::operator<(const const_iterator& rhv) const
{
    return ptr_ < rhv.ptr_;
}

template <typename T>
bool 
SingleList<T>::const_iterator::operator>(const const_iterator& rhv) const
{
    return rhv < *this;
}

template <typename T>
bool 
SingleList<T>::const_iterator::operator<=(const const_iterator& rhv) const
{
    return !(rhv < *this);
}

template <typename T>
bool 
SingleList<T>::const_iterator::operator>=(const const_iterator& rhv) const
{
    return !(*this < rhv);
}

template <typename T>
void 
SingleList<T>::const_iterator::setPtr(Node* ptr)
{
    ptr_ = ptr;
}

template <typename T>
typename SingleList<T>::Node* 
SingleList<T>::const_iterator::getPtr() const
{    
    return ptr_;
}

template <typename T>
void 
SingleList<T>::const_iterator::increment()
{
    ptr_ = ptr_->next_;
}

template <typename T>
typename SingleList<T>::const_iterator
SingleList<T>::const_iterator::next() const
{
    assert(ptr_ != NULL);
    return iterator(ptr_->next_);
}

template <typename T>
void
SingleList<T>::const_iterator::next(const const_iterator& rhv) 
{
    assert(ptr_ != NULL);
    ptr_->next_ = rhv.ptr_;
}


///==================================ITERATOR===============================

template <typename T>
SingleList<T>::iterator::iterator()
    : const_iterator()
{}

template <typename T>
SingleList<T>::iterator::iterator(Node* ptr)
    : const_iterator(ptr)
{}

template <typename T>
SingleList<T>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv)
{}

template <typename T>
SingleList<T>::iterator::~iterator()
{
    this->destroy();
}

template <typename T>
typename SingleList<T>::iterator& 
SingleList<T>::iterator::operator=(const iterator& rhv)
{
    this->setPtr(rhv.getPtr());
    return *this;
}

template <typename T>
typename SingleList<T>::reference
SingleList<T>::iterator::operator*()
{
    return (this->getPtr())->data_;
}

template <typename T>
typename SingleList<T>::value_type*
SingleList<T>::iterator::operator->()
{
    return &this->getPtr();
}

template <typename T>
typename SingleList<T>::iterator 
SingleList<T>::iterator::operator++()
{
    this->increment();
    return iterator(this->getPtr());
}

template <typename T>
typename SingleList<T>::iterator 
SingleList<T>::iterator::operator++(int)
{
    Node* temp = this->getPtr();
    this->increment();
    return iterator(temp);
}

template <typename T>
typename SingleList<T>::iterator
SingleList<T>::iterator::next() const
{
    return iterator(const_iterator::next().getPtr());
}

template <typename T>
void
SingleList<T>::iterator::next(const iterator& rhv)
{
    const_iterator::next(rhv);
}

template <typename T>
std::istream& 
operator>>(std::istream& input, SingleList<T>& rhv)
{
    const typename SingleList<T>::const_iterator end = rhv.end();
    for (typename SingleList<T>::iterator it = rhv.begin(); it != end; ++it) {
        input >> *it;
    }
    return input;
}

template <typename T>
std::ostream& 
operator<<(std::ostream& output, const SingleList<T>& rhv)
{
    const typename SingleList<T>::const_iterator end = rhv.end();
    output << "{";
    for (typename SingleList<T>::const_iterator it = rhv.begin(); it != end; ++it) {
        output << ' ' << *it;
    }
    output << " }";
    return output;
}

