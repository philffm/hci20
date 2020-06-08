
var rotationSpeed = 0.002;
var spinningKebab = document.getElementById('spinningKebab');

function spin(){
	spinningKebab.object3D.rotation.y += rotationSpeed;
	//console.log(myOtherBox.object3D.rotation);
}
setInterval(spin, 10);


spinningKebab.addEventListener('mouseenter', function(){
	rotationSpeed = 0.05;
	console.log('entered');
});

spinningKebab.addEventListener('mouseleave', function(){
	rotationSpeed = 0.001;
	console.log('left');
});



