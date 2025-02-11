//
// Purpur Tentakel
// 14.05.2023
//

#include "EventListener.hpp"
#include <vector>
#pragma once

class Hover;

class HoverRender final : public EventListener {
private:
	std::vector<Hover*> m_elements; ///< contains all hover that gets renders this frame

public:
	/**
	 * registers as EventListener
	 */
	HoverRender();

	/**
	 * removes the EventListener
	 */
	~HoverRender();

	/**
	 * renders all hovers of the frame and clears the queue
	 */
	void Render();

	/**
	 * handles the events
	 */
	void OnEvent(Event const& event) override;
};
