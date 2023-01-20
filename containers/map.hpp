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
        class Allocator = std::allocator<std::pair<const Key, T> > >
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

        ////----------iterators--------------------
        iterator begin()
        {
            return (this->_tree.begin());
        }

        const_iterator begin() const
        {
            return (this->_tree.begin());
        }

        iterator end()
        {
            return (this->_tree.end());
        }

        const_iterator end() const
        {
            return (this->_tree.end());
        }

        reverse_iterator rbegin()
        {
            return (this->_tree.rbegin());
        }

        const_reverse_iterator rbegin() const
        {
            return (this->_tree.rbegin());
        }

        reverse_iterator rend()
        {
            return (this->_tree.rend());
        }

        const_reverse_iterator rend() const
        {
            return (this->_tree.rend());
        }

        ////----------capasity------------
        bool empty() const
        {
            return (this->_tree.empty());
        }

        size_type size() const
        {
            return (this->_tree.size());
        }

        size_type max_size() const
        {
            return (this->_tree.max_size());
        }

        ////--------element access-----
        mapped_type &operator[](const key_type &key)
        {
            return (this->_tree.insert(ft::make_pair(key, mapped_type())).first->second);
        }

        mapped_type &at(const key_type &key)
        {
            iterator it;

            it = this->find(key);
            if (it == this->end())
                throw std::out_of_range("error map::at");
            return (it->second);
        }

        const mapped_type &at(const key_type &key) const
        {
            iterator it;

            it = this->find(key);
            if (it == this->end())
                throw std::out_of_range("error map::at");
            return (it->second);
        }

        ////--------modifiers----
        ft::pair<iterator, bool> insert(const value_type &val)
        {
            return (this->_tree.insert(val));
        }

        iterator insert(iterator it, const value_type &val)
        {
            return (this->_tree.insert(it, val));
        }

        template <class InputIt>
        void insert(InputIt first, InputIt last)
        {
            while (first != last)
            {
                this->_tree.insert(*first);
                ++first;
            }
        }

        void erase(iterator pos)
        {
            this->_tree.erase(pos);
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
                this->_tree.erase(first++);
        }

        size_type erase(const key_type &key)
        {
            value_type tmp(key, T());

            return (this->_tree.erase(tmp));
        }

        void swap(map &other)
        {
            this->_tree.swap(other._tree);
        }

        void clear()
        {
            this->_tree.clear();
        }

        ////----------observers---------
        key_compare key_comp() const
        {
            return (key_compare());
        }

        value_compare value_comp() const
        {
            return (value_compare(key_compare()));
        }

        ////------operations--------------
        iterator find(const key_type &key)
        {
            value_type tmp(key, T());
            iterator it(_tree.get_null(), _tree.search(tmp));

            return (it);
        }

        const_iterator find(const key_type &key) const
        {
            value_type tmp(key, T());
            const_iterator it(_tree.get_null(), _tree.search(tmp));

            return (it);
        }

        size_type count(const key_type &key) const
        {
            value_type tmp(key, T());

            return (_tree.count(tmp));
        }

        iterator lower_bound(const key_type &key)
        {
            value_type tmp(key, T());

            return (_tree.lower_bound(tmp));
        }

        const_iterator lower_bound(const key_type &key) const
        {
            value_type tmp(key, T());

            return (_tree.lower_bound(tmp));
        }

        iterator upper_bound(const key_type &key)
        {
            value_type tmp(key, T());

            return (_tree.upper_bound(tmp));
        }

        const_iterator upper_bound(const key_type &key) const
        {
            value_type tmp(key, T());

            return (_tree.upper_bound(tmp));
        }

        ft::pair<iterator, iterator> equal_range(const Key &key)
        {
            value_type tmp(key, T());

            return (_tree.equal_range(tmp));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const
        {
            value_type tmp(key, T());

            return (_tree.equal_range(tmp));
        }

        allocator_type get_allocator() const
        {
            return (this->_tree.get_allocator());
        }

        ////---------------member data--------------
    private:
        rb_tree<value_type, select_first<value_type>,
                key_compare, allocator_type, false>
            _tree;
    };

    /////-------non-member funcs-------
    template <typename Key, typename T, typename Compare, typename Alloc>
    void swap(ft::map<Key, T, Compare, Alloc> &lhs,
              ft::map<Key, T, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }
}

#endif