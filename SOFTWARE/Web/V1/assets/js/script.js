//* ACCION MENU RESPONSIVO
const menu = document.querySelector('.menu');
const toggle = document.getElementById('toggle');

toggle.addEventListener('click', function () {
    menu.classList.toggle('show_menu');
});

//* STICKY NAVBAR
const Navbar = document.querySelector('.Navbar');

window.addEventListener('scroll', function () {
    var scroll = window.scrollY;
    if (scroll > 100) {
        Navbar.classList.add('sticky');
    } else {
        Navbar.classList.remove('sticky');
    }
});

//* SPLIDE CONFIGURACIÓN
window.onload = function () {
    // Primer Splide
    new Splide('.MySplide', {
        type: 'loop',
        drag: 'free',
        focus: 'center',
        perPage: 7,
        arrow: false,
        pagination: false,
        autoScroll: {
            speed: 0.5
        },
    }).mount({ AutoScroll: window.splide.Extensions.AutoScroll });

    // Segundo Splide
    new Splide('.Photo_Gallery_Slide', {
        type: 'loop',
        drag: 'free',
        focus: 'center',
        gap: '0.8rem',
        perPage: 5,
        arrow: false,
        pagination: false,
        autoScroll: {
            speed: 0.5
        },
        breakpoints: {
            1200: { perPage: 4 },
            900: { perPage: 3 },
            768: { perPage: 2 },
            500: { perPage: 1 }
        }
    }).mount({ AutoScroll: window.splide.Extensions.AutoScroll });

    // Tercer Splide
    new Splide('.Testimonials_Splide', {
        type: 'loop',
        drag: 'free',
        focus: 'center',
        gap: '2rem',
        perPage: 2,
        arrow: false,
        pagination: false,
        autoScroll: {
            speed: 0.5
        },
        breakpoints: {
            1200: { gap: '1rem' },
            900: { perPage: 1.5 },
            500: { perPage: 1 }
        }
    }).mount({ AutoScroll: window.splide.Extensions.AutoScroll });
};

//* VISIBILIDAD CONTRASEÑA
const togglePassword = document.querySelector('.toggle-password');
const passwordInput = document.getElementById('password');

togglePassword.addEventListener('click', () => {
    const type = passwordInput.getAttribute('type') === 'password' ? 'text' : 'password';
    passwordInput.setAttribute('type', type);
});

