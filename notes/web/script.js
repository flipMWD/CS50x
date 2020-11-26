// Paragraph
function blink() {
	let pg = document.querySelector('p');
	if (pg.style.visibility === 'hidden') {
		pg.style.visibility = 'visible';
	} else {
		pg.style.visibility = 'hidden';
	}
}
window.setInterval(blink, 1000);

// Geolocation
navigator.geolocation.getCurrentPosition(function(position) {
	let pos = position.coords.latitude + ', ' + position.coords.longitude;
	document.querySelector('#pos').innerHTML = pos;
});
