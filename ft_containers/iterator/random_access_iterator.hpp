/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:57:01 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/28 10:26:26 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "iterator.hpp"

namespace ft
{
	using ft::iterator_traits;
	using ft::iterator;
	template<typename iterator>
	class random_access_iterator
	{
		public:
			typedef iterator								value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef ft::random_access_iterator_tag			iterator_category;
			typedef iterator*								pointer;
			typedef iterator&								reference;

			/*
			** All iterator Categories Requirements
			*/

			random_access_iterator(const random_access_iterator &rhs)
			:_current(rhs._current) {}

			random_access_iterator(pointer rhs)
			:_current(rhs) {}

			random_access_iterator &
			operator=(const random_access_iterator &rhs)
			{this->_current = rhs._current;}

			~random_access_iterator() {}

			pointer
			base() const
			{ return (this->_current); }

			random_access_iterator&
			operator++()
			{
				++this->_current;
				return (*this);
			}

			random_access_iterator
			operator++(int)
			{ return (random_access_iterator(this->_current++)); }

			/*
			** Forward iterator Requirements
			*/

			template<typename iteratorL, typename iteratorR>
			bool
			operator==(const random_access_iterator<iteratorR> &rhs)
			{ return (this->base() == rhs.base()); }

			template<typename iteratorL, typename iteratorR>
			bool
			operator!=(const random_access_iterator<iteratorR> &rhs)
			{ return (this->base() != rhs.base()); }

			reference
			operator*() const
			{ return (*(this->_current)); }

			pointer
			operator->() const
			{ return (this->_current); }

			random_access_iterator()
			: _current(0) {};

			/*
			** Bidirectional iterator Requirements
			*/

			iterator&
			operator--()
			{
				--this->_current;
				return (*this);
			}

			iterator
			operator--(int)
			{ return (iterator(this->_current--)); }

			/*
			** Random Access iterator Requirements
			*/

			// AJOUTER SUPPORT NON CONST ?

			random_access_iterator
			operator+(difference_type n) const
			{ return (this->_current + n); }

			random_access_iterator
			operator-(difference_type n) const
			{ return (this->_current - n); }


			template<typename iteratorR>
			difference_type
			operator+(const random_access_iterator<iteratorR> &rhs)
			{ return (this->base() - rhs.base()); }

			template<typename iteratorR>
			difference_type
			operator-(const random_access_iterator<iteratorR> &rhs)
			{ return (this->base() - rhs.base()); }


			template<typename iteratorL, typename iteratorR>
			bool
			operator<(const random_access_iterator<iteratorR> &rhs)
			{ return (this->base() < rhs.base()); }

			template<typename iteratorL, typename iteratorR>
			bool
			operator>(const random_access_iterator<iteratorR> &rhs)
			{ return (this->base() > rhs.base()); }

			template<typename iteratorL, typename iteratorR>
			bool
			operator<=(const random_access_iterator<iteratorR> &rhs)
			{ return (this->base() <= rhs.base()); }

			template<typename iteratorL, typename iteratorR>
			bool
			operator>=(const random_access_iterator<iteratorR> &rhs)
			{ return (this->base() >= rhs.base()); }

			random_access_iterator&
			operator+=(difference_type n)
			{
				this->_current += n;
				return (*this);
			}

			random_access_iterator&
			operator-=(difference_type n)
			{
				this->_current -= n;
				return (*this);
			}

			reference
			operator[](difference_type n) const
			{ return (this->_current[n]); }

		private:
			pointer _current;
	};
};