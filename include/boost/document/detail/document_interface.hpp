#ifndef _DOCUMENT_INTERFACE_HPP
#define _DOCUMENT_INTERFACE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/document/detail/document_file_format.hpp>

namespace boost {

	class document_interface {
		virtual void open() = 0;
		virtual void close() = 0;
		virtual void save() = 0;
		virtual void export(boost::document_file_format::type format) = 0;
		virtual ~document_interface();
	};	
} // namespace boost

#endif
