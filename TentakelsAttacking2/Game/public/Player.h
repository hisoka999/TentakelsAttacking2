//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "PlayerType.hpp"

/**
 * player class.
 * contains id and type.
 */
class Player final {
private:
	unsigned int m_ID; ///< contains the unique player id
	PlayerType m_playerType; ///< contains the player type like HUMAN
public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	Player(unsigned int ID, PlayerType playerType);

	/**
	 * returns if it is an human player.
	 */
	[[nodiscard]] bool IsHumanPlayer() const;

	/**
	 * returns the unique player id.
	 */
	[[nodiscard]] unsigned int GetID() const;

	/**
	 * compares 2 players by their id.
	 */
	friend bool operator== (Player const& lhs, Player const& rhs);
};
