package bounce;

import java.util.Iterator;

import jig.Collision;
import jig.ResourceManager;
import jig.Vector;

import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.state.BasicGameState;
import org.newdawn.slick.state.StateBasedGame;

/**
 * This state is active prior to the Game starting. In this state, sound is
 * turned off, and the bounce counter shows '?'. The user can only interact with
 * the game by pressing the SPACE key which transitions to the Playing State.
 * Otherwise, all game objects are rendered and updated normally.
 * 
 * Transitions From (Initialization), GameOverState
 * 
 * Transitions To PlayingState
 */
class StartUpState extends BasicGameState {

	@Override
	public void init(GameContainer container, StateBasedGame game) throws SlickException {
	}

	@Override
	public void enter(GameContainer container, StateBasedGame game) {
		container.setSoundOn(false);
	}

	@Override
	public void render(GameContainer container, StateBasedGame game, Graphics g) throws SlickException {
		BounceGame bg = (BounceGame) game;
		for (Brick s : bg.brick) {
			s.render(g);
		}
		bg.paddle.render(g);
		for (Ball balls : bg.ball)
			balls.render(g);
		g.drawString("Lives: ?", 10, 30);
		g.drawString("Controls:", bg.ScreenWidth / 2 - 250, bg.ScreenHeight / 2 + 40);
		g.drawString("Press Esc While Playing to Exit to Start Screen.", bg.ScreenWidth / 2 - 250,
				bg.ScreenHeight / 2 + 60);
		g.drawString("Press K While Playing To Skip a Level.", bg.ScreenWidth / 2 - 250, bg.ScreenHeight / 2 + 80);
		g.drawString("When You Gain Bonuses, Left-Click the Mouse to Use Them.:", bg.ScreenWidth / 2 - 250,
				bg.ScreenHeight / 2 + 100);
		g.drawString("There is An Easter Egg Key Too :D (I guess you can just check the code...)",
				bg.ScreenWidth / 2 - 250, bg.ScreenHeight / 2 + 120);
		for (Bang b : bg.explosions)
			b.render(g);
		g.drawImage(ResourceManager.getImage(BounceGame.STARTUP_BANNER_RSC), bg.ScreenWidth / 2 - 187,
				bg.ScreenHeight / 2 - 30);
	}

	@Override
	public void update(GameContainer container, StateBasedGame game, int delta) throws SlickException {
		Collision p = null;
		Input input = container.getInput();
		BounceGame bg = (BounceGame) game;
		Vector v;
		if (input.isKeyDown(Input.KEY_SPACE))
			bg.enterState(BounceGame.PLAYINGSTATE);
		bg.state = 0;
		bg.paddle.setPosition(input.getMouseX(), bg.ScreenHeight - 10);
		if (input.isMousePressed(Input.MOUSE_LEFT_BUTTON)) {
			for (Ball balls : bg.ball)
				if (balls.free == false) {
					balls.free = true;
					balls.setVelocity(new Vector(.005f, -.2f));
				}
		}
		container.setMouseGrabbed(false);
		// bounce the ball...

		boolean bounced = false;
		for (Ball balls : bg.ball) {
			if (balls.free == false) {
				balls.setPosition(input.getMouseX(), bg.ScreenHeight - 50);
			}
			if ((p = balls.collides(bg.paddle)) != null) {
				v = p.getMinPenetration();
				// System.out.println(k);
				if (v.getY() != 0) {
					balls.setPosition(balls.getX(), balls.getY() - 10);
					balls.bounce(0);
				} else if (v.getX() > 0) {
					balls.setPosition(balls.getX(), balls.getY() - 10);
					balls.bounce(0);
				} else if (v.getX() < 0) {
					balls.setPosition(balls.getX(), balls.getY() - 10);
					balls.bounce(0);
				}
				bounced = true;
			}
			if (balls.getCoarseGrainedMaxX() > bg.ScreenWidth) {
				balls.setPosition(balls.getX() - 10, balls.getY());
				balls.bounce(90);
				bounced = true;
			}
			if (balls.getCoarseGrainedMinX() < 0) {
				balls.setPosition(balls.getX() + 10, balls.getY());
				balls.bounce(90);
				bounced = true;
			}
			if (balls.getCoarseGrainedMaxY() > bg.ScreenHeight) {
				balls.setPosition(balls.getX(), balls.getY() - 10);
				balls.bounce(0);
				bounced = true;
			}
			if (balls.getCoarseGrainedMinY() < 0) {
				balls.setPosition(balls.getX(), balls.getY() + 10);
				balls.bounce(0);
				bounced = true;
			}

			for (Brick s : bg.brick) {
				if ((p = balls.collides(s)) != null) {
					v = p.getMinPenetration();
					if (v.getY() == 1) {
						balls.setPosition(balls.getX(), balls.getY() + 10);
						balls.bounce(0);
					} else if (v.getY() == -1) {
						balls.setPosition(balls.getX(), balls.getY() - 10);
						balls.bounce(0);
					} else if (v.getX() == -1) {
						balls.setPosition(balls.getX() - 10, balls.getY());
						balls.bounce(90);
					} else if (v.getX() == 1) {
						balls.setPosition(balls.getX() + 10, balls.getY());
						balls.bounce(90);
					}
					// System.out.println(v);
					bounced = true;
					break;
				}

			}
			if (bounced) {
				bg.explosions.add(new Bang(balls.getX(), balls.getY()));
			}

			balls.update(delta);

		}
		// check if there are any finished explosions, if so remove them
		for (Iterator<Bang> i = bg.explosions.iterator(); i.hasNext();) {
			if (!i.next().isActive()) {
				i.remove();
			}
		}

	}

	@Override
	public int getID() {
		return BounceGame.STARTUPSTATE;
	}

}