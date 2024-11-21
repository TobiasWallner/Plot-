#pragma once

#include <ostream>
#include <iterator>
#include <optional>

#include "plotpp/IPlot.hpp"


/* TODO: parameterise boxwidth 
				float width
				BoxWithType:: Absolute | Relative
*/

/* TODO: Add Color

*/


namespace plotpp{
	
	template<class Tx, class Ty>
	class Boxes : public IPlot{
	public:
		
		Boxes(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{}
		
		// ---- setters getters ----
		
		Boxes& label(const char* label) & {this->IPlot::label(label); return *this;}
		Boxes&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		Boxes& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		Boxes&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		Boxes& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		Boxes&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		float opacity() const {return this->opacity_;}
		Boxes& opacity(float opacity) & {this->opacity_ = opacity; return *this;}
		Boxes&& opacity(float opacity) && {this->opacity_ = opacity; return std::move(*this);}
		
		float boxWidth() const {return this->box_width;}
		Boxes& boxWidth(float bw) & {this->box_width = bw; return *this;}
		Boxes&& boxWidth(float bw) && {this->box_width = bw; return std::move(*this);}
		
		bool relativeBoxWidth() const {return this->relative_boxwidth;}
		Boxes& relativeBoxWidth(bool rbw) & {this->relative_boxwidth = rbw; return *this;}
		Boxes&& relativeBoxWidth(bool rbw) && {this->relative_boxwidth = rbw; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		// TODO: set the boxwidth individually using replot in the figure. 
		virtual void printSettings(std::ostream& stream) const {
			stream << "set boxwidth " << this->boxWidth() << (this->relativeBoxWidth() ? " relative" : "") << '\n';
		}
		
		virtual void printData(std::ostream& stream) const {
			auto xitr = std::begin(*x_);
			auto yitr = std::begin(*y_);
			for(; yitr!=std::end(*y_) && xitr!=std::end(*x_); ++yitr, (void)++xitr)
				stream << *xitr << ' ' << *yitr << '\n';				
		}
		
		virtual void printPlot(std::ostream& stream) const {
			stream << "using 1:2 with boxes fs transparent solid " << this->opacity();
			
			if(this->IPlot::label().empty()){
				stream << " notitle";
			}else{
				stream <<  " title '" << this->IPlot::label() << "'";
			}
		}
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_color = std::nullopt;
		float opacity_ = 0.5;
		float box_width = 0.8;
		bool relative_boxwidth = true;
	};
	
	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto boxes(U1&& x, U2&& y) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxes<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}
}