package bounce;

import jig.Entity;
import jig.ResourceManager;
import jig.Vector;

/**
 * The Ball class is an Entity that has a velocity (since it's moving). When the
 * Ball bounces off a surface, it temporarily displays a image with cracks for a
 * nice visual effect.
 * 
 */
class Ball extends Entity {
	private Vector velocity;

	boolean free = true;
	boolean dead = false;

	public Ball(final float x, final float y, final float vx, final float vy, int flag) {
		super(x, y);
		if (flag == 3) {
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BALL_BALL3IMG_RSC));
		}
		switch (flag) {
		case 0:
			velocity = new Vector(vx, vy);
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BALL_BALLIMG_RSC));
			break;
		case 1:
			velocity = new Vector(0, 0);
			free = false;
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BALL_BALL2IMG_RSC));
			break;
		case 2:
			velocity = new Vector(0, 0);
			free = false;
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BALL_BALLIMG_RSC));
			break;
		case 3:
			velocity = new Vector(vx, vy);
			break;
		default:
			velocity = new Vector(0, 0);
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BALL_BALLIMG_RSC));
			free = false;
			break;
		}
		velocity.clampY(.02f, 2f);
		velocity.clampX(0f, 2f);
	}

	public void setVelocity(final Vector v) {
		velocity = v;
	}

	public Vector getVelocity() {
		return velocity;
	}

	/**
	 * Bounce the ball off a surface. This simple implementation, combined with
	 * the test used when calling this method can cause "issues" in some
	 * situations. Can you see where/when? If so, it should be easy to fix!
	 * 
	 * @param surfaceTangent
	 */
	public void bounce(float surfaceTangent) {
		velocity = velocity.bounce(surfaceTangent);
	}

	/**
	 * Update the Ball based on how much time has passed...
	 * 
	 * @param delta
	 *            the number of milliseconds since the last update
	 */
	public void update(final int delta) {
		translate(velocity.scale(delta));
	}

}
