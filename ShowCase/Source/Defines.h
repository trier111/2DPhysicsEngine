#pragma once

namespace ShowcaseConfig 
{
	constexpr int WINDOW_WIDTH = 1920;
	constexpr int WINDOW_HEIGHT = 1080;
	constexpr float ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

	constexpr float MAX_FPS = 60.0f;

	constexpr float SPAWN_COOLDOWN_USER = 0.1f;
	constexpr float SPAWN_COOLDOWN_SPAWNER = 0.2f;
	constexpr float DEFAULT_CIRCLE_RADIUS = 20.f;
	constexpr float DEFAULT_AABB_SIZE = 30.f;

}
