//
// Purpur Tentakel
// 15.09.2022
//

#pragma once
#include "UIElement.hpp"

enum class AssetType;

/**
 * provides a texture that keeps the correct ratio by default.
 * you can disabled it.
 */
class Picture final : public UIElement {
private:
	Texture2D* m_texture{ nullptr }; ///< contains a pointer to the picture
	bool m_isScaleToFit{ true }; ///< contains if the picture scales itself to fit.

public:
	/**
	 * ctor.
	 * scales the size to fit if it should be.
	 */
	Picture(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		AssetType assetType, bool scaleToFit = true);

	/**
	 * renders the picture.
	 */
	void Render(AppContext const& appContext);
};
