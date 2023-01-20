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
        typedef typename allocator_type::template rebind<Node<value_type> >::other allocator_node_type;

        ////--------CONSTRCT DESTRUCT---------
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
            this->_size = 0;
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
            this->_head = this->_null_node;
            this->_null_node->p = this->_head;
            _null_node->color = ft::BLACK;
            this->deep_copy(other.get_head(), other._null_node);
            this->_size = other._size;
        }
        rb_tree &operator=(const rb_tree &other)
        {
            if (this != &other)
            {
                if (this->_head != _null_node)
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
            if (this->_head != _null_node)
                this->clear(this->_head);
            if (_null_node != 0)
            {
                this->_alloc_node.destroy(_null_node);
                this->_alloc_node.deallocate(_null_node, 1);
                _null_node = 0;
            }
        }

        ////----------TREE FUNC---------
        node create_node(value_type data)
        {
            node new_node = this->_alloc_node.allocate(1);
            try
            {
                this->_alloc_node.construct(new_node, data);
            }
            catch (...)
            {
                this->_alloc_node.deallocate(new_node, 1);
                throw;
            }
            new_node->left = _null_node;
            new_node->right = _null_node;
            new_node->p = _null_node;
            return (new_node);
        }

        node get_head() const
        {
            return (this->_head);
        }
        node get_null() const
        {
            return (this->_null_node);
        }
        int height(node head) const
        {
            if (head == this->_null_node)
                return (0);
            else
            {
                int left_height = height(head->left);
                int right_height = height(head->right);
                if (left_height > right_height)
                    return (left_height + 1);
                else
                    return (right_height + 1);
            }
        }
        int height() const
        {
            return (this->height(this->_head));
        }

        node min(node head) const
        {
            if (head == this->_null_node)
                return (this->_null_node);
            while (head->left != this->_null_node)
                head = head->left;
            return (head);
        }

        node min() const
        {
            return (this->min(this->_head));
        }

        node max(node head) const
        {
            if (head == this->_null_node)
                return (this->_null_node);
            while (head->right != this->_null_node)
                head = head->right;
            return (head);
        }

        node max() const
        {
            return (this->max(this->_head));
        }

        node successor(node head) const
        {
            node parent;

            if (head == this->_null_node)
                return (this->_null_node);
            if (head->right != this->_null_node)
                return (this->min(head->right));
            else
            {
                parent = head->p;
                while (parent != this->_null_node && head == parent->right)
                {
                    head = parent;
                    parent = head->p;
                }
                return (parent);
            }
        }

        node successor() const
        {
            return (this->successor(this->_head));
        }

        node predecessor(node head) const
        {
            node parent;

            if (head == this->_null_node)
                return (this->_null_node);
            if (head->left != this->_null_node)
                return (this->min(head->left));
            else
            {
                parent = head->p;
                while (parent != this->_null_node && head == parent->left)
                {
                    head = parent;
                    parent = head->p;
                }
                return (parent);
            }
        }

        node predecessor() const
        {
            return (this->predecessor(this->_head));
        }

        ////----------CAPACITY--------
        bool empty() const
        {
            if (this->_size == 0)
                return (true);
            return (false);
        }

        size_type size() const
        {
            return (this->_size);
        }
        size_type max_size() const
        {
            return (this->_alloc_node.max_size());
        }

        ////----------OPERATIONS---------------
        node search(node head, const value_type &data) const
        {
            if (head == this->_null_node || (!this->comp_data(head->data, data) && !this->comp_data(data, head->data)))
                return (head);
            if (this->comp_data(data, head->data))
                return (this->search(head->left, data));
            else
                return (this->search(head->right, data));
        }

        node search(const value_type &data) const
        {
            return (this->search(this->_head, data));
        }

        void count_in_level(node head, const value_type &data, int level, size_type &count) const
        {
            if (head != this->_null_node)
            {
                if (level == 1)
                {
                    if (!this->comp_data(head->data, data) && !this->comp_data(data, head->data))
                        count++;
                }
                else if (level > 1)
                {
                    count_in_level(head->left, data, level - 1, count);
                    count_in_level(head->right, data, level - 1, count);
                }
            }
        }

        size_type count(node head, const value_type &data) const
        {
            size_type count = 0;
            node res = search(head, data);
            if (res != this->_null_node)
                ++count;
            return (count);
        }

        size_type count(const value_type &data) const
        {
            return (this->count(this->_head, data));
        }

        iterator lower_bound(const value_type &data)
        {
            iterator it1;
            iterator it2;

            it1 = this->begin();
            it2 = this->end();
            while (it1 != it2)
            {
                if (!this->comp_data(*it1, data))
                    break;
                ++it1;
            }
            return (it1);
        }

        const_iterator lower_bound(const value_type &data) const
        {
            const_iterator it1;
            const_iterator it2;

            it1 = this->begin();
            it2 = this->end();
            while (it1 != it2)
            {
                if (!this->comp_data(*it1, data))
                    break;
                ++it1;
            }
            return (it1);
        }

        iterator upper_bound(const value_type &data)
        {
            iterator it1, it2;

            it1 = this->begin();
            it2 = this->end();
            while (it1 != it2)
            {
                if (this->comp_data(data, *it1))
                    break;
                ++it1;
            }
            return (it1);
        }

        const_iterator upper_bound(const value_type &data) const
        {
            const_iterator it1, it2;

            it1 = this->begin();
            it2 = this->end();
            while (it1 != it2)
            {
                if (this->comp_data(data, *it1))
                    break;
                ++it1;
            }
            return (it1);
        }

        ft::pair<iterator, iterator> equal_range(const value_type &data)
        {
            return (ft::pair<iterator, iterator>(this->lower_bound(data), this->upper_bound(data)));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const value_type &data) const
        {
            return (ft::pair<const_iterator, const_iterator>(this->lower_bound(data), this->upper_bound(data)));
        }

        ////------------tree walk----------------
        void preorder_tree_walk(node head) const
        {
            if (head != this->_null_node)
            {
                std::cout << KeyOfValue()(head->data) << ' ';
                preorder_tree_walk(head->left);
                preorder_tree_walk(head->right);
            }
        }

        void preorder_tree_walk() const
        {
            this->preorder_tree_walk(this->_head);
        }

        void inorder_tree_walk(node head) const
        {
            if (head != this->_null_node)
            {
                inorder_tree_walk(head->left);
                std::cout << KeyOfValue()(head->data) << " ";
                inorder_tree_walk(head->right);
            }
        }

        void inorder_tree_walk() const
        {
            this->inorder_tree_walk(this->_head);
        }

        void postorder_tree_walk(node head) const
        {
            if (head != this->_null_node)
            {
                postorder_tree_walk(head->left);
                postorder_tree_walk(head->right);
                std::cout << KeyOfValue()(head->data) << " ";
            }
        }

        void postorder_tree_walk() const
        {
            this->postorder_tree_walk(this->_head);
        }

        void print_level(node head, int level) const
        {
            if (head != this->_null_node)
            {
                if (level == 1)
                    std::cout << KeyOfValue()(head->data) << " ";
                else if (level > 1)
                {
                    print_level(head->left, level - 1);
                    print_level(head->right, level - 1);
                }
            }
        }

        void print_level(int level) const
        {
            this->print_level(this->_head, level);
        }

        void print_tree(node head) const
        {
            int tree_height;
            int level;

            tree_height = this->height(head);
            level = 1;
            while (level <= tree_height)
            {
                std::cout << "Level " << level - 1 << " - | ";
                print_level(head, level);
                std::cout << "|" << std::endl;
                ++level;
            }
        }

        void print_tree() const
        {
            this->print_tree(this->_head);
        }

        ////-------------insert, erase, swap------------
        ft::pair<iterator, bool> insert(node head, node new_node)
        {
            node tmp = head;
            node parent = this->_null_node;

            while (tmp != this->_null_node)
            {
                parent = tmp;
                if (!this->comp_data(new_node->data, tmp->data) &&
                    !this->comp_data(tmp->data, new_node->data))
                {
                    if (multivalues == false)
                        return (ft::pair<iterator, bool>(iterator(_null_node, tmp), false));
                }
                else if (this->comp_data(new_node->data, tmp->data))
                    tmp = tmp->left;
                else
                    tmp = tmp->right;
            }
            new_node->p = parent;

            if (parent == this->_null_node)
                this->_head = new_node;
            else if (this->comp_data(new_node->data, parent->data))
                parent->left = new_node;
            else
                parent->right = new_node;

            ++(this->_size);
            this->insert_fixup(new_node);
            this->_null_node->p = this->_head;

            return (ft::pair<iterator, bool>(iterator(_null_node, new_node), true));
        }
        ft::pair<iterator, bool> insert(node new_node)
        {
            return (insert(_head, new_node));
        }

        iterator insert(iterator hint, const value_type &value)
        {
            node new_node = this->create_node(value);
            node head_node = hint.get_node();
            ft::pair<iterator, bool> res;

            while (head_node != _null_node)
            {
                if (head_node->p != _null_node &&
                    head_node->p->left == head_node &&
                    comp_data(value, head_node->p->data))
                    break;
                if (head_node->p != _null_node &&
                    head_node->p->right == head_node &&
                    comp_data(head_node->p->data, value))
                    break;
                head_node = head_node->p;
            }

            if (head_node == _null_node)
                head_node = this->_head;

            res = this->insert(head_node, new_node);

            if (res.second == false)
            {
                this->_alloc_node.destroy(new_node);
                this->_alloc_node.deallocate(new_node, 1);
            }
            return (res.first);
        }

        ft::pair<iterator, bool> insert(const value_type &value)
        {
            node new_node = this->create_node(value);
            ft::pair<iterator, bool> res = this->insert(new_node);

            if (res.second == false)
            {
                this->_alloc_node.destroy(new_node);
                this->_alloc_node.deallocate(new_node, 1);
            }
            return (res);
        }

        void insert_fixup(node new_node)
        {
            node y;

            while (new_node->p->color == ft::RED)
            {
                if (new_node->p == new_node->p->p->left)
                {
                    y = new_node->p->p->right;
                    if (y->color == ft::RED)
                    {
                        y->color = ft::BLACK;
                        new_node->p->color = ft::BLACK;
                        new_node->p->p->color = ft::RED;
                        new_node = new_node->p->p;
                    }
                    else
                    {
                        if (new_node == new_node->p->right)
                        {
                            new_node = new_node->p;
                            rotate_left(new_node);
                        }
                        new_node->p->color = ft::BLACK;
                        new_node->p->p->color = ft::RED;
                        rotate_right(new_node->p->p);
                    }
                }
                else
                {
                    y = new_node->p->p->left;
                    if (y->color == ft::RED)
                    {
                        y->color = ft::BLACK;
                        new_node->p->color = ft::BLACK;
                        new_node->p->p->color = ft::RED;
                        new_node = new_node->p->p;
                    }
                    else
                    {
                        if (new_node == new_node->p->left)
                        {
                            new_node = new_node->p;
                            rotate_right(new_node);
                        }
                        new_node->p->color = ft::BLACK;
                        new_node->p->p->color = ft::RED;
                        rotate_left(new_node->p->p);
                    }
                }
            }
            _head->color = ft::BLACK;
        }

        void erase(node old_node)
        {
            node u = old_node;
            node x;
            t_color u_original_color = u->color;

            if (old_node == _null_node)
                return;
            if (old_node->left == this->_null_node)
            {
                x = old_node->right;
                this->transplant(old_node, old_node->right);
            }
            else if (old_node->right == this->_null_node)
            {
                x = old_node->left;
                this->transplant(old_node, old_node->left);
            }
            else
            {
                u = this->min(old_node->right);
                u_original_color = u->color;
                x = u->right;
                if (u != old_node->right)
                {
                    this->transplant(u, u->right);
                    u->right = old_node->right;
                    u->right->p = u;
                }
                else
                    x->p = u;
                this->transplant(old_node, u);
                u->left = old_node->left;
                u->left->p = u;
                u->color = old_node->color;
            }
            this->_alloc_node.destroy(old_node);
            this->_alloc_node.deallocate(old_node, 1);
            --(this->_size);
            if (u_original_color == ft::BLACK)
                erase_fixup(x);
            this->_null_node->p = this->_head;
        }

        size_type erase(value_type value)
        {
            size_type count = 0;
            node found = this->search(value);

            if (found != _null_node)
            {
                this->erase(found);
                ++count;
            }
            return (count);
        }

        void erase(iterator pos)
        {
            this->erase(pos.get_node());
        }

        void erase_fixup(node x)
        {
            node w;

            while (x != _head && x->color == ft::BLACK)
            {
                if (x == x->p->left)
                {
                    w = x->p->right;
                    if (w->color == ft::RED)
                    {
                        w->color = ft::BLACK;
                        x->p->color = ft::RED;
                        rotate_left(x->p);
                        w = x->p->right;
                    }
                    if (w->left->color == ft::BLACK && w->right->color == ft::BLACK)
                    {
                        w->color = ft::RED;
                        x = x->p;
                    }
                    else
                    {
                        if (w->right->color == ft::BLACK)
                        {
                            w->left->color = ft::BLACK;
                            w->color = ft::RED;
                            rotate_right(w);
                            w = x->p->right;
                        }
                        w->color = x->p->color;
                        x->p->color = ft::BLACK;
                        w->right->color = ft::BLACK;
                        rotate_left(x->p);
                        x = _head;
                    }
                }
                else
                {
                    w = x->p->left;
                    if (w->color == ft::RED)
                    {
                        w->color = ft::BLACK;
                        x->p->color = ft::RED;
                        rotate_right(x->p);
                        w = x->p->left;
                    }
                    if (w->right->color == ft::BLACK && w->left->color == ft::BLACK)
                    {
                        w->color = ft::RED;
                        x = x->p;
                    }
                    else
                    {
                        if (w->left->color == ft::BLACK)
                        {
                            w->right->color = ft::BLACK;
                            w->color = ft::RED;
                            rotate_left(w);
                            w = x->p->left;
                        }
                        w->color = x->p->color;
                        x->p->color = ft::BLACK;
                        w->left->color = ft::BLACK;
                        rotate_right(x->p);
                        x = _head;
                    }
                }
            }
            x->color = ft::BLACK;
        }

        void clear(node head)
        {
            if (head != this->_null_node)
            {
                this->clear(head->left);
                this->clear(head->right);
                this->_alloc_node.destroy(head);
                this->_alloc_node.deallocate(head, 1);
                --(this->_size);
            }
        }

        void clear()
        {
            this->clear(_head);
            _head = _null_node;
        }

        void swap(rb_tree &other)
        {
            node tmp_head = this->_head;
            this->_head = other._head;
            other._head = tmp_head;

            node tmp_null = this->_null_node;
            this->_null_node = other._null_node;
            other._null_node = tmp_null;

            size_type tmp_size = this->_size;
            this->_size = other._size;
            other._size = tmp_size;

            key_compare tmp_comp = this->_comp;
            this->_comp = other._comp;
            other._comp = tmp_comp;
        }

        ///////-----------------iterators---------------
        iterator begin()
        {
            return (iterator(this->_null_node, this->min()));
        }

        const_iterator begin() const
        {
            return (const_iterator(this->_null_node, this->min()));
        }

        iterator end()
        {
            return (iterator(this->_null_node, this->_null_node));
        }

        const_iterator end() const
        {
            return (const_iterator(this->_null_node, this->_null_node));
        }

        reverse_iterator_t rbegin()
        {
            return (reverse_iterator_t(this->end()));
        }

        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(this->end()));
        }

        reverse_iterator_t rend()
        {
            return (reverse_iterator_t(this->begin()));
        }

        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(this->begin()));
        }

        ////------------allocator-----------
        allocator_type get_allocator() const
        {
            return (this->_alloc);
        }

    private:
        void transplant(node u, node v)
        {
            if (u->p == _null_node)
                this->_head = v;
            else if (u == u->p->left)
                u->p->left = v;
            else
                u->p->right = v;
            v->p = u->p;
        }

        void deep_copy(node other_node, node other_null)
        {
            if (other_node != other_null)
            {
                this->insert(create_node(other_node->data));
                this->deep_copy(other_node->left, other_null);
                this->deep_copy(other_node->right, other_null);
            }
        }

        bool comp_data(value_type v1, value_type v2) const
        {
            return (_comp(KeyOfValue()(v1), KeyOfValue()(v2)));
        }

        void rotate_left(node n)
        {
            node y = n->right;

            n->right = y->left;
            if (y->left != _null_node)
                y->left->p = n;
            y->p = n->p;
            if (n->p == _null_node)
                _head = y;
            else if (n == n->p->left)
                n->p->left = y;
            else
                n->p->right = y;
            y->left = n;
            n->p = y;
        }

        void rotate_right(node n)
        {
            node y = n->left;

            n->left = y->right;
            if (y->right != _null_node)
                y->right->p = n;
            y->p = n->p;
            if (n->p == _null_node)
                _head = y;
            else if (n == n->p->left)
                n->p->left = y;
            else
                n->p->right = y;
            y->right = n;
            n->p = y;
        }

    private:
        node _head;
        node _null_node;
        allocator_type _alloc;
        allocator_node_type _alloc_node;
        key_compare _comp;
        size_type _size;

        // void transplant(node u, node v);
        // void deep_copy(node other_node, node other_null);
        // bool comp_data(value_type v1, value_type v2) const;
        // void rotate_left(node node);
        // void rotate_right(node node);
    };
}

#endif