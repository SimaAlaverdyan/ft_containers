#ifndef SET_HPP
#define SET_HPP

#include "../includes/algo.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/utility.hpp"
#include "../includes/rbtree.hpp"

// namespace ft
// {
//     template <
//         class Key,
//         class Compare = std::less<Key>,
//         class Alloc = std::allocator<Key> >
//     class set
//     {
//     public:
//         class value_compare;
//         typedef Key key_type;
//         typedef Compare key_compare;
//         typedef Alloc allocator_type;
//         typedef typename allocator_type::value_type value_type;
//         typedef typename allocator_type::size_type size_type;
//         typedef typename allocator_type::difference_type difference_type;
//         typedef typename allocator_type::reference reference;
//         typedef typename allocator_type::const_reference const_reference;
//         typedef typename allocator_type::pointer pointer;
//         typedef typename allocator_type::const_pointer const_pointer;
//         // typedef ft::bidirectional_iterator<const value_type> iterator;
//         // typedef ft::bidirectional_iterator<const value_type> const_iterator;
//         // typedef ft::reverse_iterator<iterator> reverse_iterator;
//         // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
//         typedef typename rb_tree<value_type, select_first<value_type>, key_compare, allocator_type,
//                                  false>::iterator iterator;
//         typedef typename rb_tree<value_type,
//                                  select_first<value_type>, key_compare, allocator_type,
//                                  false>::const_iterator const_iterator;
//         typedef typename rb_tree<value_type,
//                                  select_first<value_type>, key_compare, allocator_type,
//                                  false>::reverse_iterator_t reverse_iterator;
//         typedef typename rb_tree<value_type,
//                                  select_first<value_type>, key_compare, allocator_type,
//                                  false>::const_reverse_iterator const_reverse_iterator;

//         class value_compare : binary_function<value_type, value_type, bool>
//         {
//         public:
//             value_compare(key_compare c) : _comp(c)
//             {
//             }

//             bool operator()(const value_type &lhs,
//                             const value_type &rhs) const
//             {
//                 return (this->_comp(lhs.first, rhs.first));
//             }

//         protected:
//             key_compare _comp;

//         private:
//             friend class set<key_type,
//                              key_compare, allocator_type>;
//         };

//         explicit set(const Compare &comp = key_compare(),
//                      const Alloc &alloc = allocator_type()) : _tree(comp, alloc)
//         {
//         }

//         template <class InputIt>
//         set(InputIt first, InputIt last,
//             const Compare &comp = key_compare(),
//             const Alloc &alloc = allocator_type()) : _tree(comp, alloc)
//         {
//             insert(first, last);
//         }

//         set(const set &other) : _tree(Compare(), Alloc())
//         {
//             *this = other;
//         }

//         ~set()
//         {
//         }

//         set &operator=(const set &other)
//         {
//             _tree = other._tree;
//             return (*this);
//         }

//         allocator_type get_allocator() const
//         {
//             return allocator_type();
//         }

//         ////-------iterators---------
//         iterator begin()
//         {
//             return (this->_tree.begin());
//         }

//         const_iterator begin() const
//         {
//             return (this->_tree.begin());
//         }

//         iterator end()
//         {
//             return (this->_tree.end());
//         }

//         const_iterator end() const
//         {
//             return (this->_tree.end());
//         }

//         reverse_iterator rbegin()
//         {
//             return (this->_tree.rbegin());
//         }

//         const_reverse_iterator rbegin() const
//         {
//             return (this->_tree.rbegin());
//         }

//         reverse_iterator rend()
//         {
//             return (this->_tree.rend());
//         }

//         const_reverse_iterator rend() const
//         {
//             return (this->_tree.rend());
//         }

//         ////--------capacity----------
//         bool empty() const
//         {
//             return (this->_tree.empty());
//         }

//         size_type size() const
//         {
//             return (this->_tree.size());
//         }

//         size_type max_size() const
//         {
//             return (this->_tree.max_size());
//         }

//         ////--------modifiers-----------
//         ft::pair<iterator, bool> insert(const value_type &val)
//         {
//             return (this->_tree.insert(val));
//         }

//         iterator insert(iterator it, const value_type &val)
//         {
//             return (this->_tree.insert(it, val));
//         }

//         template <class InputIt>
//         void insert(InputIt first, InputIt last)
//         {
//             while (first != last)
//             {
//                 this->_tree.insert(*first);
//                 ++first;
//             }
//         }

