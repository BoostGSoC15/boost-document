#ifndef _OO_FUNCTIONS_HPP
#define _OO_FUNCTIONS_HPP

#include <string>
#include <boost/filesystem.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

namespace boost { namespace doc { namespace oo_functions {

	std::string convert_extension_to_pdf_filter(const std::string extension);
	::com::sun::star::uno::Reference<com::sun::star::lang::XMultiServiceFactory> connect_to_oo_server();
	void set_bootstrap_offapi();
	void start_oo_server();
	::rtl::OUString get_url_from_path(const boost::filesystem::path& path);
	void open_oo(const boost::filesystem::path& path);
	void export_oo(const boost::filesystem::path &inputPath, boost::document_file_format::type format);

}}}

#endif