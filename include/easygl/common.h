#ifndef __EASYGL_COMMON_H__
#define __EASYGL_COMMON_H__

#include <glad/glad.h>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

#endif // __EASYGL_COMMON_H__