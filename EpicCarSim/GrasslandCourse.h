#ifndef GRASSLANDCOURSE_H
#define GRASSLANDCOURSE_H

#include "Course.h"

class GrasslandCourse : public Course
{
private:


public:
	GrasslandCourse();
	~GrasslandCourse();
	int init();
	virtual int getCondition(const int x, const int y);
};




#endif // !GRASSLANDCOURSE_H


