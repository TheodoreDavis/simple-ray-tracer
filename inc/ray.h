#ifndef _RAY_
#define _RAY_

#include <inc/v3.h>

class ray {
	private:
		v3 origin_;
		v3 direction_;
	public:
		/*
			constructors
		*/
		ray() {  }
		ray(v3 origin, v3 direction) {
			
			this->origin_ = origin;
			this->direction_ = direction;
		}
		
		/*
			accessors
		*/
		v3 ori() const { return this->origin_; }
		v3& ori() { return this->origin_; }
		v3 dir() const { return this->direction_; }
		v3& dir() { return this->direction_; }
		
		/*
			i/o functions
		*/
		friend std::ostream& operator<<(std::ostream& out, const ray &rhs);
		
		/*
			utility functions
		*/
		const v3 eval(const float t);
};	

#endif