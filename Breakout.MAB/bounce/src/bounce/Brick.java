package bounce;

import jig.Entity;
import jig.ResourceManager;

class Brick extends Entity {
	int k = 0;
	boolean destroyed = false;
	// private Vector velocity;

	public Brick(final float x, final float y, final int state) {
		super(x, y);
		k = (int) (Math.random() * 4.5);
		// System.out.println(k);
		switch (k) {
		case 0:
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK1_BRICK1IMG_RSC));
			break;
		case 1:
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK1_BRICK1IMG_RSC));
			break;
		case 2:
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK2_BRICK2IMG_RSC));
			break;
		case 3:
			if (state >= 2) {
				addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK4_BRICK4IMG_RSC));
			} else {
				addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK2_BRICK2IMG_RSC));
				k = 2;
			}
			break;
		case 4:
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK3_BRICK3IMG_RSC));
			break;
		case 5:
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK4_BRICK42IMG_RSC));
			break;
		}
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
	public void update() {
		switch (k) {
		case 2:
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK1_BRICK1IMG_RSC));
			k = 1;
			break;
		case 3:
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK4_BRICK42IMG_RSC));
			k = 5;
			break;
		case 5:
			addImageWithBoundingBox(ResourceManager.getImage(BounceGame.BRICK2_BRICK2IMG_RSC));
			k = 2;
			break;
		}

	}
}