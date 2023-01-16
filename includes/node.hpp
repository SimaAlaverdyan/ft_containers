#ifndef NODE_HPP
#define NODE_HPP

namespace ft
{
    typedef enum e_color
    {
        BLACK,
        RED
    }           t_color;

    template <typename T>
    struct Node
    {
        Node() : data()
        {
            this->left = NULL;
            this->right = NULL;
            this->p = NULL;
            this->color = ft::RED;
        }
        Node(const T &elem) : data()
        {
            this->left = NULL;
            this->right = NULL;
            this->p = NULL;
            this->color = ft::RED;
        }
        Node(const Node &copy)
        {
            this->data = copy.data;
            this->left = copy.left;
            this->right = copy.right;
            this->p = copy.p;
            this->color = copy.color;
        }
        Node &operator=(const Node &copy)
        {
            if (this != &copy)
            {
                this->data = copy.data;
                this->left = copy.left;
                this->right = copy.right;
                this->p = copy.p;
                this->color = copy.color;
            }
            return (*this);
        }
        ~Node() {};

        T   data;
        Node    *left;
        Node    *right;
        Node    *p;
        t_color color;
    };
}

#endif