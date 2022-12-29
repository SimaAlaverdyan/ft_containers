#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

namespace ft
{
    template <typename T>
	class	random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
        public:
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference reference;
            typedef pointer iterator_type;
    };
}

#endif