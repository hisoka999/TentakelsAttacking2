//
// Purpur Tentakel
// 20.11.2022
//

#include "ValidateGalaxy.h"
#include "GenerelEvents.hpp"
#include "SceneType.h"
#include "AppContext.h"
#include "ClassicButton.h"
#include "GalaxyAndSlider.h"
#include "Text.h"
#include <iostream>

void ValidateGalaxyScene::Initialize() {

	auto text = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.01f),
		GetElementSize(0.4f, 0.07f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_MID,
		0.07f,
		"Validate your galaxy:"
		);
	m_elements.push_back(text);

	auto backBtn = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.1f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"Back",
		SoundType::CLICKED_RELEASE_STD
		);
	backBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::NEW_GAME_PARAMETER));
		});
	m_elements.push_back(backBtn);

	auto reGenerateBtn = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(0.5f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		m_resolution,
		"Regenerate",
		SoundType::CLICKED_RELEASE_STD
		);
	reGenerateBtn->SetOnClick([this]() {
		this->NewGalaxy();
		});
	m_elements.push_back(reGenerateBtn);

	auto nextBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(0.9f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"Next",
		SoundType::ACCEPTED
		);
	nextBtn->SetOnClick([this]() {
			this->StartGame();
		});
	m_elements.push_back(nextBtn);
}
void ValidateGalaxyScene::InitializePlayerLegend() {
	AppContext const& appContext = AppContext::GetInstance();

	auto const players = appContext.playerCollection.GetPlayerData();

	float const width { 0.15f };
	float const height{ 0.03f };
	float const X     { 0.97f };
	float       Y     { 0.5f - (height * players.size() / 2) };

	for (auto const& player : players) {
		auto text = std::make_shared<Text>(
			GetElementPosition(X, Y),
			GetElementSize(width, height),
			Alignment::TOP_RIGHT,
			m_resolution,
			Alignment::TOP_RIGHT,
			height,
			player.name
		);
		text->SetColor(player.color);

		m_elements.push_back(text);

		Y += height;
	}

}
void ValidateGalaxyScene::InitializeGalaxy() {
	AppContext const& appContext{ AppContext::GetInstance() };

	m_galaxy = std::make_shared<GalaxyScene>(
		GetElementPosition(0.05f, 0.465f),
		GetElementSize(0.75f, 0.75f),
		Alignment::MID_LEFT,
		m_resolution
		);
	m_galaxy->SetActive(true, appContext);
	m_elements.push_back(m_galaxy);
}

void ValidateGalaxyScene::NewGalaxy() {
	AppContext const& appContext{ AppContext::GetInstance() };

	m_galaxy->SetActive(false, appContext);
	m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_galaxy), m_elements.end());
	m_galaxy = nullptr;

	GenerateGalaxyEvent const event;
	appContext.eventManager.InvokeEvent(event);

	InitializeGalaxy();
}

void ValidateGalaxyScene::StartGame() const {
	AppContext const& appContext{ AppContext::GetInstance() };
	appContext.eventManager.InvokeEvent(StartGameEvent{ });
	appContext.eventManager.InvokeEvent(SwitchSceneEvent{ SceneType::MAIN });
}

ValidateGalaxyScene::ValidateGalaxyScene(Vector2 resolution)
	: Scene{ {0.0f,0.0f}, {1.0f,1.0f}, Alignment::DEFAULT, resolution } {

	Initialize();
	InitializeGalaxy();
	InitializePlayerLegend();
}
