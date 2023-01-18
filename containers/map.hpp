#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "../includes/algo.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/utility.hpp"
#include "../includes/rbtree.hpp"

namespace ft
{
    template <
        class Key,
        class T,
        class Compare = ft::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, T>>>
    class map
    {
        ////-------------member types--------------
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef Allocator allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef typename rb_tree<value_type, select_first<value_type>, key_compare, allocator_type,
                                 false>::iterator iterator;
        typedef typename rb_tree<value_type,
                                 select_first<value_type>, key_compare, allocator_type,
                                 false>::const_iterator const_iterator;
        typedef typename rb_tree<value_type,
                                 select_first<value_type>, key_compare, allocator_type,
                                 false>::reverse_iterator_t reverse_iterator;
        typedef typename rb_tree<value_type,
                                 select_first<value_type>, key_compare, allocator_type,
                                 false>::const_reverse_iterator const_reverse_iterator;

        ////--------------member classes-----------
        class value_compare : binary_function<value_type, value_type, bool>
        {
        public:
            value_compare(key_compare c) : _comp(c)
            {
            }

            bool operator()(const value_type &lhs,
                            const value_type &rhs) const
            {
                return (this->_comp(lhs.first, rhs.first));
            }

        protected:
            key_compare _comp;

        private:
            friend class map<key_type, value_type,
                             key_compare, allocator_type>;
        };

        ////------------construct destruct
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : _tree(comp, alloc)
        {
        }

        template <typename InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _tree(comp, alloc)
        {
            this->insert(first, last);
        }

        map(const map &other) : _tree(other._tree)
        {
        }

        map &operator=(const map &other)
        {
            if (this != &other)
                this->_tree = other._tree;
            return (*this);
        }

        ~map() {}

        ////---------------member data--------------
    private:
        rb_tree<value_type, select_first<value_type>,
                key_compare, allocator_type, false>
            _tree;
    };
}

#endif