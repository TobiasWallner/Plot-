#include "plotpp/LineType.hpp"

#include <string_view>
#include <sstream>

namespace plotpp{

	std::string_view to_command(LineType dt){
		switch(dt){
			case LineType::none: return "dt -1";
			case LineType::solid: return "dt 1";
			case LineType::dashed: return "dt 2";
			case LineType::doted: return "dt 3";
			case LineType::dash_doted: return "dt 4";
			case LineType::dash_doted2: return "dt 5";
		}
		std::stringstream message;
		message << "Error in funtion: " << __FUNCTION__ << "\n"
				<< "  in file: " << __FILE__ << "\n"
				<< "  at line: " << __LINE__ << "\n"
				<< "  message: missing switch case: " << static_cast<int>(dt) << "\n";
		throw std::runtime_error(message.str());
	}

}