#ifndef _CELL_INTERFACE_HPP
#define _CELL_INTERFACE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/document/detail/cell_content_type.hpp>

namespace boost {

	class cell_interface {
	 public:
	 	virtual void set_cell_value(const std::string& str) = 0;
    	virtual void set_cell_formula(const std::string& str) = 0;
    	virtual void set_cell_value(double i) = 0;
    	virtual boost::cell_content_type::type get_content_type() const = 0;
    	virtual bool empty() const = 0;
    	virtual void reset() = 0;
		virtual std::string get_formula() const = 0;
		virtual std::string get_string() const = 0;
		virtual std::size_t get_row_index() const = 0;
		virtual std::size_t get_column_index() const = 0;	
		virtual double get_value() const = 0;
   		virtual ~cell_interface() {}
	};	
} // namespace boost

#endif
