//
// PurpurTentakel
// 10.08.22
//

#include "Player.h"

Player::Player(unsigned int ID, PlayerType playerType)
	: m_ID{ ID }, m_playerType{ playerType } { }

bool Player::IsHumanPlayer() const {
	return m_playerType == PlayerType::HUMAN;
}

unsigned int Player::GetID() const {
	return m_ID;
}

bool operator==(Player const& lhs, Player const& rhs) {
	return lhs.m_ID == rhs.m_ID;
}
