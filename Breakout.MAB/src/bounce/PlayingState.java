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
import org.newdawn.slick.state.transition.EmptyTransition;
import org.newdawn.slick.state.transition.HorizontalSplitTransition;

/**
 * This state is active when the Game is being played. In this state, sound is
 * turned on, the bounce counter begins at 0 and increases until 10 at which
 * point a transition to the Game Over state is initiated. The user can also
 * control the ball using the WAS & D keys.
 * 
 * Transitions From StartUpState
 * 
 * Transitions To GameOverState
 */
class PlayingState extends BasicGameState {
	int lives;
	int ballqueue = 0;
	boolean skip = false;
	boolean shia = false;
	float k;
	Vector v;
	boolean sfx = false;

	@Override
	public void init(GameContainer container, StateBasedGame game) throws SlickException {
	}

	@Override
	public void enter(GameContainer container, StateBasedGame game) throws SlickException {
		lives = 3;
		container.setSoundOn(true);

	}

	@Override
	public void render(GameContainer container, StateBasedGame game, Graphics g) throws SlickException {
		BounceGame bg = (BounceGame) game;
		Input input = container.getInput();
		if (skip == true) {
			bg.brick.clear();
			skip = false;
		}
		for (int i = 0; i < bg.brick.size(); i++) {
			if (bg.brick.get(i).destroyed == true)
				bg.brick.remove(i);
		}
		for (Brick s : bg.brick) {
			s.render(g);
		}
		bg.paddle.render(g);
		while (ballqueue > 0 && bg.ball.size() < 4) {
			ballqueue -= 1;
			bg.ball.add(new Ball(input.getMouseX(), input.getMouseX(), 0, 0, 2));
		}
		for (int i = 0; i < bg.ball.size(); i++) {
			if (bg.ball.get(i).dead == true)
				bg.ball.remove(i);
		}
		for (Ball balls : bg.ball) {
			balls.render(g);
		}

		if (bg.ball3 != null) {
			if (bg.ball3.dead == true)
				bg.ball3 = null;
			else
				bg.ball3.render(g);
		}
		if (bg.ball2 != null)
			bg.ball2.render(g);
		g.drawString("Lives: " + lives, 10, 30);
		g.drawString("Level: " + bg.state, 10, 50);
		for (Bang b : bg.explosions)
			b.render(g);
	}

