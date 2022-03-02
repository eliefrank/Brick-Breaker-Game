# Brick-Breaker-Game

Brick Breaker Game - Project in OOP

<h1>General explanation of the game:</h1>
The player controls a small bat at the bottom of the screen which can be used to bounce a ball towards the bricks arranged at the top of the screen.
When the ball hits one of the bricks, it causes the brick in which it hit to break or disappear (depending on the type of brick and its condition) if it is a brick that can be broken.
For each brick that the player manages to break and hide he gets 50 points double the number of the stage.
When all the bricks are gone, the player moves on to the next stage, where new bricks appear.

Disqualification - When the ball leaves the bottom edge of the playing field and there are no balls left (for life three balls).

Also, behind some of the bricks are surprises that allow you to increase or decrease the bat for 10 seconds, add 3 balls,
Equip the player with bullets for 5 seconds, slow or fast movement of the surface for 10 seconds, adding life and bonus points (50,100,250,500).

Rules and restrictions:
<ul>
  <li>The game will have several types of bricks.</li>
  <li>In the game there will be an option for only one player with 3 lives, the game ends when there are 0 lives left or at the end of the stages.</li>
  <li>In each life the player has three balls - in each loss of the ball the player will get a new ball and will be able to continue from the same situation he was in, after three times he loses life and the stage will start again.
  Note: Losing a ball will only count when the player has no bullets bonus.</li>
  <li>The game will have six stages. The difference between the stages is expressed in the difficulty of the bricks and the way in which they are arranged.</li>
  <li>It will not be possible to save the game and continue it another time, however it will be possible to stop the game for a while (pause) and continue later until we have closed the game.</li>
  <li>The object of the game is to complete all the stages and reach the highest score.</li>
  <li>For the activities of the facilitator, there is details in the game menu in the Help.</li>
</ul>

<h1>Other notes:</h1>

Attached is a UML diagram to explain the design.

I used the Box2D library for physics.

Explanation of creating a step (by creating a suitable file):
The file name should be level.N so that N is the step number.
The first row of the file should have the number of rows and columns of the step separated by a space.
In the rest of the rows, depending on the number of columns and rows, either the letters A - J will appear for a brick or space for an empty space.
Note: It is the responsibility of the creator of the stage to take care of the solvable stage.
Lettering:
A - light green brick. Disappears after one break.
B - light blue brick. Disappears after one break.
C - Purple brick. Disappears after two breaks.
D - Orange brick. Disappears after two breaks.
E - Brown brick. Disappears after two breaks.
F - Red brick. Disappears after two breaks.
G - Yellow brick. Disappears after two breaks.
H - Blue brick. Disappears after three breaks.
I - Green brick. Disappears after three breaks.
J - Gray brick. No breakage.    

The record table will show the top 5 and in sixth place will show the last player if he is lower than the top 5 otherwise he was in fifth place.

<h1>Elie Frankenhuis</h1>
<p>Email: eliezerfr@edu.hac.ac.il</p>
<p>Linkedin: <a href="https://www.linkedin.com/in/elie-frankenhuis/" target="_blank">linkedin.com/in/elie-frankenhuis</a></p>

<h1>Compile, build & debug:</h1>
To build this game-project you must have SFML library downloaded on your computer and located in the C directory because that is where the cmake directs the compiler to find it. When you have it you can build it (cmake project building) and run/debug as you wish. SFML can be downloded from: https://www.sfml-dev.org/download.php
