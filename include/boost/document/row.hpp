#ifndef _ROW_HPP
#define _ROW_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <boost/document/cell.hpp>
#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/document_exception.hpp>

namespace boost {
	class row {
		protected:
		std::shared_ptr<sheet_interface> obj_;
		std::size_t column_;
		boost::cell current_cell_;
		public:		
		row(std::shared_ptr<sheet_interface> obj, std::size_t column) : obj_(obj), column_(column), current_cell_(obj->get_cell_unchecked(0,column_)) {
		}
		boost::cell get_cell(std::size_t row) {
			return obj_->get_cell(row,column_);
		}
		boost::cell operator[](std::size_t row) {
			return obj_->get_cell_unchecked(row,column_);
		}
		boost::cell& set_current_cell(std::size_t row) {
			current_cell_ = obj_->get_cell_unchecked(row,column_);
			return current_cell_;
		}
		class row_iterator: public boost::iterator_facade<
		    row_iterator, 
		    boost::cell, 
		    boost::random_access_traversal_tag
		    > {
		    public:
		    friend class boost::iterator_core_access;
		    boost::row* r_;
		    std::size_t cell_no_;
		    //boost::cell current_cell_;
		                
		    typedef boost::iterator_facade<
		        row_iterator, 
		        boost::cell,
		        boost::random_access_traversal_tag
		    > base_t;

		    row_iterator(boost::row* r, std::size_t num) : r_(r), cell_no_(num) 
		    {}

		    void increment() { ++this->cell_no_; }

		    void decrement() { --this->cell_no_; }
		                
		    void advance(std::size_t n) { this->cell_no_ += n; }
		                 
		    bool equal(row_iterator const& other) const {
		        return this->r_ == other.r_ and this->cell_no_ == other.cell_no_;
		    }

		    std::size_t distance_to(row_iterator const& other) const {
		        if(this->r_ != other.r_) {
		            boost::throw_exception(document_exception(
		            "Error: Both the iterators are not equal"));    
		        }
		        int s = (int)this->cell_no_ - (int)other.cell_no_;
		        return (std::size_t)(s>0?s:-s);
		    }

		    base_t::reference dereference() const { 
		        return r_->set_current_cell(cell_no_);
		    }
		};  
		row_iterator begin() { return row_iterator(this, (std::size_t)0); }
		row_iterator end() { return row_iterator(this, obj_->max_column()); }
	};
} // namespace boost

#endif