package bounce;

import java.util.Iterator;

import jig.ResourceManager;

import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.state.BasicGameState;
import org.newdawn.slick.state.StateBasedGame;
import org.newdawn.slick.state.transition.EmptyTransition;
import org.newdawn.slick.state.transition.HorizontalSplitTransition;

/**
 * This state is active when the Game is over. In this state, the ball is
 * neither drawn nor updated; and a gameover banner is displayed. A timer
 * automatically transitions back to the StartUp State.
 * 
 * Transitions From PlayingState
 * 
 * Transitions To StartUpState
 */
class GameOverState extends BasicGameState {

	private int timer;
	private int lives; // the user's score, to be displayed, but not updated.

	@Override
	public void init(GameContainer container, StateBasedGame game) throws SlickException {
	}

	@Override
	public void enter(GameContainer container, StateBasedGame game) {
		timer = 4000;
	}

	public void setUserScore(int bounces) {
		lives = bounces;
	}

	@Override
	public void render(GameContainer container, StateBasedGame game, Graphics g) throws SlickException {

		BounceGame bg = (BounceGame) game;
		bg.rebrick();
		g.drawString("Lives: " + lives, 10, 30);
		for (Bang b : bg.explosions)
			b.render(g);
		if (lives > 0)
			g.drawImage(ResourceManager.getImage(BounceGame.VICTORY_BANNER_RSC), bg.ScreenWidth / 2 - 187,
					bg.ScreenHeight / 2 - 30);
		else
			g.drawImage(ResourceManager.getImage(BounceGame.GAMEOVER_BANNER_RSC), bg.ScreenWidth / 2 - 187,
					bg.ScreenHeight / 2 - 30);

	}

	@Override
	public void update(GameContainer container, StateBasedGame game, int delta) throws SlickException {
		container.setMouseGrabbed(false);
		timer -= delta;
		if (timer <= 0)
			game.enterState(BounceGame.STARTUPSTATE, new EmptyTransition(), new HorizontalSplitTransition());

		// check if there are any finished explosions, if so remove them
		for (Iterator<Bang> i = ((BounceGame) game).explosions.iterator(); i.hasNext();) {
			if (!i.next().isActive()) {
				i.remove();
			}
		}

	}

	@Override
	public int getID() {
		return BounceGame.GAMEOVERSTATE;
	}

}