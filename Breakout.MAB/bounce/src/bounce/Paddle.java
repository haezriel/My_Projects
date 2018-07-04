package bounce;

import jig.Entity;
import jig.ResourceManager;

class Paddle extends Entity {

	public Paddle(final float x, final float y) {
		super(x, y);
		addImageWithBoundingBox(ResourceManager.getImage(BounceGame.PADDLE_PADDLEIMG_RSC));
	}

	/*
	 * public void setVelocity(final Vector v) { velocity = v; }
	 */

	/*
	 * public Vector getVelocity() { return velocity; }
	 */

	/**
	 * Bounce the ball off a surface. This simple implementation, combined with
	 * the test used when calling this method can cause "issues" in some
	 * situations. Can you see where/when? If so, it should be easy to fix!
	 * 
	 * @param surfaceTangent
	 */
	/*
	 * public void bounce(float surfaceTangent) {
	 * removeImage(ResourceManager.getImage(BounceGame.BALL_BALLIMG_RSC));
	 * addImageWithBoundingBox(ResourceManager
	 * .getImage(BounceGame.BALL_BROKENIMG_RSC)); countdown = 500; //velocity =
	 * velocity.bounce(surfaceTangent); }
	 */

	/**
	 * Update the Ball based on how much time has passed...
	 * 
	 * @param delta
	 *            the number of milliseconds since the last update
	 */
	public void update(final int X, final int MaxX) {

	}
}