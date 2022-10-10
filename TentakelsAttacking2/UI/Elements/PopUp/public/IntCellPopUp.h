//
// Purpur Tentakel
// 04.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"

class IntCell;

class IntCellPopUp : public CellPopUp {
private:
	std::shared_ptr<InputLine<int>> m_inputChange;
	IntCell* m_currentCell;

	void Initialize(AppContext const& appContext, Vector2 resolution) override;
	void SetValue() override;

public:
	IntCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture, IntCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
};