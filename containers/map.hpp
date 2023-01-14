#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "../includes/algo.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/utility.hpp"
#include "../Iterators/rbtree.hpp"


namespace ft
{
    template<
    class Key,
    class T,
    class Compare = ft::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
    > class map
    {
        public:
            typedef Key key_type;
            typedef T   mapped_type;
            typedef typename ft::pair<const Key, T> value_type;
            typedef size_t  size_type;
            typedef typename iterator_traits<iterator>::difference_type difference_type;
            typedef Compare key_compare;
            typedef Allocator allocator_type;
            typedef allocator_type:reference reference;
            

    };
}

#endif