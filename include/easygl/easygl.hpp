#ifndef __EASY_GL_HPP__
#define __EASY_GL_HPP__

#include <glad/glad.h>
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include <iostream>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

std::optional<std::string> loadTextFile(const std::string& filename);

#endif // __EASY_GL_HPP__