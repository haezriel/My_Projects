process.stdin.setEncoding('utf8');

var Polygon = function (k){
		if (k.length < 3){
			return [];
		}
		length=k.length;
		//console.log(length);
		vertices=k;
		indices=[];
		trianglesarray=[];
		polyarea=0;
		for(var i =0; i<length; i++){
			polyarea=polyarea+0.5*(k[i].x*k[(i+1)%length].y - k[(i+1)%length].x*k[i].y);
		}
		//console.log("Area of Polygon = " + polyarea);
		for (i = 0; i < length; i++){
			indices.push(i);
		}
		//console.log(indices);
		var Ai=0;

		while (indices.length > 3){
			a=0.0;
			n=0;
			for(i=0;i<indices.length;i++){ 
				n1=indices[n];
				if (i-1<0){
					i1=indices[indices.length-1];
				}
				else
					i1=indices[i-1];
				i2=indices[i];
				i3=indices[(i+1)%indices.length];
				//console.log("computing area of "+i1, i2, i3);
				v1=0.5*(k[i1].x*k[i2].y-k[i2].x*k[i1].y);
				v2=0.5*(k[i2].x*k[i3].y-k[i3].x*k[i2].y);
				v3=0.5*(k[i3].x*k[i1].y-k[i1].x*k[i3].y);
				Ai=v1+v2+v3;
				//console.log("area is " + Ai);
				if(Math.abs(Ai)>a && (Ai*polyarea)>0){
					ear=true;
					for(j=0;j<indices.length;j++){
						j1=indices[j];
						if (j1==i1 || j1==i2 || j1==i3)
							null;
						else{
							//console.log("checking " + j1);
							if(earcheck(j1,i1,i2,i3,vertices)==true){
								ear=false;
								break;
							}
						}

						}
					if (ear==true){
						//console.log(i1,i2,i3 + " are an ear!");
						n=i;
						//console.log(n);
						a=Math.abs(Ai);
						}	
					}
				}

			if(n-1<0)
				trianglesarray.push(indices[indices.length-1],indices[n], indices[(n+1)%indices.length]);
			else
				trianglesarray.push(indices[n-1], indices[n], indices[(n+1)%indices.length]);
			//console.log("spliced "+ indices[n]);
			//console.log("n");
			//console.log(indices);
			indices.splice(n,1);
			//console.log(trianglesarray);
			//console.log(indices);

		
		}
		trianglesarray.push(indices[0],indices[1],indices[2]);
		//console.log(k);
		//console.log(trianglesarray);
		//console.log(vertices.verts[1].x);
	}

function earcheck(j1,i1,i2,i3,k) {
	d=0;
	var v=[];
	v.push(i1);
	v.push(i2);
	v.push(i3);
	u={x:0,y:0};
	w={x:0,y:0};
	for(i=0;i<3;i++){
		u.x=k[v[(i+1)%3]].x-k[v[i]].x;
		u.y=k[v[(i+1)%3]].y-k[v[i]].y;
		w.x=k[j1].x-k[v[i]].x;
		w.y=k[j1].y-k[v[i]].y;
		z=u.x*w.y-u.y*w.x;
		if (i==0)
			d=z;
		else if ((z*d)<0){
			//console.log("compared "+i1,i2,i3+" and " +j1+" recieved false.");
			return false;
		}
	}
	//console.log("compared "+i1,i2,i3+" and " +j1+" recieved true.");
	return true;
}

Polygon.prototype.triangulate= function(){
this.verts=vertices;
this.triangles=trianglesarray;
return this;
	
}
var inputChunks = [];

process.stdin.on('data', function(chunk) {
	inputChunks.push(chunk);
});

process.stdin.on('end', function() {
	var inputJSON = inputChunks.join();
	var verts = JSON.parse(inputJSON);
	var poly = new Polygon(verts);
	var triangles = poly.triangulate();
	process.stdout.write(JSON.stringify(triangles,null, 4) + '\n');
});

