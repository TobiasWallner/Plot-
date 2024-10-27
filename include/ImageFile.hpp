#pragma once

#include <string>
#include <sstream>
#include <ostream>


#include "ImageFileType.hpp"
#include "IPlot.hpp"


namespace plotpp{

	[[deprecated("needs fixing, does not integrate in the way variables are defined and assigned to plots in gnuplot scripts")]]
	class ImageFile : public IPlot {
	public:
	std::string filename;
	ImageFileType filetype;
	
	ImageFile(std::string filename, Text title="")
		: IPlot(std::move(title))
		, filename(std::move(filename))
		, filetype(image_filetype_from_filename(this->filename))
	{
		if(filetype == ImageFileType::NONE){
			std::stringstream message;
			message << "Error in funtion: " << __FUNCTION__ << "\n"
					<< "  in file: " << __FILE__ << "\n"
					<< "  at line: " << __LINE__ << "\n"
					<< "  message: NONE is not a valid filetype\n";
			throw std::runtime_error(message.str());
		}
	}
	
	ImageFile(std::string filename, ImageFileType filetype, Text title = "")
		: IPlot(std::move(title))
		, filename(std::move(filename))
		, filetype((filetype == ImageFileType::NONE) ? image_filetype_from_filename(filename) : filetype)
	{
		if(filetype == ImageFileType::NONE){
			std::stringstream message;
			message << "Error in funtion: " << __FUNCTION__ << "\n"
					<< "  in file: " << __FILE__ << "\n"
					<< "  at line: " << __LINE__ << "\n"
					<< "  message: NONE is not a valid filetype\n";
			throw std::runtime_error(message.str());
		}
	}
	
	virtual void print_plot(std::ostream& stream) const {
		stream << "with rgbalpha title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "file='" << this->filename <<"' binary filetype=" << to_string(this->filetype) << "\n";
	}
	
};

}