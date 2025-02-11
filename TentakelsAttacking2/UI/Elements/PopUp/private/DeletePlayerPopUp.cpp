//
// Purpur Tentakel
// 15.10.2022
//

#include "DeletePlayerPopUp.h"
#include "GenerelEvents.hpp"
#include "HGeneral.h"
#include "HFocusEvents.h"

void DeletePlayerPopUp::Initialize(AppContext const& appContext,
	Vector2 resolution) {

	auto acceptBtn = InitializeAcceptButton(appContext, resolution);
	acceptBtn->SetOnClick([this]() {this->SetValue();});

	auto inputLine = std::make_shared<InputLine<int>>(
		3,
		GetElementPosition(m_pos, m_size, 0.5f, 0.45f),
		GetElementSize(m_size, 0.5f, 0.1f),
		Alignment::TOP_MID,
		resolution,
		5
		);
	inputLine->SetPlaceholderText("Player ID");
	m_inputLine = inputLine;
	m_elements.push_back(inputLine);

	AddFocusElement(m_inputLine.get(), true);
	SelectFocusElement(m_inputLine.get(), true);
}

void DeletePlayerPopUp::SetValue() {
	unsigned int const ID{ static_cast<unsigned int const>(m_inputLine->GetValue()) };

	m_onClick(ID);

	SetShouldClose();
}

DeletePlayerPopUp::DeletePlayerPopUp(Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution,
	std::string const& title, AssetType inputTexture,
	std::function<void(unsigned int)> onClick)
	: CellPopUp{ pos, size, alignment, resolution,
		title, inputTexture }, m_onClick{ onClick } {
	Initialize(AppContext::GetInstance(), resolution);

	if (IsKeyReleased(KEY_ENTER)
		or IsKeyReleased(KEY_KP_ENTER)) {
		m_firstEnter = true;
	}
}
