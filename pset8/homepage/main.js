function sendEmail() {
	alert('Email Sent!');
}

let dark_theme = true;
let body = document.querySelector('body');
let nav = document.querySelector('nav');

document.querySelector('#theme').onclick = function() {
	if (dark_theme) {
		body.style.backgroundColor = '#e2e2e2';
		nav.style.backgroundColor = '#c1c1c1';
		dark_theme = false;
	} else {
		body.style.backgroundColor = '#37474f';
		nav.style.backgroundColor = '#263238';
		dark_theme = true;
	}
}
