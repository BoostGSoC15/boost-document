#ifndef _DOCUMENT_FILE_FORMAT_HPP
#define _DOCUMENT_FILE_FORMAT_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost {
	
	//! \brief Document File Format
	//!       which can be exported.
	//!
	struct document_file_format {
		enum type {
			PDF,CSV,XML,
		};
	};
} // namespace boost

#endif
