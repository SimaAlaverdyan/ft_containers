#ifndef RBTREE
#define RBTREE

#include <iostream>
#include <memory>
#include "algo.hpp"
#include "utility.hpp"
#include "node.hpp"
#include "../iterators/bidirectional_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
    template <
        typename T,
        typename KeyOfValue,
        typename Compare = ft::less<T>,
        typename Alloc = std::allocator<T>,
        bool multivalues = false>
    class rb_tree
    {
    public:
        typedef T value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef ft::Node<value_type> *node;
        typedef size_t size_type;
        typedef bidirectional_iterator<Node<value_type>, T> iterator;
        typedef bidirectional_iterator<const Node<value_type>, const T> const_iterator;
        typedef reverse_iterator<iterator> reverse_iterator_t;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        typedef typename allocator_type::template rebind<Node<value_type>>::other allocator_node_type;

    public:
        rb_tree(const key_compare &comp = key_compare(),
                const allocator_type &alloc = allocator_type()) : _alloc(alloc),
                                                                  _alloc_node(allocator_node_type()),
                                                                  _comp(comp)
        {
            _null_node = this->_alloc_node.allocate(1);
            try
            {
                this->_alloc_node.construct(_null_node);
            }
            catch (...)
            {
                this->_alloc_node.deallocate(_null_node, 1);
                throw;
            }
            this->_head = this->_null_node;
            _null_node->p = this->_head;
            _null_node->color = ft::BLACK;
            this->_size = 0
        }
        rb_tree(const node head, const key_compare &comp = key_compare(),
                const allocator_type &alloc = allocator_type()) : _alloc(alloc),
                                                                  _alloc_node(allocator_node_type()),
                                                                  _comp(comp)
        {
            this->_null_node = this->_alloc_node.allocate(1);
            try
            {
                this->_alloc_node.construct(this->_null_node);
            }
            catch (...)
            {
                this->_alloc_node.deallocate(this->_null_node, 1);
                throw;
            }
            this->_head = head;
            this->_null_node->p = this->_head;
            _null_node->color = ft::BLACK;
            this->_size = 1;
        }
        rb_tree(const rb_tree &other) : _alloc(other._alloc),
                                        _alloc_node(other._alloc_node),
                                        _comp(other._comp)
        {
        }
        rb_tree &operator=(const rb_tree &other)
        {
            if (this != &other)
            {
                if (_head != _null_node)
                    this->clear(this->_head);
                this->_alloc = other._alloc;
                this->_alloc_node = other._alloc_node;
                this->_head = this->_null_node;
                this->_comp = other._comp;
                this->deep_copy(other.get_head(), other._null_node);
                this->_size = other._size;
            }
            return (*this);
        }
        ~rb_tree()
        {
            if (_head != _null_node)
                this->clear(this->_head);
            if (_null_node != 0)
            {
                this->_alloc_node.destroy(_null_node);
                this->_alloc_node.deallocate(_null_node, 1);
                _null_node = 0;
            }
        }

    private:
        node _head;
        node _null_node;
        allocator_type _alloc;
        allocator_node_type _alloc_node;
        key_compare _comp;
        size_type _size;

        void transplant(node u, node v);
        void deep_copy(node other_node, node other_null);
        bool comp_data(value_type v1, value_type v2) const;
        void rotate_left(node node);
        void rotate_right(node node);
    };
}

#endif