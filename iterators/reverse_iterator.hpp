#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterators.hpp"

namespace ft
{
    template<class Iter>
    class reverse_iterator
    {
        public:
            ////-------------Member functions----------
            typedef Iter iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer pointer;
            typedef typename ft::iterator_traits<Iterator>::reference reference;

            reverse_iterator() 
            {
                this->cur = Iter();
            };
            explicit reverse_iterator( iterator_type x )
            {
                this->cur = x;
            }
            template<class Iter>
            reverse_iterator( const reverse_iterator<Iter> &other)
            {
                this->cur = other.base();
            }
            iterator_type base() const
            {
                return this->cur;
            }
            reference operator*() const
            {
                iterator_type   tmp = this->elem--;
                return (*tmp);
            }
            pointer operator->() const
            {
                iterator_type   tmp = this->elem--;
                return (*tmp);
            }
            operator[]( difference_type n ) const
            {
                return (*(this->cur - n - 1));
            }
            reverse_iterator& operator++()
            {
                ++(this->cur);
                return (*this);
            }
            reverse_iterator& operator--()
            {
                --(this->cur);
                return (*this);
            }
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                --(*this);
                return tmp;
            }
            reverse_iterator operator+( difference_type n ) const
            {
                return (reverse_iterator(this->cur - n));
            }
            reverse_iterator operator-( difference_type n ) const
            {
                return (reverse_iterator(this->cur + n));
            }
            reverse_iterator& operator+=( difference_type n )
            {
                this->cur -= n;
                return (*this);
            }
            reverse_iterator& operator-=( difference_type n )
            {
                this->cur += n;
                return (*this);
            }
        /////-------------Member objects---------
        protected:
            iterator_type   cur;
    };
    ////------------------Non-member functions----------
    template< class Iterator1, class Iterator2 >
    bool operator==( const std::reverse_iterator<Iterator1>& lhs,
    const std::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() == rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator!=( const std::reverse_iterator<Iterator1>& lhs,
    const std::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() != rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator<( const std::reverse_iterator<Iterator1>& lhs,
    const std::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() > rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
    const std::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() >= rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>( const std::reverse_iterator<Iterator1>& lhs,
    const std::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() < rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
    const std::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() <= rhs.base());
    }
    template< class Iter >
    reverse_iterator<Iter>
    operator+( typename reverse_iterator<Iter>::difference_type n,
                const reverse_iterator<Iter>& it )
    {
        return (it + n);
    }
    template< class Iterator1, class Iterator2 >
    typename reverse_iterator<Iterator1>::difference_type
    operator-( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
    {
        return (rhs.base() - lhs.base());
    }
}

#endif