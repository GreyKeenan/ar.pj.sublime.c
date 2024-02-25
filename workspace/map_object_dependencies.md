
# object/map dependency structure


object
	has:
		struct definition
		initilizers

object-events
	has:
		movement functions, collision checks
		onEnter functions
		onLeave functions
	dependent:
		object

		map
		map-access

object-type-initializers
	has:
		game-object specific type initializers
	dependent:
		object
		object-events
	
map
	has:
		struct definition
	dependent:
		object

map-populate
	has:
		populating map
	dependent:
		map
		map-access

		object
		object-type-initializers

map-access
	has:
		index getting
		index setting
		isInBounds
	dependent:
		map

		object

