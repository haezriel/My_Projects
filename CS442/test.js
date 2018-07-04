var Vec2 = function(x,y) {
	this.x=x || 0;
	this.y=y || 0;

}

Vec2.prototype.dot=function(other){
	return this.x*other.x+this.y*other.y;
}

Vec2.prototype.magnitude = function(){
	return Math.sqrt(this.dot(this));
}

Vec2.prototype.subtract=function(other){
	return new Vec2(this.x-other.x, this.y-other.y);
}

var line = {
	A : new Vec2(0,0),
	B : new Vec2(10,10),
	length: function(){
		return this.A.subtract(this.B).magnitude();
	}
}

var L = Object.create(line);