//
// Purpur Tentakel
// 19.09.2022
//

#include "MainMenu.h"
#include "AppContext.h"
#include "UIManager.h"
#include "ClassicButton.h"
#include "GalaxyAndSlider.h"
#include "Title.h"
#include "Text.h"
#include <memory>

void MainMenu::Initialize(Vector2 resolution, AppContext& appContext) {
	float btnPosX = 0.25f;
	float btnPosY = 0.3f;
	float btnSizX = 0.2f;
	float btnSizY = 0.1f;
	int focusID;

	auto newGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"New Game",
		SoundType::ACCEPTED
		);
	newGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::NEW_GAME_PLAYER)
			);
		});
	m_elements.push_back(newGameBtn);

	btnPosY += 0.15f;
	++focusID;

	auto loadGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"Load Game",
		SoundType::ACCEPTED
		);
	loadGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::TEST)
			);
		}
	);
	loadGameBtn->SetEnabled(false);
	m_elements.push_back(loadGameBtn);

	btnPosY += 0.15f;
	++focusID;

	auto settingsBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"Settings",
		SoundType::CLICKED_RELEASE_STD
		);
	settingsBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::SETTINGS)
			);
		}
	);
	m_elements.push_back(settingsBtn);

	btnPosY += 0.15f;
	++focusID;

	auto creditsBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"Credits",
		SoundType::CLICKED_RELEASE_STD
		);
	creditsBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::CREDITS)
		);
		}
	);
	m_elements.push_back(creditsBtn);

	btnPosY += 0.15f;
	++focusID;

	auto quitBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"Quit",
		SoundType::ACCEPTED
		);
	quitBtn->SetOnClick([]() {AppContext::GetInstance().eventManager.InvokeEvent(CloseWindowEvent());});
	m_elements.push_back(quitBtn);

	auto galaxy = std::make_shared<GalaxyScene>(
		GetElementPosition(0.95f, 0.95f),
		GetElementSize(0.7f, 0.7f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		true
		);
	galaxy->SetActive(true, appContext);
	galaxy->SetIsScaling(false);
	galaxy->SetIsEnabled(false);
	m_elements.push_back(galaxy);

	auto title = std::make_shared<Title>(
		GetElementPosition(0.625f, 0.025f),
		GetElementSize(0.7f, 0.2f),
		Alignment::TOP_MID,
		resolution,
		false,
		appContext
		);
	m_elements.push_back(title);

	auto versionAndCopyRight = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.98f),
		GetElementSize(0.1f, 0.1f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		Alignment::BOTTOM_RIGHT,
		0.02f,
		appContext.constants.global.version + '\n' 
			+ appContext.constants.global.copyRight
		);
	m_elements.push_back(versionAndCopyRight);
}

MainMenu::MainMenu(Vector2 resolution)
	: Scene(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Alignment::DEFAULT, resolution) {

	AppContext& appContext = AppContext::GetInstance();
	Initialize(resolution, appContext);
}
