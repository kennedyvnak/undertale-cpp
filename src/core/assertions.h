#pragma once

#define EN_BREAK __debugbreak

#define EN_ASSERT(cond, ...)\
if(!(cond)) {\
	EN_LOG_ERROR(__VA_ARGS__);\
    EN_BREAK();\
}\
