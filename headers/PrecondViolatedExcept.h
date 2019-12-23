#ifndef __PRECOND_VIOLATED_EXCEPT_H__
#define __PRECOND_VIOLATED_EXCEPT_H__

#include <stdexcept>
#include <string>

class PrecondViolatedExcept : public std::logic_error
{
public:
	PrecondViolatedExcept(const std::string& message = "") : logic_error("PrecondViolatedExcept" + message) {}
};	// end PrecondViolatedExcept
 #endif /*__PRECOND_VIOLATED_EXCEPT_H__*/