//         void erase(iterator pos)
//         {
//             this->_tree.erase(pos);
//         }

//         void erase(iterator first, iterator last)
//         {
//             while (first != last)
//                 this->_tree.erase(first++);
//         }

//         size_type erase(const key_type &key)
//         {
//             iterator it = find(key);
//             if (it == end())
//                 return 0;
//             else
//                 erase(it);
//             return 1;
//         }

//         void swap(set &other)
//         {
//             this->_tree.swap(other._tree);
//         }

//         void clear()
//         {
//             this->_tree.clear();
//         }

//         ////----------observers---------
//         key_compare key_comp() const
//         {
//             return (key_compare());
//         }

//         value_compare value_comp() const
//         {
//             // return (value_compare(key_compare()));
//             return value_compare(typename ft::set<Key, Compare, Alloc>::key_compare());
//         }

//         ////------operations--------------
//         iterator find(const key_type &key)
//         {
//             // value_type tmp(key, T());
//             // iterator it(_tree.get_null(), _tree.search(tmp));

//             // return (it);
//             return _tree.find(key);
//         }

//         const_iterator find(const key_type &key) const
//         {
//             // value_type tmp(key, T());
//             // const_iterator it(_tree.get_null(), _tree.search(tmp));

//             // return (it);
//             return _tree.find(key);
//         }

//         size_type count(const key_type &key) const
//         {
//             // value_type tmp(key, T());

//             // return (_tree.count(tmp));
//             return (this->find(key) != this->end());
//         }

//         iterator lower_bound(const key_type &key)
//         {
//             // value_type tmp(key, T());

//             // return (_tree.lower_bound(tmp));
//             return iterator(_tree.lower_bound(key));
//         }

//         const_iterator lower_bound(const key_type &key) const
//         {
//             // value_type tmp(key, T());

//             // return (_tree.lower_bound(tmp));
//             return iterator(_tree.lower_bound(key));
//         }

//         iterator upper_bound(const key_type &key)
//         {
//             // value_type tmp(key, T());

//             // return (_tree.upper_bound(tmp));
//             return iterator(_tree.upper_bound(key));
//         }

//         const_iterator upper_bound(const key_type &key) const
//         {
//             // value_type tmp(key, T());

//             // return (_tree.upper_bound(tmp));
//             return iterator(_tree.upper_bound(key));
//         }

//         ft::pair<iterator, iterator> equal_range(const Key &key)
//         {
//             // value_type tmp(key, T());

//             // return (_tree.equal_range(tmp));
//             return ft::make_pair(lower_bound(key), upper_bound(key));
//         }

//         ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const
//         {
//             // value_type tmp(key, T());

//             // return (_tree.equal_range(tmp));
//             return ft::make_pair(lower_bound(key), upper_bound(key));
//         }

//     private:
//         typedef ft::Node<const value_type> node_type;
//         typedef rb_tree<const value_type, value_compare, allocator_type> tree_type;

//         tree_type _tree;
//     };

//     template <typename Key, typename Compare, typename Alloc>
//     void swap(ft::set<Key, Compare, Alloc> &lhs,
//               ft::set<Key, Compare, Alloc> &rhs)
//     {
//         lhs.swap(rhs);
//     }

//     template <typename Key, typename Compare, typename Alloc>
//     bool operator==(const ft::set<Key, Compare, Alloc> &lhs,
//                     const ft::set<Key, Compare, Alloc> &rhs)
//     {
//         if (lhs.size() != rhs.size())
//             return (false);
//         return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
//     }

//     template <typename Key, typename Compare, typename Alloc>
//     bool operator!=(const ft::set<Key, Compare, Alloc> &lhs,
//                     const ft::set<Key, Compare, Alloc> &rhs)
//     {
//         return (!(lhs == rhs));
//     }

//     template <typename Key, typename Compare, typename Alloc>
//     bool operator<(const ft::set<Key, Compare, Alloc> &lhs,
//                    const ft::set<Key, Compare, Alloc> &rhs)
//     {
//         return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
//     }

//     template <typename Key, typename Compare, typename Alloc>
//     bool operator<=(const ft::set<Key, Compare, Alloc> &lhs,
//                     const ft::set<Key, Compare, Alloc> &rhs)
//     {
//         return (!(rhs < lhs));
//     }

