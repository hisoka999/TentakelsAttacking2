//
// Purpur Tentakel
// 05.09.2022
//

#include "PopUpManager.h"
#include "HFocusEvents.h"
#include "HPrint.h"

PopUpManager::PopUpManager(Vector2 resolution)
	: m_appContext{ &(AppContext::GetInstance()) }, m_resolution{ resolution } {
	m_appContext->eventManager.AddListener(this);
	Print("PopUpManager", PrintType::INITIALIZE);
}

bool PopUpManager::IsActivePopUp() const {
	return !m_popUps.empty();
}

void PopUpManager::OnEvent(Event const& event) {

	// Message Pop Up
	if (auto const PopUpEvent = dynamic_cast<ShowMessagePopUpEvent const*>(&event)) {
		NewMessagePopUp(PopUpEvent);
		return;
	}

	// Delete Player Pop Up
	if (auto const PopUpEvent = dynamic_cast<ShowDeletePlayerPopUpEvent const*>(&event)) {
		NewDeletePlayerPopUp(PopUpEvent);
		return;
	}

	// Table Pop Up
	if (auto const PopUpEvent = dynamic_cast<ShowCellPopUpEvent<std::string> const*>(&event)) {
		NewTableCellPopUp<std::string, ShowCellPopUpEvent<std::string>>(PopUpEvent);
		return;
	}
	if (auto const PopUpEvent = dynamic_cast<ShowCellPopUpEvent<int> const*>(&event)) {
		NewTableCellPopUp<int, ShowCellPopUpEvent<int>>(PopUpEvent);
		return;
	}
	if (auto const PopUpEvent = dynamic_cast<ShowCellPopUpEvent<float> const*>(&event)) {
		NewTableCellPopUp<float, ShowCellPopUpEvent<float>>(PopUpEvent);
		return;
	}
	if (auto const PopUpEvent = dynamic_cast<ShowCellPopUpEvent<double> const*>(&event)) {
		NewTableCellPopUp<double, ShowCellPopUpEvent<double>>(PopUpEvent);
		return;
	}
	if (auto const PopUpEvent = dynamic_cast<ShowCellPopUpEvent<Color> const*>(&event)) {
		NewColorCellPopUp(PopUpEvent);
		return;
	}

	// Initial Sound Pop Up
	if (auto const PopUpEvent = dynamic_cast<ShowInitialSoundLevelPopUpEvent const*>(&event)) {
		NewSoundLevelPopUp(PopUpEvent);
		return;
	}

	// Turn Events
	if (auto const PopUpEvent = dynamic_cast<ShowValidatePopUp const*>(&event)) {
		NewValidatePopUp(PopUpEvent);
		return;
	}

	// Close Pop Up
	if (auto const PopUpEvent = dynamic_cast<ClosePopUpEvent const*>(&event)) {
		DeleteLastPopUp(PopUpEvent->GetPop());
		return;
	}
}

void PopUpManager::NewMessagePopUp(ShowMessagePopUpEvent const* event) {
	AddFocusLayer(true);

	m_popUps.push_back(std::make_unique<MessagePopUp>(
		Vector2(0.5f, 0.5f),
		Vector2(0.5f, 0.5f),
		Alignment::MID_MID,
		m_resolution,
		event->GetTitle(),
		const_cast<std::string&>(event->GetSubTitle()),
		AssetType::EXCLAMATION_MARK,
		event->GetCallback()
		)
	);
}
void PopUpManager::NewDeletePlayerPopUp(ShowDeletePlayerPopUpEvent const* event) {
	AddFocusLayer(true);

	m_popUps.push_back(std::make_unique<DeletePlayerPopUp>(
		Vector2(0.5f, 0.5f),
		Vector2(0.5f, 0.5f),
		Alignment::MID_MID,
		m_resolution,
		event->GetTitle(),
		AssetType::QUESTION_MARK,
		event->GetOnClick()
		));
}
void PopUpManager::NewValidatePopUp(ShowValidatePopUp const* event) {
	AddFocusLayer(true);

	m_popUps.push_back(std::make_unique<ValidatePopUp>(
		Vector2(0.5f, 0.5f),
		Vector2(0.5f, 0.5f),
		Alignment::MID_MID,
		m_resolution,
		event->GetTitle(),
		const_cast<std::string&>(event->GetSubTitle()),
		AssetType::QUESTION_MARK,
		event->GetCallback()
		)
	);
}
void PopUpManager::NewColorCellPopUp(ShowCellPopUpEvent<Color> const* event) {
	NewFocusPopUpLayerEvent focusEvent;
	m_appContext->eventManager.InvokeEvent(focusEvent);

	m_popUps.push_back(std::make_unique<ColorCellPopUp>(
		Vector2(0.5f, 0.5f),
		Vector2(0.7f, 0.7f),
		Alignment::MID_MID,
		m_resolution,
		event->GetTitle(),
		AssetType::LOGO,
		event->GetCurrentValue(),
		event->GetOnClick()
		)
	);
}
void PopUpManager::NewSoundLevelPopUp(ShowInitialSoundLevelPopUpEvent const* event) {
	NewFocusPopUpLayerEvent focusEvent;
	m_appContext->eventManager.InvokeEvent(focusEvent);

	m_popUps.push_back(std::make_unique<SoundLevelPopUp>(
		Vector2(0.5f,0.5f),
		Vector2(0.5f,0.5f),
		Alignment::MID_MID,
		m_resolution,
		event->GetTitle(),
		const_cast<std::string&>(event->GetSubTitle())
		)
	);
}

void PopUpManager::DeleteLastPopUp(PopUp* toDelete) {
	if (m_popUps.size() == 0) {
		return;
	}

	if (toDelete == m_popUps.back().get()) {

		DeleteFocusLayer(true);
		m_popUps.pop_back();

		CheckForDeleteRemainingPopUps();
	}
	else {
		m_toDelete.push_back(toDelete);
	}
}
void PopUpManager::CheckForDeleteRemainingPopUps() {
	while (true) {
		if (m_popUps.size() == 0) {
			m_toDelete.clear();
			return;
		}
		if (m_toDelete.size() == 0) {
			return;
		}

		bool found{ false };
		for (auto& p : m_toDelete) {
			if (p == m_popUps.back().get()) {
				found = true;
				DeleteFocusLayer(true);
				m_popUps.pop_back();

				m_toDelete.erase(std::remove(
					m_toDelete.begin(), m_toDelete.end(), p),
					m_toDelete.end());
				break;
			}
		}

		if (!found) {
			return;
		}
	}
}

void PopUpManager::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	if (!IsActivePopUp()) {
		return;
	}

	m_popUps.back()->CheckAndUpdate(mousePosition, appContext);
}
void PopUpManager::Render(AppContext const& appContext) {
	for (auto& p : m_popUps) {
		p->Render(appContext);
	}
}
void PopUpManager::Resize(Vector2 resolution, AppContext const& appContext) {
	m_resolution = resolution;
	for (auto& e : m_popUps) {
		e->Resize(resolution, appContext);
	}
}
