//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "UIElement.hpp"

/**
 * provides a line.
 * the line is drawn from collider.x, collider.y to collider.x + with, collider.y + height.
 * to draw a line from right to left used a negative width.
 * same applies for the height.
 */
class Line final : public UIElement {
private:
	float m_thick; ///< contains the thickness of the line

public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	Line(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		float thick);

	/**
	 * renders the line.
	 */
	void Render(AppContext const& appContext);
};