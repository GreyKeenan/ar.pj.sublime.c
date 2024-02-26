
# Todo


collision

	Probably need to split player back out into its own array to store hasMoved property
	Game_Object.collides can just be onPush, dont need the value

	would be easier and neater if make empty tile a static obj instead of NULL
		although, need a check for edge of map anyways, so maybe fine to incorporate NULL into that check?

rendering scaling

input support for non-alhpabetic chars

error standardization

... also, yaknow, a ton of other stuff like most of the game 



# reworking mechanics

If not tired of this by the time I have the original game remade, here are some ideas for future stuff to add and do

push strength is dependent on num of slimes in a row / can push 2 blocks if have 2 slimes lined up
	Should it decrease if slimes are separated by blocks? probably

slimes become conjoined when near each other
	visual or mechanical?
	maybe way to invoke it and force them to stay conjoined?

slimes can be squished btwn blocks, sticking the block in place

box placed on top of falling ground at map creation so it can never be pushed but can brace other box / for level design
