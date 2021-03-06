#ifndef _MS_CELL_IMPL_HPP
#define _MS_CELL_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/cell_content_type.hpp>

#include <boost/document/detail/ms_api/ms_cell_func.hpp>

namespace boost { namespace detail {

class ms_cell : public cell_interface {

	protected:
	IDispatch* cell_ptr_;
	std::size_t row_, column_;
	public:

	ms_cell(IDispatch* cell_ptr,std::size_t row,std::size_t column) {
		cell_ptr_ = cell_ptr;
		row_ = row;
		column_ = column;
	}

	void set_cell_formula(const std::string& str) {
		boost::doc::ms_cell_func::set_cell_formula(cell_ptr_, str);
	}

	void set_cell_value(const std::string& str) {
		boost::doc::ms_cell_func::set_cell_value(cell_ptr_,str);
	}

	void set_cell_value(double x) {
		boost::doc::ms_cell_func::set_cell_value(cell_ptr_,x);
	}

	boost::cell_content_type::type get_content_type() {
		return boost::doc::ms_cell_func::get_content_type(cell_ptr_);
	}

	std::string get_string() {
		return boost::doc::ms_cell_func::get_string(cell_ptr_);
	}


	std::string get_formula() {
		return boost::doc::ms_cell_func::get_formula(cell_ptr_);
	}

	double get_value() {
		return boost::doc::ms_cell_func::get_value(cell_ptr_);
	}

	bool empty() {
		if(boost::doc::ms_cell_func::get_content_type(cell_ptr_) == boost::cell_content_type::EMPTY) {
			return true;
		}
		return false;
	}

	void reset() {
		boost::doc::ms_cell_func::set_cell_value(cell_ptr_,"");
	}

	std::size_t get_row_index() {
		return row_;
	}

	std::size_t get_column_index() {
		return column_;
	}

 	~ms_cell() {
 	}

};

}} // namespace boost::detail


#endif
