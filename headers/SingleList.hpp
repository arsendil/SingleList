#ifndef __SINGLE_LIST_HPP__
#define __SINGLE_LIST_HPP__

#include <cstdlib>
#include <iostream>

template <typename T>
class SingleList
{
    template <typename T1> 
    friend std::istream& operator>>(std::istream& input, SingleList<T1>& rhv);
    template <typename T1>
    friend std::ostream& operator<<(std::ostream& output, const SingleList<T1>& rhv);

public:
    typedef size_t         size_type;
    typedef T              value_type;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef std::ptrdiff_t difference_type;
                                            ///====NODE===
private:
    struct Node
    {
        Node(const_reference data = T(), Node* next = NULL)
            : data_(data)
            , next_(next) 
        {}
        T data_;
        Node* next_; 
    };
                            ///====CONST_ITERATOR=====
public:
    class const_iterator {
    friend class SingleList<T>;
    public:
        const_iterator();
        const_iterator(const const_iterator& rhv);
        ~const_iterator();

        
        const_iterator& operator=(const const_iterator& rhv);
        const_reference operator*()  const;
        pointer         operator->() const;
        const_iterator  operator++();
        const_iterator  operator++(int);
        bool            operator==(const const_iterator& rhv) const;
        bool            operator!=(const const_iterator& rhv) const;
        bool            operator>(const const_iterator& rhv)  const;
        bool            operator<(const const_iterator& rhv)  const;
        bool            operator<=(const const_iterator& rhv) const;
        bool            operator>=(const const_iterator& rhv) const;

    protected:
        void increment();
        void destroy();
        Node* getPtr()                       const;
        void setPtr(Node* ptr);
        const_iterator next()                const;
        void next(const const_iterator& rhv);

    private:
        explicit const_iterator(Node* node);

    private:
        Node* ptr_;

    };
                                    ///====ITERATOR====
public:
    class iterator : public const_iterator {
    friend class SingleList<T>;
    public:
        iterator();
        iterator(const iterator& rhv);
        ~iterator();
       
        iterator&   operator=(const iterator& rhv);
        reference   operator*();
        value_type* operator->();
        iterator    operator++();
        iterator    operator++(int);

        operator Node*();
        
    private:
        explicit iterator(Node* node);
        iterator next() const;
        void next(const iterator& rhv); 
    };
 
public:
    SingleList(); 
    SingleList(const long size, const_reference value = T());
    SingleList(const int size, const_reference value = T());
    SingleList(const size_type newSize, const_reference value = T());
    SingleList(const SingleList<T>& rhv);
    template <typename InputIterator>
    SingleList(InputIterator first, InputIterator last);
    ~SingleList(); 
    
    SingleList<T>& operator=(const SingleList<T>& rhv);
    bool           operator==(const SingleList<T>& rhv)  const;
    bool           operator!=(const SingleList<T>& rhv)  const;
    bool           operator<(const SingleList<T>& rhv)   const;
    bool           operator>(const SingleList<T>& rhv)   const;
    bool           operator>=(const SingleList<T>& rhv)  const;
    bool           operator<=(const SingleList<T>& rhv)  const;

    size_type size()     const;
    size_type max_size() const;
    bool empty()         const;
    void clear();
    void resize(const size_type newSize, const_reference value);
    void resize(const int newSize, const_reference value);

    void     insert(iterator position, const size_type size, const_reference value);
    void     insert(iterator position, const int size, const_reference value);
    iterator insert(iterator position, const_reference value = T());
    template <typename InputIterator>
    void     insert(iterator position, InputIterator first, InputIterator last);

    iterator insert_after(iterator position, const_reference value = T());
    void     insert_after(iterator position, const size_type size, const_reference value);
    void     insert_after(iterator position, const int size, const_reference value);
    template<typename InputIterator>
    void     insert_after(iterator position, InputIterator first, InputIterator last);

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    iterator erase_after(iterator position);
    iterator erase_after(iterator first, iterator last);
    
    reference front();
    const_reference front() const;
    void push_front(const_reference value);
    void pop_front();
    
    void splice(iterator pos, SingleList& rhv);
    void splice(iterator pos, SingleList& rhv, iterator it);
    void splice(iterator pos, SingleList& rhv, iterator first, iterator last);
    
    void splice_after(iterator pos, iterator prev);
    void splice_after(iterator pos, iterator before_first, iterator before_last);

    void sort();
    void swap(SingleList<T>& rhv);
    void unique();
    void merge(SingleList<T>& rhv);
    void reverse();
    void remove(const_reference value);

    const_iterator begin() const; 
    const_iterator end()   const; 
    iterator       begin(); 
    iterator       end(); 

private:
    template <typename InputIterator>
    void copyHelper(InputIterator first, InputIterator last);
    template <typename InputIt1, typename InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2); 

private:
    Node* begin_;
    Node* end_;
};

#include "../templates/SingleList.cpp"

#endif /// __SINGLE_LIST_HPP__
