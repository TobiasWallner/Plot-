#pragma once

#include <string>
#include <sstream>
#include <ostream>


#include "ImageFileType.hpp"
#include "IPlot.hpp"


namespace plotpp{

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
	
	virtual void print_config(std::ostream& stream) const {
		stream << " '" << this->filename << "' binary filetype=" << to_string(this->filetype) 
				<< " with rgbalpha title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data([[maybe_unused]]std::ostream& stream) const {}
	
};

}