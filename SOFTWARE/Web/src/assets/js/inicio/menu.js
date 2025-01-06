// menu.js
let bars = document.querySelector('.bars');
let close = document.querySelector('.close');
let menu = document.querySelector('.full_menu');

bars.addEventListener('click', () => {
    menu.classList.toggle('show_menu');
});
close.addEventListener('click', () => {
    menu.classList.toggle('show_menu');
});