	@Override
	public void update(GameContainer container, StateBasedGame game, int delta) throws SlickException {
		Collision p = null;
		Input input = container.getInput();
		BounceGame bg = (BounceGame) game;

		if (!(ResourceManager.getSound(BounceGame.CENA_RSC).playing()) && !bg.mainMusic.playing()) {
			bg.mainMusic.resume();
			sfx = false;
		}

		if (!bg.mainMusic.playing() && sfx == false)
			bg.mainMusic.loop();

		if (bg.brick.isEmpty()) {
			if (bg.ball3 != null)
				bg.ball3 = null;
			if (bg.state == 3) {
				((GameOverState) game.getState(BounceGame.GAMEOVERSTATE)).setUserScore(lives);
				game.enterState(BounceGame.GAMEOVERSTATE);
			} else {
				bg.state++;
				lives = 3;
				bg.rebrick();
			}
		}
		if (bg.ball.isEmpty()) {
			lives -= 1;
			ballqueue = 1;
		}
		if (lives <= 0) {
			bg.mainMusic.stop();
			((GameOverState) game.getState(BounceGame.GAMEOVERSTATE)).setUserScore(lives);
			game.enterState(BounceGame.GAMEOVERSTATE);
		}
		container.setMouseGrabbed(true);
		bg.paddle.setPosition(input.getMouseX(), bg.ScreenHeight - 10);
		if (bg.ball2 != null && bg.ball2.free == false)
			bg.ball2.setPosition(input.getMouseX(), bg.ScreenHeight - 10);
		if (input.isMousePressed(Input.MOUSE_LEFT_BUTTON)) {
			for (Ball balls : bg.ball) {
				if (balls.free == false) {
					balls.free = true;
					if (bg.state == 2 || bg.state >= 3)
						balls.setVelocity(new Vector((float) (Math.random() * .7), -.5f));
					else
						balls.setVelocity(new Vector((float) (Math.random() *.05f), -.2f));
				}
			}
			if (bg.ball2 != null) {
				bg.ball2.free = true;
				bg.ball2.setVelocity(new Vector(0f, -2f));
				bg.explosions.add(new Bang(bg.ball2.getX(), bg.ball2.getY()));
			}
		}
		if (input.isKeyPressed(Input.KEY_L)) {
			bg.mainMusic.pause();
			sfx = true;
			ResourceManager.getSound(BounceGame.CENA_RSC).play();
			bg.ball3 = new Ball(bg.ScreenWidth / 2, bg.ScreenHeight / 2 + 50, .1f, .2f, 3);
		}
		if (input.isKeyPressed(Input.KEY_K))
			skip = true;
		if (input.isKeyPressed(Input.KEY_ESCAPE)) {
			bg.mainMusic.stop();
			ballqueue=0;
			bg.rebrick();
			game.enterState(BounceGame.STARTUPSTATE, new EmptyTransition(), new HorizontalSplitTransition());
		}
		// bounce the ball...

		boolean bounced = false;
		for (Ball balls : bg.ball) {
			if (balls.free == false) {
				balls.setPosition(input.getMouseX(), bg.ScreenHeight - 50);
			}
			if ((p = balls.collides(bg.paddle)) != null) {
				v = p.getMinPenetration();
				k = balls.getX() - bg.paddle.getX();
				// System.out.println(k);
				if (v.getY() != 0) {
					balls.setPosition(balls.getX(), balls.getY() - 10);
					balls.bounce(k / 5);
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
			if (balls.getCoarseGrainedMinY() > bg.ScreenHeight) {
				balls.dead = true;
			}
			if (balls.getCoarseGrainedMinY() < 0) {
				balls.setPosition(balls.getX(), balls.getY() + 10);
				balls.bounce(0);
				bounced = true;
			}
			if (bg.ball2 != null && bg.ball2.getCoarseGrainedMaxY() < 0)
				bg.ball2 = null;

			for (Brick s : bg.brick) {
				if ((p = balls.collides(s)) != null) {
					v = p.getMinPenetration();
					if (s.k == 4) {
						if (bg.state == 1 || bg.state == 2 || bg.state >= 3) {
							if (bg.ball2 == null) {
								bg.ball2 = new Ball(input.getMouseX(), input.getMouseY(), 0f, 0f, 1);
							}
						}
						if (bg.state == 0 || bg.state == 2 || bg.state >= 3)
							ballqueue = 1;
						s.destroyed = true;
					}
					if (s.k <= 1)
						s.destroyed = true;
					if (s.k > 1 && s.k != 4)
						s.update();
					if (v.getY() == 1) {
						balls.setPosition(balls.getX(), balls.getY() + 10);
						balls.bounce(0);
						balls.setVelocity(balls.getVelocity().add(new Vector(0, (float) ((bg.state + 1) * .005))));
					} else if (v.getY() == -1) {
						balls.setPosition(balls.getX(), balls.getY() - 10);
						balls.bounce(0);
						balls.setVelocity(balls.getVelocity().add(new Vector(0, (float) ((bg.state + 1) * -.005))));
					} else if (v.getX() == -1) {
						balls.setPosition(balls.getX() - 10, balls.getY());
						balls.bounce(90);
						balls.setVelocity(balls.getVelocity().add(new Vector((float) ((bg.state + 1) * -.005), 0)));
					} else if (v.getX() == 1) {
						balls.setPosition(balls.getX() + 10, balls.getY());
						balls.bounce(90);
						balls.setVelocity(balls.getVelocity().add(new Vector((float) ((bg.state + 1) * .005), 0)));
					}
					// System.out.println(v);
					bounced = true;
					if (bounced) {
						bg.explosions.add(new Bang(balls.getX(), balls.getY()));
					}
					break;

				}
				if (bg.ball2 != null && (p = bg.ball2.collides(s)) != null) {
					s.destroyed = true;
					bg.explosions.add(new Bang(bg.ball2.getX(), bg.ball2.getY(), true));
				}
				if (bg.ball3 != null && (p = bg.ball3.collides(s)) != null) {
					s.destroyed = true;
					bg.explosions.add(new Bang(bg.ball3.getX(), bg.ball3.getY(), true));
				}
			}

			balls.update(delta);
		}
		if (bg.ball2 != null) {
			bg.ball2.update(delta);
		}
		if (bg.ball3 != null) {

			if ((p = bg.ball3.collides(bg.paddle)) != null) {
				v = p.getMinPenetration();
				k = bg.ball3.getX() - bg.paddle.getX();
				// System.out.println(k);
				if (v.getY() != 0) {
					bg.ball3.setPosition(bg.ball3.getX(), bg.ball3.getY() - 10);
					bg.ball3.bounce(k / 5);
				} else if (v.getX() > 0) {
					bg.ball3.setPosition(bg.ball3.getX(), bg.ball3.getY() - 10);
					bg.ball3.bounce(0);
				} else if (v.getX() < 0) {
					bg.ball3.setPosition(bg.ball3.getX(), bg.ball3.getY() - 10);
					bg.ball3.bounce(0);
				}
				bounced = true;
			}
			if (bg.ball3.getCoarseGrainedMaxX() > bg.ScreenWidth) {
				bg.ball3.setPosition(bg.ball3.getX() - 10, bg.ball3.getY());
				bg.ball3.bounce(90);
				bounced = true;
			}
			if (bg.ball3.getCoarseGrainedMinX() < 0) {
				bg.ball3.setPosition(bg.ball3.getX() + 10, bg.ball3.getY());
				bg.ball3.bounce(90);
				bounced = true;
			}
			if (bg.ball3.getCoarseGrainedMinY() > bg.ScreenHeight) {
				bg.ball3.dead = true;
			}
			if (bg.ball3.getCoarseGrainedMinY() < 0) {
				bg.ball3.setPosition(bg.ball3.getX(), bg.ball3.getY() + 10);
				bg.ball3.bounce(0);
				bounced = true;
			}
			bg.ball3.update(delta);
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
		return BounceGame.PLAYINGSTATE;
	}

}