#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
// Default Colors.
namespace color { // RGB to 0-1 range
	const glm::vec4 PURPLE = glm::vec4(104.f / 255, 31.f / 255, 112.f / 255,1);
	const glm::vec4 BLUE = glm::vec4(13.f / 255, 13.f / 255, 181.f / 255,1);
	const glm::vec4 GREEN = glm::vec4(8.f / 255, 168.f / 255, 5.f / 255,1);
	const glm::vec4 RED = glm::vec4(168.f / 255, 5.f / 255, 5.f / 255,1);
	const glm::vec4 YELLOW = glm::vec4(211.f / 255, 214.f / 255, 17.f / 255,1);

	const std::vector<glm::vec4> colors = { PURPLE, BLUE, GREEN, RED, YELLOW };


};
