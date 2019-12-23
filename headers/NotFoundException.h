#ifndef __NOT_FOUND_EXCEPTION_H__
#define __NOT_FOUND_EXCEPTION_H__

#include <stdexcept>
#include <string>

using namespace std;

class NotFoundException : public logic_error
{
public:
   NotFoundException(const string& message = "") : logic_error("Not Found Violated Exception: " + message) {}
}; // end NotFoundException

#endif /*__NOT_FOUND_EXCEPTION_H__*/
