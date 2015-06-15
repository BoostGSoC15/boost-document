#ifndef _MS_DOCUMENT_IMPL_HPP
#define _MS_DOCUMENT_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <memory>

#include <windows.h>
#include <ole2.h>

#include <boost/filesystem.hpp>

#include <boost/document/sheet.hpp>

#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_file_format.hpp>

#include <boost/document/detail/document_interface.hpp>
#include <boost/document/detail/sheet_interface.hpp>

#include <boost/document/detail/ms_api/ms_functions.hpp>
#include <boost/document/detail/ms_api/ms_sheet.hpp>

#include "sheet_impl.hpp"

namespace boost { namespace detail { 

class ms_document: public document_interface {
protected:
	boost::filesystem::path doc_path_;
	bool is_file_opened;	
	CLSID clsid_;
	IDispatch *appl_ptr_;
	IDispatch *book_ptr_;
	IDispatch *sheets_ptr_;
public:
	void initialize(const boost::filesystem::path& fpath) {
		CoInitialize(NULL);
		this->doc_path_ = boost::filesystem::system_complete(fpath);
		if(!boost::filesystem::exists(this->doc_path_)) {
        		boost::throw_exception(document_exception(
            		"Error: Path is empty or does not exist."));
    		}
		this->clsid_ = boost::doc::ms_functions::get_clsid();
		boost::doc::ms_functions::get_application_pointer(clsid_,this->appl_ptr_);
		this->sheets_ptr_ = NULL;
		this->is_file_opened = false;
	}

	void create() {
		if (!this->is_file_opened) {
			boost::doc::ms_functions::create_ms(this->doc_path_, this->appl_ptr_, this->book_ptr_);
			this->is_file_opened = true;
		}
	}

	void open() {
		if(!this->is_file_opened) {
			boost::doc::ms_functions::open_ms(this->doc_path_, this->appl_ptr_, this->book_ptr_);
			this->is_file_opened = true;
		}
 	}

 	void close() {
 		if(this->is_file_opened) {
			boost::doc::ms_functions::close_ms(this->doc_path_, false, this->appl_ptr_, this->book_ptr_);
			this->is_file_opened = false;
		}
		else {
			boost::throw_exception(document_exception(
            		"Error: Trying to close unopened file."));	
		}
 	}
 	
 	void save() {
 		if(!this->is_file_opened) {
			boost::throw_exception(document_exception(
            		"Error: Trying to save unopened file."));
		}
		boost::doc::ms_functions::save_ms(this->doc_path_, this->appl_ptr_, this->book_ptr_);
 	}
 	
 	void save_as(const boost::filesystem::path& fpath) {
 		if(!this->is_file_opened) {
			boost::throw_exception(document_exception(
            		"Error: Trying to save unopened file."));
		}
		boost::doc::ms_functions::save_ms(boost::filesystem::system_complete(fpath), this->appl_ptr_, this->book_ptr_);
 	}
 	
 	void export_as(boost::document_file_format::type format) {
		if (!this->is_file_opened) {
			boost::throw_exception(document_exception(
				"Error: Trying to save unopened file."));
		}
		boost::doc::ms_functions::export_ms(this->doc_path_, format, this->appl_ptr_, this->book_ptr_);
 	}


	boost::sheet get_sheet(const std::string& str) {
		if (!this->sheets_ptr_) {
			boost::doc::ms_sheet::get_sheets_of_document(this->sheets_ptr_, this->book_ptr_);
		}
		IDispatch* sheet_ptr;
		boost::doc::ms_sheet::get_sheet_by_name(this->sheets_ptr_, str, sheet_ptr);
		std::string new_str(str);
		return boost::sheet(std::dynamic_pointer_cast<sheet_interface>(std::make_shared<boost::detail::ms_sheet>(sheet_ptr,new_str)));
	}

	boost::sheet get_sheet(int index) {
		if (!this->sheets_ptr_) {
			boost::doc::ms_sheet::get_sheets_of_document(this->sheets_ptr_, this->book_ptr_);
		}
		IDispatch* sheet_ptr; 
		boost::doc::ms_sheet::get_sheet_by_index(this->sheets_ptr_, index, sheet_ptr);
		return boost::sheet(std::dynamic_pointer_cast<sheet_interface>(std::make_shared<boost::detail::ms_sheet>(sheet_ptr,index)));
	}

	int sheet_count() {
		boost::throw_exception(document_exception(
			"Function Un-implemented. :("));
	}

	void delete_sheet(const std::string& str) {
		boost::throw_exception(document_exception(
			"Function Un-implemented. :("));
	}

	void delete_sheet(int index) {
		boost::throw_exception(document_exception(
			"Function Un-implemented. :("));
	}

 	~ms_document() {
 		if(this->is_file_opened) {
			boost::doc::ms_functions::close_ms(this->doc_path_, false, this->appl_ptr_, this->book_ptr_);
			this->is_file_opened = false;
		}
		boost::doc::ms_functions::close_app(this->appl_ptr_);
		CoUninitialize();
 	}

};

std::shared_ptr<document_interface> open_ms_instance() {
	return std::dynamic_pointer_cast<document_interface>(std::make_shared<boost::detail::ms_document>());
}

}} // namespace boost::detail


#endif
