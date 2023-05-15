//
// PurpurTentakel
// 08.11.22
//

#pragma once
#include "Planet.h"
#include "TargetPoint.h"
#include "Fleet.h"
#include "GenerelEvents.hpp"
#include "Vec2.hpp"
#include <vector>
#include <memory>

struct AppContext;

/**
 * contains objects witch include planetx, fleets, target points
 * generates itself.
 */
class Galaxy {
private:
	bool m_validGalaxy = true; ///< specifies if the generation in valid and the galaxy is able to use
	std::vector<std::shared_ptr<SpaceObject>> m_objects; ///< contains all space object for updating 
	std::vector<std::shared_ptr<Planet>> m_planets; ///< contains all planets 
	std::vector<std::shared_ptr<Fleet>> m_fleets; ///< contains all fleets
	std::vector<std::shared_ptr<TargetPoint>> m_targetPoints; ///< contains all target points

	Vec2<int> m_size; ///< contains the size of the galaxy

	/**
	 * returns the next free ID for an Space object that is the nearest to 0.
	 */
	[[nodiscard]] unsigned int GetNextID() const;

	// Planet
	/**
	 * coordinates the geration of all planets.
	 */
	void InitialzePlanets(size_t planetCount, std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> neutralPlayer);
	/**
	 * geretes one home planet for every player.
	 * returns the planet count for generating the other planets. 
	 */
	[[nodiscard]] int GenerateHomePlanets(std::vector<std::shared_ptr<Player>> players);
	/**
	 * geretes all other planet until the planet count is reached.
	 */
	void GenerateOtherPlanets(size_t PlanetCount, int currentPlanet, std::shared_ptr<Player> player);
	/**
	 * validates if the new planet has a valid position.
	 * mainly if the distance to every other planet is big enough.
	 * returns a bool.
	 */
	[[nodiscard]] bool IsValidNewPlanet(std::shared_ptr<Planet> newPlanet, AppContext const& appContext) const;

	// Fleet
	/**
	 * validates the data from the UI if the instruction is for a planet.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] bool AddFleetFromPlanet(SendFleedInstructionEvent const* event, std::shared_ptr<Player> currentPlayer);
	/**
	 * validates the data from the UI if the instruction is for a fleet.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] bool AddFleetFromFleet(SendFleedInstructionEvent const* event, std::shared_ptr<Player> currentPlayer);
	/**
	 * validates the data from the UI if the instruction is for a target point.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] bool AddFleetFromTargetPoint(SendFleedInstructionEvent const* event, std::shared_ptr<Player> currentPlayer);

	[[nodiscard]] std::shared_ptr<SpaceObject> GetOrGenerateDestination(unsigned int ID,
		int X, int Y, std::shared_ptr<Player> currentPlayer);

public:
	/**
	 * generates all planets.
	 * IsValid should be called after construction becautse there is no garanty,
	 * that the	generation is valid. 
	 */
	Galaxy(Vec2<int> size, size_t planetCount, std::vector<std::shared_ptr<Player>> players,
		std::shared_ptr<Player> neutralPlayer);
	/**
	 * makes a exact copy of a galaxy
	 */
	Galaxy(Galaxy const&);

	/**
	 * return if the galaxy is valid.
	 * if its not valid I really to not use this galaxy.
	 * this galaxy will not be complete then.
	 * you should generate a new one.
	 */
	[[nodiscard]] bool IsValid() const;

	/**
	 * returns if the provided ID is exsiting in this galaxy.
	 */
	[[nodiscard]] bool IsValidSpaceObjectID(unsigned int ID) const;

	/**
	 * returns the size of the galaxy.
	 */
	[[nodiscard]] Vec2<int> GetSize() const;
	/**
	 * returns the planets of the galaxy.
	 */
	[[nodiscard]] std::vector<std::shared_ptr<Planet>> const GetPlanets() const;
	/**
	 * returns the fleets of the galaxy.
	 */
	[[nodiscard]] std::vector<std::shared_ptr<Fleet>> const GetFleets() const;
	/**
	 * returns a specific planet by ID.
	 */
	[[nodiscard]] std::shared_ptr<Planet> const GetPlanetByID(unsigned int ID) const;

	[[nodiscard]] std::shared_ptr<SpaceObject> const GetSpaceObjectByID(unsigned int ID) const;

	[[nodiscard]] bool AddFleet(SendFleedInstructionEvent const* event, std::shared_ptr<Player> currentPlayer);
};