//     template <typename Key, typename Compare, typename Alloc>
//     bool operator>(const ft::set<Key, Compare, Alloc> &lhs,
//                    const ft::set<Key, Compare, Alloc> &rhs)
//     {
//         return (rhs < lhs);
//     }

//     template <typename Key, typename Compare, typename Alloc>
//     bool operator>=(const ft::set<Key, Compare, Alloc> &lhs,
//                     const ft::set<Key, Compare, Alloc> &rhs)
//     {
//         return (!(lhs < rhs));
//     }
// }

namespace ft
{
    template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
    class set
    {
        public:
            typedef T key_type;
            typedef T value_type;
            typedef Compare key_compare;
            typedef Compare value_compare;
            typedef Alloc allocator_type;
            typedef typename ft::Node<value_type> node;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename ft::bidirectional_iterator<const value_type, node> iterator;
            typedef typename ft::bidirectional_iterator<const value_type, node> const_iterator;
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef size_t size_type;

            explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            {
                this->_alloc = alloc;
                this->_comp = comp;
            }
            template <class InputIterator>
            set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
                const allocator_type &alloc = allocator_type()): _comp(comp), _alloc(alloc)
            {
                this->insert(first, last);
            }
            set(const set &x) : _comp(x._comp), _alloc(x._alloc)
            {
                this->insert(x.begin(), x.end());
            }
            ~set()
            {
            }
            set &operator=(const set &x)
            {
                if (this != &x)
                {
                    _comp = x._comp;
                    _alloc = x._alloc;
                    this->clear();
                    this->insert(x.begin(), x.end());
                }
                return (*this);
            }
            iterator begin()
            {
                return (tree.begin());
            }
            const_iterator begin() const
            {
                return (const_iterator(tree.begin()));
            }
            iterator end()
            {
                return (tree.end());
            }
            const_iterator end() const
            {
                return const_iterator(tree.end());
            }
            reverse_iterator rbegin()
            {
                return (tree.rbegin());
            }
            const_reverse_iterator rbegin() const
            {
                return (const_reverse_iterator(tree.rbegin()));
            }
            reverse_iterator rend()
            {
                return (tree.rend());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(tree.rend());
            }
            bool empty() const
            {
                return (tree.size() == 0);
            }
            size_type size() const
            {
                return (tree.size());
            }
            size_type max_size() const
            {
                return (tree.max_size());
            }
            pair<iterator, bool> insert(const value_type &val)
            {
                return (tree.insert(val));
            }
            iterator insert(iterator position, const value_type &val)
            {
                return (tree.insert(position, val));
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                tree.insert(first, last);
            }
            void erase (iterator position)
            {
                tree.erase(position);
            }
            size_type erase (const value_type& val)
            {
                return (tree.erase(val));
            }
            void erase (iterator first, iterator last)
            {
                tree.erase(first, last);
            }
            void swap (set& x)
            {
                tree.swap(x.tree);
            }
            void clear()
            {
                tree.clear();
            }
            key_compare key_comp() const
            {
                return (_comp);
            }
            value_compare value_comp() const
            {
                return (_comp);
            }
            iterator find (const value_type& val) const
            {
                return (tree.find(val));
            }
            size_type count (const value_type& val) const
            {
                return (tree.count(val));
            }
            iterator lower_bound (const value_type& val) const
            {
                return (tree.lower_bound(val));
            }
            iterator upper_bound (const value_type& val) const
            {
                return (tree.upper_bound(val));
            }
            pair<iterator,iterator> equal_range (const value_type& val) const
            {
                return (tree.equal_range(val));
            }
            allocator_type get_allocator() const
            {
                return (_alloc);
            }
    protected:
        key_compare _comp;
        allocator_type _alloc;
        ft::rb_tree<value_type,
        key_compare, true, allocator_type>   tree;
    };
     template< class Key, class Compare, class Alloc >
        bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            if (lhs.size() != rhs.size())
                return (false);
            return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
        }
        template< class Key, class Compare, class Alloc >

        bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (!(lhs == rhs));
        }
        template< class Key, class Compare, class Alloc >
        bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
        }
        template< class Key, class Compare, class Alloc >
        bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (!(rhs < lhs));
        }        
        template< class Key, class Compare, class Alloc >
        bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (rhs < lhs);
        }
        template< class Key, class Compare, class Alloc >
        bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (!(lhs < rhs));
        }
        template< class Key, class Compare, class Alloc >
        void swap( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs)
        {
            lhs.swap(rhs);
        }
}



#endif