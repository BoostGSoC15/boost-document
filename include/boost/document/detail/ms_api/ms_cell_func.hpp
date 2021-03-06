#ifndef _MS_CELL_FUNC_HPP
#define _MS_CELL_FUNC_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ole2.h>
#include <objbase.h>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/document_exception.hpp>

namespace boost { namespace doc { namespace ms_cell_func {

void get_cell(IDispatch* sheet_ptr,int i, int j, IDispatch*& cell_ptr);
void get_cell_unchecked(IDispatch* sheet_ptr,int i, int j, IDispatch*& cell_ptr);

void set_cell_value(IDispatch* cell_ptr, const std::string& str);
void set_cell_value(IDispatch* cell_ptr, double x);
void set_cell_formula(IDispatch* cell_ptr, const std::string& str)

std::string get_string(IDispatch* cell_ptr);
std::string get_formula(IDispatch* cell_ptr);
double get_value(IDispatch* cell_ptr);

boost::cell_content_type::type get_content_type(IDispatch* cell_ptr);

}}}
#endif