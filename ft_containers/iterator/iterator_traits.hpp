/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:21:54 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/13 17:49:21 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{
	/*
	** ITERATOR TAGS
	** Empty types used to differenciate the iterators
	*/

	struct input_iterator_tag {};

	struct output_iterator_tag {};

	struct forward_iterator_tag : public input_iterator_tag {};

	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/*
	** ITERATOR TAGS
	*/

	template <class Iterator>
	struct iterator_traits
	{
		public:
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
	};
	template <class Iterator>
	struct iterator_traits<Iterator*>
	{
		typedef Iterator								value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef random_access_iterator_tag				iterator_category;
		typedef Iterator*								pointer;
		typedef Iterator&								reference;
	};

	template <class Iterator>
	struct iterator_traits<const Iterator*>
	{
		typedef Iterator								value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef random_access_iterator_tag				iterator_category;
		typedef const Iterator*							pointer;
		typedef const Iterator&							reference;
	};

};