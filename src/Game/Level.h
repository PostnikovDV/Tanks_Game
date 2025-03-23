#pragma once
#include <iostream>
#include <vector>

class IGameObject;

class Level
{
public:

	Level(const std::vector<std::string> levelDescription);


	void render() const;
	void update(const uint64_t delta);

	size_t getLevelWidth() const;

	size_t getLevelHight() const;

private:
	size_t m_width;
	size_t m_height;

	std::vector<std::shared_ptr<IGameObject>> m_mapObject;
};