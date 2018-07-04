package bounce;

import java.util.ArrayList;
import jig.Entity;
import jig.ResourceManager;

import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Music;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.state.StateBasedGame;

/**
 * A Simple Game of Bounce.
 * 
 * The game has three states: StartUp, Playing, and GameOver, the game
 * progresses through these states based on the user's input and the events that
 * occur. Each state is modestly different in terms of what is displayed and
 * what input is accepted.
 * 
 * In the playing state, our game displays a moving rectangular "ball" that
 * bounces off the sides of the game container. The ball can be controlled by
 * input from the user.
 * 
 * When the ball bounces, it appears broken for a short time afterwards and an
 * explosion animation is played at the impact site to add a bit of eye-candy
 * additionally, we play a short explosion sound effect when the game is
 * actively being played.
 * 
 * Our game also tracks the number of bounces and syncs the game update loop
 * with the monitor's refresh rate.
 * 
 * Graphics resources courtesy of qubodup:
 * http://opengameart.org/content/bomb-explosion-animation
 * 
 * Sound resources courtesy of DJ Chronos:
 * http://www.freesound.org/people/DJ%20Chronos/sounds/123236/
 * 
 * 
 * @author wallaces
 * 
 */
public class BounceGame extends StateBasedGame {

	public static final int STARTUPSTATE = 0;
	public static final int PLAYINGSTATE = 1;
	public static final int GAMEOVERSTATE = 2;

	public static final String BALL_BALLIMG_RSC = "bounce/resource/ball.png";
	public static final String BALL_BROKENIMG_RSC = "bounce/resource/brokenball.png";
	public static final String GAMEOVER_BANNER_RSC = "bounce/resource/gameover.png";
	public static final String STARTUP_BANNER_RSC = "bounce/resource/PressSpace.png";
	public static final String BANG_EXPLOSIONIMG_RSC = "bounce/resource/explosion.png";
	public static final String BANG_EXPLOSIONSND_RSC = "bounce/resource/explosion.wav";
	public static final String PADDLE_PADDLEIMG_RSC = "bounce/resource/paddle.png";
	public static final String BRICK1_BRICK1IMG_RSC = "bounce/resource/brick1.png";
	public static final String BRICK2_BRICK2IMG_RSC = "bounce/resource/brick2.png";
	public static final String BRICK3_BRICK3IMG_RSC = "bounce/resource/brick3.png";
	public static final String VICTORY_BANNER_RSC = "bounce/resource/victory.png";
	public static final String BRICK4_BRICK4IMG_RSC = "bounce/resource/brick4.png";
	public static final String BRICK4_BRICK42IMG_RSC = "bounce/resource/brick4-2.png";
	public static final String BALL_BALL3IMG_RSC = "bounce/resource/ball3.png";
	public static final String BALL_BALL2IMG_RSC = "bounce/resource/ball2.png";
	public static final String CENA_RSC = "bounce/resource/cena.wav";
	public final int ScreenWidth;
	public final int ScreenHeight;
	public int state;
	ArrayList<Brick> brick;
	ArrayList<Ball> ball;
	Ball ball2 = null;
	Ball ball3 = null;
	ArrayList<Bang> explosions;
	Paddle paddle;
	Music mainMusic;

	/**
	 * Create the BounceGame frame, saving the width and height for later use.
	 * 
	 * @param title
	 *            the window's title
	 * @param width
	 *            the window's width
	 * @param height
	 *            the window's height
	 */
	public BounceGame(String title, int width, int height) {
		super(title);
		try {
			mainMusic = new Music("bounce/resource/hey.wav");
		} catch (SlickException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ScreenHeight = height;
		ScreenWidth = width;
		state = 0;
		Entity.setCoarseGrainedCollisionBoundary(Entity.AABB);
		explosions = new ArrayList<Bang>(50);
		brick = new ArrayList<Brick>(200);
		ball = new ArrayList<Ball>(20);
	}

	@Override
	public void initStatesList(GameContainer container) throws SlickException {
		addState(new StartUpState());
		addState(new GameOverState());
		addState(new PlayingState());

		// the sound resource takes a particularly long time to load,
		// we preload it here to (1) reduce latency when we first play it
		// and (2) because loading it will load the audio libraries and
		// unless that is done now, we can't *disable* sound as we
		// attempt to do in the startUp() method.
		ResourceManager.loadSound(BANG_EXPLOSIONSND_RSC);
		ResourceManager.loadSound(CENA_RSC);
		// preload all the resources to avoid warnings & minimize latency...
		ResourceManager.loadImage(PADDLE_PADDLEIMG_RSC);
		ResourceManager.loadImage(BALL_BALLIMG_RSC);
		ResourceManager.loadImage(BALL_BROKENIMG_RSC);
		ResourceManager.loadImage(GAMEOVER_BANNER_RSC);
		ResourceManager.loadImage(STARTUP_BANNER_RSC);
		ResourceManager.loadImage(BANG_EXPLOSIONIMG_RSC);
		ResourceManager.loadImage(BRICK1_BRICK1IMG_RSC);
		ResourceManager.loadImage(BRICK2_BRICK2IMG_RSC);
		ResourceManager.loadImage(BRICK3_BRICK3IMG_RSC);
		ResourceManager.loadImage(VICTORY_BANNER_RSC);
		ResourceManager.loadImage(BRICK4_BRICK4IMG_RSC);
		ResourceManager.loadImage(BRICK4_BRICK42IMG_RSC);
		ResourceManager.loadImage(BALL_BALL3IMG_RSC);
		ResourceManager.loadImage(BALL_BALL2IMG_RSC);
		int k = 0;
		while (k < ScreenHeight / 2) {
			k += 40;
			for (int i = 1; i < ScreenWidth / 80 + 1; i++)
				brick.add(new Brick(i * 80 - 40, k - 10, state));
		}
		paddle = new Paddle(ScreenWidth / 2, ScreenHeight - 12);
		ball.add(new Ball(ScreenWidth / 2, ScreenHeight / 2 + 50, .1f, .2f, 0));
	}

	public void rebrick() {
		ball.clear();
		brick.clear();
		int k = 0;
		while (k < ScreenHeight / 2) {
			k += 40;
			for (int i = 1; i < ScreenWidth / 80 + 1; i++)
				brick.add(new Brick(i * 80 - 40, k - 10, state));
		}
		ball.add(new Ball(ScreenWidth / 2, ScreenHeight / 2 + 50, 0f, 0f, 2));

	}

	public static void main(String[] args) {
		AppGameContainer app;
		try {
			app = new AppGameContainer(new BounceGame("Breakout!", 1300, 700));
			app.setDisplayMode(1300, 700, false);
			app.setVSync(true);
			app.start();
		} catch (SlickException e) {
			e.printStackTrace();
		}

	}

}
